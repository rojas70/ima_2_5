// SESManager.cpp: implementation of the SESManager class for ISAC.
//
// Derived from KAH's code by Katherine Achim for ISAC-- Nov. 05--
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SESManager.h"
#include <afx.h>
#include "mysql++"
#include "custom.hh"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// for nodes table
//sql_create_12 (tblNodesB, 1, 11, int, ID, int, i_index, int, j_index, double, phi, double, theta, int, N1, int, N2, int, N3, int, N4, int, N5, int, N6, int, Type)

// for attention table
//sql_create_5 (tblAttentionB, 1, 5, int, ID, double, salience, double, priority, double, inhibition, double, habituation)

//create the tables I need here:
//tbl activation  //attention points still at node of origin
//tbl attention	  //remapped attentional locations on SES

/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// set up database connection and frequency used in SES
SESManager::SESManager()
{
	m_connSES = new Connection("dbses_kat", "localhost", "user");
	m_iTessFreq = 14;
	dbName = "dbses_kat";
	Server = "localhost";
	Username = "user";
//	m_Decay = new CDecayManager();

}

// delete database connection
SESManager::~SESManager()
{
	delete m_connSES;
//	delete m_Decay;
}

//Constructor--lets you specify the Database you want to connect to
void SESManager::Connect(char* dbNameTemp, char* ServerTemp, char* UsernameTemp)
{
	
	dbName = dbNameTemp;
	Server = ServerTemp;
	Username = UsernameTemp;
	m_connSES = new Connection(dbName, Server, Username);
	m_iTessFreq = 14;
}

//Kills the db connection
void SESManager::Disconnect()
{
	delete m_connSES;
}



/*	CreateNewSES makes the SES; m_iTessFreq in the constructor defines the
		frequency at which the geodesic sphere is tessellated
	The indexing is confusing but in the end, you will have a phi,theta angle
		pair that matches a i,j index pair and an ID index. This is very 
		helpful when getting neighbors etc. 
	This routine creates tblNodes that holds phi, theta, i_index, j_index, 
		ID, and IDs of the node's immediate neighbors (either 5 or 6, 
		depending on where the node lies).
	Don't worry about anything to do w/ tblAttention - that is for Kim's
		research. 
*/
/************************************************************************
*************************************************************************
*		
*		THE FOLLOWING ARE ROUTINES THAT SUPPORT SES FUNCTIONALITY
*
*************************************************************************
************************************************************************/

//Post method for ISAC.  Posts a full image at node location.  saves filename information of img
int SESManager::PostImg(char *Name, char *Type, char *Identifier, double Pan, double Tilt, char *Image_Name)
{
	// MySQL query object
	Query qySES = m_connSES->query();
	
	CString	cstrSQL;
	char*	cpSQL;
	char	cpID[5];
	char	pan[6];
	char	tilt[6];

	int*	ipIndices;			//i,j indices
	int		iIndexID = 0;		//nodeID
	int		temp;
	int		iSESRecs = 0;

	double	phi,theta;


	//find closest node
	
	//Convert from pan/tilt to phi/theta
	theta = 90 - Tilt;

	if((Pan >= 0)&&(Pan <= 180))
		phi = Pan;
	else
		phi = Pan + 360;
	
	//cout << "Phi: " << phi << " Theta: " << theta << endl;

	//Find nodeID from phi/theta
	// all angles will map to a pair of indices or an index ID
	ipIndices = AnglesToIndices(phi, theta);
	temp = ipIndices[0];
	temp = ipIndices[1];
	iIndexID = ipIndices[2];
	
	//cout << "nodeID " << iIndexID << endl;

	// convert nodeID to char* for use in SQL statement
	_itoa(iIndexID, cpID, 10);
	sprintf(pan, "%G", Pan);
	sprintf(tilt, "%G", Tilt);

	//cout << cpID << " " << pan << " " << tilt << endl;

	//post at that node
	cstrSQL.Insert(0, "')");
	cstrSQL.Insert(0, Image_Name);
	cstrSQL.Insert(0, "', '");
	cstrSQL.Insert(0, tilt);
	cstrSQL.Insert(0, "', '");
	cstrSQL.Insert(0, pan);
	cstrSQL.Insert(0, ", '");
	cstrSQL.Insert(0, " NOW()");
	cstrSQL.Insert(0, "', ");
	cstrSQL.Insert(0, Identifier);
	cstrSQL.Insert(0, "', '");
	cstrSQL.Insert(0, Type);
	cstrSQL.Insert(0, "', '");
	cstrSQL.Insert(0, Name);
	cstrSQL.Insert(0, ", '");
	cstrSQL.Insert(0, cpID);
	cstrSQL.Insert(0, "INSERT INTO tblSES (ID, name, type, identifier, timestamp, pan, tilt, image_name) VALUES (");
	cpSQL = cstrSQL.GetBuffer(1);
	qySES.exec(cpSQL);

//	TRACE0("Inserted new record\n");
	cstrSQL.ReleaseBuffer();
	cstrSQL.Empty();
	cpSQL = NULL;
	qySES.reset();

return iIndexID;
	
}

