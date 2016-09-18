
//Modified 10/19/05 by Katherine Achim to be used with ISAC

// CreateNewSES.cpp: implementation of the CCreateNewSES class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CreateNewSES.h"
#include "mysql++"
#include "custom.hh"
#include <iostream>
#include <vector>
#include <string>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

sql_create_11 (tblNodes, 1, 10, int, ID, int, i_index, int, j_index, double, phi, double, theta, int, N1, int, N2, int, N3, int, N4, int, N5, int, N6)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CCreateNewSES::CCreateNewSES( )
{

	m_dbconnSES = new Connection("dbKat", "129.59.72.55", "root"); 
	m_fDegToRad = (float)0.017453;
	m_fRadToDeg = (float)57.29577;

}

CCreateNewSES::~CCreateNewSES()
{
	delete m_dbconnSES;
}

bool CCreateNewSES::CheckCurrentTables()
{
	Query	qySES = m_dbconnSES->query();
	Result	rsSES;
	Result::iterator R;
	Row		rwSES;
	bool	blnRetVal = false;
	char*	cpTemp;

	//qySES << "SHOW TABLES FROM Robonaut_SES_DB";
	qySES << "SHOW TABLES FROM dbKat";

	rsSES = qySES.store();
	for (R = rsSES.begin(); R < rsSES.end(); R++)
	{
		
		rwSES = *R;
		cpTemp = (char*) rwSES[0].data();
		// check to see if complete match of field names
		if(!_stricmp(cpTemp, "tblNodes"))
		{	
			blnRetVal = true;
		
		}
	}
	if(blnRetVal)
	{
		
		return false;
    }
	else
	{
		cpTemp = new char [300];
	
		strcpy(cpTemp, "CREATE TABLE tblNodes (ID int, i_index int, j_index int, phi double, theta double, N1 int, N2 int, N3 int, N4 int, N5 int, N6 int)");
		if(qySES.exec(cpTemp))
			return true;
		else
			return false;
	}
}


// A FEW NOTES ABOUT THE ORIENTATION OF THE SES  9/14/04
///////////////////////////////////////////////
//  The SES is centered at Robonaut's chest coordinate frame.
//	The SES has azimuth, elevation (0,0) pointing down and 
//     the azimuth increases from 0 to 360 going right. 
//  This orientation supports the x-axis coming out of the fron
//		of Robonaut and the z-axis pointing down.
//////////////////////////////////////////////////////////////

