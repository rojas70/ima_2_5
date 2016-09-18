// CreateNewSES.h: interface for the CCreateNewSES class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CREATENEWSES_H__2D1B88AA_F2E2_4F5F_A9BB_2C6B899EB6D2__INCLUDED_)
#define AFX_CREATENEWSES_H__2D1B88AA_F2E2_4F5F_A9BB_2C6B899EB6D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ctime>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "mysql++"
#include "custom.hh"
#include "custom-macros.hh"


//const double RAD_TO_DEG = 57.2957795130824;
//const double DEG_TO_RAD = .0174532925199433;

using namespace std;

class CCreateNewSES  
{

public:
	float m_fRadToDeg;
	float m_fDegToRad;
	bool AssignNeighbors();
	bool ShiftIndices();
	bool m_blnFlag;
	bool CreateNew();
	bool CheckCurrentTables();
	bool CCreateNewSES::CreateNewNodes();
	bool CCreateNewSES::CreateTables();
	bool CCreateNewSES::MakeNewSES(int Tessellation);
	double RotatePhi(double phi, double phi1, double theta1, double theta2);
	double RotateTheta(double phi, double phi1, double theta, double theta1);

	int m_iTessFreq;
	int	m_iVertex;
	
	CCreateNewSES();
	virtual ~CCreateNewSES();

	struct SphereCoord{
		//vertex coordinates: 0,0,0 equals zenith
		long x_prime;
		long y_prime;
		long z_prime;
	};

	//structure containing vertex indices
	struct SphereIndices{
		//vertex labels: 0,0 equals zenith
		long i_index;
		long j_index;
	};

	//structure defines geodesic coordinate points in phi, theta format
	struct EgoCoord{
		//vertex spherical coordinates - This is the main data structure
		double phi;
		double theta;
		double radius;
	};

protected:
	Connection* m_dbconnSES;

};

#endif // !defined(AFX_CREATENEWSES_H__2D1B88AA_F2E2_4F5F_A9BB_2C6B899EB6D2__INCLUDED_)