//ReturnNodeList  Returns a list of all nodes between a pan range and a tilt range
CImg<double> SESManager::ReturnNodeList(double dPanLo, double dPanHi, double dTiltLo, double dTiltHi)
{
	// MySQL query object
	Query				qySES = m_connSES->query();
	Result				resSES;
	Result::iterator	R;
	Row					rwSES;
	char*				cpTemp = new char[255];
	char*				cpValue = new char[15];
	
	double				dPhi1, dPhi2, dTheta1, dTheta2, dTemp;
	CImg<double>*		ciNodeList;				
	int					i;

	//Convert from pan/tilt to phi/theta
	dTheta1 = 90 - dTiltLo;
	dTheta2 = 90 - dTiltHi;

	//adjust if 2 is smaller than 1:
	if(dTheta2 < dTheta1)
	{
		dTemp = dTheta1;
		dTheta1 = dTheta2;
		dTheta2 = dTemp;
	}

	if((dPanLo >= 0)&&(dPanLo <= 180))
		dPhi1 = dPanLo;
	else
		dPhi1 = dPanLo + 360;

	if((dPanHi >= 0)&&(dPanHi <= 180))
		dPhi2 = dPanHi;
	else
		dPhi2 = dPanHi + 360;



	//Build Query
	strcpy(cpTemp, "Select phi, theta from tblNodes where ( phi >= ");
	sprintf(cpValue, "%G",dPhi1);
	strcat(cpTemp, cpValue);
	if(dPanLo < 0 && dPanHi >= 0)
		strcat(cpTemp, " or phi <= ");
	else
		strcat(cpTemp, " and phi <= ");
	sprintf(cpValue, "%G",dPhi2);
	strcat(cpTemp, cpValue);
	strcat(cpTemp, " ) and theta >= ");
	sprintf(cpValue, "%G",dTheta1);
	strcat(cpTemp, cpValue);
	strcat(cpTemp, " and theta <= ");
	sprintf(cpValue, "%G",dTheta2);
	strcat(cpTemp, cpValue);
	strcat(cpTemp, " ;");


	cout << cpTemp <<endl;		//for testing

	//Execute Query	
	//qySES.exec(cpTemp);
	qySES << cpTemp;
	resSES = qySES.store();
	qySES.reset();

	
	//Retrieve Results
	rwSES = *resSES.begin();
	if(resSES.size() < 1)
	{
		//return empty Cimg
		ciNodeList = new CImg<double>(1,1);
	}
	else
	{
		//Initialize CImg structure
		ciNodeList = new CImg<double>(resSES.size(),2);

		//Go through results and convert to pan/tilt and put in CImg array
		R = resSES.begin();
		for (i = 0; i < resSES.size(); i++)
	    {
		 	rwSES = *R;
			*ciNodeList->ptr(i,0) = rwSES[0];
			*ciNodeList->ptr(i,1) = rwSES[1];
		
			//convert from phi/theta to pan/tilt
			if(*ciNodeList->ptr(i,0) > 180)
			{
				dTemp = *ciNodeList->ptr(i,0);
				*ciNodeList->ptr(i,0) = dTemp -360;
			}

			dTemp = *ciNodeList->ptr(i,1);
			*ciNodeList->ptr(i,1) = 90 - dTemp;
			R++;
			
		}
	}
CImg<double> ciNodeListTemp = *ciNodeList;
delete ciNodeList;

return ciNodeListTemp;
}

