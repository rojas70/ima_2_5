// SESManager.h: interface for the SESManager class.
//
// derived from KAH's code
//////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
	#pragma once
#endif // _MSC_VER > 1000

#include "CImg.h"
  using namespace cimg_library;

#include <ctime>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <winsock.h>
#include "mysql.h"
#include "mysql++"
#include "custom.hh"
#include "custom-macros.hh"
//#include "DecayManager.h"

const double RAD_TO_DEG = 57.2957795130824;
const double DEG_TO_RAD = .0174532925199433;
const double PI = 3.14159265;

#define MAX_DATA_LENGTH 100
#define MAX_TEXT_LENGTH 32

#define UPDATE 1
#define POST   0


//Image center pixels (based on camera calibration)
const int CTR_R = 125;
const int CTR_C = 161;

//Focal Lengths
const double FOCAL_C = 307.97804;           //focal length (in pixels) in pan direction
const double FOCAL_R = 307.13756;           //focal length (in pixels) in tilt direction

//Pixel-per-degree Measures
const double PAN_PIXPERDEG = 6.072;
const double TILT_PIXPERDEG = 5.536;

// modes for salience assignment


class SESManager  
{

public:
	bool	DeleteByName		(char *Name);
	bool	RetrieveAtAngles	(float Phi, float Theta, char* Name, char* Type, char* Identifier, char* Time);
//	bool	Update				(char *Name, char* Type, char* Attribute, char* DataType, int DataSize, char** DataText, double* DataNums);
	bool	FindRecord			(char* Name);
	bool	RetrieveByIdentifier(char *Identifier, char *Type, double* Phi, double* Theta, char *Name);

//  New Functions
	int		PostImg				(char *Name, char *Type, char *Identifier, double Pan, double Tilt, char *Image_Name);
	bool	DumpAllData			();
	bool	PostAttnPts			(CImg<double>* salientPts, int nodeID);	//posts FGate results
CImg<double>* CalculateSalience (int N);		//Returns the N most salient locations on the SES
	void	ReturnFOA(double* mostSalientarray);						//like CalculateSalience but only returns FOA + pan/tilt angles 
CImg<double> ReturnNodeList(double dPanLo, double dPanHi, double dTiltLo, double dTiltHi);	//returns list of nodes within range
	
	//maybe write an Update function
	

	SESManager();
	virtual ~SESManager();

	//If you don't want to use default connection, you can disconnect and Reconnect using the following functions
	void Disconnect();
	void Connect(char* dbName, char* Server, char* Username);

protected:
	double	*m_returnNum;
	int		m_returnNumSize;
	char	**m_returnText;
	int		m_returnTextSize;
	int		m_iTessFreq;

	int*	AnglesToIndices		(float AnglePhi, float AngleTheta);
	void	IndicesToAngles		(int I, int J);

	int CopyTextValue(Row &r, int size, char *data);		// returns number of strings copied
	int CopyNumValue(Row &r, int size, double *data);		// returns number numbers copied

	Connection	*m_connSES;
	
	char* dbName;
	char* Server;
	char* Username;

//	CDecayManager*	m_Decay;
};


