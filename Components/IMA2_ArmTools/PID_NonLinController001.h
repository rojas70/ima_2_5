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
		m_pKp    = NULL;
		m_pKi    = NULL;
		m_pKd    = NULL;
		m_A0     = NULL;
		m_A1     = NULL;
		m_A2     = NULL;
		m_A3     = NULL;
		m_A4     = NULL;
/*		m_Amp1   = NULL;				// Amplitudes of Gaussian Phasic Functions
		m_Amp2   = NULL;
		m_Amp3   = NULL;
		m_Mu1    = NULL;				// Centers of Gaussian Phasic Functions
		m_Mu2    = NULL;
		m_Mu3    = NULL;
		m_Sigma1 = NULL;				// Widths of Gaussian Phasic Functions
		m_Sigma2 = NULL;
		m_Sigma3 = NULL;*/
		m_pMaxClamp			= NULL;
		m_pMinClamp			= NULL;
		m_pIntegrator		= NULL;
//		m_pStartAngle		= NULL;
		m_pBiasedPressure	= NULL;		
		m_pControl_Law		= NULL;
		m_pInvertPressure	= NULL;
		m_pAlpha			= NULL;
//		m_pPrevPressure		= NULL;     // Previous pressures sent to arm
//		m_pPressure			= NULL;
		m_pAngleDirection	= NULL;
		//m_pIntegrator2		= NULL;		// integrator for new control law March 27, 2000


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
/*
		if (m_Amp1 == NULL)
			m_Amp1 = new double[MAX_AXES];
		assert( m_Amp1 != NULL );


		if (m_Amp2 == NULL)
			m_Amp2 = new double[MAX_AXES];
		assert( m_Amp2 != NULL );


		if (m_Amp3 == NULL)
			m_Amp3 = new double[MAX_AXES];
		assert( m_Amp3 != NULL );


		if (m_Mu1 == NULL)
			m_Mu1 = new double[MAX_AXES];
		assert( m_Mu1 != NULL );


		if (m_Mu2 == NULL)
			m_Mu2 = new double[MAX_AXES];
		assert( m_Mu2 != NULL );


		if (m_Mu3 == NULL)
			m_Mu3 = new double[MAX_AXES];
		assert( m_Mu3 != NULL );


		if (m_Sigma1 == NULL)
			m_Sigma1 = new double[MAX_AXES];
		assert( m_pKd != NULL );


		if (m_Sigma2 == NULL)
			m_Sigma2 = new double[MAX_AXES];
		assert( m_Sigma2 != NULL );

		
		if (m_Sigma3 == NULL)
			m_Sigma3 = new double[MAX_AXES];
		assert( m_Sigma3 != NULL );

*/
		if (m_pMaxClamp == NULL)
			m_pMaxClamp = new double[MAX_AXES];
		assert( m_pMaxClamp != NULL );


		if (m_pMinClamp == NULL)
			m_pMinClamp = new double[MAX_AXES];
		assert( m_pMinClamp != NULL );


		if (m_pIntegrator == NULL)
			m_pIntegrator = new double[MAX_AXES];
		assert( m_pIntegrator != NULL );


//		if (m_pStartAngle == NULL)
//			m_pStartAngle = new double[MAX_AXES];
//		assert( m_pStartAngle != NULL );


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


//		if (m_pPrevPressure == NULL)
//			m_pPrevPressure = new double[MAX_AXES];
//		assert( m_pPrevPressure != NULL );


//		if (m_pPressure == NULL)
//			m_pPressure = new double[MAX_AXES];
//		assert( m_pPressure != NULL );


		if (m_pAngleDirection == NULL)
			m_pAngleDirection = new long[MAX_AXES];
		assert( m_pAngleDirection != NULL );


//		if (m_pIntegrator2 == NULL)
//			m_pIntegrator2 = new double[MAX_AXES];
//		assert( m_pIntegrator2 != NULL );


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
/*			m_Amp1[Index]		= 0.0;
			m_Amp2[Index]		= 0.0;
			m_Amp3[Index]		= 0.0;
			m_Mu1[Index]		= 0.0;
			m_Mu2[Index]		= 0.0;
			m_Mu3[Index]		= 0.0;
			m_Sigma1[Index]		= 1.0;
			m_Sigma2[Index]		= 1.0;
			m_Sigma3[Index]		= 1.0;*/
			m_pMaxClamp[Index]			=  1600.0;
			m_pMinClamp[Index]			= -1600.0;
			m_pIntegrator[Index]		= 0.0;			// Controller state variable
			m_pBiasedPressure[Index]	= 2000.0;		// {1000,2000,2000,2000,2000,2000}