//RecordAttnPts takes in the results of FGate processing and posts the top N points in
//tblactivation at the appropriate nodeID. It also remaps the points to the node closest to
//them in space and posts these results in tblattention 
bool SESManager::PostAttnPts(CImg<double>* salientPts, int nodeID)
{
	Query qyACT =		m_connSES->query();
	Query qyATTN =		m_connSES->query();
	Query qySES =		m_connSES->query();
	Result				resSES;
	Row					rwSES;

	int i, difR, difC, newID; 
	double phi, theta, pan, tilt, newPan, newTilt;
	char* cpTemp = new char[255];
	char* cpID = new char[5];
	char* cpNewID = new char[5];
	char* cpActiv = new char[10];
	char* cpRow = new char[5];
	char* cpCol = new char[5];
	char* cpPan = new char[10];
	char* cpTilt = new char[10];
	int*	ipIndices;			//i,j indices & nodeID

	//first find out how many elements are in salientPts
	int N = salientPts->dimy();
	//cout << "N: " << N <<endl;
	
	
	//get pan/tilt location of node with ID nodeID
	_itoa(nodeID, cpID, 10);
	qySES << "SELECT PHI, THETA from tblNodes where ID = " << cpID << ";";
	resSES = qySES.store();
	rwSES = *resSES.begin();
	phi = rwSES[0];
	theta = rwSES[1];
	qySES.reset();
	//convert to pan/tilt from phi/theta
	tilt = 90 - theta;
	if((phi >= 0)&&(phi <= 180))
		pan = phi;
	else
		pan = phi - 360;

	//cout << "phi: " << phi << " theta: " << theta << " pan " << pan << " tilt " << tilt <<endl;

	//post these at correct nodeID in tblactivation
	for(i=0; i<N; i++)
	{
		//post each point to tblactivation
		strcpy(cpTemp, "Insert into tblactivation (ID, activation, row_location, col_location) Values (");
		strcat(cpTemp, cpID);
		strcat(cpTemp, ", ");
		sprintf(cpActiv, "%G", *salientPts->ptr(0,i));
		strcat(cpTemp, cpActiv);
		strcat(cpTemp, ", ");
		_itoa(*salientPts->ptr(1,i),cpRow, 10);
		strcat(cpTemp, cpRow);
		strcat(cpTemp, ", ");
		_itoa(*salientPts->ptr(2,i),cpCol,10);
		strcat(cpTemp, cpCol);
		strcat(cpTemp, " )");
		//cout << cpTemp <<endl;
		qyACT.exec(cpTemp);
		qyACT.reset();
		

		//now, for each point, find what node ID it should be mapped to
	
		//find displacement from center of Image
		difR = CTR_R - (int) *salientPts->ptr(1,i);
		difC = CTR_C - (int) *salientPts->ptr(2,i);
	
		//calculate pan/tilt of location based on:  angle = invtan [(C-C0)/f]
		newPan = pan + (atan(difC / FOCAL_C)*(180/PI));
		newTilt = tilt + (atan(difR / FOCAL_R)*(180/PI));

		//cout << "difR " << difR << " difC " << difC << " newPan " << newPan << " newTilt " << newTilt <<endl;

		//find ID associated with this new pan/tilt pair
		//Convert back from pan/tilt to phi/theta
		theta = 90 - newTilt;
		if((newPan >= 0)&&(newPan <= 180))
			phi = newPan;
		else
		phi = newPan + 360;
		ipIndices = AnglesToIndices(phi, theta);
		newID = ipIndices[2];
	
		//post attention point at the correct nodeID in table attention
		strcpy(cpTemp, "Insert into tblattention (imageCenterID, activation, row_location, col_location, ID, new_pan, new_tilt) Values( ");
		strcat(cpTemp, cpID);
		strcat(cpTemp, ", ");
		strcat(cpTemp, cpActiv);
		strcat(cpTemp, ", ");
		strcat(cpTemp, cpRow);
		strcat(cpTemp, ", ");
		strcat(cpTemp, cpCol);
		strcat(cpTemp, ", ");
		_itoa(newID, cpNewID, 10);
		strcat(cpTemp, cpNewID);
		strcat(cpTemp, ", ");
		sprintf(cpPan, "%G", newPan);
		strcat(cpTemp, cpPan);
		strcat(cpTemp, ", ");
		sprintf(cpTilt, "%G", newTilt);
		strcat(cpTemp, cpTilt);
		strcat(cpTemp, ")");

		//cout << cpTemp << endl;
		qyATTN.exec(cpTemp);
		qyATTN.reset();
	}

	cpTemp = NULL;
	cpID = NULL;
	cpRow = NULL;
	cpCol = NULL;
	cpActiv = NULL;
	cpPan = NULL;
	cpTilt = NULL;
	cpNewID = NULL;
	return true;

}

//ReturnFOA
void SESManager::ReturnFOA(double* mostSalientarray)
{
	Query				qySES = m_connSES->query();
	Result				resSES;
	Result::iterator	R;
	Row					rwSES;
	int					i,iNumRecs;
	double				dTemp;
	char*				cpTemp = new char[255];


	//sum activation at each node
	strcpy(cpTemp, "Select a.ID, sum(a.activation), n.phi, n.theta from tblattention a, tblnodes n where n.ID = a.ID group by a.activation, a.ID, n.phi, n.theta order by activation DESC limit 12;");
	qySES << cpTemp;
	resSES = qySES.store();
	rwSES = *resSES.begin();
	iNumRecs = resSES.size();
	if (iNumRecs >= 0)
	{
		//cout << "most salient (ID, Activation, pan,tilt): "<<endl;
		R = resSES.begin();
		for (i = 0; i < 1; i++)
	    {
		 	rwSES = *R;
			mostSalientarray[0] = rwSES[0];
			mostSalientarray[1] = rwSES[1];
			mostSalientarray[2] = rwSES[2];
			mostSalientarray[3] = rwSES[3];
	
			//convert from phi/theta to pan/tilt
			if(mostSalientarray[2] > 180)
			{
				dTemp = mostSalientarray[2];
				mostSalientarray[2] = dTemp -360;
			}

			dTemp = mostSalientarray[3];
			mostSalientarray[3] = 90 - dTemp;
			R++;
		}
	}
	else
	{
		cout << "There are no records in tblattention."<<endl;
		mostSalientarray[0] = mostSalientarray[1] = mostSalientarray[2] = mostSalientarray[3] = 0;
	}
	qySES.reset();
	cpTemp = NULL;

}


