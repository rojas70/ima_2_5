// Saccade.h : Declaration of the CSaccade

#ifndef __SACCADE_H_
#define __SACCADE_H_

#include "resource.h"       // main symbols
#include "VisualInputRepresentation.h"

#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh" // property bag dll
#include "O:\Components\Representations\IMA2_DynamicRepsLib\IMA2_DynamicRepsLib.h"

/**** Neural Network file *****/
#include "I:\Include\NeuralNet.h"


/////////////////////////////////////////////////////////////////////////////
// CSaccade
class ATL_NO_VTABLE CSaccade : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSaccade, &CLSID_Saccade>,
	public IDispatchImpl<ISaccade, &IID_ISaccade, &LIBID_IMA2_PTVISIONLIBLib>,
	public CComponentImpl 
{
public:
	CSaccade():
  				// DP Pan
  				MOTOR_RANGE_ANGLES_PAN(318.0f),	// pan angle range
				MOTOR_RANGE_PULSES_PAN(6182.0),	// pulses in servo's range
				PULSE_TO_ANG_PAN((double) (MOTOR_RANGE_ANGLES_PAN/MOTOR_RANGE_PULSES_PAN)),

    			// DP Tilt
				MOTOR_RANGE_ANGLES_TILT(106.0f),	// tilt angle range	
				MOTOR_RANGE_PULSES_TILT(2061.0f),	// pulses in servo's range
				PULSE_TO_ANG_TILT((double) (MOTOR_RANGE_ANGLES_TILT/MOTOR_RANGE_PULSES_TILT))

	{
		int i;
		// TODO: Initialize all variables
		m_pIUnkVisualInputRep = NULL;

		m_sNeuralNetFileName[0] = "I:\\Src\\Mechanisms\\PTVisionCompProj\\PTposw1";
		m_sNeuralNetFileName[1] = "I:\\Src\\Mechanisms\\PTVisionCompProj\\PTposw2";
		m_sNeuralNetFileName[2] = "I:\\Src\\Mechanisms\\PTVisionCompProj\\PTposb1";
		m_sNeuralNetFileName[3] = "I:\\Src\\Mechanisms\\PTVisionCompProj\\PTposb2";

		m_bNeuralNetReady = FALSE;

		for(i=0;i<4;i++)
			UpdateAngles[i] = 0.0f;

		for(i=0;i<9;i++)
			LeftTarget[i] = RightTarget[i] = 0.0f;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SACCADE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSaccade)
	COM_INTERFACE_ENTRY(ISaccade)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// ISaccade
public:

	// Main Interface Callable Function
	STDMETHOD(aaSaccade)();
	
	// Other Functions
	STDMETHOD(SaccadeFunction)(double *ImagePosition, double *MotorOutput);
	STDMETHOD(GetUpdate)(long CameraID, double* Value);	
	
	void DoSaccade(long CameraID, double *Value);
	void DoSaccade(long CameraID);
	void ComputeAngles(double x,double y,double* updateAngles);
	void ClearTargetLocation();
	void ClearTargetVariables();
	void SetTargetLocation();
	void GetTargetLocation();
	
	IComponent* m_pIUnkVisualInputRep;
	
	// Neural Net variables
	NeuralNet net;
	BOOL InitializeNeuralNet();
	BOOL m_bNeuralNetReady;
	CComBSTR  m_sNeuralNetFileName[4];

	double UpdateAngles[4];
	double LeftTarget[9];
	double RightTarget[9];

	// DP Pan
	const double MOTOR_RANGE_ANGLES_PAN;	// pan angle range	
	const double MOTOR_RANGE_PULSES_PAN;	// left pulses in servo's range
	const double PULSE_TO_ANG_PAN;

	// DP Tilt
	const double MOTOR_RANGE_ANGLES_TILT;	// tilt angle range	
	const double MOTOR_RANGE_PULSES_TILT;	// pulses in servo's range
	const double PULSE_TO_ANG_TILT;


private:
	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component


};

#endif //__SACCADE_H_
