// JR3Sensor.h : Declaration of the CJR3Sensor

#ifndef __JR3SENSOR_H_
#define __JR3SENSOR_H_

#include "resource.h"       					// main symbols
#include "O:\Base Classes\ComponentImpl.h"		// Component Lib file
#include "O:\Components\msvbvm60.tlh"			// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal 
#include "O:\Include\JR3\jr3pci_ft.h"
#include "math.h"
#include <windows.h>

#define NUM_AXES 6
#define NOT_INITIALIZED	0
#define INITIALIZED		1

// Data tracking definitions
#define FORCE	  "ForceData.txt"										// Change the string to reflect your date and version. This will simplify tracking results.
#define PATH	  "U:\\School\\Ph_D\\Experiments\\ControlBasis\\Data\\HP3JC\\"
/////////////////////////////////////////////////////////////////////////////
// CJR3Sensor
class ATL_NO_VTABLE CJR3Sensor : 
	public CComObjectRootEx<CComSingleThreadModel>,	
	public CComCoClass<CJR3Sensor, &CLSID_JR3Sensor>,
	public IDispatchImpl<IJR3Sensor, &IID_IJR3Sensor, &LIBID_IMA2_JR3FTSENSORLib>,
	public CComponentImpl 
{
public:
	CJR3Sensor()
	{
		// Do not include any JR3 calls in this constructor or component creation will fail.
		int i					= 0;
		
		// Averaging weight parameter
		alpha					= 0.85;

		// Flags
		m_status				= 0;					// Flag that indicates the state of the sensor. Once you have initialized the sensor it should not be initialize again.
		m_bWrite2File			= true;					// Flag to indicate whether or not to write data to file. Should be true when trying to collect data.
		
		m_sFullScaleIndex		= 0;
		m_sOffsetsIndex			= 0;
		m_sFTDataIndex			= 0;
		m_sFTMaxMinPeaksIndex	= 0;
		m_sFTMaxMinPeaksValue	= 0;

		for (i=0;i<NUM_AXES;i++) 
		{
			m_dFTData[i]		= 0.0;
			m_dCurrentFTData[i] = 0.0;
			m_dPreviousFTData[i]= 0.0;
			m_dOffsets[i]		= 0.0;
			m_dFTPeaks[i]		= 0.0;
			m_dFullScales[i]	= 0.0;
		}

		(short) m_FT.fx=m_FT.fy=m_FT.fz=m_FT.mx=m_FT.my=m_FT.mz=m_FT.v1=m_FT.v2 = 0;
		
		// File
		stream = NULL;

		// Timing Variables
		ticksPerSecond.QuadPart	= 0;
		start_ticks.QuadPart	= 0;
		end_ticks.QuadPart		= 0;
		sample_time				= 0.0;

	}

	~CJR3Sensor()
	{
		if(m_status != 99)
			close_jr3();
	}


DECLARE_REGISTRY_RESOURCEID(IDR_JR3SENSOR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CJR3Sensor)
	COM_INTERFACE_ENTRY(IJR3Sensor)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()
// IJR3Sensor
public:

	// Methods
	STDMETHOD(Initialize)();	
	STDMETHOD(Close)();

	STDMETHOD(Read_FTData)();
	STDMETHOD(Read_Offsets)();
	STDMETHOD(Read_FTMax_or_MinPeaks)();
	STDMETHOD(Read_RecommendedMinScales)();
	STDMETHOD(Read_RecommendedMaxScales)();
	STDMETHOD(Read_FullScales)();	

	STDMETHOD(Set_FullScales)();
	STDMETHOD(ResetOffsets)();

	// Get's
	STDMETHOD(get_FTData)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_MaxMinPeakData)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_status)(/*[out, retval]*/ short *pVal);

	// Get/Put's
	STDMETHOD(get_AveragingWeight_FTData)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_AveragingWeight_FTData)(/*[in]*/ double newVal);
	STDMETHOD(get_FTDataIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_FTDataIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_OffsetData)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_OffsetData)(/*[in]*/ double newVal);					// We will be able to set offsets here
	STDMETHOD(get_OffsetDataIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_OffsetDataIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_FullScales)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_FullScales)(/*[in]*/ double newVal);
	STDMETHOD(get_MaxMinPeakIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_MaxMinPeakIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_MaxMinValue)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_MaxMinValue)(/*[in]*/ BSTR newVal);

	// Local
	void Write2File(char * title, double time, double * positions, char * textfile);		// Writes time and force data to a file


private:

// Binding methods
STDMETHOD(OnConstruct)(void);	// Set bindings
STDMETHOD(OnDestruct)(void);	// Delete them
// Override of IMA base components
virtual STDMETHODIMP Load(VARIANT pData);
virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

	// Members
	short	m_status;						// Indicates the status of the sensor;
	double	alpha;							// Parameter used to adjust averaging weight of filtered data
	bool	m_bWrite2File;					// Flag to indicate whether or not to print data to file

	// Writing to files
	FILE *stream;							// Stream to write to files.

	// Indeces
	short	m_sFullScaleIndex;				// Index to traverse the Fullscale array
	short	m_sOffsetsIndex;				// ... the Offsets array
	short	m_sFTDataIndex;					// ... the FT data array
	short	m_sFTMaxMinPeaksIndex;			// ... MaxMinPeaksArray
	short	m_sFTMaxMinPeaksValue;			// Selects whether to look at max or min values

	// JR3 Structures
	struct	force_array		m_FT;			// Contains FxyzMxyzV1V2
	struct	six_axis_array	m_FS;			// Holds Full Scales 
	struct	six_axis_array	m_OS;			// Contains 6DOF Offset Information
	struct	force_array		m_FTPeaks;		// Contains Max or Min Fxyz Mxyz V12
	struct  force_array		m_FullScales;	// Used to read full scale values
	struct	six_axis_array	m_RecFullScales;// Used for recommended max and min scales
	struct	six_axis_array	m_setFullScales;// Used to set full scale values

	// Private storage
	double	m_dFTData[NUM_AXES];			// Data member to send out FTData
	double	m_dCurrentFTData[NUM_AXES];		// Stores incoming values of FTData
	double	m_dPreviousFTData[NUM_AXES];	// Used to store the history of FTData
	double	m_dOffsets[NUM_AXES];			// To save Offset data
	double	m_dFTPeaks[NUM_AXES];			// To save max/min data for FT data
	double	m_dFullScales[NUM_AXES];		// To save Full Scales values

	// Timing Variables						// Timing variables. Need <windows.h>
	LARGE_INTEGER ticksPerSecond;			// CPU frequency, counts per second. In essence number of ticks per second. Method: QueryPerformanceFrequency(&ticksPerSecond) must be called to get value.
	LARGE_INTEGER start_ticks;				// Retrives starting value of counter
	LARGE_INTEGER end_ticks;				// Retrives ending value of counter
	double		  sample_time;				// Variable to compute cpu time
	
	// Binding variables
	IComponent*	m_pIUnkFTData;				// Holds pointer to FT data to VS
	// Probably don't need the ones below.
	IComponent*	m_pIUnkOffsetData;			// Holds pointer to Offset data to VS
	IComponent*	m_pIUnkFTPeaks;				// Holds pointer to Max/Min values of FT
	// Might need one for full scales. Do we need to share this value outside at all?

};

#endif //__JR3SENSOR_H_