//CalculateSalience returns a CImg with the top N most salient locations on the SES by summing 
//activation values at each node (using tblattention)
CImg<double>* SESManager::CalculateSalience(int N)
{
	Query				qySES = m_connSES->query();
	Result				resSES;
	Result::iterator	R;
	Row					rwSES;
	int					i,iNumRecs;
	CImg<double>*		nMostSalient;

	nMostSalient = new CImg<double>(2, N);
	char* cpTemp = new char[255];


	//sum activation at each node
	strcpy(cpTemp, "Select ID, sum(activation) from tblattention group by activation, ID order by activation DESC;");
	qySES << cpTemp;
	resSES = qySES.store();
	rwSES = *resSES.begin();
	iNumRecs = resSES.size();
	if (iNumRecs >= N)
	{
		cout << "most salient (ID, Activation): "<<endl;
		R = resSES.begin();
		for (i = 0; i < N; i++)
	    {
		 	rwSES = *R;
			*nMostSalient->ptr(0,i) = rwSES[0];
			*nMostSalient->ptr(1,i) = rwSES[1];
			R++;
			cout << *nMostSalient->ptr(0,i) << " " <<*nMostSalient->ptr(1,i) <<endl;
		}
	}
	else
	{
		cout << "There are fewer than "<< N << " records in tblattention. Here are the top "<< iNumRecs << ": "<<endl;
		cout << "most salient (ID, Activation): "<<endl;
		R = resSES.begin();
		for (i = 0; i < iNumRecs; i++)
	    {
		 	rwSES = *R;
			*nMostSalient->ptr(0,i) = rwSES[0];
			*nMostSalient->ptr(1,i) = rwSES[1];
			R++;
			cout << *nMostSalient->ptr(0,i) << " " <<*nMostSalient->ptr(1,i) <<endl;
		}
	}
	qySES.reset();
	cpTemp = NULL;
	return nMostSalient;
}



// RetrieveAtAngles returns all main information about an object at the specified location
// Returns TRUE if data is found
// Returns FALSE if data is not found
// If >1 data records found, returns data closest to specified point, not most recent data
bool SESManager::RetrieveAtAngles(float Phi, float Theta, char* Name, char* Type, char* Identifier, char* Time)
{
	Query qySES = m_connSES->query();
	Result		resSES;
	
	Result::iterator	R;
	Row					rwSES;

	CString		cstrSQL;

	bool	records_found = false;

	char*	cpTemp;
	char	cpI[5];
	char	cpJ[5];
	char	keepI[5];
	char	keepJ[5];

	int*	Indices;
	int		indexI,indexJ;
	int		max_i = 0;
	int		max_j = 0;
	int		tempI,tempJ;
	int		valI, valJ;

	int		x, y;
	int		iNumRecs = 0;
	int		iNumFields = 0;

	float*	fpLeft = NULL;
	float*	fpRight = NULL;
	float*	fpWaist = NULL;
	float*	fpHead = NULL;
	float	min_dist, dist;

	// search for first record that is closest to location
	// First, change angles into indices
	Indices = AnglesToIndices(Phi, Theta);
	indexI = Indices[0];
	indexJ = Indices[1];

	// Second, change indices to strings
	_itoa(indexI, cpI, 10);
	_itoa(indexJ, cpJ, 10);

	// first find max vals of indices 
	// this may not work very well at poles (i = 0, i = max)
	qySES << "SELECT MAX(i_index) AS i_index FROM tblNodes WHERE j_index = " << cpJ << ";";
	resSES = qySES.store();
	rwSES = *resSES.begin();
	max_i = rwSES[0];
	qySES << "SELECT MAX(j_index) AS j_index FROM tblNodes WHERE i_index = " << cpI << ";";
	resSES = qySES.store();
	rwSES = *resSES.begin();
	max_j = rwSES[0];

	// initialize min distance
	min_dist = 1000;

	// go through neighborhood of 5 - can set this during run time if you want
	for(x=-5; x<=5; x++)
	{
		// check indices to make sure they aren't negative or over the max value
		if((indexI + x) < 0)
			tempI = max_i + (indexI + x) + 1;
		else if ((indexI + x) > max_i)
			tempI = indexI + x - max_i - 1;
		else
			tempI = indexI + x;
		// change short to char*
		_itoa(tempI, cpI, 10);
		for(y=-5; y<= 5; y++)
		{
			// check indices to make sure they aren't negative or over the max value
			if((indexJ + y) < 0)
				tempJ = max_j + (indexJ + y) + 1;
			else if ((indexJ + y) > max_j)
				tempJ = indexJ + y - max_j - 1;
			else
				tempJ = indexJ + y;
			// change short to char*
			_itoa(tempJ, cpJ, 10);
			// select records
			qySES << "SELECT tblSES.name, tblSES.type, tblSES.identifier, tblSES.timestamp, tblNodes.i_index, tblNodes.j_index FROM tblSES INNER JOIN tblNodes on tblSES.ID = tblNodes.ID WHERE tblNodes.i_index = " << cpI << " and tblNodes.j_index = " << cpJ << ";";
			resSES = qySES.store();
			iNumRecs = resSES.size();
			if (iNumRecs > 0)
			{
				// keep record that is closest to actual location
				for(R = resSES.begin(); R < resSES.end(); R++)
				{
					rwSES = *R;
					valI = rwSES[4];
					valJ = rwSES[5];
					dist = (float)pow((pow(valI-tempI, 2) + pow(valJ-tempJ, 2)), 0.5);
					if (dist < min_dist)
					{
						min_dist = dist;
						// keep these records
						cpTemp = (char*) rwSES[0].data();
						strcpy(Name, cpTemp);
					//	cpTemp = (char*) rwSES[3].data();
//						strcpy(Time, cpTemp);
						cpTemp = (char*) rwSES[2].data();
						strcpy(Identifier, cpTemp);
						cpTemp = (char*) rwSES[1].data();
						strcpy(Type, cpTemp);
						// keep i and j
						_itoa(valI, keepI, 10);	
						_itoa(valJ, keepJ, 10);

					}
				}
			}
		}
	}

	if (min_dist == 1000.0)
	{
		// no records were returned
		strcpy(Name, "No records found in that area");
		return false;
	}
	else
		return true;

}