bool CCreateNewSES::CreateNewNodes()	// as of 9/13/04 this works absolutely correctly
{
	SphereIndices*  psiFullIndex;
	tblNodes		NodesT;
	Query			qyNodes = m_dbconnSES->query();

	int		i, j, k, m, iFaceInd;
	int		/*m_iVertex,*/ iFaces, iEdges, iIndex, iVIndex;
    int		j_track = 0;
	int		k_hack;
	int*    piVertParams = NULL;
	double	X, Y, Z;
   
	// these hold the vertices of the sphere, their indices and angles
    SphereIndices*	psiIndices = NULL;
    SphereCoord* pscXYZCoord = NULL;
    EgoCoord* pecAngles = NULL;
    EgoCoord* pecSphere = NULL;

    //  determine how many vertices/triangle for desired tessellation frequency
    for(i=1; i<=m_iTessFreq; i++)
	{
        if(i==1)
            m_iVertex = 3;
        else
            m_iVertex += (i+1);
	}
	

    // get # of faces and edges
    iFaces = m_iTessFreq*m_iTessFreq;
    iEdges = (m_iVertex + iFaces) - 1;



    // initialize size of all structures
    piVertParams = new int [m_iTessFreq + 1];
    psiIndices = new SphereIndices [m_iVertex];
    pscXYZCoord = new SphereCoord [m_iVertex];
    pecAngles = new EgoCoord [m_iVertex];

	// determine number of vertices per triangle
    if(m_iTessFreq == 1)
        k = 12;
    else
        k = 2*(5*(m_iVertex-m_iTessFreq-1)+1)+10*(m_iVertex-2*m_iTessFreq-1);
	
	// init below according to vert/triangle
    pecSphere = new EgoCoord [k];
    psiFullIndex = new SphereIndices [k];

    //  init indices to find euclid. coordinates of vertices on triangle
    iIndex = 0;
    for(i=0; i<=m_iTessFreq; i++)
	{
		piVertParams[i] = iIndex;		// need to set the i_index for each row
        for(j=0; j<=i; j++)
		{
            psiIndices[iIndex].i_index = i;
            psiIndices[iIndex].j_index = j;
            pscXYZCoord[iIndex].x_prime = j;
            pscXYZCoord[iIndex].y_prime = i - j;
            pscXYZCoord[iIndex].z_prime = m_iTessFreq - i;
            iIndex++;
        }
    }
	
    for(i=0; i<m_iVertex; i++)
	{
        X = pscXYZCoord[i].x_prime * sin(72*m_fDegToRad);
        Y = pscXYZCoord[i].y_prime + (pscXYZCoord[i].x_prime * cos(72*m_fDegToRad));
        Z = m_iTessFreq/2 + (pscXYZCoord[i].z_prime/(2*cos(36*m_fDegToRad)));

        // Calculate phi while avoiding trig errors
        if(Y==0 && X==0)
            pecAngles[i].phi = 0;
        else if(Y==0)
            pecAngles[i].phi = 90;
        else
            pecAngles[i].phi = atan(X/Y)*m_fRadToDeg;
        
        // adjust value to correct quadrant
        if(pecAngles[i].phi < 0)
            pecAngles[i].phi = pecAngles[i].phi + 180;

        if(Z==0)
            pecAngles[i].theta = 90;
        else
            pecAngles[i].theta = atan(sqrt(X*X + Y*Y)/Z)*m_fRadToDeg;

        // make sure the right quadrant is used
        if(pecAngles[i].theta < 0)
            pecAngles[i].theta = pecAngles[i].theta + 180;
        
        // Set Radius = 1
        pecAngles[i].radius = 1;
	}
    
/////////////////////////////////////////////////////////////////////////////////////
//      THE FOLLOWING CODE GENERATES THE NODES OF THE SPHERE
//      Must generate for each face - 20 in all b/c number of pentagons in
//      sphere always stays same - only # of hexagons change
//      ** adapted from GEODESIC.CPP
//		The code produces a unique ID, a row,column index pair, and a phi,theta
//			angle pair for each node. (1st node is a 0,0, last node is at 0,180)
/////////////////////////////////////////////////////////////////////////////////////

   

	//  Am trying to make indices follow order along w/ angles
    iIndex = 0;
    //  set top point of sphere (j=0)
    pecSphere[iIndex].phi = pecAngles[iIndex].phi;
    pecSphere[iIndex].theta = pecAngles[iIndex].theta;
    pecSphere[iIndex].radius = 1;
    psiFullIndex[iIndex].i_index = 0;
    psiFullIndex[iIndex].j_index = 0;
    iIndex++;

    //  Set points of sphere in first 5 triangles
    for(i=1; i<=m_iTessFreq; i++)
	{
		j_track = 0;
        for(iFaceInd=0; iFaceInd<5; iFaceInd++)
		{
            iVIndex = piVertParams[i];
            for(j=0; j<i; j++)
		{
				pecSphere[iIndex].phi = pecAngles[iVIndex+j].phi + 72*iFaceInd;
                if(pecSphere[iIndex].phi >= 360)
                    pecSphere[iIndex].phi = 0;
                pecSphere[iIndex].theta = pecAngles[iVIndex+j].theta;
                pecSphere[iIndex].radius = 1;
                psiFullIndex[iIndex].i_index = i;
                psiFullIndex[iIndex].j_index = j_track;
                iIndex++;
                j_track++;
			}
		}
	}

    // Set points of sphere in middle front 5 triangles
    //  Start at 1 b/c we already have indices from the bottom row of 1st five triangles
    for(i=1; i<m_iTessFreq; i++)
	{
        j_track = 0;
        for(iFaceInd=5; iFaceInd<10; iFaceInd++)
		{
            k = iFaceInd - 5;
            if(k==0)
                k_hack = 0;
            else if(k==2)
                k_hack = 1;
            else if(k==4)
                k_hack = 2;

            if((k%2) == 0)
			{
				//  then triangle is flipped upside down
                m = m_iTessFreq - i;
				// so use vertex points from next to last row first
                iVIndex = piVertParams[m+1] - 1;
                if(m!=0)
                    for(j=1; j<=m; j++)
					{
						// this rotation is fine for flipping the triangle upside down
                        pecSphere[iIndex].theta = RotateTheta(36,pecAngles[iVIndex-j].phi, (180-(atan(2)*m_fRadToDeg)), pecAngles[iVIndex-j].theta);
                        pecSphere[iIndex].phi = (RotatePhi(36,pecAngles[iVIndex-j].phi,pecAngles[iVIndex-j].theta,pecSphere[iIndex].theta)+36)+72*k_hack;
                        if(pecSphere[iIndex].phi>=360)
                            pecSphere[iIndex].phi = 0;
                        pecSphere[iIndex].radius = 1;
                        psiFullIndex[iIndex].i_index = i + m_iTessFreq;
                        psiFullIndex[iIndex].j_index = j_track;
                        iIndex++;
                        j_track++;
					}
			}
			else   // else triangle is right side up
			{
				iVIndex = piVertParams[i];
                for(j=1; j<=i; j++)
				{
                    pecSphere[iIndex].theta = 180 - RotateTheta(36, pecAngles[iVIndex+j].phi, (180 -(atan(2)*m_fRadToDeg)), pecAngles[iVIndex+j].theta);
                    pecSphere[iIndex].phi = 180 - ((RotatePhi(36, pecAngles[iVIndex+j].phi, pecAngles[iVIndex+j].theta, pecSphere[iIndex].theta) + 36) + 72) + 72 * k_hack;
                    if(pecSphere[iIndex].phi >= 360)
                        pecSphere[iIndex].phi = 0;
                    pecSphere[iIndex].radius = 1;
                    psiFullIndex[iIndex].i_index = i + m_iTessFreq;
                    psiFullIndex[iIndex].j_index = j_track;
                    iIndex++;
                    j_track++;
				}
			}
		}
	}

    //  Set points for next 5 middle triangles
    for(i=1; i<m_iTessFreq; i++)
	{
        j_track = 3*m_iTessFreq - i;
        for(iFaceInd=10; iFaceInd<15; iFaceInd++)
		{
            // do a downward rotation then rotate 72° x k phi and 180° theta
            k = iFaceInd - 10;       //phi rotation factor
            if(k==0)
                k_hack = 3;
            else if(k==2)
                k_hack = 4;
            else if(k==4)
                k_hack = 0;

            if(k%2 != 0)
			{
                //  then triangle is flipped upside down
                m = m_iTessFreq - i;
                // so use vertex points from next to last row first
                iVIndex = piVertParams[m+1]-1;
                if(m!=0)
				{
					for(j=1; j<=m; j++)
					{
                        pecSphere[iIndex].theta = RotateTheta(36, pecAngles[iVIndex-j].phi, (180-(atan(2)*m_fRadToDeg)), pecAngles[iVIndex-j].theta);
                        pecSphere[iIndex].phi = (RotatePhi(36, pecAngles[iVIndex-j].phi, pecAngles[iVIndex-j].theta, pecSphere[iIndex].theta) + 36) + 72*k_hack;
                        if(pecSphere[iIndex].phi >= 360)
                            pecSphere[iIndex].phi = 0;
						pecSphere[iIndex].radius = 1;
                        psiFullIndex[iIndex].i_index = i+m_iTessFreq;
                        psiFullIndex[iIndex].j_index = j_track;
                        iIndex++;
                        j_track++;
					}
				}
			}
			else
			{
				iVIndex = piVertParams[i];
                for(j=1; j<=i; j++)
				{
					pecSphere[iIndex].theta = 180-RotateTheta(36,pecAngles[iVIndex+j].phi, (180 - (atan(2)*m_fRadToDeg)), pecAngles[iVIndex+j].theta);
                    pecSphere[iIndex].phi = 180-((RotatePhi(36,pecAngles[iVIndex+j].phi, pecAngles[iVIndex+j].theta, pecSphere[iIndex].theta) + 36)+72+72) +72*k_hack;
                    if(pecSphere[iIndex].phi >= 360)
                        pecSphere[iIndex].phi = 0;
                    if(pecSphere[iIndex].phi < 0)
                        pecSphere[iIndex].phi = pecSphere[iIndex].phi + 360;
                    pecSphere[iIndex].radius = 1;
                    psiFullIndex[iIndex].i_index = i+m_iTessFreq;
                    psiFullIndex[iIndex].j_index = j_track;
                    iIndex++;
					j_track++;
				}
			}
		}
	}
 
    // Set points for bottom 5 triangles (all are upside down)
    // rotate bottom cap into place and the sphere is done!
    for(i=0; i<=m_iTessFreq; i++)
	{
        j_track = 0;
        for(iFaceInd=15; iFaceInd<20; iFaceInd++)
		{
            k = iFaceInd - 15;
            m = m_iTessFreq - i; // may need to be i + 1????????????
            iVIndex = piVertParams[m];
            if(m!=0)
			{
				for(j=1; j<=m; j++)
				{
					// below doesn't work so I replaced w/ the one below it
					pecSphere[iIndex].phi = (pecAngles[iVIndex+j-1].phi + 72 * k) + 36;
                    //pecSphere[iIndex].phi = (pecAngles[iVIndex-j].phi + 72 * k) + 36; //used to be this
                    //pecSphere[iIndex].phi = pecAngles[iVIndex+j-1].phi + 72*k;		//wrong
                    if(pecSphere[iIndex].phi >= 360)
                        //pecSphere[iIndex].phi = 0;
						pecSphere[iIndex].phi = pecSphere[iIndex].phi -360;
					
                    pecSphere[iIndex].theta = 180-pecAngles[iVIndex+j-1].theta;
                    pecSphere[iIndex].radius = 1;
                    psiFullIndex[iIndex].i_index = i+2*m_iTessFreq;
                    if(psiFullIndex[iIndex].i_index == 41)
						pecSphere[iIndex].radius = 1;
					//changed code below to get correct j_indices --Kat
					//psiFullIndex[iIndex].j_index = j_track;
					psiFullIndex[iIndex].j_index = j_track + floor(m/2);
					if (psiFullIndex[iIndex].j_index >= m*5 ) //exceeds # nodes for this row
						psiFullIndex[iIndex].j_index = psiFullIndex[iIndex].j_index - (m*5);
					//end
                    iIndex++;
                    j_track++;
				}
			}
			else if(m==0 && iFaceInd==19)
			{
				pecSphere[iIndex].phi = 0;
                pecSphere[iIndex].theta = 180 ;
                pecSphere[iIndex].radius = 1;
                psiFullIndex[iIndex].i_index = psiFullIndex[iIndex-1].i_index+1;
                psiFullIndex[iIndex].j_index = 0;
                iIndex++;
			}
		}
	}
    
	// release pointers no longer needed
	delete [] piVertParams;
	delete []psiIndices;
	delete []pscXYZCoord;
	delete [] pecAngles;

	// now must put all of this into a table
	for(i=0; i<iIndex; i++)
	{
		if(i==1166)
			i = 1166;
		NodesT.ID				= i;
		NodesT.i_index			= psiFullIndex[i].i_index;
		NodesT.j_index			= psiFullIndex[i].j_index;
		if(pecSphere[i].phi > 359) 
			NodesT.phi			= 0.0;
		else
			NodesT.phi				= pecSphere[i].phi;
		NodesT.theta			= pecSphere[i].theta;
		NodesT.N1				= 0;
		NodesT.N2				= 0;
		NodesT.N3				= 0;
		NodesT.N4				= 0;
		NodesT.N5				= 0;
		NodesT.N6				= 0;
		qyNodes.insert(NodesT);
		qyNodes.execute();
		
	}

	delete [] psiFullIndex;
	delete [] pecSphere;

	return true;
}

