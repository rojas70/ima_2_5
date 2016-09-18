// PID_NonLinController.h : Declaration of the CPID_NonLinController

#ifndef __PID_NonLinController_H_
#define __PID_NonLinController_H_

#include "resource.h"								// main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"				// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal 
#include <assert.h>

#define MAX_AXES 6
/////////////////////////////////////////////////////////////////////////////
// CPID_NonLinController
class ATL_NO_VTABLE CPID_NonLinController : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPID_NonLinController, &CLSID_PID_NonLinController>,
	public IDispatchImpl<IPID_NonLinController, &IID_IPID_NonLinController, &LIBID_IMA2_ARMTOOLSLib>,
	public CComponentImpl 
{
public:
	CPID_NonLinController()
	{
		unsigned long Index;
		// Controller Variables
		m_pKp    = NULL;
		m_pKi    = NULL;
		m_pKd    = NULL;
		m_A0     = NULL;
		m_A1     = NULL;
		m_A2     = NULL;
		m_A3     = NULL;
		m_A4     = NULL;
		m_pIntegrator		= NULL;
		m_pControl_Law		= NULL;

		// Clamp Variables
		m_pMaxClamp			= NULL;
		m_pMinClamp			= NULL;

		// Pressure Variables
		m_pBiasedPressure	= NULL;		
		m_pInvertPressure	= NULL;
		m_pAlpha			= NULL;

		// Allocate parameter memory space:

		if (m_pKp == NULL)
			m_pKp = new double[MAX_AXES];
		assert( m_pKp != NULL );			/* Cannot be NULL */

		if (m_pKi == NULL)
			m_pKi = new double[MAX_AXES];
		assert( m_pKi != NULL );

		if (m_pKd == NULL)
			m_pKd = new double[MAX_AXES];
		assert( m_pKd != NULL );				
   

		if (m_A0 == NULL)
			m_A0 = new double[MAX_AXES];
		assert( m_A0 != NULL );

		if (m_A1 == NULL)
			m_A1 = new double[MAX_AXES];
		assert( m_A1 != NULL );

		if (m_A2 == NULL)
			m_A2 = new double[MAX_AXES];
		assert( m_A2 != NULL );

		if (m_A3 == NULL)
			m_A3 = new double[MAX_AXES];
		assert( m_A3 != NULL );

		if (m_A4 == NULL)
			m_A4 = new double[MAX_AXES];
		assert( m_A4 != NULL );


		if (m_pMaxClamp == NULL)
			m_pMaxClamp = new double[MAX_AXES];
		assert( m_pMaxClamp != NULL );


		if (m_pMinClamp == NULL)
			m_pMinClamp = new double[MAX_AXES];
		assert( m_pMinClamp != NULL );


		if (m_pIntegrator == NULL)
			m_pIntegrator = new double[MAX_AXES];
		assert( m_pIntegrator != NULL );


		if (m_pBiasedPressure == NULL)
			m_pBiasedPressure = new double[MAX_AXES];
		assert( m_pBiasedPressure != NULL );


		if (m_pControl_Law == NULL)
			m_pControl_Law = new short[MAX_AXES];
		assert( m_pControl_Law != NULL );


		if (m_pInvertPressure == NULL)
			m_pInvertPressure = new short[MAX_AXES];
		assert( m_pInvertPressure != NULL );


		if (m_pAlpha == NULL)
			m_pAlpha = new double[MAX_AXES];
		assert( m_pAlpha != NULL );

		// Values for variables is shown below. Deliberatly trying to ease readability and avoid mistakes. 
		// Values were found empirically by testing. 

		// Set the PID Constants
		m_pKp[0] = 500.0;	// {500, 850, 850, 850, 900, 900} Values were assigned to 3.0 before
		m_pKp[1] = 850.0;
		m_pKp[2] = 850.0;
		m_pKp[3] = 850.0;
		m_pKp[4] = 900.0;
		m_pKp[5] = 900.0;

		m_pKi[0] = 15.0;	// {15, 90, 150, 150, 150, 150} Values were 2.0 before
		m_pKi[1] = 90.0;
		m_pKi[2] = 150.0;
		m_pKi[3] = 150.0;
		m_pKi[4] = 150.0;
		m_pKi[5] = 150.0;

		m_pKd[0] = 1.0;
		m_pKd[1] = 1.0;
		m_pKd[2] = 1.0;
		m_pKd[3] = 1.0;
		m_pKd[4] = 1.0;
		m_pKd[5] = 1.0;	// {1, 1, 1, 1, 1, 1}

		// Set the Nonlinear constants
		m_A0[0]	= 118.5;	// Values found in Agent Builder: {118.15, -3374.4, 199900, 394250, 6270.2, 6458.5}
		m_A0[1]	= -3374.4;
		m_A0[2]	= 199900.0;
		m_A0[3]	= 394250.0;
		m_A0[4]	= 6270.2;
		m_A0[5]	= 6458.5;

		m_A1[0]	= 488.08;	// {488.08, 4064.7, 216870, 419240, 8378.7, 9958.3}
		m_A1[1]	= 4064.7;
		m_A1[2]	= 216870.0;
		m_A1[3]	= 419240.0;
		m_A1[4]	= 8378.7;
		m_A1[5]	= 9958.3;

		m_A2[0]	= 62.189;	// {62.189, -1981.6, 78642, 148870, 4413, 6325.3}
		m_A2[1]	= -1981.6;
		m_A2[2]	= 78642.0;
		m_A2[3]	= 148870.0;
		m_A2[4]	= 4413.0;
		m_A2[5]	= 6325.3;

		m_A3[0]	= 251.58;	// {251.58, 539.69, 9534.9, 17656, 979.98 1702.1}
		m_A3[1]	= 539.69;
		m_A3[2]	= 9534.9;
		m_A3[3]	= 17656.0;
		m_A3[4]	= 979.98;
		m_A3[5]	= 1702.1;

		m_A4[0]=m_A4[1]=m_A4[2]=m_A4[3]=m_A4[4]=m_A4[5]= 0.0;	// {0, 0, 0, 0, 0, 0}

		// Initialize arrays with values
		for (Index = 0; Index < MAX_AXES; Index++)
		{

		// Setting Nonlinear Member Variables	
			m_pMaxClamp[Index]			=  1600.0;
			m_pMinClamp[Index]			= -1600.0;
			m_pIntegrator[Index]		= 0.0;			// Controller state variable
			m_pBiasedPressure[Index]	= 2000.0;		// {1000,2000,2000,2000,2000,2000}
			m_pControl_Law[Index]		= 0;			// Control type,	0 Po+/-deltaP
														//					1 Ag/Antag
														//					2 Antag/Ag
			m_pAlpha[Index]				= 100.0;		// Was 50 in the code but 100 in Agent Builder
			
			m_pCurrentPressures[2*Index]	=	0.0;	// i.e. 0,2,4,6,8,10,12
			m_pCurrentPressures[2*Index+1]	=	0.0;	// i.e. 1,3,5,7,9,11,
		}

		// First index of pressure bias is set to 1000 here. The rest are set to 2000 in the previous For-loop.
		m_pBiasedPressure[0] = 1000.0;
	
		// Invert Boolean Pressure for Right Arm
		m_bInvertPressure[0]	= FALSE;
		m_bInvertPressure[1]	= TRUE;
		m_bInvertPressure[2]	= TRUE;
		m_bInvertPressure[3]	= FALSE;
		m_bInvertPressure[4]	= TRUE;
		m_bInvertPressure[5]	= FALSE;

		// Invert pointer Pressure for Right Arm
		m_pInvertPressure[0]	= 0;
		m_pInvertPressure[1]	= 1;
		m_pInvertPressure[2]	= 1;
		m_pInvertPressure[3]	= 0;
		m_pInvertPressure[4]	= 1;
		m_pInvertPressure[5]	= 0;					// Initial values copied from agent file to here for Right arm

		// Number of axes
		m_Axes					= 6;					// Default to what we need.

		// Left Arm flag originally set to FALSE
		m_LeftArm				= 0;
		
		// Setup IMA component linking for intpus and outputs of this component:
		m_pIUnkInputState			= NULL;
		m_pIUnkOutput				= NULL;
		m_pIUnkDesiredState			= NULL;
		m_pIUnkBiasedPressureState	= NULL;

		// Initialize indeces for array members
		m_sInvertPressureIndex		= 0;
		m_sA0Index					= 0;	
		m_sA1Index					= 0;
		m_sA2Index					= 0;
		m_sA3Index					= 0;
		m_sA4Index					= 0;
		m_sMinClampIndex			= 0;
		m_sMaxClampIndex			= 0;
		m_sKpIndex					= 0;
		m_sKiIndex					= 0;
		m_sKdIndex					= 0;
		m_sControl_LawIndex			= 0;
		m_sBiasedPressureIndex		= 0;
		m_sAlphaIndex				= 0;

	}

~CPID_NonLinController()
{
	// Free parameter memory space
	if (m_pKp != NULL)
		delete [] m_pKp;

	if (m_pKi != NULL)
		delete [] m_pKi;

	if (m_pKd != NULL)
		delete [] m_pKd;

	if (m_A0 != NULL)
		delete [] m_A0;

	if (m_A1 != NULL)
		delete [] m_A1;
	
	if (m_A2 != NULL)
		delete [] m_A2;

	if (m_A3 != NULL)
		delete [] m_A3;

	if (m_A4 != NULL)
		delete [] m_A4;

	if (m_pMinClamp != NULL)
		delete [] m_pMinClamp;

	if (m_pMaxClamp != NULL)
		delete [] m_pMaxClamp;

	if (m_pBiasedPressure != NULL)
		delete [] m_pBiasedPressure;

	if (m_pControl_Law != NULL)
		delete [] m_pControl_Law;

	if (m_pInvertPressure != NULL)
		delete [] m_pInvertPressure;

	if (m_pIntegrator != NULL)
		delete [] m_pIntegrator;

	if (m_pAlpha != NULL)
		delete [] m_pAlpha;
}

DECLARE_REGISTRY_RESOURCEID(IDR_PID_NONLINCONTROLLER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPID_NonLinController)
	COM_INTERFACE_ENTRY(IPID_NonLinController)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IPID_NonLinController
public:
	STDMETHOD(get_LeftArm)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_LeftArm)(/*[in]*/ short newVal);
	STDMETHOD(Read_CurrentPressure)();
	STDMETHOD(PID_NonLin_12Press)();
	STDMETHOD(PID_NonLin_6Press)();
	STDMETHOD(get_AlphaIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_AlphaIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_BiasedPressureIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_BiasedPressureIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_Control_LawIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_Control_LawIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_KdIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_KdIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_KiIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_KiIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_KpIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_KpIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_MaxClampIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_MaxClampIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_MinClampIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_MinClampIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_A4Index)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_A4Index)(/*[in]*/ short newVal);
	STDMETHOD(get_A3Index)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_A3Index)(/*[in]*/ short newVal);
	STDMETHOD(get_A2Index)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_A2Index)(/*[in]*/ short newVal);
	STDMETHOD(get_A1Index)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_A1Index)(/*[in]*/ short newVal);
	STDMETHOD(get_A0Index)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_A0Index)(/*[in]*/ short newVal);
	STDMETHOD(get_InvertPressureIndex)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_InvertPressureIndex)(/*[in]*/ short newVal);
	STDMETHOD(get_BiasedPressure)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_BiasedPressure)(/*[in]*/ double newVal);
	STDMETHOD(get_Control_Law)(/*[out, retval]*/ int  *pVal);
	STDMETHOD(put_Control_Law)(/*[in]*/ int  newVal);
	STDMETHOD(get_Kd)(/*[out, retval]*/ double  *pVal);
	STDMETHOD(put_Kd)(/*[in]*/ double  newVal);
	STDMETHOD(get_Ki)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Ki)(/*[in]*/ double newVal);
	STDMETHOD(get_Kp)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Kp)(/*[in]*/ double newVal);
	STDMETHOD(get_MaxClamp)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_MaxClamp)(/*[in]*/ double newVal);
	STDMETHOD(get_MinClamp)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_MinClamp)(/*[in]*/ double newVal);
	STDMETHOD(get_A4)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_A4)(/*[in]*/ double newVal);
	STDMETHOD(get_A3)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_A3)(/*[in]*/ double newVal);
	STDMETHOD(get_A2)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_A2)(/*[in]*/ double newVal);
	STDMETHOD(get_A1)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_A1)(/*[in]*/ double newVal);
	STDMETHOD(get_A0)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_A0)(/*[in]*/ double newVal);
	STDMETHOD(get_InvertPressure)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_InvertPressure)(/*[in]*/ BOOL newVal);
	STDMETHOD(Initial)();

	// Internal Variables
	short  *m_pControl_Law;
	short  *m_pInvertPressure;
	double *m_pKp;
	double *m_pKi;
	double *m_pKd;
	double *m_A0;
	double *m_A1;
	double *m_A2;
	double *m_A3;
	double *m_A4;
	double *m_pMaxClamp;
	double *m_pMinClamp;
	double *m_pIntegrator;
	double *m_pBiasedPressure;
	double *m_pAlpha;

	long    m_Axes;

	// LeftArm
	short m_LeftArm;

	// Files
	BSTR	m_bstrInputFile;					// For input file. Changed to BSTR from CComBSTR
	FILE     *m_fp;
			
	// Pressure
	BOOL	m_bInvertPressure[MAX_AXES];
	double	m_pCurrentPressures[2*MAX_AXES];

	// Binding variables
	IComponent *m_pIUnkInputState;
	IComponent *m_pIUnkOutput;
	IComponent *m_pIUnkDesiredState;
	IComponent *m_pIUnkBiasedPressureState;

	// Index variables for arrays necessary for IMA 2.5 DAD
	short m_sInvertPressureIndex;
	short m_sA0Index;
	short m_sA1Index;
	short m_sA2Index;
	short m_sA3Index;
	short m_sA4Index;
	short m_sMinClampIndex;
	short m_sMaxClampIndex;
	short m_sKpIndex;
	short m_sKiIndex;
	short m_sKdIndex;
	short m_sControl_LawIndex;
	short m_sBiasedPressureIndex;
	short m_sAlphaIndex;


private:
	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT													// STDMETHOD returns a virtual HRESULT
};

#endif //__PID_NonLinController_H_