//Dump All data from tables tblses, tblactivation, tblattention
bool SESManager::DumpAllData()
{
	
	Query	qySES = m_connSES->query();
	Result	rsSES;
	Result::iterator R;
	Row		rwSES;
	char	*cpSQL = new char[255];
	char*	cpTemp = new char[255];
	int		flag[3];
	flag[0] = flag[1] = flag[2] = 0;
	int iNumRecs = 0;

	cout << "hi" << endl;
	try{
	strcpy (cpSQL, "Show tables from ");
	strcat (cpSQL, dbName);
	cout << cpSQL <<endl;

	qySES << cpSQL;

	rsSES = qySES.store();
	}
	catch(BadQuery er)
	{
		cerr << er.error<<endl;
	}
	for (R = rsSES.begin(); R < rsSES.end(); R++)
	{
		
		rwSES = *R;
		cpTemp = (char*) rwSES[0].data();
		
		// check to see if these tables exist, if so, delete contents
		if(!_stricmp(cpTemp, "tblses"))
			flag[0] = 1;
		
		else if(!_stricmp(cpTemp, "tblactivation"))
			flag[1] = 1;
		
		else if(!_stricmp(cpTemp, "tblattention"))
			flag[2] = 1;
	}
	qySES.reset();

	if(flag[2] == 1)
	{
		try{
			strcpy(cpTemp,"DELETE FROM tblattention;");
			//cout << cpTemp << endl;
			qySES << cpTemp;
			rsSES = qySES.store();
			qySES.reset();
		}
		catch(BadQuery er)
		{
		//	cerr <<"ERROR: " << er.error << endl;

		}
		//make sure it was deleted:
		strcpy(cpTemp, "SELECT * FROM tblattention;");
		qySES << cpTemp;
		rsSES = qySES.store();
		qySES.reset();
		if(rsSES.size() == 0)
		{
			//	cout << "delete tblattention: SUCCESS" <<endl;
		}
		else
			return false;
	}
	if(flag[0] == 1)
	{
		try{
			strcpy(cpTemp, "DELETE FROM tblSES;");
			qySES << cpTemp;
			rsSES = qySES.store();
			qySES.reset();
			//cout << cpTemp << endl;
		}
		catch(BadQuery er)
		{
		//	cerr <<"ERROR: " << er.error << endl;
		}
		//make sure it was deleted:
		strcpy(cpTemp, "SELECT * FROM tblses;");
		qySES << cpTemp;
		rsSES = qySES.store();
		qySES.reset();
		if(rsSES.size() == 0)
		{
			//cout << "delete tblSES: SUCCESS" <<endl;
		}
		else
			return false;
	}
	if(flag[1] == 1)
	{
		try{
			strcpy(cpTemp, "DELETE FROM tblactivation;");
			qySES << cpTemp;
			rsSES = qySES.store();
			qySES.reset();
			//cout << cpTemp << endl;
		}
		catch(BadQuery er)
		{
		//	cerr <<"ERROR: " << er.error << endl;
		}
		//make sure it was deleted:
		strcpy(cpTemp, "SELECT * FROM tblactivation;");
		qySES << cpTemp;
		rsSES = qySES.store();
		qySES.reset();
		if(rsSES.size() == 0)
		{
		//	cout << "delete tblactivation: SUCCESS" <<endl;
		}
		else
			return false;
	}

	cpTemp = NULL;
	cpSQL = NULL;

	return true;

}