// used in CreateNewSES
double CCreateNewSES::RotatePhi(double phi, double phi1, double theta1, double theta2)
{
	//phi half of the rotation formula given in Kenner's "Geodesic Math &
	//How to Use it" Kenner credits this formula to Professor George Owen

	double result;

	result = (sin(theta1 * m_fDegToRad)* sin((phi-phi1) * m_fDegToRad)) /
					sin(theta2 * m_fDegToRad);

	//Apply correction for round-off errors
	if(result > 1.0)
		result = 1.0;
	else if(result < -1.0)
		result = -1.0;

	return (asin(result) * m_fRadToDeg);

}

// used in CreateNewSES
double CCreateNewSES::RotateTheta(double phi, double phi1, double theta, double theta1)
{
	//theta half of the rotation formula given in Kenner's "Geodesic Math &
	//How to Use it" Kenner credits this formula to Professor George Owen
	double result;

	result = cos(theta1 * m_fDegToRad) * cos(theta * m_fDegToRad) +
					sin(theta1 * m_fDegToRad) * sin(theta * m_fDegToRad) *
						cos((phi-phi1) * m_fDegToRad);

	//Apply correction for round-off errors
	if(result > 1.0)
		result = 1.0;
	else if(result < -1.0)
		result = -1.0;

	return (acos(result) * m_fRadToDeg);
}



