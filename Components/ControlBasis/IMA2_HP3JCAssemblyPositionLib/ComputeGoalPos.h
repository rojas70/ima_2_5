// ComputeGoalPos.h : Declaration of the CComputeGoalPos

#ifndef __COMPUTEGOALPOS_H_
#define __COMPUTEGOALPOS_H_

#include "resource.h"       					// main symbols
#include "O:\Base Classes\ComponentImpl.h"		// Component Lib file
#include "O:\Components\msvbvm60.tlh"			// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h"
#include "O:\Include\IMA2_MatlabStateMachineLib.h"
#include "O:\Include\IMA2_ColorSegmenterLib.h"
#include "O:\Include\IMA2_PTHeadLib.h"
#include "O:\Include\IMA2_PTVisionLib.h"

// Define Color Models
#define BLUE_COLOR  0
#define GREEN_COLOR 1
/////////////////////////////////////////////////////////////////////////////
// CComputeGoalPos
class ATL_NO_VTABLE CComputeGoalPos : 
	public CComObjectRootEx<CComSingleThreadModel>,	
	public CComCoClass<CComputeGoalPos, &CLSID_ComputeGoalPos>,
	public IDispatchImpl<IComputeGoalPos, &IID_IComputeGoalPos, &LIBID_IMA2_HP3JCASSEMBLYPOSITIONLIBLib>,
	public CComponentImpl 
{
public:
	CComputeGoalPos()
	{
		int i		= 0;
		retVal		= 0;
		WhatRobot	= 0;	

		// Flags
		m_bStable			= 0;
		m_bHP3JC			= 0;
		m_bGoalHasBeenFound = 0;

		// Centroids
		for(i=0; i<2; i++)
		{
			m_dLeftCentroid[i] = 0.0;
			m_dRightCentroid[i] = 0.0;
		}

		for(i=0; i<4; i++)
			m_dCentroidError[i] = 0.0;


		// 3D Outputs
		for(i=0; i<3; i++)
		{
			m_dHP3JC_3D_Output[i] = 0.0;
			m_dISAC_3D_Output[i]  = 0.0;
			m_dGoalPosition[i]    = 0.0;
		}
		
		// Error Parameters
		m_dErrorLeft			= 0.0;						
		m_dErrorRight			= 0.0;			

		m_dThresholdBlue		= 0.006;			
		m_dThresholdGreen		= 0.006;
		m_dThreshold			= 0.0;

		m_dPrevErrorLeft		= 1.0;		// Cannot start with an error of zero, otherwise the min value would never be selected
		m_dPrevErrorRight		= 1.0;
		// Previouslly we only had one variable for this. m_dThreshold	= 0.002; //0.003;//	0.004; // 0.005				// Threshold to determine if system is stable

		for(i=0; i<2; i++)
		{
			m_dMinErrorBlue[i]	= 0.0;						
			m_dMinErrorGreen[i]	= 0.0;
		}

		// File stream
		m_fp = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMPUTEGOALPOS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CComputeGoalPos)
	COM_INTERFACE_ENTRY(IComputeGoalPos)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()
// IComputeGoalPos

public:
	//STDMETHOD(get_Error)(/*[out, retval]*/ double *pVal);
	//STDMETHOD(put_Error)(/*[in]*/ double newVal);
	//STDMETHOD(get_ErrorThreshold)(/*[out, retval]*/ double *pVal);
	//STDMETHOD(put_ErrorThreshold)(/*[in]*/ double newVal);
	STDMETHOD(ComputeGoalPosition)();

private:

	short  CheckHeadStability(short TypeOfColorModel);

	short  StartSM();
	short  StopSM(bool stable);

	short  GetPosition(bool WhatRobot);
	short  ComputeHP3JCTransform();

	short  WriteNewColorModel(short TypeOfColorModel);

	// Member variables
	short	retVal;					// Flag to check return value of functions
	bool	WhatRobot;				// Flag to indicate what robot is selected
	bool	m_bGoalHasBeenFound;	// Flag to indicate whether the goal has been found, related to State Machine performance.

	// Flags	
	bool	m_bStable;				// Stability flag
	bool	m_bHP3JC;				// Indicates whether the HP3JC position detection completed successfully

	// Centroid Variables
	double m_dLeftCentroid[2];			// Hold centroid values
	double m_dRightCentroid[2];
	double m_dCentroidError[4];			// Holds 2 pans and 2 tilts

	// Error variables
	// Centroids
	double m_dErrorLeft;				// Error accumulation for centroids in the left image (x,y)
	double m_dErrorRight;				// Error accumulation for centroids in the left image (x,y)

	// Error thresholds for blue and green color models
	double m_dThresholdBlue;			// Threshold to determine stability on blue color model
	double m_dThresholdGreen;			// Threshold to determine stability on green color model
	double m_dThreshold;				// Will save the values in blue or green

	// Min Values
	double m_dPrevErrorLeft;			// Holds previous values of history. Useful in computing min error.
	double m_dPrevErrorRight;			// Holds previous values of history. Useful in computing min error.

	double m_dMinErrorBlue[2];			// Holds value of lowest recorded error throughout the program. Index 0 = left image, 1 = right image.
	double m_dMinErrorGreen[2];			// Holds value of lowest recorded error throughout the program

	// 3D Cartesian Coordinates
	double m_dHP3JC_3D_Output[3];		// Holds 3D output for HP3JC
	double m_dISAC_3D_Output[3];		// Holds 3D output for ISAC
	double m_dGoalPosition[3];			// Holds the goal position generaged by the previous arrays.

	// IMA Functions

	// Centroid Components and Interfaces
	IComponent*		IUnkLeftCentroidPtr;		// IComponent Pointers
	IComponent*		IUnkRightCentroidPtr;
	IVectorSignal*	pILC;						// VectorSignal Interfaces
	IVectorSignal*	pIRC;

	// 3DOutput Components and Interfaces
	IComponent*		IUnk3dOuputPtr;				// IComponent Pointer
	IVectorSignal*	pI3D;						// VectorSignal Interface

	// State Machine
	IComponent*		IUnkStateMachinePtr;		// IComponent Pointer
	IStateMachine*	pISM;						// MatlabStateMachine Interface

	// ColorSegmenter
	IComponent*		IUnkLeftColorSegPtr;		// IComponent Pointers
	IComponent*		IUnkRightColorSegPtr;
	IColorSegmenter* pILCS;						// ColorSegmenter Interface
	IColorSegmenter* pIRCS;						// ColorSegmenter Interface

	// Error
	IComponent*		IUnkError;
	IVectorSignal*	pIError;					// VectorSignal Interfaces

	// File stream
	FILE *		m_fp;							// Pointer to file strea

	// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them
	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
	// Include IMA Component Bindings of type IComponent *

};

#endif //__COMPUTEGOALPOS_H_
