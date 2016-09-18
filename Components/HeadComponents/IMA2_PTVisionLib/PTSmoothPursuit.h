// PTSmoothPursuit.h : Declaration of the CPTSmoothPursuit

#ifndef __PTSMOOTHPURSUIT_H_
#define __PTSMOOTHPURSUIT_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\Representations\IMA2_DynamicRepsLib\IMA2_DynamicRepsLib.h"

/////////////////////////////////////////////////////////////////////////////
// CPTSmoothPursuit
class ATL_NO_VTABLE CPTSmoothPursuit : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPTSmoothPursuit, &CLSID_PTSmoothPursuit>,
	public IDispatchImpl<IPTSmoothPursuit, &IID_IPTSmoothPursuit, &LIBID_IMA2_PTVISIONLIBLib>,
	public CComponentImpl 
{
public:
	CPTSmoothPursuit(){

		// TODO: Initialize all variables
		int i;
		m_pIUnkVisualInputRep			= NULL;
		m_pIUnkMotorVector				= NULL;
		m_pIUnkTargetVelVector			= NULL;
		m_pIUnkMotorControllerLink		= NULL;

		m_sSamplingIndex				= 0;
		m_sLowPassFilterConstantIndex	= 0;
		m_sSchemaWeightsIndex			= 0;
		m_sSamplingLength				= 64;

		m_dLowPassFilterConstant[0]		= 0.65f;
		m_dLowPassFilterConstant[1]		= 0.65f;
		m_dLowPassFilterConstant[2]		= 0.65f;
		m_dLowPassFilterConstant[3]		= 0.65f;

		for(i=0;i<9;i++)
			LeftTarget[i] = RightTarget[i] = 0.0f;

		for(i=0;i<4;i++)
		{
			m_dPreviousUpdate[i] = m_dBuffAngles[i] = 0.0f;
			m_dTargetVel[i] = 0.0f;
			m_dPreviousSamplingTargetLocation[i] = 0.0f;
		}

		for(i=0;i<m_sSamplingLength;i++)
		{
			m_dVector[0][i] =
			m_dVector[1][i] =
			m_dVector[2][i] =
			m_dVector[3][i] =
			m_dVector[4][i] =
			m_dVector[5][i] =
			m_dVector[6][i] =
			m_dVector[7][i] = 0.0f;
			m_dVelVector[0][i] =
			m_dVelVector[1][i] =
			m_dVelVector[2][i] =
			m_dVelVector[3][i] = 0.0f;
		}

		SchemaWeights[0] = 0.1f;  /** left pan   **/
		SchemaWeights[1] = 0.1f;  /** left tilt  **/
		SchemaWeights[2] = 0.1f;  /** right pan  **/
		SchemaWeights[3] = 0.1f;  /** right tilt **/

		// TODO: Call SetupMechanism(ops, flags)
		// SetupMechanism( 2, 8 );

		// TODO: Setup component links
//		SetupComponentLink( &IID_IVisualInputRepresentation , &m_pIUnkVisualInputRep);
//		SetupComponentLink( &IID_IDynamicVector , &m_pIUnkMotorVector);
//		SetupComponentLink( &IID_IDynamicVector , &m_pIUnkTargetVelVector);
//		SetupComponentLink( &IID_IMotionLink, &m_pIUnkMotorControllerLink);

	}

DECLARE_REGISTRY_RESOURCEID(IDR_PTSMOOTHPURSUIT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPTSmoothPursuit)
	COM_INTERFACE_ENTRY(IPTSmoothPursuit)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IPTSmoothPursuit
public:

	// Callable Methods
	STDMETHOD(GetUpdate)(SAFEARRAY* Value, short Method);

	// Interface functions
	STDMETHOD(get_SchemaWeights)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_SchemaWeights)(/*[in]*/ double newVal);
	STDMETHOD(get_LowPassFilterConstant)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_LowPassFilterConstant)(/*[in]*/ double newVal);


private:
	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT
	// Internal Functions
	double LowPassMotor();
	void SetupMotorVector();
	void RecordMotorValue();
	void GetTargetLocation();
	void ReadTargetVelocity();
	void SampleCameraHeadAngles();
	void DoPursuit(double* Value, short Method);
	void AddToVector(long VectorNumber, long Length, double* Value, double y_Offset);
	void Add2VelVector(long VectorNumber, long Length, double * Value, double y_Offset);

	// IMA Component Links
	IComponent *m_pIUnkVisualInputRep;			// IComponent pointer to the VisualInputRep component
	IComponent *m_pIUnkMotorVector;				
	IComponent *m_pIUnkTargetVelVector;			
	IComponent *m_pIUnkMotorControllerLink;	

	// Internal Variables
	double LeftTarget[9];
	double RightTarget[9];
	double SchemaWeights[4];
	double m_dLowPassFilterConstant[4];   /*** for each left pan, left tilt, right pan, and right tilt ***/

	double m_dBuffAngles[4];
	double m_dPreviousUpdate[4];
	double m_dLowPassUpdate[4];

	double m_dSampleAngles[4];

	double m_dTargetVel[4];
	double m_dPreviousSamplingTargetLocation[4];

	double m_dVector[8][256];
	double m_dVelVector[4][256];

	short  m_sSamplingLength;
	short  m_sSamplingIndex;

	// Added indeces for IMA 2.5
	// Juan Rojas 5/05
	short	m_sLowPassFilterConstantIndex;
	short	m_sSchemaWeightsIndex;
};

#endif //__PTSMOOTHPURSUIT_H_
