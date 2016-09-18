// ComputePosition.h : Declaration of the CComputePosition

#ifndef __COMPUTEPOSITION_H_
#define __COMPUTEPOSITION_H_

#include "resource.h"       					// main symbols
#include "O:\Base Classes\ComponentImpl.h"		// Component Lib file
#include "O:\Components\msvbvm60.tlh"			// property bag dll
#include "O:\Components\MultiTypeComponents\IMA2_BasicComponentsLib\IMA2_BasicComponentsLib.h"		//VectorSignal functionality
/////////////////////////////////////////////////////////////////////////////
// CComputePosition
class ATL_NO_VTABLE CComputePosition : 
	public CComObjectRootEx<CComSingleThreadModel>,	
	public CComCoClass<CComputePosition, &CLSID_ComputePosition>,
	public IDispatchImpl<IComputePosition, &IID_IComputePosition, &LIBID_IMA2_3DPOSITIONLIBLib>,
	public CComponentImpl 
{
public:
	CComputePosition()
	{
		int i = 0;
		// Incoming Angles
		for(i=0;i<4;i++)
			m_dIncomingAngles[i]	= 0;

		// Outgoing position
		for(i=0;i<3;i++)
		{
			m_dPosition[i]			= 0;
			m_dPreviousPositions[i] = 0;
			m_dAveragePositions[i]	= 0;
		}

		// Gain for averaging filter
		alpha						= 0.50;

		// Trigonometric variables
		
		// Section 1
		thetaL	= 0.0; 
		thetaR	= 0.0;
		PhiLeft = 0.0;
		PhiRight= 0.0;
		PhiTilt	= 0.0;
		dtempL	= 0.0;
		dtempR	= 0.0;
		t		= 0.0;
		A		= 279.4;
		Hyp		= 0.0;
		X		= 0.0;
		Y		= 0.0;
		Z		= 0.0;

		// Section 2
		height			= 6.4;
		length			= 5.0;

		intrinsic_angle	= 0;
		tot_tilt_angle	= 0;
		tilt_hyp		= 0;

		X_tilt			= 0;
		Z_tilt			= 0;

		pan_hyp			= 0;
		X_pan			= 0;
		Y_pan			= 0;

		X_hat			= 0;
		Y_hat			= 0;
		Z_hat			= 0;

		// Initialize pointers	
		m_pCartesianPosition	= NULL;
		m_pHeadInput			= NULL;

	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMPUTEPOSITION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CComputePosition)
	COM_INTERFACE_ENTRY(IComputePosition)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()
// IComputePosition
// This is where all your interface methods will appear and be displayed on DAD
public:
	STDMETHOD(FindCartesianCoordinates)();

private:
	// Angle and Position arrays
	double		m_dIncomingAngles[4];
	double		m_dPosition[3];
	double		m_dPreviousPositions[3];
	double		m_dAveragePositions[3];

	// Averaging gain for positions
	double		alpha;

	// Trigonometric variables
	// Section 1 of computations (see the method FindCartesianCoordinates() )
	double	thetaL, thetaR;						// Interior angles of triangle
	double	PhiLeft, PhiRight, PhiTilt;			// Tilt angles
	double	dtempL, dtempR;
	double	t, A;								// Hypoteneuse of outside triangle, and baseline
	double	Hyp;								// Hypoteneuse of triangle constructed by the singular pan angle
	double	X, Y, Z;							// Cartesian coordiantes

	// Section 2
	double height, length;						// Lengths of camera, from extremities to the center point
	double intrinsic_angle;						// The natural angle formed by the armature of the PT system
	double tot_tilt_angle;						// The sum of the tilt angle and the intrinsic angle
	double tilt_hyp;							// The hypotenuse in the tilt system

	double X_tilt;								// The new distance for X in the tilt system
	double Z_tilt;								// Thew new distance for Z in the tilt system

	double pan_hyp;								// The hypoteneuse formed in the pan system (it's a function of the tilt angle)
	double X_pan;								// It's the new X due to the pan system which is a function of the tilt system
	double Y_pan;								// Same as above for Y.

	double X_hat, Y_hat, Z_hat;					// Average total results for both cameras

	// Interface members
	IComponent	*m_pCartesianPosition;				// Used to output the Cartesian Position
	IComponent	*m_pHeadInput;						// Used as input to receive info from head.
	
	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData); 
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT
	// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them
};

#endif //__COMPUTEPOSITION_H_