bool CCreateNewSES::ShiftIndices()	// this routine shifts indices so that the beginning index 
// matches up w/ the smallest phi value (i.e. j_index=0 corresponds to angle closest to 0)
{
	Query	qySES = m_dbconnSES->query();
	Result	resSES;
	Row		rwSES;
	Result::iterator R;

	CString	cstrSQL;
	char*	cpSQL = NULL;
	char	cpID[5];
	char	cpI[2];
	char	cpShift[2];
	char	cpMax[4];
	int		i, index;
	int		iTempI, iShiftIndex, iShiftID;

	// figure out where j_index closest to phi = 0 is
	for(i=m_iTessFreq+1; i<m_iTessFreq*2; i++)	//was iTessFreq*2
	{
		index = 0;
		qySES << "SELECT ID, i_index, j_index, phi FROM tblNodes WHERE i_index = " << i << " AND phi < 50 ORDER BY phi";
		resSES = qySES.store();
		for(R=resSES.begin(); R<resSES.end(); R++)
		{
			rwSES = *R;
			if(index == 0)
				iShiftID = rwSES[0];
			iTempI = rwSES[2];
			if(iTempI == 0)				
			{
				iShiftIndex = index;
				break;
			}
			else
				index++;
		}

// UPDATE tblNodes SET j_index = j_index+iShiftIndex WHERE i_index = i AND ID < iShiftID
		if(index > 0)
		{
			_itoa(iShiftID, cpID, 10);
			cstrSQL.Insert(0, cpID);
			cstrSQL.Insert(0, " AND ID < ");
			_itoa(i, cpI, 10);
			cstrSQL.Insert(0, cpI);
			cstrSQL.Insert(0, " WHERE i_index = ");
			_itoa(iShiftIndex, cpShift, 10);
			cstrSQL.Insert(0, cpShift);
			cstrSQL.Insert(0, "UPDATE tblNodes SET j_index = j_index+");
			cpSQL = cstrSQL.GetBuffer(1);
			qySES.execute(cpSQL);
			cpSQL = NULL;
			cstrSQL.ReleaseBuffer();
			cstrSQL.Empty();

	// UPDATE tblNodes SET j_index = j_index-(5*m_iTessFreq-iShiftIndex) WHERE i_index = i AND ID >= iShiftID
			cstrSQL.Insert(0, cpID);
			cstrSQL.Insert(0, " AND ID >= ");
			cstrSQL.Insert(0, cpI);
			cstrSQL.Insert(0, " WHERE i_index = ");
			_itoa((5*m_iTessFreq-iShiftIndex), cpMax, 10);
			cstrSQL.Insert(0, cpMax);
			cstrSQL.Insert(0, "UPDATE tblNodes SET j_index = j_index-");
			cpSQL = cstrSQL.GetBuffer(1);
			qySES.execute(cpSQL);
			cpSQL = NULL;
			cstrSQL.ReleaseBuffer();
			cstrSQL.Empty();

		}	
	}


	return true;
}