// DeleteByName
bool SESManager::DeleteByName(char *Name)
{
	Query		qySES = m_connSES->query();
	Result		rsSES;
	Result		rsSES2;
	Row			rwSES;

	char *cpTemp = new char[255];
//	char *cpSQL = new char[255];

	// first see if record name exists
	strcpy(cpTemp, "Select ID from tblSES where name = '");
	strcat(cpTemp, Name);
	strcat(cpTemp, "';");
	//cout << cpTemp << endl;
	qySES << cpTemp;
	rsSES = qySES.store();
	qySES.reset();

	if(rsSES.size() > 0)
	{
		strcpy(cpTemp, "DELETE FROM tblSES WHERE name = '");
		strcat(cpTemp, Name);
		strcat(cpTemp, "' ;");
	//	cout << cpTemp << endl;
		qySES << cpTemp;
		rsSES2 = qySES.store();
		qySES.reset();

		cpTemp = NULL;

		//make sure the operation was successful
		qySES << "SELECT ID from tblSES WHERE name = '"<< Name << "';";
		rsSES2 = qySES.store();
		if (rsSES2.size() > 0)
			return false;
		else
			return true;
				
	}
	else
	{
		cpTemp = NULL;
		return false;
	}
}


/*
// Update updates Attribute of a given data record 
bool SESManager::Update(char *Name, char* Type, char* Attribute, char* DataType, int DataSize, char** DataText, double* DataNums)
{
	Query		qySES = m_connSES->query();
	
	CString		cstrSQL;

	char*		cpField;
	char*		cpSQL;
	char*		cpTemp = new char[32];
	char		cpDataNumTemp[10];
	char		cpTempSize[5];

	int			strLen;
	int			i;
	int			count = 0;

	bool		no_new_field = false;

	// if Attribute has info in, then just update attribute
	if(Attribute != NULL)
	{
		if (strcmp(Attribute, ""))
		{
			// see if attribute meets any in tblObjects
			qySES << "SHOW COLUMNS FROM tblObjects";
			Result	rsRecords = qySES.store();
			int		numRecs = rsRecords.size();
			if(numRecs != 0)
			{
				Row		row;
				Result::iterator	a;
				for(a=rsRecords.begin(); a != rsRecords.end(); a++)
				{
					row = *a;
					cpField = (char*)row[0].data();
					strLen = strlen(Attribute);
					if (!_stricmp(cpField, Attribute))
					{
						no_new_field = true;
						break;
					}
					else if(!_strnicmp(cpField, Attribute, strLen))
					{
						no_new_field = true;
						break;
					}			
				}
			}

			// if attribute is new field
			if (!no_new_field)
			{
				//1. must first make sure data type is OK for sql
				if (!_stricmp(DataType, "boolean"))
					strcpy(DataType, "TINYINT");
				else if(!_stricmp(DataType, "integer") || !_stricmp(DataType, "int"))
					strcpy(DataType, "INT");
				else if(!_stricmp(DataType, "long"))
					strcpy(DataType, "BIGINT");
				else if(!_stricmp(DataType, "float"))
					strcpy(DataType, "FLOAT");
				else if(!_stricmp(DataType, "double"))
					strcpy(DataType, "DOUBLE");
				else if(!_stricmp(DataType, "char") || !_stricmp(DataType, "character") || !_stricmp(DataType, "char*"))
					strcpy(DataType, "TEXT");
				// check to see how many data points entered
				if(DataSize > 1)
				{
					// must make >1 fields
					cstrSQL.Insert(0, ");");
					for (i=DataSize; i>0; i--)
					{
						if(i != DataSize)
							cstrSQL.Insert(0, ", ");
						cstrSQL.Insert(0, DataType);
						cstrSQL.Insert(0, " ");
						_itoa(i, cpTempSize, 10);
						cstrSQL.Insert(0, cpTempSize);
						cstrSQL.Insert(0, Attribute);
					}
				}
				else
				{
					cstrSQL.Empty();
					cstrSQL.Insert(0, ");");
					cstrSQL.Insert(0, DataType);
					cstrSQL.Insert(0, " ");
					cstrSQL.Insert(0, Attribute);
				}

				cstrSQL.Insert(0, "ALTER TABLE tblObjects ADD (");
				cpSQL = cstrSQL.GetBuffer(1);
				qySES.exec(cpSQL);
				cstrSQL.ReleaseBuffer();
				cstrSQL.Empty();
				cpSQL = NULL;
			}

			// now must update records in table
			// if there are multiple fields to fill
			if (DataSize > 1)
			{
				cstrSQL.Insert(0, "';");
				cstrSQL.Insert(0, Name);
				cstrSQL.Insert(0, " WHERE name = '");

				// if data type is text, must add single quotes
				if(!_stricmp(DataType, "text"))
				{
					cstrSQL.Insert(0, "'");
					cstrSQL.Insert(0, DataText[DataSize-1]);
					cstrSQL.Insert(0, " = '");
					_itoa(DataSize, cpTempSize, 10);
					cstrSQL.Insert(0, cpTempSize);
					cstrSQL.Insert(0, Attribute);
					for(i=DataSize-1; i>0; i--)
					{
						cstrSQL.Insert(0, ", ");
						cstrSQL.Insert(0, "'");
						cstrSQL.Insert(0, DataText[i-1]);
						cstrSQL.Insert(0, " = '");
						_itoa(i, cpTempSize, 10);
						cstrSQL.Insert(0, cpTempSize);
						cstrSQL.Insert(0, Attribute);
					}
				}
				else
				{
					sprintf(cpDataNumTemp, "%f", DataNums[DataSize-1]);
					cstrSQL.Insert(0, cpDataNumTemp);
					cstrSQL.Insert(0, " = ");
					_itoa(DataSize, cpTempSize, 10);
					cstrSQL.Insert(0, cpTempSize);
					cstrSQL.Insert(0, Attribute);
					for(i=DataSize-1; i>0; i--)
					{
						cstrSQL.Insert(0, ", ");
						sprintf(cpDataNumTemp, "%f", DataNums[i-1]);
						cstrSQL.Insert(0, cpDataNumTemp);
						cstrSQL.Insert(0, " = ");
						_itoa(i, cpTempSize, 10);
						cstrSQL.Insert(0, cpTempSize);
						cstrSQL.Insert(0, Attribute);
					}
				}
			}
			// else if there is jsut one field
			else
			{
				cstrSQL.Insert(0, "';");
				cstrSQL.Insert(0, Name);
				cstrSQL.Insert(0, " WHERE name = '");
				// if data type is text, must add single quotes
				if(!_stricmp(DataType, "char") || !_stricmp(DataType, "character") || !_stricmp(DataType, "char*"))
				{
					cstrSQL.Insert(0, "'");
					cstrSQL.Insert(0, DataText[0]);
					cstrSQL.Insert(0, " = '");
				}
				else
				{
					sprintf(cpDataNumTemp, "%f", DataNums[0]);
					cstrSQL.Insert(0, cpDataNumTemp);
					cstrSQL.Insert(0, " = ");
				}
				cstrSQL.Insert(0, Attribute);
			}

			cstrSQL.Insert(0, "UPDATE tblObjects SET ");
			cpSQL = cstrSQL.GetBuffer(1);
			qySES.exec(cpSQL);
			cstrSQL.ReleaseBuffer();
			cstrSQL.Empty();
			cpSQL = NULL;
			
			delete cpTemp;
			return true;
		}
		else
		{
			delete cpTemp;
			return false;
		}
	}
	else
	{
		delete cpTemp;
		return false;
	}
}
*/