//			m_pStartAngle[Index]		= 0.0;
			m_pControl_Law[Index]		= 0;			// Control type,	0 Po+/-deltaP
														//					1 Ag/Antag
														//					2 Antag/Ag
			m_pAlpha[Index]				= 100.0;		// Was 50 in the code but 100 in Agent Builder
//			m_pPrevPressure[Index]		= 0.0;			// Was 1000.0 before feedforward term added.
//			m_pPressure[Index]			= 0.0;
			m_pAngleDirection[Index]	= 0;
//			m_pIntegrator2[Index]		= 0.0;

			// 12-Joint Data
//			m_PressureMax[2*Index]			=	4000.0;
//			m_PressureMax[2*Index+1]		=	4000.0;
			
			m_pCurrentPressures[2*Index]	=	0.0;	// i.e. 0,2,4,6,8,10,12
			m_pCurrentPressures[2*Index+1]	=	0.0;	// i.e. 1,3,5,7,9,11,
/*			m_dTonicOffset[2*Index]			=	0.0;
			m_dTonicOffset[2*Index+1]		=	0.0;


			m_pProprioIntegrator[Index] = 0.0;
			m_B0[Index]					= 0.0;		// Polynomial coeffs for  Theta(t) for memorized reaching movement
			m_B1[Index]					= 0.0;
			m_B2[Index]					= 0.0;
			m_B3[Index]					= 0.0;
			m_B4[Index]					= 0.0;
			m_B5[Index]					= 0.0;
			m_B6[Index]					= 0.0;
			m_C0[Index]					= 0.0;     // Polynomial coeffs for  t(Theta) for memorized reaching movement
			m_C1[Index]					= 0.0;
			m_C2[Index]					= 0.0;
			m_C3[Index]					= 0.0;
			m_C4[Index]					= 0.0;
			m_C5[Index]					= 0.0;
			m_C6[Index]					= 0.0;*/
//			m_pVelRef[Index]			= 0.0;
//			m_pPrevThetaRef[Index]		= 0.0;	
//			m_pProprioAntAgPressBuff[Index]		= 0.0;
//			m_pProprioAgPressBuff[Index]		= 0.0;
//			m_pProprioAgStiffFactor[Index]		= 0.0;
//			m_pProprioAntAgStiffFactor[Index]	= 0.0;



/*			m_pKpPhas[0][Index]	=	0.0;   // Allow THREE different gains for accel, move, decel
			m_pKiPhas[0][Index]	=	0.0;
			m_pKdPhas[0][Index]	=	0.0;

			m_pKpPhas[1][Index]	=	0.0;   // Allow THREE different gains for accel, move, decel
			m_pKiPhas[1][Index]	=	0.0;
			m_pKdPhas[1][Index]	=	0.0;

			m_pKpPhas[2][Index]	=	0.0;   // Allow THREE different gains for accel, move, decel
			m_pKiPhas[2][Index]		=	0.0;
			m_pKdPhas[2][Index]	=	0.0;
			m_pThetaErrorThreshold[Index]	= 0.0;	*/
			
		}

		// First index of pressure bias is set to 1000 here. The rest are set to 2000 in the previous For-loop.
		m_pBiasedPressure[0] = 1000.0;

		//  CONTROL LAW		
		//	SO, if m_pControl_Law	== 0,  Control Law is Po+/-DeltaP   (for both rubbertuator i and rubbertuator i+1)
		//							== 1,  Control Law is Ag/Antag		(for rubbertuator i and rubbertuator i+1)
		//							== 2,  Control Law is Antag/Ag		(for rubbertuator i and rubbertuator i+1)
		
		// Invert Pressure
		m_bInvertPressure[0] = FALSE;
		m_bInvertPressure[1] = TRUE;
		m_bInvertPressure[2] = TRUE;
		m_bInvertPressure[3] = FALSE;
		m_bInvertPressure[4] = TRUE;
		m_bInvertPressure[5] = FALSE;

		m_pInvertPressure[0] = 0;
		m_pInvertPressure[1] = 1;
		m_pInvertPressure[2] = 1;
		m_pInvertPressure[3] = 0;
		m_pInvertPressure[4] = 1;
		m_pInvertPressure[5] = 0;	// Initial values copied from agent file to here for Right arm
									// need to update with an interface

