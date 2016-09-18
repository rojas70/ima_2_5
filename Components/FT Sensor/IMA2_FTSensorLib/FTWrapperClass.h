// FTWrapperClass.h: interface for the CFTWrapperClass class.
//
// Class originally crated on Jun, 1997
// By Anthony Alford

// CFTWrapper class 
// This class is threaded.  
// Its thread function updates its current force/torque values

/*	The class has data members which represent:
	 - Force/Torque data:		the current force/torque in the current frame
	 - Frame:					the current frame (w.r.t. the origin of the sensor)
	 - Peaks:					force/torque peaks
	 - Moving average length
	 - Comm Port object

	The class has operations which:
	 - Set the current frame, useful to alighn the FT sensor to the coordinate axes of the robot.
	 - Get the current frame

	 - Get the current force/torque reading
	 - Get force/torque peaks

	 - Bias/Unbias sensor readings
	 - Enable/Disable peak detection
	 - Clear stored peaks
	 - Set moving average length
	 - Get moving average length

//	 Calibration Information

Left Calibration: Serial No. FT3642-3F

D774: FF7B0016 009113EE FFBDEBDA 00000000 00CEE8B3 002C0BB4 FFEE0B76 00000000
D794: DAEBFF2E DB3EFF5B DB38FF83 00000000 00F1F577 2A3C060A D65F04A1 00000000
D7B4: CF3EFF88 183AF6A5 18C909BA 00000000 FF6F1952 00541880 0043186D 00000000
D7D4: 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000

Right Calibration: Serial No. FT3643-3F

D774: FFBA0025 000214BA FF9AEAF5 00000000 003FE7FA 00640C16 FFFD0C02 00000000
D794: D96DFFDC DA0EFF5E DA67FF79 00000000 00BEF4B9 2BAA0654 D55D04F8 00000000
D7B4: CD8F0034 1933F631 19690A60 00000000 FF501A17 002D19A3 00BE199B 00000000
D7D4: 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
*/
//////////////////////////////////////////////////////////////////////
class CCommPort;
#include "CommPort1.h"											// Include defs for CCommPort Class

#if !defined(AFX_FTWRAPPERCLASS_H__6D77350C_E864_465D_B50A_F2D825C4D893__INCLUDED_)
#define AFX_FTWRAPPERCLASS_H__6D77350C_E864_465D_B50A_F2D825C4D893__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NUM_AXES 6
#define SZLen 2000
//////////////////////////////////////////////////////////////////////////////////////////////////////
class CFTWrapperClass  
{
public:
	int SetForceFormat();
	CCommPort* m_pPort;

	// Constructors
	CFTWrapperClass();
	CFTWrapperClass(char* sCommName, BOOL bInit=TRUE, BOOL bThread=TRUE, int nWait=50);
	CFTWrapperClass(char* sCommName, double pfFrame[NUM_AXES], BOOL bInit=TRUE, BOOL bThread=TRUE, int nWait=50);
	virtual ~CFTWrapperClass();

	// Methods
	// Initialization
	void InitSensor();

	// Frame 
	void SetFrame(double pfFrame[NUM_AXES]);						// Fx, Fy, Fz, Tx, Ty, Tz
	void GetFrame(double pfFrame[NUM_AXES]);

	// FT Info
	void GetFT(double m_pFT[NUM_AXES]);							// Returns Fx, Fy, Fz, Tx, Ty, Tz
	int SampleFT(double* m_pFT);							// Queries sensor

	// Peaks
	void EnablePeaks(BOOL bPeak);							// True for enabling, false for not
	void SampleFTPeaks(double pfMaxFT[NUM_AXES], double pfMinFT[NUM_AXES]);// Queries sensor
	BOOL GetFTPeaks(double m_pFTMax[NUM_AXES], double m_pFTMin[NUM_AXES]);// Return status of peak enabling
	BOOL ClearPeaks();										// Return status of peak enabling

	// Misc
	void BiasSensor(BOOL bBias);							// True for biasing, false for not

	BOOL SetAverageLength(int nLen);						// nLen must be an element of {0,2,4,8,16}. Returns old value.
	int  GetAverageLength();								// Returns length of moving average.

	BOOL SendCommand(char* szCmd, char* szRet);				// Send command to sensor

private:

	// Date Members
	double m_pfCurrentFT[NUM_AXES];			// FT data
	double m_pfCurrentFrame[NUM_AXES];		// Frame data

	// Peaks
	double m_pfMaxFT[NUM_AXES];
	double m_pfMinFT[NUM_AXES];

	// Misc parameters
	BOOL m_bThreaded;
	BOOL m_bPeaksEnabled;

	BOOL m_bThread;
	BOOL m_bTerminateSensorThread;

	int m_nAverageMovingLength;
	int m_nSampleWaitTime;

	HANDLE m_hSensorThread;

};

#endif // !defined(AFX_FTWRAPPERCLASS_H__6D77350C_E864_465D_B50A_F2D825C4D893__INCLUDED_)