bool CCreateNewSES::AssignNeighbors()	// assigns 1st edge neighbors for each node (5 or 6)
{
	Query	qySES = m_dbconnSES->query();
	Result	resSES;
	Row		rwSES;
	Result::iterator R;

	CString	cstrSQL;
	char*	cpSQL = NULL;
	char	cpTemp[5];

	double	phi = 0;

	short	offset;

	int		i1, i2, i3, i4, i5, i6;
	int		j1, j2, j3, j4, j5, j6;
	int		i, k;
	int		i_index, j_index;
	int		N, M;
	int		temp;
	int shift;
	bool	blnFiveNbrFlag = false;

	// below only for current testing

	if(m_iTessFreq == 1)
		k = 12;
	else
		k = 2*(5*(m_iVertex-m_iTessFreq-1)+1)+10*(m_iVertex-2*m_iTessFreq-1);
		
	for(i=1; i<k-1; i++)
	{
		
		blnFiveNbrFlag = false;
		if (i==493)
			k = k;
		// for each node, select neighbors and assign to db
		qySES << "SELECT i_index, j_index, phi FROM tblNodes WHERE ID = " << i;
		resSES = qySES.store();
		rwSES = *resSES.begin();
		i_index = rwSES[0];
		j_index = rwSES[1];
		phi = rwSES[2];
		// determine offset (due to the geodesic nature of the dome, each row has 
		// significantly more j_index values than the row above it in the top section)
		//KAT: changed these a little bit b/c bottom pentagons do not always end up at exact angle measures
		if(phi>=0 && phi<71.990)
			offset = 0;
		else if(phi>=71.990 && phi<143.990)
			offset = 1;
		else if(phi>=143.990 && phi<215.990)
			offset = 2;
		else if(phi>=215.990 && phi<287.990)
			offset = 3;
		else
			offset = 4;
		// determine which section it lies in (top, middle, bottom)
		// since the base coordinate frame of robonaut has x=0 pointing down, (0,0) point on SES points down
		if(i_index <= m_iTessFreq)
		{
			// there are a few special cases to take care of here
			if (j_index == 0)	// if node is on 0 axis
			{
				if(i_index == m_iTessFreq) // has only five nbrs
				{
					i1=i_index-1;	i2=i3=i_index;	i4=i5=i_index+1;
					j1=0;	j2=i_index*5-1; j3=1; j4=i_index*5-1; j5=0;
					blnFiveNbrFlag = true;
				}
				else
				{
					i1=i_index-1;	i2=i3=i_index; i4=i5=i6=i_index+1;
					j1=0;	j2=i_index*5-1;	j3=1; j4=(i_index+1)*5-2; j5=j4+1; j6=0;
				}
			}
			else if(j_index == (i_index*5-1))	// if node is last index in row
			{
				if(i_index == m_iTessFreq)
				{
					i1=i2=i_index-1; i3=i4=i_index; i5=i6=i_index+1;
					j1=(i_index-1)*5-1;	j2=j4=0; j3=i_index*5-1; j5=j_index-1; j6=j_index;
				}
				else
				{
					i1=i_index-1; i2=i3=i_index; i4=i5=i6=i_index+1;
					j1=0;	j2=j_index-1; j3=0; j6=(i_index+1)*5-1; j4=j6-2; j5=j6-1;
				}
			}
			else if((int)phi%72 == 0)		// if node is on other axis
			{
				if(i_index == m_iTessFreq) // has only five nbrs
				{
					i1=i_index-1;	i2=i3=i_index;	i4=i5=i_index+1;
					j1=(i_index-1)*offset;	j2=j_index-1; j3=j_index+1;
					j4=j_index-1;	j5=j_index; 
					blnFiveNbrFlag = true;
				}
				else
				{
					i1=i_index-1; i2=i3=i_index;	i4=i5=i6=i_index+1;
					j1=(i_index-1)*offset; j2=j_index-1; j3=j_index+1;
					j5=(i_index+1)*offset; j4=j5-1;		j6=j5+1;
				}
			}
			else	// all other nodes
			{
				temp = j_index-(i_index*offset);
				i1=i2=i_index-1;	i3=i4=i_index;	i5=i6=i_index+1;
				j2=(i_index-1)*offset+temp;	j1=j2-1; j3=j_index-1; j4=j_index+1;
				if(i_index == m_iTessFreq)
				{
					j5=j_index-1;	j6=j_index;
				}
				else
				{
					j5=(i_index+1)*offset+temp; j6=j5+1;
				}
			}
		}
		else if(m_iTessFreq < i_index && i_index < m_iTessFreq*2)	// else is in middle section
		{
			i1=i2=i_index-1;	i3=i4=i_index;	i5=i6=i_index+1;

			if(((m_iTessFreq%2==0)&&(i_index%2==0)) || ((m_iTessFreq%2!=0)&&(i_index%2!=0)))
			{
				if(j_index == 0)		// account for zero and last indices
				{
					j1=j3=j5=m_iTessFreq*5-1; j2=j6=j_index; j4=j_index+1;
				}
				else if(j_index == m_iTessFreq*5-1)
				{
					j1=j3=j5=j_index-1; j2=j6=j_index; j4=0;
				}
				else
				{
					j1=j3=j5=j_index-1;	j2=j6=j_index;	j4=j_index+1;
				}
				
			}
			else
			{
				if(j_index==0)
				{
					j1=j5=j_index;	j2=j4=j6=j_index+1;	j3=m_iTessFreq*5-1;
				}
				else if(j_index==m_iTessFreq*5-1)
				{
					j1=j5=j_index;	j2=j4=j6=0;	j3=j_index-1;
				}
				else
				{
					j1=j5=j_index;	j2=j4=j6=j_index+1;	j3=j_index-1;
				}
			}
		}
		//Kat: changed a lot in the code below from the original version.  
		//code seems to assign all neighbors properly now
		else	// else is in bottom section
				
		{
				
			if(j_index==0)
			{
				if(i_index == m_iTessFreq*3-1)		//if last bottom pentagon
				{
					i1 =i2 = i3 = i_index-1; i4=i5 = i_index; i6 = i_index+1;
					j1 = 0; j2 = 1; j3 = 2; j4 = (3*m_iTessFreq-i_index)*5-1;
					j5 = 1; j6 = 0;
				}
					
				else
				{
					i1 = i2 = i_index-1; i3 = i4 = i_index; i5 = i6 = i_index+1;

					if (i_index==m_iTessFreq*2)				//if at 2nd row of 5 pentagons
					{
						j1=(3*m_iTessFreq-(i_index))*5-1; j2=0; j3 = (3*m_iTessFreq-(i_index))*5-1;
						j4 = 1; j5 = (3*m_iTessFreq-(i_index+1))*5-1; j6 = 1;

					}
					
					//if tess and row are both even or both odd:
					else if((m_iTessFreq%2==0 && i_index%2==0) || (m_iTessFreq%2!=0 && i_index%2!=0))
					{
						j1=(3*m_iTessFreq-(i_index-1))*5-1; j2=0; j3 = (3*m_iTessFreq-(i_index))*5-1;
						j4 = 1; j5 = (3*m_iTessFreq-(i_index+1))*5-1; j6 = 1;
						
					}
					else
					{
						j1 = 0; j2 = 1; j3 = (3*m_iTessFreq-(i_index))*5-1;
						j4 = 1;	j5 = 0; j6 = 1;
					}
				}

			}
			else if(j_index==(3*m_iTessFreq-i_index)*5-1) //last j in the row
			{
				if(i_index == m_iTessFreq*3-1)		//if last bottom pentagon
				{
					i1 =i2 = i3 = i_index-1; i4=i5 = i_index; i6 = i_index+1;
					j1 = (3*m_iTessFreq-(i_index-1))*5-2; j2 = (3*m_iTessFreq-(i_index-1))*5-1;
					j3 = 0; j4 = (3*m_iTessFreq-(i_index))*5-2; j5 = 0; j6 = 0;
				}
				else
				{

					i1 = i2 = i_index-1; i3 = i4 = i_index; i5 = i6 = i_index+1;
				
					if (i_index ==m_iTessFreq*2) //if at 2nd row of 5 pentagons
					{
						j1=(3*m_iTessFreq-(i_index))*5-2;  j2 =(3*m_iTessFreq-(i_index))*5-1;
						j3 = (3*m_iTessFreq-(i_index))*5-2; j4 = 0;
						j5 = (3*m_iTessFreq-(i_index+1))*5-2; j6 = (3*m_iTessFreq-(i_index+1))*5-1;

					}
					
					//if tess and row are both even or both odd:
					else if((m_iTessFreq%2==0 && i_index%2==0) || (m_iTessFreq%2!=0 && i_index%2!=0))
					{
						j1=(3*m_iTessFreq-(i_index-1))*5-2; j2=(3*m_iTessFreq-(i_index-1))*5-1;
						j3 = (3*m_iTessFreq-(i_index))*5-2; j4 = 0;
						j5 = (3*m_iTessFreq-(i_index+1))*5-2; j6 = (3*m_iTessFreq-(i_index+1))*5-1;
					}
					else
					{
						j1 = (3*m_iTessFreq-(i_index-1))*5-1; j2 = 0;
						j3 = (3*m_iTessFreq-(i_index))*5-2;	j4 = 0;
						j5 = (3*m_iTessFreq-(i_index+1))*5-1; j6 = 0;
					}
				}

			}
			//else if((int)phi%72 == 0)  //KAT: changed incorrect for bottom triangles
			else if ((int)(phi+36)%72==0)
			{
				if(i_index == m_iTessFreq*2) // has only five nbrs
				{
					i1=i2=i_index-1;	i3=i4=i_index;	i5=i_index+1;
					j1=j3=j_index-1; j2=j_index; j4=j_index+1; 
					j5=(m_iTessFreq*3-(i_index+1))*offset;
					blnFiveNbrFlag = true;
				}
				else
				{
					shift = floor((m_iTessFreq-(i_index-1-(m_iTessFreq*2)))/2);
					i1=i2=i3=i_index-1;	i4=i5=i_index;	i6=i_index+1;
					j2=(3*m_iTessFreq-(i_index-1))*offset+shift;	j1=j2-1;	j3=j2+1;
					j4=j_index-1;	j5=j_index+1;	j6=(3*m_iTessFreq-(i_index+1))*offset+shift-1;
				}
			}
			else
			{
				temp = j_index-(3*m_iTessFreq-i_index)*offset;
				i1=i2=i_index-1;	i3=i4=i_index;	i5=i6=i_index+1;
				j3=j_index-1; j4=j_index+1; 

				j6=(3*m_iTessFreq-(i_index+1))*offset+temp;	j5=j6-1;

				if(i_index == m_iTessFreq*2)
				{
					if((m_iTessFreq%2==0 && i_index%2==0) || (m_iTessFreq%2!=0 && i_index%2!=0))
					{
						j1=j_index-1;	j2=j_index;
					}
					else
					{
						j1 = j_index;	j2 = j_index+1;
					}
				}
				else
				{
					//if even tessellation and i_index
					if((m_iTessFreq%2==0 && i_index%2==0) || (m_iTessFreq%2!=0 && i_index%2!=0))
					{	
						j2=(3*m_iTessFreq-(i_index-1))*offset+temp;  j1=j2-1;
						
					}
					//if odd i_index
					else
					{
						j1=(3*m_iTessFreq-(i_index-1))*offset+temp;	j2=j1+1;
					}
				}
			
			}
		}
		
		if(blnFiveNbrFlag)
		{
			// now query for the id's of the neighbors
			qySES << "SELECT ID FROM tblNodes WHERE (i_index = " << i1 << " AND j_index = " << j1 
				<< ") OR (i_index = " << i2 << " AND j_index = " << j2 << ") OR (i_index = " 
				<< i3 << " AND j_index = " << j3 << ") OR (i_index = " << i4 << " AND j_index = " 
				<< j4 << ") OR (i_index = " << i5 << " AND j_index = " << j5 <<	")";
		}
		else
		{
			// now query for the id's of the neighbors
			qySES << "SELECT ID FROM tblNodes WHERE (i_index = " << i1 << " AND j_index = " << j1 
				<< ") OR (i_index = " << i2 << " AND j_index = " << j2 << ") OR (i_index = " 
				<< i3 << " AND j_index = " << j3 << ") OR (i_index = " << i4 << " AND j_index = " 
				<< j4 << ") OR (i_index = " << i5 << " AND j_index = " << j5 <<	") OR (i_index = " 
				<< i6 << " AND j_index = " << j6 << ")";
		}

		// store the query
		resSES = qySES.store();

		// for each neighbor nodes, store the proper ID
		_itoa(i, cpTemp, 10);
		cstrSQL.Insert(0, cpTemp);
		cstrSQL.Insert(0, " WHERE ID = ");
		M = 1;
		for(R=resSES.begin(); R<resSES.end(); R++)
		{
			rwSES = *R;
			N = rwSES[0];
			_itoa(N, cpTemp, 10);
			cstrSQL.Insert(0, cpTemp);
			cstrSQL.Insert(0, " = ");
			_itoa(M, cpTemp, 10);
			cstrSQL.Insert(0, cpTemp);
			if(blnFiveNbrFlag && M!= 5)
				cstrSQL.Insert(0, ", N");

			else if(blnFiveNbrFlag && M == 5)
			{
				//to make 6th neighbor -1 for table (Kat)
			    cstrSQL.Insert(0, ", N");
				_itoa(-1, cpTemp, 10);
				cstrSQL.Insert(0,cpTemp);
				cstrSQL.Insert(0, " = ");
				_itoa(6,cpTemp, 10);
				cstrSQL.Insert(0,cpTemp);
				
			}
			else if (!blnFiveNbrFlag && M!=6)
				cstrSQL.Insert(0, ", N");
			M++;
		}
		cstrSQL.Insert(0, "UPDATE tblNodes SET N");
		cpSQL = cstrSQL.GetBuffer(1);
		
		qySES.execute(cpSQL);
		cpSQL = NULL;
		cstrSQL.ReleaseBuffer();
		cstrSQL.Empty();
	}

	// now do top and bottom poles
	cstrSQL.Insert(0, "UPDATE tblNodes SET N1 = 1, N2=2, N3 = 3, N4 = 4, N5 = 5, N6 = -1 WHERE ID = 0");
	cpSQL = cstrSQL.GetBuffer(1);
	qySES.execute(cpSQL);
	cpSQL = NULL;
	cstrSQL.ReleaseBuffer();
	cstrSQL.Empty();

	j1 = k-2;
	j2 = k-3;
	j3 = k-4;
	j4 = k-5;
	j5 = k-6;
	N = k-1;
	_itoa(N, cpTemp, 10);
	cstrSQL.Insert(0, cpTemp);
	cstrSQL.Insert(0, " WHERE ID = ");
	_itoa(-1, cpTemp, 10);
	cstrSQL.Insert(0, cpTemp);
	cstrSQL.Insert(0, ", N6 = ");
	_itoa(j5,cpTemp, 10); 
	cstrSQL.Insert(0, cpTemp);
	cstrSQL.Insert(0, ", N5 = "); 
	_itoa(j4, cpTemp, 10);   
	cstrSQL.Insert(0, cpTemp);
	cstrSQL.Insert(0, ", N4 = ");
	_itoa(j3, cpTemp, 10);
	cstrSQL.Insert(0, cpTemp);
	cstrSQL.Insert(0, ", N3 = ");
	_itoa(j2, cpTemp, 10);
	cstrSQL.Insert(0, cpTemp);
	cstrSQL.Insert(0, ", N2 = ");
	_itoa(j1, cpTemp, 10);
	cstrSQL.Insert(0, cpTemp);
	cstrSQL.Insert(0, "UPDATE tblNodes SET N1 = ");

	cpSQL = cstrSQL.GetBuffer(1);
	qySES.execute(cpSQL);
	cpSQL = NULL;
	cstrSQL.ReleaseBuffer();
	cstrSQL.Empty();

//	TRACE0("emptied and released sql buffer\n");
	return true;

}

