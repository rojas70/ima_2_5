///////////////////////////////////////////////////////////////
// IMA2_FTSensorLib
///////////////////////////////////////////////////////////////
//
//  Originally created by Anthony Alford on Jun, 1997
//
// CFTSensor class
// The force/torque wrapper class. 
// This class is threaded.  Its thread function updates its current force/torque values

/*	The class has data members which represent:
	 - the current force/torque in the current frame
	 - the current frame (w.r.t. the origin of the sensor
	 - force/torque peaks
	 - moving average length

	 - commport object

	The class has operations which:
	 - Set the current frame
	 - Get the current frame

	 - Get the current force/torque reading
	 - Get force/torque peaks

	 - Bias/Unbias sensor readings
	 - Enable/Disable peak detection
	 - Clear stored peaks
	 - Set moving average length
	 - Get moving average length


Calibration Information

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

class CCommPort;

class CFTSensor {

private:

	// FT Data
	double m_pfCurrentFT[6];
	double m_pfCurrentFrame[6];

	// Peak Data
	double m_pfMaxFT[6];
	double m_pfMinFT[6];
	BOOL m_bPeaksEnabled;

	// Thread Info
	BOOL m_bThread;
	BOOL m_bThreaded;
	BOOL m_bTerminateSensorThread;
	HANDLE m_hSensorThread;

	// Misc
	int m_nAverageMovingLength;
	int m_nSampleWaitTime;

public:
	CCommPort *m_pPort;
	
	// Methods
	CFTSensor();
	CFTSensor(char * sCommName, BOOL bInit=TRUE, BOOL bThread=TRUE, int nWait=50);
	CFTSensor(char * sCommName, double pfFrame[6], BOOL bInit=TRUE, BOOL bThread=TRUE, int nWait=50);

	~CFTSensor();

	void InitSensor();

	// FT Data
	void GetFT(double pfFT[6]);								// Returns last sensor smample: Fx,Fy,Fz,Tx,Ty,Tz,
	int SampleFT(double pfFT[6]);							// Queries sensor

	// Frames
	void SetFrame(double pfFrame[6]);						// Fx, Fy, Fz, Tx, Ty, Tz
	void GetFrame(double pfFrame[6]);						// as above

	// Peaks
	void EnablePeaks(BOOL bPeak);							// True for enabling, false for diabling
	void SampleFTPeaks(double pfMaxFT[6], double pfMinFT[6]);// Queries sensor
	BOOL GetFTPeaks(double pfFTMax[6],double pfFTMin[6]);	// Returns status of peak enabling
	BOOL ClearPeaks();										// Returns status of peak enabling

	// Average Length
	BOOL SetAverageLength(int nLen);						// nLen must be element of {0,2,4,8,16}, returns old value;
	int GetAverageLength();									// Returns length of moving average

	// Miscellaneous
	BOOL SendCommand(char * szCmd, char * szRet);			// Send commands to sensor
	void BiasSensor(BOOL bBias);							// True for biasing; false for unbiasing

};