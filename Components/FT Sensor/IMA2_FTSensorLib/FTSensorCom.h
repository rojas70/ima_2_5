// FTSensorCom.h : Declaration of the CFTSensorCom

#ifndef __FTSENSORCOM_H_
#define __FTSENSORCOM_H_

// Include FTWrapper Class
class CFTWrapperClass;
#include "FTWrapperClass.h"							// Include definitions for CFTWrapper Class

#include "resource.h"								// main symbols
#include "O:\Components\msvbvm60.tlh"				// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal 
#include "O:\Base Classes\ComponentImpl.h"

#define NUM_AXES 6
#define	COUNTES_PER_POUND 80.0

// Data tracking definitions
#define FORCE_DATA_LEFT		  "ForceDataLeft.txt"										// Change the string to reflect your date and version. This will simplify tracking results.
#define FORCE_DATA_RIGHT	  "ForceDataRight.txt"										// Change the string to reflect your date and version. This will simplify tracking results.
#define PATH		  "U:\\School\\Ph_D\\Experiments\\ControlBasis\\Data\\ISAC\\"
/////////////////////////////////////////////////////////////////////////////
// CFTSensorCom
class ATL_NO_VTABLE CFTSensorCom : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CFTSensorCom, &CLSID_FTSensorCom>,
	public IDispatchImpl<IFTSensorCom, &IID_IFTSensorCom, &LIBID_IMA2_FTSENSORLIBLib>,
	public CComponentImpl 
{
public:
	CFTSensorCom()
	{
		// Averaging weight parameter
		alpha					= 0.85;

		// String parameters
		m_sCommFileName		= SysAllocString(L"\\COM2");
		m_sCommParams		= SysAllocString(L"38400, N, 8, 1");		// Baud Rate, Parity, Data bits, stop bit. Check to see if 2nd param is not in the wrong order in the string
		m_sCommReadTimeouts	= SysAllocString(L"1000, 1000, 1000");

		// Wrapper Class Pointer
		m_pftSensor			= NULL;

		// Flags
		m_bInitialized		= FALSE;
		m_bBiasSensor		= TRUE;		// Always set to true to bias sensor
		m_bPeaks			= FALSE;

		m_sFTWristSide		= 0;	// Left == 0, Right == 1
		m_sCurrentFrameIndex= 0;
		m_lAverageLength	= 4;	// Can be 0,2,4,8,16,32,64,128		

		// IComponent Pointers
		m_pIUnkFTSensorData			= NULL;
		m_pIUnkFTSensorDataPeaks	= NULL;

		// Data pointers
		m_pdMax						= NULL;
		m_pdMin						= NULL;
		m_pdData					= NULL;

		// Dynamically allocated memory
		m_pdMax = new double[NUM_AXES];
		m_pdMin = new double[NUM_AXES];
		m_pdData= new double[NUM_AXES];
		
		for(int i=0;i<NUM_AXES;i++) 
		{
			m_pdFrame[i]			= 0.0;
			m_pdMax[i]				= 0.0;
			m_pdMin[i]				= 0.0;
			m_pdData[i]				= 0.0;
			m_dCorrectedFTAxes[i]	= 0.0;
			m_dFTAveragedData[i]	= 0.0;
			m_dPreviousFTData[i]	= 0.0;

		}

		// Update values of sensor frame to conform: [0,0,0,-90,0,-90].
		// This will make both the JR3 FT sensor in the HP3JC robot have the same axis assignment.
		m_pdFrame[3] = -90.0;
		m_pdFrame[5] = -90.0;

		// Error message
		m_bstrError = SysAllocString(L"Please make sure that COM2 is associated w/ right wrist and COM1 w/ left wrist");

		// File
		stream = NULL;

		// Flags
		m_bWrite2File			= true;					// Flag to indicate whether or not to write data to file. Should be true when trying to collect data.

		// Timing Variables
		ticksPerSecond.QuadPart	= 0;
		start_ticks.QuadPart	= 0;
		end_ticks.QuadPart		= 0;
		sample_time				= 0.0;

		// Initalize class
		m_pftSensor = new CFTWrapperClass();
	}

	~CFTSensorCom()
	{
		delete [] m_pdMax;
		delete [] m_pdMin;
		delete [] m_pdData;
	
		if(m_pftSensor!=NULL) 
			delete m_pftSensor;
		
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FTSENSORCOM)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFTSensorCom)
	COM_INTERFACE_ENTRY(IFTSensorCom)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IFTSensorCom
public:
	STDMETHOD(Close)();
	STDMETHOD(EnablePeaks)();
	STDMETHOD(BiasSensor)();
	STDMETHOD(get_ErrorMessage)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ErrorMessage)(/*[in]*/ BSTR newVal);

	STDMETHOD(Initialize)();
	STDMETHOD(get_FTWristSide)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FTWristSide)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_DeviceFilename)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_DeviceFilename)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_AverageLength)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_AverageLength)(/*[in]*/ long newVal);
	STDMETHOD(get_CurrentFrameIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_CurrentFrameIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_CurrentFrame)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_CurrentFrame)(/*[in]*/ double newVal);

	STDMETHOD(SampleFTData)();
	//STDMETHOD(SampleFTDataPeaks)();

private:	
	// Local
	void Write2File(char * title, double time, double * positions, char * textfile);		// Writes time and force data to a file
	
	// File related
	bool	m_bWrite2File;					// Flag to indicate whether or not to print data to file
	FILE    *stream;						// Stream operator used to write to files

	short	m_sCurrentFrameIndex;			// Index for m_pdFrame
	short	m_sFTWristSide;					// left or right
	long	m_lAverageLength;				// number of frames to average out for the sensors

	double	m_pdFrame[NUM_AXES];			// frame in which Fx, ... is on.
	double	m_dCorrectedFTAxes[NUM_AXES];	// Frame to hold initial coordinate transform for sensor 
	
	// Used in averaging filter
	double	alpha;							// Parameter used to adjust averaging weight of filtered data
	double	m_dFTAveragedData[NUM_AXES];	// Data member to send out FTData
	double	m_dPreviousFTData[NUM_AXES];	// Used to store the history of FTData

	// Flags
	bool	m_bInitialized;					// Flag to determine if the Initialize() routine has been called.
	bool	m_bPeaks;
	int		m_bBiasSensor;					// Flag to indicate whether or not sensor is biased
	
	// FT Data
	double*	m_pdMax;
	double* m_pdMin;
	double* m_pdData;

	// BSTRs
	BSTR m_sCommFileName;				// "\\COM1" or "\\COM2"
	BSTR m_sCommParams;					// Baud Rate, Data bits, Parity, stop bit, Control Flow
	BSTR m_sCommReadTimeouts;			// 
	BSTR m_bstrError;					// BSTR string that stores error message. 

	// Timing Variables						// Timing variables. Need <windows.h>
	LARGE_INTEGER ticksPerSecond;			// CPU frequency, counts per second. In essence number of ticks per second. Method: QueryPerformanceFrequency(&ticksPerSecond) must be called to get value.
	LARGE_INTEGER start_ticks;				// Retrives starting value of counter
	LARGE_INTEGER end_ticks;				// Retrives ending value of counter
	double		  sample_time;				// Variable to compute cpu time

	// Class pointer
	CFTWrapperClass* m_pftSensor;

	// Binding variables
	IComponent* m_pIUnkFTSensorData;
	IComponent* m_pIUnkFTSensorDataPeaks;

	// Internal Functions
	STDMETHODIMP SampleAxes(double pdData[NUM_AXES]);	// Get FT info from the sensor

	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

};

#endif //__FTSENSORCOM_H_