bool CCreateNewSES::CreateTables()
{
	Query	qySES = m_dbconnSES->query();
	char*	cpSQL = NULL;

	cpSQL = new char [300];
	strcpy(cpSQL, "CREATE TABLE tblSES (ID int NOT NULL default -1, name text NOT NULL, type text NOT NULL, identifier text, timestamp datetime NOT NULL, pan double NOT NULL default 0.000, tilt double NOT NULL default 0, left_pan double NOT NULL default 0, right_pan double NOT NULL default 0, image_name text)");
	if(qySES.exec(cpSQL))
	{
		return true; //inserted (don't need other tables for now for ISAC)
	/*	cpSQL = NULL;
		cpSQL = new char [100];
		strcpy(cpSQL, "CREATE TABLE tblObjects (name text NOT NULL, identity text NOT NULL)");
		if(qySES.exec(cpSQL))
		{
			cpSQL = NULL;
			cpSQL = new char [500];
			strcpy(cpSQL, "CREATE TABLE tblPosition (ID int NOT NULL default -1, name text NOT NULL, type text NOT NULL, w1 double NOT NULL, w2 double NOT NULL, w3 double NOT NULL, w4 double NOT NULL, w5 double NOT NULL, w6 double NOT NULL, w7 double NOT NULL, w8 double NOT NULL, w9 double NOT NULL, w10 double NOT NULL, w11 double NOT NULL, w12 double NOT NULL, w13 double NOT NULL, w14 double NOT NULL, w15 double NOT NULL, w16 double NOT NULL, h1 double NOT NULL, h2 double NOT NULL, h3 double NOT NULL, h4 double NOT NULL, h5 double NOT NULL, h6 double NOT NULL, h7 double NOT NULL, h8 double NOT NULL, h9 double NOT NULL, h10 double NOT NULL, h11 double NOT NULL, h12 double NOT NULL, h13 double NOT NULL, h14 double NOT NULL, h15 double NOT NULL, h16 double NOT NULL, la1 double NOT NULL, la2 double NOT NULL, la3 double NOT NULL, la4 double NOT NULL, la5 double NOT NULL, la6 double NOT NULL, la7 double NOT NULL, la8 double NOT NULL, la9 double NOT NULL, la10 double NOT NULL, la11 double NOT NULL, la12 double NOT NULL, la13 double NOT NULL, la14 double NOT NULL, la15 double NOT NULL, la16 double NOT NULL, ra1 double NOT NULL, ra2 double NOT NULL, ra3 double NOT NULL, ra4 double NOT NULL, ra5 double NOT NULL, ra6 double NOT NULL, ra7 double NOT NULL, ra8 double NOT NULL, ra9 double NOT NULL, ra10 double NOT NULL, ra11 double NOT NULL, ra12 double NOT NULL, ra13 double NOT NULL, ra14 double NOT NULL, ra15 double NOT NULL, ra16 double NOT NULL)");
			if(qySES.exec(cpSQL))
			{
				cpSQL = NULL;
				cpSQL = new char [300];
				strcpy(cpSQL, "CREATE TABLE tblWaist (w1 double NOT NULL, w2 double NOT NULL, w3 double NOT NULL, w4 double NOT NULL, w5 double NOT NULL, w6 double NOT NULL, w7 double NOT NULL, w8 double NOT NULL, w9 double NOT NULL, w10 double NOT NULL, w11 double NOT NULL, w12 double NOT NULL, w13 double NOT NULL, w14 double NOT NULL, w15 double NOT NULL, w16 double NOT NULL, timestamp datetime NOT NULL)");
				if(qySES.exec(cpSQL))
				{
					cpSQL = NULL;
					cpSQL = new char [200];
					strcpy(cpSQL, "CREATE TABLE tblHistory (ID int NOT NULL default 0, name text NOT NULL, type text NOT NULL, identity text NOT NULL, timestamp datetime NOT NULL, originating_joint text NOT NULL)");
					if(qySES.exec(cpSQL))
					{
						cpSQL = NULL;
						cpSQL = new char [100];
						strcpy(cpSQL, "CREATE TABLE tblLims (name text  NOT NULL, orientation double  NOT NULL default 0)");
						if(qySES.exec(cpSQL))
							return true;
						else
							return false;
					}
					else 
						return false;
				}
				else 
					return false;
			}
			else
				return false;
		}
		else 
			return false; */
	}
	else
		return false;

	delete cpSQL;

}

bool CCreateNewSES::MakeNewSES(int Tessellation)
{
	m_iTessFreq = Tessellation;
	if(CheckCurrentTables())
	{
		
		if(CreateNewNodes())
		{
			
			if(CreateTables())
			{
				ShiftIndices();
				AssignNeighbors();
				return true;
			}
			else
			{
				
				return false;
			}
		}
		else
			return false;
	}
	else
		return false;

}
