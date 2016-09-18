// ISAC_Assembly.h : Declaration of the CISAC_Assembly

#ifndef __ISAC_ASSEMBLY_H_
#define __ISAC_ASSEMBLY_H_

#include "resource.h"       					// main symbols
#include "O:\Base Classes\ComponentImpl.h"		// Component Lib file
#include "O:\Components\msvbvm60.tlh"			// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"		// Vector Signal 

// Definitions
#define NUM_AXES 6

/////////////////////////////////////////////////////////////////////////////
// CISAC_Assembly
class ATL_NO_VTABLE CISAC_Assembly : 
	public CComObjectRootEx<CComSingleThreadModel>,	
	public CComCoClass<CISAC_Assembly, &CLSID_ISAC_Assembly>,
	public IDispatchImpl<IISAC_Assembly, &IID_IISAC_Assembly, &LIBID_IMA2_VIRTUALCONTACTLIBLib>,
	public CComponentImpl 
{
public:
	CISAC_Assembly()
	{
		// Data variables
		m_bInitial = false;

		for(int i=0;i<NUM_AXES;i++)
		{
			// Force variables
			m_dLeftForceValues[i]		= 0.0;				// Used to store incoming values from left force sensor
			m_dRightForceValues[i]		= 0.0;
			m_dAvgActualForce[i]		= 0.0;

			// Joint variables
			m_dLeftJointAngles[i]		= 0.0;				// Used to store actual joint angle positions for ISACs left arm
			m_dRightJointAngles[i]		= 0.0;
			m_dAvgActualJointAngles[i]	= 0.0;

			// Averaging variables
			m_dAveragedForceData[i]		= 0.0;
			m_dPreviousForceData[i]		= 0.0;

			m_dAveragedJointData[i]		= 0.0;
		}	

		// Previous Joint data should be the same as the home position for ISAC
		m_dPreviousJointData[i]		= 0.0;
		m_dPreviousJointData[i]		= 90.0;
		m_dPreviousJointData[i]		= -180.0;
		m_dPreviousJointData[i]		= 0.0;
		m_dPreviousJointData[i]		= 90.0;
		m_dPreviousJointData[i]		= 0.0;
		
		// Weighted averaging parameter
		alpha						= 0.85;

		// IComponent Pointers
		IUnkRightForceSensor		= NULL;
		IUnkLeftForceSensor			= NULL;
		IUnkAvgForce				= NULL;

		IUnkRightActualJointAngle	= NULL;
		IUnkLeftActualJointAngle	= NULL;				
		IUnkAvgJointAngle			= NULL;	

		// IVectorSignal Pointers
		pIVSLeftForce	= NULL;
		pIVSRightForce	= NULL;
		pIVSAvgForce	= NULL;
		
		pIVSLeftJointAngle	= NULL;
		pIVSRightJointAngle	= NULL;
		pIVSLAvgJointAngle	= NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ISAC_ASSEMBLY)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CISAC_Assembly)
	COM_INTERFACE_ENTRY(IISAC_Assembly)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()
// IISAC_Assembly
public:
	STDMETHOD(Close)();
	STDMETHOD(AverageValues)();

private:

	bool m_bInitial;									// Flag for use in one call at the beginning of the program

	// Averaging parameters
	double alpha;										// Parameter used to adjust averaging weight of filtered data
	double m_dAveragedForceData[NUM_AXES];				// Data member to average data sets over time
	double m_dPreviousForceData[NUM_AXES];				// Stores previous set of values
	double m_dAveragedJointData[NUM_AXES];
	double m_dPreviousJointData[NUM_AXES];

	// Data Arrays
	double	m_dLeftForceValues[NUM_AXES];				// Used to store incoming values from left force sensor
	double	m_dRightForceValues[NUM_AXES];				// Same for right force sensor
	double	m_dAvgActualForce[NUM_AXES];				// Holds averaged data for ATI force readings for right and left arms

	double m_dLeftJointAngles[NUM_AXES];				// Used to store actual joint angle positions for ISACs left arm
	double m_dRightJointAngles[NUM_AXES];				// Same for right arm
	double m_dAvgActualJointAngles[NUM_AXES];			// Holds averaged data for both readings of actual joint angle positions for the right and left arm of ISAC

	// Include IMA Component Bindings of type IComponent *
	IComponent* IUnkRightForceSensor;					// Input Force Sensors
	IComponent* IUnkLeftForceSensor;
	IComponent* IUnkAvgForce;							// Output force reading

	IComponent* IUnkRightActualJointAngle;				// Input Joint Angle reading
	IComponent* IUnkLeftActualJointAngle;				
	IComponent* IUnkAvgJointAngle;						// Output Joint Angle position

	// Vector Signal Pointers
	IVectorSignal*	pIVSLeftForce;
	IVectorSignal*	pIVSRightForce;
	IVectorSignal*	pIVSAvgForce;

	IVectorSignal*	pIVSLeftJointAngle;
	IVectorSignal*	pIVSRightJointAngle;
	IVectorSignal*	pIVSLAvgJointAngle;
	
	// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them
	
	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
	
};

#endif //__ISAC_ASSEMBLY_H_