//		m_dArmMovingThreshold		= 0.0010;
//		m_dStartAngleResetThreshold	= 0.5235;     // Angle is in Radians ~ 30 degrees
//		m_dSpeedFactor				= 1.0;

		//m_dStartMovingTime			= 0.0;
//		m_dPhasicTime				= 0.0;
		m_Axes = 6;					// Default to what we need.
		m_bDataAvailable			= FALSE;
		//m_bPhasicMove				= FALSE;
		//m_bStop						= FALSE;
		//m_bProprioceptive			= FALSE;
		m_InitializeDataLength		= 0;
		m_DataLength				= 0;
		m_bstrInputFile				= SysAllocString(L"O:\\ArmFiles\\Temp\\Pressures.txt");
		m_pFile						= fopen("O:\\ArmFiles\\ArmData.txt","w+");      assert( m_pFile != NULL );
		
//		m_dMovementOnsetTime		= 0.0;
//		m_dMovementEndTime			= 0.0;
//		m_dTimeOffset				= 0.0;
//		m_dPrevPhasicTime			= 0.0;
//		m_dTimeDelay				= 0.0;	

		// Temporary Variable (Agonist-Pressures) for Debugging: m_dAgPressBuff
//		for (i=0; i < 4000; i++)
//			for (Index = 0; Index < MAX_AXES+1; Index++)
//				m_dAgPressBuff[Index][i]    = 0.0 ;

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
/*
	if (m_Amp1 != NULL)
		delete [] m_Amp1;
	
	if (m_Amp2 != NULL)
		delete [] m_Amp2;

	if (m_Amp3 != NULL)
		delete [] m_Amp3;

	if (m_Mu1 != NULL)
		delete [] m_Mu1;

	if (m_Mu2 != NULL)
		delete [] m_Mu2;

	if (m_Mu3 != NULL)
		delete [] m_Mu3;

	if (m_Sigma1 != NULL)
		delete [] m_Sigma1;

	if (m_Sigma2 != NULL)
		delete [] m_Sigma2;

	if (m_Sigma3 != NULL)
		delete [] m_Sigma3;
*/
//	if (m_pStartAngle != NULL)
//		delete [] m_pStartAngle;

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

	if(m_pFile != NULL)
		fclose(m_pFile);

	if (m_pAlpha != NULL)
		delete [] m_pAlpha;

//	if (m_pPrevPressure != NULL)
//		delete [] m_pPrevPressure;

//	if (m_pPressure != NULL)
//		delete [] m_pPressure;

	if (m_pAngleDirection != NULL)
		delete [] m_pAngleDirection;

//	if (m_pIntegrator2 != NULL)
//		delete [] m_pIntegrator2;
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
	STDMETHOD(Read_CurrentPressure)();
	STDMETHOD(Read_DataFile)();
	STDMETHOD(PID_NonLin_12Press)();
	STDMETHOD(PID_NonLin_6Press)();
	STDMETHOD(LoadPropertiesFromFile)(BSTR Filename);
	//STDMETHOD(LoadFileGaussian)(BSTR Filename);
	STDMETHOD(LoadCoeffsFromFile)(BSTR Filename);
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

	STDMETHOD(get_InputFileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_InputFileName)(/*[in]*/ BSTR newVal);
//	STDMETHOD(get_ArmMovingThreshold)(/*[out, retval]*/ double *pVal);
//	STDMETHOD(put_ArmMovingThreshold)(/*[in]*/ double newVal);
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

	// Internal Functions
	STDMETHOD(Initial)();

	// Internal Variables

	short  *m_pControl_Law;
	short  *m_pInvertPressure;
	long   *m_pAngleDirection;
	double *m_pKp;
	double *m_pKi;
	double *m_pKd;
	double *m_A0;
	double *m_A1;
	double *m_A2;
	double *m_A3;
	double *m_A4;
	/*double *m_Amp1;		// Amplitudes of Gaussian Phasic Functions
	double *m_Amp2;
	double *m_Amp3;
	double *m_Mu1;			// Centers of Gaussian Phasic Functions
	double *m_Mu2;
	double *m_Mu3;
	double *m_Sigma1;		// Widths of Gaussian Phasic Functions
	double *m_Sigma2;
	double *m_Sigma3;*/
	double *m_pMaxClamp;
	double *m_pMinClamp;
	double *m_pIntegrator;
	//double *m_pStartAngle;
	double *m_pBiasedPressure;
	double *m_pAlpha;
	//double *m_pPrevPressure;
