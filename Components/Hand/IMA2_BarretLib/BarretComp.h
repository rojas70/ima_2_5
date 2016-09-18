// BarretComp.h : Declaration of the CBarretComp

#ifndef __BARRETCOMP_H_
#define __BARRETCOMP_H_

#include "resource.h"								// main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"				// property bag dll
#include "O:\Include\Barrett\bhand.h"				// Device (COMM Conection) is defined in bhand.cpp

#define	 NUM_AXES 4
#define  DEFAULT_FINGER_POSITION  8500									// Default position for fingers
#define	 DEFAULT_SPREAD_POSITION  1575									// Default position for spread
#define  DEFAULT_FINGER_VELOCITY    50									// In the Barret Interface it would be 100
#define  DEFAULT_SPREAD_VELOCITY    25									// In the Barret Interface it would be 60
/////////////////////////////////////////////////////////////////////////////
// CBarretComp
class ATL_NO_VTABLE CBarretComp : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CBarretComp, &CLSID_BarretComp>,
	public IDispatchImpl<IBarretComp, &IID_IBarretComp, &LIBID_IMA2_BARRETLIBLib>,
	public CComponentImpl 
{
public:
	CBarretComp()
	{
		m_lPosition			= 8500;							// This value is applied to the motors flagged by the HandParameter
		m_lDefaultPosition	= 8500;
		m_lStepSize			= 1024;
		m_lVelocity			=   50;							// This value is applied to the motors flagged by the HandParameter
		m_lStrainGauge		=  255;							// This value is applied to the motors flagged by the HandParameter
		m_lParameterValue	= 8500;
		m_bstrHandParameter = SysAllocString(L"123");		// Holds flag to activate fingers 1,2,3. or spread S
		m_bstrParameterFlag = SysAllocString(L"DP");
	}

	~CBarretComp()
	{
		// Free the strings
		SysFreeString(m_bstrHandParameter);
		SysFreeString(m_bstrParameterFlag);

		// Stop the motors
		if( result = bh.StopMotor("123S") )
			Error();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_BARRETCOMP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBarretComp)
	COM_INTERFACE_ENTRY(IBarretComp)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IBarretComp
public:
	STDMETHOD(StopMotors)();

	// Properties
	STDMETHOD(get_Position)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Position)(/*[in]*/ long newVal);
	STDMETHOD(get_ParameterValue)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ParameterValue)(/*[in]*/ long newVal);
	STDMETHOD(get_ParameterFlag)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ParameterFlag)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_DefaultPosition)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_DefaultPosition)(/*[in]*/ long newVal);
	STDMETHOD(get_StrainGauge)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_StepSize)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_StepSize)(/*[in]*/ long newVal);
	STDMETHOD(get_HandParamter)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_HandParamter)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Velocity)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Velocity)(/*[in]*/ long newVal);
	// Methods
	STDMETHOD(Set)();
	STDMETHOD(Get)();
	STDMETHOD(Open)();
	STDMETHOD(Close)();
	STDMETHOD(GoHome)();
	STDMETHOD(StepOpen)();
	STDMETHOD(StepClose)();
	STDMETHOD(Initialize)();
	STDMETHOD(GoToPosition)();
	STDMETHOD(GoToDefaultPosition)();
	// Behaviors
	STDMETHOD(_IndexFingerPointing)();
	STDMETHOD(_ClosedHandGrasp)();
	STDMETHOD(_ThreeFingerGrasp)();

private:
	Bhand	bh;										// Handles all hand communication
	int		value;									// Hand parameter obtained with Get
	int		result;									// Return value (error) of all BHand calls
	long	m_lVelocity;							// Holds value for velocity
	long	m_lStrainGauge;							// Holds value for strain gauge
	long	m_lDefaultPosition;						// Holds the value for default position
	long	m_lPosition;							// Holds value for single position
	long	m_lStepSize;							// Holds value for step size
	long	m_lParameterValue;						// Holds value for a generic parameter. Used alongside of Get()/Set()

	char	motorflag;								// Holds flag to indicate what finger or spread is going to be used
	BSTR	m_bstrHandParameter;					// String to decide what finger and/or spread to activate
	BSTR	m_bstrParameterFlag;					// Holds flag to indicate what parameter one wishes to set/get: velocity/straing gauge, etc. (Look at the GUI interface to see parameters available to get/set).
	
	// IMA 2.5 Specific
	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT
	
	// Automatically generated functions by Barret GUI
	void Error(void);


};

#endif //__BARRETCOMP_H_
