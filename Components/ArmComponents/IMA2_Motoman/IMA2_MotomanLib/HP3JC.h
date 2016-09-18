// HP3JC.h : Declaration of the CHP3JC

#ifndef __HP3JC_H_
#define __HP3JC_H_

#include "stdafx.h"
#include "resource.h"     
#include <stdlib.h>  							// main symbols
#include "O:\Base Classes\ComponentImpl.h"		// Component Lib file
#include "O:\Components\msvbvm60.tlh"			// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h" // Vector signal
#include "O:\Include\IMA2_MatlabStateMachineLib.h"// Matlab state machine
#include "O:\Include\IMA2_TextQueueLib.h"		// TextQueue
#include "O:\Include\Motoman\MotoCom.h"			// Motoman declarations


// Serial Communication standard data
#define SERIAL		0x01						// Defines communication type (serial or ethernet). See BscOpen 
#define ETHERNET	0x10						// Hex value 10, decimal value 16. Necessary for ethernet connection.
#define COM1		1							// Define port number
#define COM2		2
#define BRATE		9600						// Define baud rate
#define EVEN		2							// Define parity scheme
#define EIGHT_BIT	8							// Define data length for communication transmission
#define ONE_BIT		0							// Define data length for stop bit
												// Value should be 1. (Sometimes it seems that it will only work with 0.
												// Data Transmission Manual p. 37/116
												// Intuitively it should be 1, but a value of 0 is the only way it will work.											// !! For more on this see: Data Transmission Manual p. 37/116
#define NUM_AXES	6

// Robot Coordinate Systems
#define BASE		"BASE"						// Cartesian Coordinate system 
#define ROBOT		"ROBOT"						// Pulse Coordinate system

// Angle and Pulse conversions
// For each of the joints, we moved with precision the joint until a difference of 90 degrees was achieved.
// The results of pulses per degrees are as follows:
#define ANGLE2PULSE1 1137.7666666666666666666666666667			
#define ANGLE2PULSE2 2546.7333333333333333333333333333	
#define ANGLE2PULSE3 1313.1888888888888888888888888889
#define ANGLE2PULSE4 1365.2777777777777777777777777778	
#define ANGLE2PULSE5 1137.9666666666666666666666666667
#define ANGLE2PULSE6 926.72222222222222222222222222222
												
#define CARTESIAN	0
#define	ANGLES		1

// Tool number and name definitions
#define EMPTY		0							// No tool is used
#define BARRET		1							// Barrett Hand is defined as tool number 0 in the NX100
#define ASSEMBLY	2							// Assembly tool is used = barret + truss
/////////////////////////////////////////////////////////////////////////////
// CHP3JC
class ATL_NO_VTABLE CHP3JC : 
	public CComObjectRootEx<CComMultiThreadModel>,	
	public CComCoClass<CHP3JC, &CLSID_HP3JC>,
	public IDispatchImpl<IHP3JC, &IID_IHP3JC, &LIBID_IMA2_MOTOMANLIBLib>,
	public CComponentImpl 
{
public:
	CHP3JC()
	{
		int i;
		// File stream
		stream			= NULL;

		// Connection Variables
		m_sComType		= SERIAL;//ETHERNET;
		m_sPort			= COM1;							
		m_dwBaud		= BRATE;							
		m_sParity		= EVEN;						
		m_sDataLen		= EIGHT_BIT;							
		m_sStopBit		= ONE_BIT;	
		m_bConnected	= 0;
		m_sComHandle	= 0;
		m_bServoOn		= 0;

		// Ethernet param's
		//m_hWnd		DO NOT ASSIGN
		scIPAddress		= "129.59.72.79";					// IP address assigned to Motoman controller by network manager

		// Motion Variables
		m_bstrError		 = SysAllocString(L"Check Emergency stop, Remote Switch, and COM driver if not connecting.");
		m_dSpeed		 = 10.0;							// 50% of max speed
		m_sRconf	     = 1;								// Represents a bit value of 000001. Understand what each bit does.
		m_cMotionType	 = "MOVL";							// Default string
		m_sMotionType	 = 0;								// Value of '1', represents MOVL
															// See p. 138/217 (Motocom SDK.pdf) for example
		// General Variables
		m_sSuccess		= 0;
		for(i=0;i<NUM_AXES*2;i++)	
		{
			m_pdDesPos[i]				= 0.0;				// Desired Positions
			m_pdActualJointPositions[i]	= 0.0;				// Actual Joint Angle Positions
		}
		for(i=0;i<NUM_AXES;i++)
			m_pdActualXYZPositions[i]	= 0.0;				// Acutal XYZ Positions

		// To read positions
		m_sRconfPosition	= new WORD;						// Form to RECEIVE information on end-effector position. DO NOT SET POINTER TO NULL
		m_sToolNo			= new WORD;						// RECEIVES information on what tool number is being used. DO NOT SET POINTER TO NULL
		m_sReadPositionType = 1;							// To determine if we want to read positions in XYZ coords (0) or pulses (1)
		m_cReadPositionType = "BASE";
		m_sToolType			= BARRET;


		// Jobs
		strcpy(m_cJobName,"HOME.JBI");							// Default to the job name to move to initial position for assembly job
		m_bSelectJob		= false;						// Set flag to false

		// Error Info
		m_iReturnError		= 0;
		hResult				= 0;
		m_sErrorData		= new WORD;
	}

	~CHP3JC()
	{
		delete m_sRconfPosition;
		delete m_sToolNo;
		delete m_sErrorData;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_HP3JC)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHP3JC)
	COM_INTERFACE_ENTRY(IHP3JC)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()