//	double *m_pPressure;
//	double *m_pIntegrator2;							// Integrator for new control law 04/27/2000
//	double  m_dAgPressBuff[MAX_AXES+1][4000];		// Temporary Variable for Debugging

// Proprioceptive Control Variables
	//double  m_dMovementOnsetTime;
	//double  m_dMovementEndTime;
	//double  m_dTimeOffset;
	//double	m_dTimeDelay;
	/*double  m_pProprioIntegrator[MAX_AXES];
	double  m_B0[MAX_AXES];		// Polynomial coeffs for  Theta(t) for memorized reaching movement
	double  m_B1[MAX_AXES];
	double  m_B2[MAX_AXES];
	double  m_B3[MAX_AXES];
	double  m_B4[MAX_AXES];
	double  m_B5[MAX_AXES];	
	double  m_B6[MAX_AXES];
	double  m_C0[MAX_AXES];     // Polynomial coeffs for  t(Theta) for memorized reaching movement
	double  m_C1[MAX_AXES];
	double  m_C2[MAX_AXES];
	double  m_C3[MAX_AXES];
	double  m_C4[MAX_AXES];
	double  m_C5[MAX_AXES];
	double  m_C6[MAX_AXES];*/
	//double  m_pVelRef[MAX_AXES];
	//double  m_pPrevThetaRef[MAX_AXES];
	//double  m_dPrevPhasicTime;
	//double  m_pKpPhas[3][MAX_AXES];   // Allow three different gains for accel, move, decel
	//double  m_pKiPhas[3][MAX_AXES];
	///double  m_pKdPhas[3][MAX_AXES];
	//double  m_pThetaErrorThreshold[MAX_AXES];
	//double	m_pProprioAgPressBuff[MAX_AXES];
	//double  m_pProprioAntAgPressBuff[MAX_AXES];
	//double  m_pProprioAgStiffFactor[MAX_AXES];
	//double  m_pProprioAntAgStiffFactor[MAX_AXES];

//	double  m_dArmMovingThreshold;
//	double  m_dStartAngleResetThreshold;
//	double	m_dSpeedFactor;
//	double  m_dStartMovingTime;					// may need to cast from DWORD
	//double  m_dPhasicTime;						// may need to cast from DWORD

	long    m_Axes;

	BSTR	m_bstrInputFile;					// For input file. Changed to BSTR from CComBSTR
	FILE     *m_fp;
			
	BOOL	m_bInvertPressure[MAX_AXES];
	BOOL    m_bDataAvailable;					// boolean to see if the data has been read
	//BOOL	m_bPhasicMove;						// boolean to see if Phasic Move is going to start
	//BOOL	m_bStop;							// TEMPORARY VARIABLE BECAUSE AGENT NOT CHANGING STATES QUICKLY, Feb 27, 2001 SGN
	//BOOL	m_bProprioceptive;

	// Read Data File Variables
	long    m_DataLength;
	long    m_InitializeDataLength;
	long    m_TonicDataLength;					// Same length as the number of milisecs of movement

	double	**m_TonicPressures;					//  Vector of vectors: [num of pressure vectors][12 pressures]
//	double	m_PressureMax[2*MAX_AXES];
	double	m_pCurrentPressures[2*MAX_AXES];
//	double	m_dTonicOffset[2*MAX_AXES];			// offset between final closed loop pressures and initial Tonic pressures

	// Binding variables
	IComponent *m_pIUnkInputState;
	IComponent *m_pIUnkOutput;
	IComponent *m_pIUnkDesiredState;
	IComponent *m_pIUnkBiasedPressureState;

	// File variables
	FILE *m_pFile;								// Opens "O:\\ArmFiles\\ArmData.txt"
	FILE *m_pFileCoefs;							// Reads m_A0-m_A4
	FILE *m_pFileProps;							// Loads Properties from file: Kp,i,d, Max/MinClamp, Ctrl_Law...
	//FILE *m_pFileProprioCoeffs;
//	FILE *m_pFileGaussian;

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
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT
};

#endif //__PID_NonLinController_H_
