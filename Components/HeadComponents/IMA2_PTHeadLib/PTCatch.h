// PTCatch.h : Declaration of the CPTCatch

#ifndef __PTCATCH_H_
#define __PTCATCH_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\MultiTypeComponents\IMA2_BasicComponentsLib\IMA2_BasicComponentsLib.h"		//VectorSignal functionality
#include "commport.h"
#include <cstring>

#define ACCELERATION 4250	// max value 8500
#define SPEED        1450	// max value 2900
/////////////////////////////////////////////////////////////////////////////
// CPTCatch
class ATL_NO_VTABLE CPTCatch : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPTCatch, &CLSID_PTCatch>,
	public IDispatchImpl<IPTCatch, &IID_IPTCatch, &LIBID_IMA2_PTHEADLIBLib>,
	public CComponentImpl 
{
public:
/******************************************************************************

Name:			CPTCatch Component Constructor

Purpose:		Revised 'Catch' class to operate 2 Pan-Tilt units. 

Created By:		Li SUN		- li.sun@vanderbilt.edu
Revised By:		JUAN ROJAS  - juan.rojas@vanderbilt.edu

Date Modified:	Friday, March 21, 2003
Revise Date:	Tuesday, April 6, 2005

*******************************************************************************/

	CPTCatch() :
		// *** Note: If you want to change the command packet layout, then
		// you need to change these next 4 constants!
				
				LEFT_PAN(0),			// index of the left pan motor in the arrays
				LEFT_TILT(1),			// index of the left tilt motor in the arrays
				RIGHT_PAN(2),			// index of the right pan motor in the arrays
				RIGHT_TILT(3),			// index of the right tilt motor in the arrays
	
				NUM_AXES(6),			// # axes on the left/right pan-tilt units currently.
				//NUM_AXES_ALL(6),			// # axes on the Left/right pan-tilt units and overall pan-tilt.
		
				COMMAND_PAN_ABS("pp"),	// string which indicates you are sending a command to the pan motor.
				COMMAND_TILT_ABS("tp"),	// string which indicates you are sending a command to the tilt motor.
				COMMAND_PAN_REL("po"),	// string which commands pan relative
				COMMAND_TILT_REL("to"),	// string which commands tilt relative

				QUERY_PAN("pp"),		// get the pan position
				QUERY_TILT("tp"),		// get the tilt position
				QUERY_MIN_PAN("pn"),	// get min pan limit
				QUERY_MAX_PAN("px"),	// get max pan limit
				QUERY_MIN_TILT("tn"),	// get min tilt limit
				QUERY_MAX_TILT("tx"),	// get max tilt limit
				QUERY_PAN_SPEED("ps"),	// get pan speed
				QUERY_TILT_SPEED("ts"),	// get tilt speed
				QUERY_PAN_ACCEL("pa"),	// get pan acceleration
				QUERY_TILT_ACCEL("ta"),	// get tilt acceleration

				SET_PAN_ACCEL("pa"),	// set pan acceleration
				SET_TILT_ACCEL("ta"),	// set tilt acceleration
				SET_PAN_SPEED("ps"),	// set pan speed
				SET_TILT_SPEED("ts"),	// set tilt speed

				HALT_ALL("h"),			// stop all pan-tilt unit
				RESET("r"),				// reset the pan-tilt unit
				RESTORE_DEFAULTS("df"),	// restore factory default settings
				DISABLE_LIMITS("ld"),	// disable limits on DP head.

				SYNC_DP("a"),			// allow last DP command to finish
				TERSE_FEEDBACK("ft"),	// no wordy responses, Newman.
				DISABLE_ECHO("ed"),		// don't echo commands we send.
				
				// DP PAN
				MOTOR_RANGE_ANGLES_PAN(318.0f),			// pan angle range	
				MOTOR_RANGE_PULSES_PAN_LEFT(6184.0),	// pulses in left servo's range
				MOTOR_RANGE_PULSES_PAN_RIGHT(6178.0),	// pulses in right servo's range
				PULSE_TO_ANG_PAN_LEFT((double) (MOTOR_RANGE_ANGLES_PAN/MOTOR_RANGE_PULSES_PAN_LEFT)),
				PULSE_TO_ANG_PAN_RIGHT((double) (MOTOR_RANGE_ANGLES_PAN/MOTOR_RANGE_PULSES_PAN_RIGHT)),

    			// DP Tilt
				MOTOR_RANGE_ANGLES_TILT(106.0f),	// tilt angle range	
				MOTOR_RANGE_PULSES_TILT(2061.0f),	// pulses in servo's range
				PULSE_TO_ANG_TILT((double) (MOTOR_RANGE_ANGLES_TILT/MOTOR_RANGE_PULSES_TILT))				
	{
		// TODO: Initialize all variables
		m_bTiltFlag					= true;
		m_pdAxisGain				= NULL;
		m_pdAxisOffset				= NULL;
		m_plAxisThreshold			= NULL;

		m_plCurrentSample			= NULL;
		m_dDesiredHeadAngles	= NULL;
		m_dCurrentHeadAngles	= NULL;
		m_pdLinkOldHeadCommand		= NULL;	
		m_pdLinkOldHeadSample		= NULL;	

		m_pIUnkHeadAnglesOut		= NULL;
		m_pIUnkHeadAnglesIn			= NULL;
		
		pCommLEFT					= NULL;
	    pCommRIGHT					= NULL;
		m_psOut						= NULL;

		m_pdBuffer					= NULL;
		m_bFirstCue					= false;

		m_iFlagCue					= 0;

		m_pdBuff1					= new double[4];
		m_pdBuff2					= new double[4];
		m_pdBuff3					= new double[4];

		for (int i=0; i<4; i++) 
		{
			m_pdBuff1[i] = 0;
			m_pdBuff2[i] = 1;
			m_pdBuff3[i] = 2;
		}

		// Setup class variables to appropriate sizes

		if ( NUM_AXES > 0 )
		{			
			m_psOut				= new long[NUM_AXES];
			m_plAxisThreshold	= new long[NUM_AXES];
			m_pdAxisGain		= new double[NUM_AXES];
			m_pdAxisOffset		= new double[NUM_AXES];

			
			m_dDesiredHeadAngles = new double[NUM_AXES];
			
			// new head will display 2 more values: representing a 
			// overall pan and tilt value for both cameras
			m_dCurrentHeadAngles	= new double[NUM_AXES];  
			m_plCurrentSample			= new long[NUM_AXES];

			// Two missing pointers were noticed not having been allocated
			// It is done here:
			m_pdLinkOldHeadCommand	= new double[NUM_AXES];  
			m_pdLinkOldHeadSample	= new double[NUM_AXES];
		}


		// Initialize axis gains, offsets, and indecexs
		for (i = 0; i < NUM_AXES; i++ ) 
		{
			m_pdAxisGain[i]			= 1.0;
			m_pdAxisOffset[i]		= 0.0;
			m_plAxisThreshold[i]	= 0;
		}
		
		m_iAxisOffsetIndex			= 0;
		m_iAxisThresholdIndex		= 0;
		m_iAxisGainIndex			= 0;
		m_iPanLimitIndex			= 0;
		m_iTiltLimitIndex			= 0;
		
		// Setup default values for motors and communications parameters

		m_plCurrentSample[ LEFT_PAN  ] = 0;
		m_plCurrentSample[ LEFT_TILT ] = 0;
		m_plCurrentSample[ RIGHT_PAN ] = 0;
		m_plCurrentSample[ RIGHT_TILT] = 0;

		m_bsDevFilename1	= "\\COM1";
		m_bsDevFilename2	= "\\COM2";
		m_bsCParam1			= "";
		m_bsCParam2			= "";

	//////////////////////////////////	//////////////////////////////////
	// Connect to COMM Ports, set specifications for cameras: feedback, speed, acceleration, etc.
	// Move head to the home position 
	//////////////////////////////////	//////////////////////////////////

	USES_CONVERSION;
	
	if ( pCommLEFT == NULL ) {

		// COM1 port
		char* pFN1	= OLE2T(m_bsDevFilename1);
		pCommLEFT	= new CCommPort( pFN1, 9600 );	// Capture COM1@9600baud
	}

	if ( pCommRIGHT == NULL ) {

		// COM2 port.
		char* pFN2 = OLE2T(m_bsDevFilename2);
		pCommRIGHT	= new CCommPort( pFN2, 9600 );	// Capture COM2@9600baud
	}

	for ( int axis_index = 0; axis_index < NUM_AXES; axis_index++ )
		m_psOut[ axis_index ] = 0;

	// Re-initialize pan-tilt unit
	char strOut[35];
	BOOL commResult1 = FALSE;
	BOOL commResult2 = FALSE;

	// It won't hurt to set these commands each time this is called.

	// Enable terse feedback
	sprintf( strOut, "%s ", TERSE_FEEDBACK );
	
	commResult1 = SendToPTLeft( strOut );
	commResult2 = SendToPTRight( strOut );

	if ( commResult1 && commResult2 ) {

		// Disable DP head limits on startup
		sprintf( strOut, "%s ", DISABLE_LIMITS );
		commResult1 = SendToPTLeft( strOut );
	    commResult2 = SendToPTRight( strOut );

		if ( commResult1 && commResult2 ) {

			// Disable command echo
			sprintf( strOut, "%s ", DISABLE_ECHO );
			commResult1 = SendToPTLeft( strOut );
			commResult2 = SendToPTRight( strOut );

			double val[4];

			for ( int i = 0; i < NUM_AXES; i++ )
				val[i] = 0;
			
			// Set to the home position
			commResult1 = CommandHeadAbsolute(val,NUM_AXES);
		}

		else {
			ATLTRACE("****** CCatch::FinalComponentInit() -- Writing to COMM FAILED!\n" );
			MessageBox(NULL,"CPT_Catch::Constructor Failed","Writing to COMM Failed",MB_OK);
		}
	}

	else {
		ATLTRACE("****** CCatch::FinalComponentInit() -- Writing to COMM FAILED!\n" );
		MessageBox(NULL,"CPT_Catch::Constructor Failed","Writing to COMM Failed",MB_OK);
	}

	// Set new speed and accel for pan&tilt
	put_LeftPanAccel((long)ACCELERATION);
	put_RightPanAccel((long)ACCELERATION);

	put_LeftPanSpeed((long)SPEED); // 2900
	put_RightPanSpeed((long)SPEED);

	put_LeftTiltAccel((long)ACCELERATION);
	put_RightTiltAccel((long)ACCELERATION);

	put_LeftTiltSpeed((long)SPEED);
	put_RightTiltSpeed((long)SPEED);
}


///////////////
// Desctructor
///////////////
~CPTCatch()
	{
		ATLTRACE("*********** Beginning CCatch::~CCatch() **********\n");
		
		if ( m_psOut != NULL )
			delete[] m_psOut;

		m_psOut = NULL;

		ATLTRACE("*** Deleting Commports ....");
		if ( pCommLEFT != NULL )
			delete pCommLEFT;
		pCommLEFT = NULL;
		ATLTRACE(" ... PT Left destroyed,");
		
		if ( pCommRIGHT != NULL )
			delete pCommRIGHT;
		pCommRIGHT = NULL;
		ATLTRACE(" PT Right destroyed ...\n");

		if ( m_pdAxisGain != NULL )
			delete[] m_pdAxisGain;
		m_pdAxisGain = NULL;

		if ( m_pdAxisOffset != NULL )
			delete[] m_pdAxisOffset;
		m_pdAxisOffset = NULL;

		if ( m_plAxisThreshold != NULL )
			delete[] m_plAxisThreshold;
		m_plAxisThreshold = NULL;

		if ( m_plCurrentSample != NULL )
			delete[] m_plCurrentSample;
		m_plCurrentSample = NULL;
ATLTRACE("*********** CCatch::~CCatch() Deleted Current Sample**********\n");


		if ( m_dDesiredHeadAngles != NULL )
			delete[] m_dDesiredHeadAngles;
		m_dDesiredHeadAngles = NULL;
ATLTRACE("*********** CCatch::~CCatch() Deleted Link Head Command**********\n");


		if ( m_dCurrentHeadAngles != NULL )
			delete[] m_dCurrentHeadAngles;
		m_dCurrentHeadAngles = NULL;
ATLTRACE("*********** CCatch::~CCatch() Deleted Link Head Sample**********\n");

	
ATLTRACE("*********** Finishing CCatch::~CCatch() **********\n");

}


DECLARE_REGISTRY_RESOURCEID(IDR_PTCATCH)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPTCatch)
	COM_INTERFACE_ENTRY(IPTCatch)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IPTCatch