/************************************************************************
*************************************************************************
*		
*	The following are routines that support the above SES functionality
*
*************************************************************************
************************************************************************/


/*	AnglesToIndices converts SES angle values to index values
	A short array is returned with the matching i, j indices and an ID
	Does this by selecting a range of angles w/in 20 degrees of desired angles,
	finding the angle pair w/ the smallest distance from the desired angle
	pair and retreiving the indices that match that node*/
int* SESManager::AnglesToIndices(float AnglePhi, float AngleTheta)
{

	// MySQL Query object
	Query		qyIndices = m_connSES->query();
	// MySQL Result object
	Result		resNodes;
	
	// holds
	char	str1[20];
	char	str2[20];
	char	str3[20];
	char	str4[20];
	
	// hold either "AND" or "OR" for SQL query for retrieving phi and theta
	char*	cpPhiWhere;
	char*	cpThetaWhere;

	float*	fpPhis;
	float*	fpThetas;
	float	fPhiDist, fThetaDist, fDist;
	float	fMinDist = 100;

	int*	ipI_s;
	int*	ipJ_s;
	int*	ipID_s;
	int		ipIndices[3];
	short	sNumRecs;
	short	sKeep = -1;

	cpPhiWhere = "AND";
	cpThetaWhere = "AND";

	// must set the string to match the data
	// if theta is less than 20 degrees, will need to check thetas <=360
	// so will use an OR in SQL query
	if(AngleTheta < 20.0)
	{
		sprintf(str1, "%e", (AngleTheta + 360 - 20));
		cpThetaWhere = "OR";
	}
	else
		sprintf(str1, "%e", (AngleTheta - 20.0));
	// if theta is >340 degrees, will need to check thetas <=20
	// so will use an OR in SQL query
	if(AngleTheta >= 340)
	{
		sprintf(str2, "%e", (AngleTheta - 360 + 20.0));	
		cpThetaWhere = "OR";
	}
	else
		sprintf(str2, "%e", (AngleTheta + 20.0));
	// if phi is less than 20 degrees, will need to check phis <=360
	// so will use an OR in SQL query
	if(AnglePhi < 20.0)
	{
		sprintf(str3, "%e", (AnglePhi + 360 - 20.0));
		cpPhiWhere = "OR";
	}
	else
		sprintf(str3, "%e", (AnglePhi - 20.0));
	// if phi is >340 degrees, will need to check phis <=20
	// so will use an OR in SQL query
	if(AnglePhi >= 340)
	{
		sprintf(str4, "%e", (AnglePhi - 360 + 20.0));
		cpPhiWhere = "OR";
	}
	else
		sprintf(str4, "%e", (AnglePhi + 20.0));
		
	// insert query to select angles w/in a specific range of phi, theta
	qyIndices << "SELECT ID, i_index, j_index, phi, theta FROM tblNodes WHERE ((" << str3 << " <= phi " << cpPhiWhere << " phi <= " << str4
		<< ") AND (theta <= " << str2 << cpThetaWhere << " theta >= " << str1 << "));";

	// store results
	resNodes = qyIndices.store();
	// get result size
	sNumRecs = resNodes.size();
	// initialize arrays holding query results
	ipID_s	 = new int	[sNumRecs];
	ipI_s    = new int [sNumRecs];
	ipJ_s    = new int [sNumRecs];
	fpPhis	 = new float [sNumRecs];
	fpThetas = new float [sNumRecs];

	// assign iterator to go through result array
	Result::iterator a;
	Row		row;
	int		i = 0;
	// iterate through results
	for(a=resNodes.begin(); a != resNodes.end(); a++)
	{
		// point row to iterator
		row = *a;
		// get values for record being held in row
		ipID_s[i] = row[0];
		ipI_s[i] = row[1];
		ipJ_s[i] = row[2];
		fpPhis[i] = row[3];
		fpThetas[i] = row[4];
		i++;
	}

	// get distances b/tw original angles and result angles
	for(i=0; i<sNumRecs; i++)
	{
		fPhiDist = AnglePhi - fpPhis[i];
		fThetaDist = AngleTheta - fpThetas[i];
		fDist = (float)pow((pow(fPhiDist, 2) + pow(fThetaDist, 2)), 0.5);
		if (fDist < fMinDist)
		{
			// if distance is smallest, keep it
			fMinDist = fDist;
			sKeep = i;
		}
	}

	// get indices that match smallest distance angle pair
	ipIndices[0] = ipI_s[sKeep];
	ipIndices[1] = ipJ_s[sKeep];
	ipIndices[2] = ipID_s[sKeep];

	delete [] ipID_s;
	delete [] ipI_s; 
	delete [] ipJ_s;
	delete [] fpPhis;
	delete [] fpThetas;

	// return indices that match the closest phi,theta angle pair
	return &ipIndices[0];
}