// IHP3JC
// This is where all your interface methods will appear and be displayed on DAD
public:
	STDMETHOD(get_ToolType)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ToolType)(/*[in]*/ BSTR newVal);

	STDMETHOD(job_CopyTextQueue)();
	STDMETHOD(job_StartJob)();
	STDMETHOD(job_SelectJob)();

	STDMETHOD(error_ClearAlarm)();
	STDMETHOD(error_GetAlarm)();
	STDMETHOD(error_ClearError)();
	STDMETHOD(error_GetError)();

	STDMETHOD(servo_ServoOff)();
	STDMETHOD(servo_ServoOn)();
	STDMETHOD(read_CurrentPosition)();

	STDMETHOD(move_JointAngles)();
	STDMETHOD(move_JointMotion)();
	STDMETHOD(move_LinearMotion)();
	STDMETHOD(move_UsersChoice)();
	STDMETHOD(move_Incremental)(/*SAFEARRAY* data*/);

	STDMETHOD(connect_Initialize)();
	STDMETHOD(connect_Disconnect)();

	// Properties
	STDMETHOD(get_JobName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_JobName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_read_PositionType)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_read_PositionType)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_EndToolForm)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_EndToolForm)(/*[in]*/ long newVal);
	STDMETHOD(get_Speed)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Speed)(/*[in]*/ double newVal);
	STDMETHOD(get_MotionType)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_MotionType)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ErrorMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ErrorMessage)(/*[in]*/ BSTR newVal);

	// Local Functions
	void Write2File(char *, double *, char *);


private:

	// Writing to files
	FILE *stream;						// Stream to write to files.

	// Members used during the initialization routine to connect
	short	m_sComType;						// Stores communication type	(Serial or Ethernet)
	short	m_sPort;						// Stores port number			(Communication port number 1:COM1,2:COM2,3:COM3,4:COM4,...,255:COM255)
	DWORD	m_dwBaud;						// Stores baud rate				(Baud rate 150, 300, 600, 1200, 2400, 4800, 9600, 19200)
	short	m_sParity;						// Stores parity				(Parity 0: None, 1: Odd, 2: Even)
	short	m_sDataLen;						// Stores data bits				(Data length 7: 7 bits, 8: 8 bits)
	short	m_sStopBit;						// Stores stop bits				(Stop bit 0: 1 bit, 1: 1.5 bits, 2: 2 bits)
	short	m_sComHandle;					// Handle to communication. Used by virtually every other fnctn
	short	m_bServoOn;						// Flag to identify if servo is on or not
	bool	m_bConnected;					// Tells if there is an active connection or not
	char	m_cTempBuffer[100];				// Stores temporary char array

	HWND	m_hWnd;							// Handle used for ethernet connection configuration
	char	*scIPAddress;					// Variable to hold ipaddress

	// Members used for motion commands
	short	m_sRconf;						// The value of this variable is translated into a byte, where each bit of that byte tells the controller its configuration. I.e. 3 = 000011
	double	m_dSpeed;						// Robot motion speed
	char	*m_cMotionType;					// Motion type string
	short	m_sMotionType;					// MotionType. 1=MOVL, 2=MOVJ, 3=IMOV

	// Members used to read positions
	double	m_pdActualJointPositions[NUM_AXES*2];// Used to save current positions in joint angles/pulse format
	double	m_pdActualXYZPositions[NUM_AXES];// Used to save current positions in XYZ
	WORD	*m_sRconfPosition;				// Used to read the form for end-effector position.
	short	m_sReadPositionType;			// What configuration do we want to choose to read positions: XYZ or angles
	char	*m_cReadPositionType;			// Used to indicate in what coordinate system we want to read positinos. BASE(XYZ) or ROBOT(pulses)
	WORD	*m_sToolNo;						// Used to indicated what tool is used by providing the tool number.
	double	m_dHomeAngles[NUM_AXES];		// Home angles for motoman as derived from the DH parameter derivation.
	short	m_sToolType;					// Variable used to determined the kind of tool on the end effector.

	// Errors
	int		m_iReturnError;					// Holds error information
	WORD	*m_sErrorData;					// Returned by some functions
	long	hResult;						// Holds errors for COM calls

	// Members used generically in the component
	BSTR	m_bstrError;					// BSTR string that stores error message. 
	double	m_pdDesPos[NUM_AXES*2];			// Holds desired positions
	double	m_pdCommParams[2];				// Holds the communication handle and a flag
	short	m_sSuccess;						// Used to determine if function calls are successful. 
	
	// Jobs
	char	m_cJobName[50];					// Variable to store names of jobs. Pointer would not work, only array.
	bool	m_bSelectJob;					// Flag to indicate if this function was called
	BSTR	m_bstrJobName;					// Variable to hold BSTR job name

	// Include IMA Component Bindings of type IComponent *
	IComponent *m_pIUnkDesiredPosition;					// For cartesian position
	IComponent *m_pIUnkDesiredAngles;					// For joint angles
	IComponent *m_pIUnkActualJointAnglePos; 			// For actual position (XYZ or Angles)
	IComponent *m_pIUnkActualXYZPos;		 			// For actual position (XYZ or Angles)
	IComponent *m_pIUnkTextQueue;						// For TextQueue which contains the job 
	IComponent *m_pIUnkStateMachine;					// For matlab state machine

	// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them
	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

	// Private function
	void PrintError(int ErrorCode);				// Prints out errors through BSTRs
	void Angles2Pulses(double *Angles);			// Converts joint angles to joint pulses
	void Pulses2Angles(double *Pulses);				// Converts pulses to angles

};

#endif //__HP3JC_H_