public:
	STDMETHOD(Initialize)();
//	STDMETHOD(get_TiltLimitIndex)(/*[out, retval]*/ int *pVal);
//	STDMETHOD(put_TiltLimitIndex)(/*[in]*/ int newVal);
//	STDMETHOD(get_PanLimitIndex)(/*[out, retval]*/ int *pVal);
//	STDMETHOD(put_PanLimitIndex)(/*[in]*/ int newVal);
//	STDMETHOD(get_TiltLimit)(/*[out, retval]*/ long *pVal);
//	STDMETHOD(get_PanLimit)(/*[out, retval]*/ long *pVal);

	STDMETHOD(get_AxisThresholdIndex)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_AxisThresholdIndex)(/*[in]*/ int newVal);
	STDMETHOD(get_AxisThreshold)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_AxisThreshold)(/*[in]*/ long newVal);
	STDMETHOD(get_AxisGainIndex)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_AxisGainIndex)(/*[in]*/ int newVal);
	STDMETHOD(get_AxisGain)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_AxisGain)(/*[in]*/ double newVal);
	STDMETHOD(get_CommParams2)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_CommParams2)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_CommParams1)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_CommParams1)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_AxisOffsetIndex)(/*[out, retval]*/ int *pVal);
	STDMETHOD(put_AxisOffsetIndex)(/*[in]*/ int newVal);
	STDMETHOD(get_AxisOffset)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_AxisOffset)(/*[in]*/ double newVal);

	STDMETHOD(get_RightTiltAccel)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_RightTiltAccel)(/*[in]*/ long newVal);
	STDMETHOD(get_LeftTiltAccel)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_LeftTiltAccel)(/*[in]*/ long newVal);
	STDMETHOD(get_RightPanAccel)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_RightPanAccel)(/*[in]*/ long newVal);
	STDMETHOD(get_LeftPanAccel)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_LeftPanAccel)(/*[in]*/ long newVal);
	STDMETHOD(get_RightTiltSpeed)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_RightTiltSpeed)(/*[in]*/ long newVal);
	STDMETHOD(get_LeftTiltSpeed)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_LeftTiltSpeed)(/*[in]*/ long newVal);
	STDMETHOD(get_RightPanSpeed)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_RightPanSpeed)(/*[in]*/ long newVal);
	STDMETHOD(get_LeftPanSpeed)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_LeftPanSpeed)(/*[in]*/ long newVal);

	STDMETHOD(get_DeviceFilename2)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_DeviceFilename2)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_DeviceFilename1)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_DeviceFilename1)(/*[in]*/ BSTR newVal);

	// Callable Methods
	STDMETHOD(SampleHead)(/*[out]*/ SAFEARRAY* Val);
	STDMETHOD(CommandHeadAbsolute)(/*[in]*/SAFEARRAY* Val);

	STDMETHOD(aaHeadCommand)();
	STDMETHOD(aaHeadSample)();
	STDMETHOD(Reset)();
	STDMETHOD(Stop)();