// FindRecord detects whether or not data with Name
bool SESManager::FindRecord(char *Name)
{
	Query		qySES = m_connSES->query();
	Result		resSES;

	int			iNumRecs;

	qySES << "SELECT name FROM tblSES WHERE name = '" << Name << "';";
	resSES = qySES.store();
	iNumRecs = resSES.size();
	if (iNumRecs > 0)
		return 1;
	else
		return 0;
}

// copy text into a return value, changing size if necessary
int SESManager::CopyTextValue(Row &row, int size, char *data)
{
	char *charpL;
	int j;
	int	len = 0;

	if(size>MAX_TEXT_LENGTH)
		size=MAX_TEXT_LENGTH;

	for(j=0;j<size;j++)
	{
		charpL = (char*)row[j].data();
		strcpy(&data[len], charpL);
		len = strlen(charpL);
		if (j<(size-1))
			strcpy(&data[len], ", ");
		len += 2;
	}
	return(size);

}

// copy numerical values into a return value, changing size if necessary
int SESManager::CopyNumValue(Row &row, int size, double *data)
{
	int j;

	if(size>MAX_TEXT_LENGTH)
		size=MAX_TEXT_LENGTH;

	for(j=0; j<size; j++)
		data[j] = row[j];

	return(size);
}



// Not really used
bool SESManager::RetrieveByIdentifier(char *Identifier, char *Type, double* Phi, double* Theta, char *Name)
{
	Query qySES = m_connSES->query();
	Result	resSES;
	Row		rwSES;
	char*	temp;

	qySES << "SELECT tblNodes.phi, tblNodes.theta, tblSES.name FROM tblNodes INNER JOIN tblSES ON tblNodes.ID = tblSES.ID WHERE tblSES.identifier = '" << Identifier << "' AND tblSES.type = '" << Type << "';";
	resSES = qySES.store();
	if (resSES.size() > 0)
	{
		rwSES = *resSES.begin();
		Phi[0] = rwSES[0];
		Theta[0] = rwSES[1];
		temp = (char*)rwSES[2].data();
		strcpy(Name, temp);
		return true;
	}
	else
		return false;

}