private:

	// Internal Functions
	BOOL SendToPTRight( char* pStr );
	BOOL SendToPTLeft( char* pStr );
	BOOL DPSample();
	BOOL ExceedsThreshold( long, long );
	int ParseStringToInteger( char* pStr );

	bool IndexIsValid( long Index );
	bool CalculateOverallPanTilt(double* Val);
	
	void CalculateLeftRightAngles(double* Val1, double* Val2, double VergeAngle);  // convert old motor commands to our system 11/18/03 
	void CalculatePanTiltAngles(double* Val1, double* Val2);  // convert single pan to new head coordinates 1/04 
	
	HRESULT HeadPositions2Angles( double* pVal, long Length );
	HRESULT HeadAngles2Positions( double* pVal, long length );

	HRESULT SampleHead(double* Val, long Length);
	HRESULT CommandHeadAbsolute(double* Val, long Length);

	HRESULT CommandHeadRelative(double* Val, long Length);

	// IMA Component Links
	IComponent *m_pIUnkHeadAnglesOut;			// IComponent pointer for Angle Out representation
	IComponent *m_pIUnkHeadAnglesIn;			// IComponent pointer for Angle In representation
	IComponent *m_pIUnkHeadCommand;				// IComponent pointer for Command in representation
	IComponent *m_pIUnkHeadSample;				// IComponent pointer for Sample out representation
	// End IMA Component Links

	// constants useful for this class.
	// DP Pan
	const double	MOTOR_RANGE_ANGLES_PAN;	     // pan angle range	
	const double	MOTOR_RANGE_PULSES_PAN_LEFT; // pulses in left servo's range
	const double	MOTOR_RANGE_PULSES_PAN_RIGHT;// pulses in right servo's range
	const double	PULSE_TO_ANG_PAN_LEFT;
	const double	PULSE_TO_ANG_PAN_RIGHT;

	// DP Tilt
	const double	MOTOR_RANGE_ANGLES_TILT;	// tilt angle range	
	const double	MOTOR_RANGE_PULSES_TILT;	// pulses in servo's range
	const double	PULSE_TO_ANG_TILT;

	const long		NUM_AXES;					// how many axes does this pantilt have?
	
	const char*		COMMAND_TILT_REL;			// command for relative tilt motion
	const char*		COMMAND_PAN_REL;			// command for relative pan motion
	const char*		COMMAND_TILT_ABS;			// command for absolute tilt motion
	const char*		COMMAND_PAN_ABS;			// command for absolute pan motion

	const long		LEFT_PAN;				
	const long		LEFT_TILT;
	const long		RIGHT_PAN;
	const long		RIGHT_TILT;

	const char*		QUERY_TILT;					// get the tilt position
	const char*		QUERY_PAN;					// get the pan position

	const char*		QUERY_MIN_PAN;				// get min pan limit
	const char*		QUERY_MAX_PAN;				// get max pan limit	
	const char*		QUERY_MIN_TILT;				// get min tilt limit	
	const char*		QUERY_MAX_TILT;				// get max tilt limit
	const char*		QUERY_PAN_SPEED;			// get pan speed
	const char*		QUERY_PAN_ACCEL;			// get pan acceleration
	const char*		QUERY_TILT_SPEED;			// get tilt speed
	const char*		QUERY_TILT_ACCEL;			// get tilt acceleration

	const char*		SET_PAN_ACCEL;				// set pan acceleration
	const char*		SET_PAN_SPEED;				// set pan speed
	const char*		SET_TILT_ACCEL;				// set tilt acceleration	
	const char*		SET_TILT_SPEED;				// set tilt speed		

	const char*		HALT_ALL;					// stop the pan-tilt unit

	const char*		RESET;						// reset the pan-tilt unit	
	const char*		RESTORE_DEFAULTS;			// restore factory default settings	

	const char*		DISABLE_LIMITS;				// disable limits on DP head.
	const char*		DISABLE_ECHO;				// don't echo commands we send.

	const char*		SYNC_DP;					// allow last DP command to finish

	const char*		TERSE_FEEDBACK;				// no wordy responses, Newman.

   	// COMMPORT parameters
	CComBSTR		m_bsDevFilename2;			// Device filenames for 1 & 2
	CComBSTR		m_bsDevFilename1;
	CComBSTR		m_bsCParam2;				// Device parameters for 1 & 2
	CComBSTR		m_bsCParam1;

	bool			m_bTiltFlag;				// Used for the initialization call to tilt cameras
	
	double*			m_pdAxisGain;				// Axis gains
	double*			m_pdAxisOffset;				// Axis offsets

	double*			m_dDesiredHeadAngles;	// Data to be sent to motor units   (New PT Head)
	double*			m_dCurrentHeadAngles;	// Data to be read from motor units (New PT Head)
	long*			m_plAxisThreshold;			// Axis' threshold values. If (new_command - old_command) < threshold, 
												// then new_command will not be sent to that axis

	// Indeces for all array interface variables
	// Juan Rojas, April 05

	int				m_iAxisOffsetIndex;
	int				m_iAxisThresholdIndex;
	int				m_iAxisGainIndex;
	int				m_iPanLimitIndex;
	int				m_iTiltLimitIndex;
		
    // For the old signal vector 09/10/03
	double* m_pdLinkOldHeadCommand;				// Data to be sent to motor units   (Old PTV Head)
	double* m_pdLinkOldHeadSample;				// Data to be read from motor units (Old PTV Head)
											

	long*			m_plCurrentSample;
	long*			m_psOut;					// temp value

	CCommPort*		pCommLEFT;					// COM1 for Left pan/tilt control
	CCommPort*		pCommRIGHT;					// COM2 for right pan/tilt control

	bool			m_bFirstCue;				// Will be used as a flag to avg. sound Cues
	double*			m_pdBuffer;					// Stores data to be averaged later

	int				m_iFlagCue;					// Flag for median calculation
	double*			m_pdBuff1;					// Buffer to calculate median from three cues.
	double*			m_pdBuff2;
	double*			m_pdBuff3;

	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT
};

#endif //__PTCATCH_H_
