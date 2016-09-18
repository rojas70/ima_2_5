//////////////////////////////////////////////////////////////
// PTCatch.cpp : Implementation of CPTCatch
// This program controls the Camera Head control units.
// It can sample or write the position of the cameras.
// It can direct the cameras to an angle location in a 
// step-wise motion. Additionally, there are methods
// used to filter incoming angular signals and then move 
// the camera head in the filtered angular direction.
// (Commonly used with the Sound Agent, which inputs 
// angular signals based on the direction of sound captured).
//////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "IMA2_PTHeadLib.h"
#include "PTCatch.h"
#include "O:\components\msvbvm60.tlh" // property bag dll
#include "math.h"

#ifndef PI
#define PI	3.14159
#define R2D	(180.0/PI)
#define D2R (PI/180.0)
#endif

/////////////////////////////////////////////////////////////////////////////
// CPTCatch

STDMETHODIMP CPTCatch::get_AxisOffset(double *pVal)
{
	// TODO: Add your implementation code here
	
	if ( pVal == NULL )
		return E_POINTER;

	if ( IndexIsValid( m_iAxisOffsetIndex ) )
		*pVal = m_pdAxisOffset[m_iAxisOffsetIndex];
	else return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP CPTCatch::put_AxisOffset(double newVal)
{
	// TODO: Add your implementation code here
	if ( IndexIsValid( m_iAxisOffsetIndex ) )
		m_pdAxisOffset[m_iAxisOffsetIndex] = newVal;

	else return E_INVALIDARG;
	
	return S_OK;
}

STDMETHODIMP CPTCatch::get_AxisOffsetIndex(int *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_iAxisOffsetIndex;
	return S_OK;
}

STDMETHODIMP CPTCatch::put_AxisOffsetIndex(int newVal)
{
	// TODO: Add your implementation code here
	m_iAxisOffsetIndex = newVal;
	return S_OK;
}

STDMETHODIMP CPTCatch::get_CommParams1(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_bsCParam1.Copy();
	return S_OK;
}

STDMETHODIMP CPTCatch::put_CommParams1(BSTR newVal)
{
	// TODO: Add your implementation code here
	m_bsCParam1 = newVal;
	return S_OK;
}

STDMETHODIMP CPTCatch::get_CommParams2(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_bsCParam2.Copy();
	return S_OK;
}

STDMETHODIMP CPTCatch::put_CommParams2(BSTR newVal)
{
	// TODO: Add your implementation code here
	m_bsCParam2 = newVal;
	return S_OK;
}

STDMETHODIMP CPTCatch::get_AxisGain(double *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal == NULL )
		return E_POINTER;

	if ( IndexIsValid( m_iAxisGainIndex ) )
		*pVal = m_pdAxisGain[m_iAxisGainIndex];
	else return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CPTCatch::put_AxisGain(double newVal)
{
	// TODO: Add your implementation code here
	if ( IndexIsValid( m_iAxisGainIndex ) )
		m_pdAxisGain[m_iAxisGainIndex] = newVal;
	
	else return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CPTCatch::get_AxisGainIndex(int *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_iAxisGainIndex;
	return S_OK;
}

STDMETHODIMP CPTCatch::put_AxisGainIndex(int newVal)
{
	// TODO: Add your implementation code here
	m_iAxisGainIndex = newVal;
	return S_OK;
}

STDMETHODIMP CPTCatch::get_AxisThreshold(long *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal == NULL )
		return E_POINTER;

	if ( IndexIsValid( m_iAxisThresholdIndex ) )
		*pVal = m_plAxisThreshold[ m_iAxisThresholdIndex ];
	else return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP CPTCatch::put_AxisThreshold(long newVal)
{
	// TODO: Add your implementation code here
	if ( IndexIsValid( m_iAxisThresholdIndex ) )
		m_plAxisThreshold[ m_iAxisThresholdIndex ] = newVal;
	else return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP CPTCatch::get_AxisThresholdIndex(int *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_iAxisThresholdIndex;
	return S_OK;
}

STDMETHODIMP CPTCatch::put_AxisThresholdIndex(int newVal)
{
	// TODO: Add your implementation code here
	m_iAxisThresholdIndex = newVal;
	return S_OK;
}

/*STDMETHODIMP CPTCatch::get_PanLimitIndex(int *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_iPanLimitIndex;
	return S_OK;
}

STDMETHODIMP CPTCatch::put_PanLimitIndex(int newVal)
{
	// TODO: Add your implementation code here
	m_iPanLimitIndex = newVal;
	return S_OK;
}

STDMETHODIMP CPTCatch::get_TiltLimitIndex(int *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_iTiltLimitIndex;
	return S_OK;
}

STDMETHODIMP CPTCatch::put_TiltLimitIndex(int newVal)
{
	// TODO: Add your implementation code here
	m_iTiltLimitIndex = newVal;
	return S_OK;
}*/


STDMETHODIMP CPTCatch::get_DeviceFilename1(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_bsDevFilename1.Copy();
	return S_OK;
}

STDMETHODIMP CPTCatch::put_DeviceFilename1(BSTR newVal)
{
	// TODO: Add your implementation code here
	m_bsDevFilename1 = newVal;
	return S_OK;
}

STDMETHODIMP CPTCatch::get_DeviceFilename2(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_bsDevFilename2.Copy();
	return S_OK;
}

STDMETHODIMP CPTCatch::put_DeviceFilename2(BSTR newVal)
{
	// TODO: Add your implementation code here
	m_bsDevFilename2 = newVal;
	return S_OK;
}


STDMETHODIMP CPTCatch::get_LeftPanSpeed(long *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal != NULL )
	{
		char strOut[35];
		char strIn[35];
		BOOL result = FALSE;

		// make the query
		sprintf( strOut, "%s ", QUERY_PAN_SPEED );
		result = SendToPTLeft( strOut );

		if ( result )
		{
			// retrieve the result
			strcpy( strIn, "" );
			result = pCommLEFT->ReadComm( strIn, 10 );

			if ( result )
			{
				long speed = ParseStringToInteger( strIn );
				*pVal = speed;
			}
			else
				return E_FAIL;
		}
		else
			return E_FAIL;
	}
	else
		return E_POINTER;
	return S_OK;
}

STDMETHODIMP CPTCatch::put_LeftPanSpeed(long newVal)
{
	// TODO: Add your implementation code here
	if ( newVal > 0 )
	{
		BOOL result = FALSE;
		char strOut[35];

		sprintf( strOut, "%s%d ", SET_PAN_SPEED, newVal );
		
		result = SendToPTLeft( strOut );

		if ( !result )
			return E_FAIL;
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CPTCatch::get_RightPanSpeed(long *pVal)
{
	// TODO: Add your implementation code here
		if ( pVal != NULL )
	{
		char strOut[35];
		char strIn[35];
		BOOL result = FALSE;

		// make the query
		sprintf( strOut, "%s ", QUERY_PAN_SPEED );
		result = SendToPTRight( strOut );

		if ( result )
		{
			// retrieve the result
			strcpy( strIn, "" );
			result = pCommRIGHT->ReadComm( strIn, 10 );

			if ( result )
			{
				long speed = ParseStringToInteger( strIn );
				*pVal = speed;
			}
			else
				return E_FAIL;
		}
		else
			return E_FAIL;
	}
	else
		return E_POINTER;

	return S_OK;
}

STDMETHODIMP CPTCatch::put_RightPanSpeed(long newVal)
{
	// TODO: Add your implementation code here
		if ( newVal > 0 )
	{
		BOOL result = FALSE;
		char strOut[35];

		sprintf( strOut, "%s%d ", SET_PAN_SPEED, newVal );
		
		result = SendToPTRight( strOut );

		if ( !result )
			return E_FAIL;
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CPTCatch::get_LeftTiltSpeed(long *pVal)
{
// TODO: Add your implementation code here
	if ( pVal != NULL )
	{
		char strOut[35];
		char strIn[35];
		BOOL result = FALSE;

		// make the query
		sprintf( strOut, "%s ", QUERY_TILT_SPEED );

		result = SendToPTLeft( strOut );

		if ( result )
		{
			// retrieve the result
			strcpy( strIn, "" );
			result = pCommLEFT->ReadComm( strIn, 10 );
			
			if ( result )
			{
				long speed = ParseStringToInteger( strIn );
				*pVal = speed;
			}
			else
				return E_FAIL;
		}
		else
			return E_FAIL;
	}
	else
		return E_POINTER;

	return S_OK;
}

STDMETHODIMP CPTCatch::put_LeftTiltSpeed(long newVal)
{
	// TODO: Add your implementation code here
	if ( newVal > 0 )
	{
		char strOut[35];
		BOOL result = FALSE;

		sprintf( strOut, "%s%d ", SET_TILT_SPEED, newVal );
		result = SendToPTLeft( strOut );

		if ( !result )
		{
			return E_FAIL;
		}
			
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CPTCatch::get_RightTiltSpeed(long *pVal)
{
// TODO: Add your implementation code here
	if ( pVal != NULL )
	{
		char strOut[35];
		char strIn[35];
		BOOL result = FALSE;

		// make the query
		sprintf( strOut, "%s ", QUERY_TILT_SPEED );

		result = SendToPTRight( strOut );

		if ( result )
		{
			// retrieve the result
			strcpy( strIn, "" );
			result = pCommRIGHT->ReadComm( strIn, 10 );
			
			if ( result )
			{
				long speed = ParseStringToInteger( strIn );
				*pVal = speed;
			}
			else
				return E_FAIL;
		}
		else
			return E_FAIL;
	}
	else
		return E_POINTER;

	return S_OK;
}

STDMETHODIMP CPTCatch::put_RightTiltSpeed(long newVal)
{
	// TODO: Add your implementation code here
	if ( newVal > 0 )
	{
		char strOut[35];
		BOOL result = FALSE;

		sprintf( strOut, "%s%d ", SET_TILT_SPEED, newVal );
		result = SendToPTRight( strOut );

		if ( !result )
		{
			return E_FAIL;
		}
			
	}
	else
		return E_INVALIDARG;
	return S_OK;
}

STDMETHODIMP CPTCatch::get_LeftPanAccel(long *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal != NULL )
	{
		char strOut[35];
		char strIn[35];
		BOOL result = FALSE;

		// make the query
		sprintf( strOut, "%s ", QUERY_PAN_ACCEL );
		result = SendToPTLeft( strOut );

		if ( result )
		{
			// retrieve the result
			strcpy( strIn, "" );
			result = pCommLEFT->ReadComm( strIn, 10 );
			
			if ( result )
			{
				long acceleration = ParseStringToInteger( strIn );

				*pVal = acceleration;
			}
			else
				return E_FAIL;
		}
		else
			return E_FAIL;
	}
	else
		return E_POINTER;

	return S_OK;
}

STDMETHODIMP CPTCatch::put_LeftPanAccel(long newVal)
{
	// TODO: Add your implementation code here
	if ( newVal > 0 )
	{
		char strOut[35];
		BOOL result = FALSE;

		sprintf( strOut, "%s%d ", SET_PAN_ACCEL, newVal );
		
		result = SendToPTLeft( strOut );

		if ( !result )
			return E_FAIL;
		
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CPTCatch::get_RightPanAccel(long *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal != NULL )
	{
		char strOut[35];
		char strIn[35];
		BOOL result = FALSE;

		// make the query
		sprintf( strOut, "%s ", QUERY_PAN_ACCEL );
		result = SendToPTRight( strOut );

		if ( result )
		{
			// retrieve the result
			strcpy( strIn, "" );
			result = pCommRIGHT->ReadComm( strIn, 10 );
			
			if ( result )
			{
				long acceleration = ParseStringToInteger( strIn );

				*pVal = acceleration;
			}
			else
				return E_FAIL;
		}
		else
			return E_FAIL;
	}
	else
		return E_POINTER;

	return S_OK;
}

STDMETHODIMP CPTCatch::put_RightPanAccel(long newVal)
{
	// TODO: Add your implementation code here
	if ( newVal > 0 )
	{
		char strOut[35];
		BOOL result = FALSE;

		sprintf( strOut, "%s%d ", SET_PAN_ACCEL, newVal );
		
		result = SendToPTRight( strOut );

		if ( !result )
			return E_FAIL;
		
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CPTCatch::get_LeftTiltAccel(long *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal != NULL )
	{
		char strOut[35];
		char strIn[35];
		BOOL result = FALSE;

		// make the query
		sprintf( strOut, "%s ", QUERY_TILT_ACCEL );
		result = SendToPTLeft( strOut );

		if ( result )
		{
			// retrieve the result
			strcpy( strIn, "" );
			result = pCommLEFT->ReadComm( strIn, 10 );
			
			if ( result )
			{
				long acceleration = ParseStringToInteger( strIn );

				*pVal = acceleration;
			}
			else
				return E_FAIL;
		}
		else
			return E_FAIL;
	}
	else
		return E_POINTER;

	return S_OK;
}

STDMETHODIMP CPTCatch::put_LeftTiltAccel(long newVal)
{
	// TODO: Add your implementation code here
	if ( newVal > 0 )
	{
		char strOut[35];
		BOOL result = FALSE;

		sprintf( strOut, "%s%d ", SET_TILT_ACCEL, newVal );
		
		result = SendToPTLeft( strOut );

		if ( !result )
			return E_FAIL;
		
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CPTCatch::get_RightTiltAccel(long *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal != NULL )
	{
		char strOut[35];
		char strIn[35];
		BOOL result = FALSE;

		// make the query
		sprintf( strOut, "%s ", QUERY_TILT_ACCEL );
		result = SendToPTRight( strOut );

		if ( result )
		{
			// retrieve the result
			strcpy( strIn, "" );
			result = pCommRIGHT->ReadComm( strIn, 10 );
			
			if ( result )
			{
				long acceleration = ParseStringToInteger( strIn );

				*pVal = acceleration;
			}
			else
				return E_FAIL;
		}
		else
			return E_FAIL;
	}
	else
		return E_POINTER;

	return S_OK;
}

STDMETHODIMP CPTCatch::put_RightTiltAccel(long newVal)
{
	// TODO: Add your implementation code here
	if ( newVal > 0 )
	{
		char strOut[35];
		BOOL result = FALSE;

		sprintf( strOut, "%s%d ", SET_TILT_ACCEL, newVal );
		
		result = SendToPTRight( strOut );

		if ( !result )
			return E_FAIL;
		
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

/*STDMETHODIMP CPTCatch::get_PanLimit(long *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal != NULL ) {

		BOOL	result1			= FALSE;
		BOOL	result2			= FALSE;
		long	pan_min_Left	= 0;
		long	pan_min_Right	= 0;
		long	pan_max_Left	= 0;
		long	pan_max_Right	= 0;
		char	strOut[35];
		char	strIn1[35];
		char	strIn2[35];

		// send&receive min. pan limit query
		sprintf( strOut, "%s ", QUERY_MIN_PAN );
		result1 = SendToPTLeft( strOut );
		result2 = SendToPTRight( strOut );

		if ( result1 && result2) {

			strcpy( strIn1, "" );
			strcpy( strIn2, "" );
			strcpy( strOut, "" );
					
			result1 = pCommLEFT->ReadComm( strIn1, 10 );
			result2 = pCommRIGHT->ReadComm( strIn2, 10 );

			if ( result1 && result2) {

				pan_min_Left	= ParseStringToInteger( strIn1 );
				pan_min_Right	= ParseStringToInteger( strIn2 );

				// send/receive max. pan limit query
				sprintf( strOut, "%s ", QUERY_MAX_PAN );
				result1 = SendToPTLeft( strOut );
				result2 = SendToPTRight( strOut );

				if ( result1 && result2 )
				{
					strcpy( strIn1, "" );
					strcpy( strIn2, "" );

					result1 = pCommLEFT->ReadComm( strIn1, 10 );
					result2 = pCommRIGHT->ReadComm( strIn2, 10 );

					if ( result1 && result2 )
					{
						pan_max_Left = ParseStringToInteger( strIn1 );
						pan_max_Right = ParseStringToInteger( strIn2 );

						// now use these two results to send back to the user.
						pVal[0] = pan_min_Left;
						pVal[1] = pan_min_Right;
						pVal[2] = pan_max_Left;		
						pVal[3] = pan_max_Right;
					}
					else
						return E_FAIL;
				}
				else
					return E_FAIL;
			}
			else
				return E_FAIL;
		}
		else
			return E_FAIL;
	}
	else
		return E_POINTER;

	return S_OK;
}

STDMETHODIMP CPTCatch::get_TiltLimit(long *pVal)
{
	// TODO: Add your implementation code here
	if ( pVal != NULL ) {

		BOOL	result1			= FALSE;
		BOOL	result2			= FALSE;
		long	tilt_min_Left	= 0;
		long	tilt_min_Right	= 0;
		long	tilt_max_Left	= 0;
		long	tilt_max_Right	= 0;
		char	strOut[35];
		char	strIn1[35];
		char	strIn2[35];

		// send&receive min. pan limit query
		sprintf( strOut, "%s ", QUERY_MIN_TILT );
		result1 = SendToPTLeft( strOut );
		result2 = SendToPTRight( strOut );
		if ( result1 && result2)
		{
			strcpy( strIn1, "" );
			strcpy( strIn2, "" );
			strcpy( strOut, "" );
					
			result1 = pCommLEFT->ReadComm( strIn1, 10 );
			result2 = pCommRIGHT->ReadComm( strIn2, 10 );

			if ( result1 && result2)
			{
				tilt_min_Left= ParseStringToInteger( strIn1 );
				tilt_min_Right= ParseStringToInteger( strIn2 );

				// send/receive max. pan limit query
				sprintf( strOut, "%s ", QUERY_MAX_TILT );
				result1 = SendToPTLeft( strOut );
				result2 = SendToPTRight( strOut );

				if ( result1 && result2 )
				{
					strcpy( strIn1, "" );
					strcpy( strIn2, "" );

					result1 = pCommLEFT->ReadComm( strIn1, 10 );
					result2 = pCommRIGHT->ReadComm( strIn2, 10 );

					if ( result1 && result2 )
					{
						tilt_max_Left = ParseStringToInteger( strIn1 );
						tilt_max_Right = ParseStringToInteger( strIn2 );

						// now use these two results to send back to the user.
						pVal[0] = tilt_min_Left;
						pVal[1] = tilt_min_Right;
						pVal[2] = tilt_max_Left;		
						pVal[3] = tilt_max_Right;
					}
					else
						return E_FAIL;
				}
				else
					return E_FAIL;
			}
			else
				return E_FAIL;
		}
		else
			return E_FAIL;
	}
	else
		return E_POINTER;


	return S_OK;
}
*/
///////////////////////////////
// Commands the head to move
///////////////////////////////
STDMETHODIMP CPTCatch::aaHeadCommand() {

	// TODO: Add your implementation code here
	SAFEARRAY* mysa;
	IVectorSignal *pIVSHeadOut = NULL;		// Vector Signal Interface type

	// Retrieve pointers to the object and interface of the Vector Signal component
	m_Bindings->get_Pointers(SysAllocString(L"DesiredAngles"),&m_pIUnkHeadAnglesOut);
	if (m_pIUnkHeadAnglesOut!=NULL)			// Added to ensure failure detection
		m_pIUnkHeadAnglesOut->QueryInterface(IID_IVectorSignal,(void **)&pIVSHeadOut);

	if ( pIVSHeadOut != NULL )
	{
		ATLTRACE(" ** Command Head\n");

		// Get desired angles from the Vector Sgianl
		mysa=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		pIVSHeadOut->GetCurrentVector( mysa );
		memcpy(m_dDesiredHeadAngles,mysa->pvData,sizeof(double)*NUM_AXES);

		// Release allocated memory
		SafeArrayDestroy(mysa);
		pIVSHeadOut-> Release();
		pIVSHeadOut = NULL;

		// Convert angles to motor pulses so that the motors can move
		HRESULT hrAngleConversionStatus = E_FAIL;
		hrAngleConversionStatus = HeadAngles2Positions( m_dDesiredHeadAngles, NUM_AXES );

		// Move the PAN-TILT motos to the desired angle..
		if ( SUCCEEDED( hrAngleConversionStatus ) )
			CommandHeadAbsolute( m_dDesiredHeadAngles, NUM_AXES );
	}
	else
	{
		if ( pIVSHeadOut != NULL )
			pIVSHeadOut->Release();

		pIVSHeadOut = NULL;

		ATLTRACE(_T("CCatch::CommandHead Failure!"));
		
	}

	return S_OK;
}

////////////////////////////////////////////
// Samples the pan-tilt unit motor position
////////////////////////////////////////////
STDMETHODIMP CPTCatch::aaHeadSample() {

	SAFEARRAY* mysa;
	// TODO: Add your implementation code here
	m_Bindings->get_Pointers(SysAllocString(L"ActualAngles"),&m_pIUnkHeadAnglesIn);
	//m_Bindings->get_Pointers(SysAllocString(L"PTVActualAngles"),&m_pIUnkHeadSample);

	IVectorSignal *pIVSHeadIn	=NULL;		// Used to read (sample) data from new head
	//IVectorSignal *pIHeadSample	=NULL;		// Used to read data from old head 09/10/03

	if(m_pIUnkHeadAnglesIn != NULL)			// Added fault detection. July 2005
		m_pIUnkHeadAnglesIn->QueryInterface(IID_IVectorSignal,(void**)&pIVSHeadIn);
	
	//if(m_pIUnkHeadSample != NULL)
		//m_pIUnkHeadSample->QueryInterface(IID_IVectorSignal,(void**)&pIHeadSample);

	if ( pIVSHeadIn != NULL /*&& pIHeadSample != NULL*/)
	{
		SampleHead( m_dCurrentHeadAngles, NUM_AXES );
           
		// Send 
		mysa=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(mysa->pvData,m_dCurrentHeadAngles,sizeof(double)*NUM_AXES);
		pIVSHeadIn->SetCurrentVector( mysa );
		SafeArrayDestroy(mysa);
		
		// Not really used in the new system
//		 In order to match the old head, the order of vector is   (09/10/03)
//		[0] = verge right; [1] = verge left; [2] = pan; [3] = tilt
//		m_pdLinkOldHeadSample = m_dCurrentHeadAngles;
//		m_pdLinkOldHeadSample[0] = -m_dCurrentHeadAngles[6];
//		m_pdLinkOldHeadSample[1] = m_dCurrentHeadAngles[6];
//		m_pdLinkOldHeadSample[2] = m_dCurrentHeadAngles[4];
//		m_pdLinkOldHeadSample[3] = m_dCurrentHeadAngles[5];

//		mysa=SafeArrayCreateVector(VT_R8,0,NUM_AXES-2);
//		memcpy(mysa->pvData,m_pdLinkOldHeadSample,sizeof(double)*(NUM_AXES-2));
//		pIHeadSample->SetCurrentVector( mysa );
//		SafeArrayDestroy(mysa);
//		}

		// Deallocate pointers
		pIVSHeadIn->Release();
		pIVSHeadIn = NULL;

//		pIHeadSample->Release();
//		pIHeadSample = NULL;
	}

	else {

		if ( pIVSHeadIn != NULL )
			pIVSHeadIn->Release();

		pIVSHeadIn = NULL;
		ATLTRACE(_T("CCatch::SampleHead Failure!"));

		//if ( pIHeadSample != NULL )
		//	pIHeadSample->Release();

		//pIHeadSample = NULL;

	}
	return S_OK;
}

STDMETHODIMP CPTCatch::SampleHead(SAFEARRAY* Val)
{
	// TODO: Add your implementation code here
	long lDatalength;

	lDatalength=Val->rgsabound->cElements;
	if(lDatalength>7)
		return 2148734216;  //COR_E_INDEXOUTOFRANGE is the best error mesage I could find -CLC

	return SampleHead((double*)Val->pvData,lDatalength);
}

// Activates a routine to move the cameras through all the range of angles to 
// rescale it's gains and move to the home position.
STDMETHODIMP CPTCatch::Reset()
{
	// TODO: Add your implementation code here

	char strOut[35];
	BOOL result1 = FALSE;
	BOOL result2 = FALSE;

	// reset pan and tilt
	sprintf( strOut, "%s ", RESET );
	result1 = SendToPTLeft( strOut );
	result2 = SendToPTRight( strOut );

	if ( result1 && result2 )
	{
		m_plCurrentSample[ LEFT_PAN  ] = 0;
		m_plCurrentSample[ LEFT_TILT ] = 0;
		m_plCurrentSample[ RIGHT_PAN ] = 0;
		m_plCurrentSample[ RIGHT_TILT] = 0;
	}
	else
		return E_FAIL;

	return S_OK;
}


STDMETHODIMP CPTCatch::Stop()
{
	char strOut[35];
	BOOL result1 = FALSE;
	BOOL result2 = FALSE;

	sprintf( strOut, "%s ", HALT_ALL );
	result1 = SendToPTLeft( strOut );
	result2 = SendToPTRight( strOut );

	if ( !result1 || !result2 )
		return E_FAIL;

	return S_OK;
}

HRESULT CPTCatch::CommandHeadRelative(double *Val, long Length)
{
	// Local variables
	char strOut[35];

	if ( Val != NULL )
	{
		if ( ( pCommLEFT != NULL ) && ( pCommRIGHT != NULL ) )
		{

			// calculate values to send out.
			for ( int i = 0; i < NUM_AXES; i++ )
				m_psOut[i] = Val[i] * m_pdAxisGain[i] + m_pdAxisOffset[i];

			// pan
			if ( abs( m_psOut[ LEFT_PAN ] ) >= m_plAxisThreshold[ LEFT_PAN ] )
			{
				sprintf( strOut, "%s%d ", COMMAND_PAN_REL, m_psOut[ LEFT_PAN ] );
				SendToPTLeft( strOut );
				m_plCurrentSample[ LEFT_PAN ] += Val[ LEFT_PAN ];
			}

			if ( abs( m_psOut[ RIGHT_PAN ] ) >= m_plAxisThreshold[ RIGHT_PAN ] )
			{
				sprintf( strOut, "%s%d ", COMMAND_PAN_REL, m_psOut[ RIGHT_PAN ] );
				SendToPTRight( strOut );
				m_plCurrentSample[ RIGHT_PAN ] += Val[ RIGHT_PAN ];
			}

			// tilt
			if ( abs( m_psOut[ LEFT_TILT ] ) >= m_plAxisThreshold[ LEFT_TILT ] )
			{
				sprintf( strOut, "%s%d ", COMMAND_TILT_REL, m_psOut[ LEFT_TILT ] );
				SendToPTLeft( strOut );
				m_plCurrentSample[ LEFT_TILT ] += Val[ LEFT_TILT ];
			}

			if ( abs( m_psOut[ RIGHT_TILT ] ) >= m_plAxisThreshold[ RIGHT_TILT ] )
			{
				sprintf( strOut, "%s%d ", COMMAND_TILT_REL, m_psOut[ RIGHT_TILT ] );
				SendToPTRight( strOut );
				m_plCurrentSample[ RIGHT_TILT ] += Val[ RIGHT_TILT ];
			}
		}// if the comm ports were opened properly //

	}// if pVal is usable //
	else return !S_OK;

	return S_OK;
}

HRESULT CPTCatch::SampleHead(double *Val, long Length)
{
	// Get the new pan and tilt positions.
	BOOL result = FALSE;
	
	// Get pan and tilt positions for both right and left cameras. Save in m_plCurrentSample[]
	result = DPSample();

	// Ensure the function was successful
	if ( !result )
		return E_FAIL;

	// If the value is not null 
	if ( Val != NULL )
	{
		// Copy PT values over to local array
		Val[ LEFT_PAN  ] = (double) m_plCurrentSample[ LEFT_PAN ];  // Val[0]
		Val[ RIGHT_PAN ] = (double) m_plCurrentSample[ RIGHT_PAN ];	// Val[2]
		Val[ LEFT_TILT ] = (double) m_plCurrentSample[ LEFT_TILT ];	// Val[1]
		Val[ RIGHT_TILT] = (double) m_plCurrentSample[ RIGHT_TILT ];// Val[3]

		// Convert PT steps to angles
		HeadPositions2Angles( Val, 4 );

		// When people use the old system and need a singular value for the pan angle vs. 2,
		// We can call the command:
		// CalculateOverallPanTilt(Val);      // added on 08/05/03

		// If this is the case, HeadPositions2Angles() is called afterwards.
	}

	else return !S_OK;

	return S_OK;
}

/********************************************************************************************
/* CommandHeadAbsolute(SAFEARRAY* Val)
/* This function is called from IMA2_PTVisionLib Project.
/* It is called in the DoProportionalTracking() method.
/* That call asks the head to move and passes a SafeArray array
/* that contains 4 Angles: Left Pan, Left Tilt, Right Pan, Right Tilt.
/* This function in turns calls the overloaded function CommandHeadAbsolute(Value, length)
/* that moves the head to the desired angles.
********************************************************************************************/
STDMETHODIMP CPTCatch::CommandHeadAbsolute(SAFEARRAY *Val)
{
	// Local variable
	long lDatalength;

	// Get data length from SafeArray structure
	lDatalength=Val->rgsabound->cElements;

	// Make sure data does not exceed our expected number of elements
	if(lDatalength>NUM_AXES)
		return 2148734216;  //COR_E_INDEXOUTOFRANGE is the best error mesage I could find -CLC

	return CommandHeadAbsolute((double*)Val->pvData,lDatalength);
}

/********************************************************************************************
/* CommandHeadAbsolute(double *Val, long Length)
/* This function is called from IMA2_PTVisionLib Project.
/* It is called in the DoProportionalTracking() method.
/* That call asks the head to move and passes a SafeArray array
/* that contains 4 Angles: Left Pan, Left Tilt, Right Pan, Right Tilt.
/* This function in turns calls the overloaded function CommandHeadAbsolute(Value, length)
/* that moves the head to the desired angles.
********************************************************************************************/
HRESULT CPTCatch::CommandHeadAbsolute(double *Val, long Length)
{
	// Local variables
	char strOut[35];
	BOOL result = FALSE;

	// Check to ensure that the values passed in are not NULL
	if ( Val != NULL )
	{

		// Print message to the debug window when running debug mode
		ATLTRACE("** CPTCatch::CommandHeadAbsolute = %.0f %.0f %.0f %.0f", Val[LEFT_PAN], Val[LEFT_TILT], Val[RIGHT_PAN], Val[RIGHT_TILT] );
		
		// Make sure the CommPorts are not NULL
		if ( ( pCommLEFT != NULL ) && ( pCommRIGHT != NULL ) )
		{
			// calculate values to send out.
			for ( int i = 0; i < NUM_AXES; i++ )
			{
				m_psOut[i] = Val[i] * m_pdAxisGain[i] + m_pdAxisOffset[i];
				m_plCurrentSample[i] = Val[i];
			}

			// Send the command for the left pan
			if ( ExceedsThreshold( m_psOut[ LEFT_PAN ], LEFT_PAN ) )			// Check to ensure that the maximum angle was not exceeded
			{
				sprintf( strOut, "%s%d ", COMMAND_PAN_ABS, m_psOut[LEFT_PAN] );	// Copy string and value to strout
				SendToPTLeft( strOut );											// Send value to CommPort
			}

			// Send the command for the right pan
			if ( ExceedsThreshold( m_psOut[ RIGHT_PAN ], RIGHT_PAN ) )
			{
				sprintf( strOut, "%s%d ", COMMAND_PAN_ABS, m_psOut[RIGHT_PAN] );
				SendToPTRight( strOut );
			}

			// Send the command for the left tilt
			if ( ExceedsThreshold( m_psOut[ LEFT_TILT ], LEFT_TILT ) )
			{
				sprintf( strOut, "%s%d ", COMMAND_TILT_ABS, m_psOut[LEFT_TILT] );
				SendToPTLeft( strOut );
			}

			// Send the command for the right tilt
			if ( ExceedsThreshold( m_psOut[ RIGHT_TILT ], RIGHT_TILT ) )
			{
				sprintf( strOut, "%s%d ", COMMAND_TILT_ABS, m_psOut[RIGHT_TILT] );
				SendToPTRight( strOut );
			}

		}	// if the comm ports were opened properly 

	}		// if pVal is usable 

	else 
		return !S_OK;

	return S_OK;
}

// Write data to right CommPort
BOOL CPTCatch::SendToPTRight(char *pStr)
{
	// Local variable
	BOOL commResult = FALSE;

	// Check to make sure the right CommPort is connected
	if ( pCommRIGHT != NULL )
	{
		commResult = pCommRIGHT->WriteComm( pStr );		// Send value to port
	}

	else
		commResult = FALSE;
	
	return commResult;
}

BOOL CPTCatch::SendToPTLeft(char *pStr)
{
	BOOL commResult = FALSE;

	if ( pCommLEFT != NULL )
	{
		commResult = pCommLEFT->WriteComm( pStr );	
	}
	else
		commResult = FALSE;
	
	return commResult;
}

bool CPTCatch::IndexIsValid(long Index)
{
	return ( ( Index >= 0 ) && ( Index < NUM_AXES ) );
}

int CPTCatch::ParseStringToInteger(char *pStr)
{
	char	newStr[35];
	int		result = -1;

	// chop the first two characters
	strcpy( newStr, &(pStr[2]) );
	
	// find the position of the newline character
	int newline_position = 0;
	char* strJunk = strchr( newStr, '\n' );

	if ( strJunk != NULL )
	{
		newline_position = strJunk - newStr;

		// chop off the end of the string
		newStr[newline_position] = '\0';

		// ...finally, convert the integer.
		result = atoi( newStr );
	}
	else
		result = -1;

	return result;
}

// Sample the position of the PT system
BOOL CPTCatch::DPSample()
{
	// Local variables
	char strOut[35];
	char strIn[35];
	BOOL result = FALSE;

	// get left Pan-tilt unit position

	// Initialize the strings
	strcpy( strIn, "" );
	strcpy( strOut, "" );

	// Check that the left CommPort is not null
	if ( pCommLEFT != NULL)
	{
		// Query the system for the pan angle
		sprintf( strOut, "%s ", QUERY_PAN );
		SendToPTLeft( strOut );

		strcpy( strOut, "" );

		result = pCommLEFT->ReadComm( strIn, 10 );

		//*****************************************************************************
		// The Sampling of data is executed twice to increase chances of reading a better angle
		// both for the Pan and the Tilt.
		// added on 10/25/03
		//*****************************************************************************

		// LEFT PAN
		// Run # 1
		// Tell the system we are querying for the pan angle
		strcpy( strIn, "" );						// Initialize StringIn
		sprintf( strOut, "%s ", QUERY_PAN );		// Copy the query command to StringOut
		SendToPTLeft( strOut );						// Send the command

		strcpy( strOut, "" );						// Initialize StringOut
		result = pCommLEFT->ReadComm( strIn, 10 );	// Read the result (in PT steps not angles) and place in StringIn
	
		// Run # 2
		strcpy( strIn, "" );
		sprintf( strOut, "%s ", QUERY_PAN );
		SendToPTLeft( strOut );

		strcpy( strOut, "" );
		result = pCommLEFT->ReadComm( strIn, 10 );

		// The result is a string as it would appear in a prompt. Must parse stringn to isolate numerical value
		// Check to make sure we got a result:
		if ( result)
		{
			// Print to debug window
			ATLTRACE("** DPSAMPLE LEFT PAN = %s\n", strIn );

			// Parse the string
			// The returned command looks like: "* 0", so parse it properly.
			m_plCurrentSample[ LEFT_PAN ] = ParseStringToInteger( strIn );
			
			// ***** GET LEFT TILT ****
			strcpy( strIn, "" );
			strcpy( strOut, "" );

			sprintf( strOut, "%s ", QUERY_TILT );			// Copy command to query left tilt
			SendToPTLeft( strOut );							// Send command

			result = pCommLEFT->ReadComm( strIn, 10 );		// Read result

			// Check to make sure we get a result
			if ( result)
			{
				// Print to debug window
				ATLTRACE("** DPSAMPLE LEFT TILT = %s\n", strIn );

				// Parse string to isolate numerical value
				m_plCurrentSample[ LEFT_TILT ] = ParseStringToInteger( strIn );
			}
			else
				return FALSE;
		}
		else
			return FALSE;
	}

	// ***** RIGHT PAN *****
	strcpy( strIn, "" );
	strcpy( strOut, "" );

	// Check to make sure we are connected to the right CommPort
	if ( pCommRIGHT != NULL)
	{
		// Retrieve the right pan
		sprintf( strOut, "%s ", QUERY_PAN );		// Copy command to query for right pan
		SendToPTRight( strOut );					// Send command

		strcpy( strOut, "" );						// Initialize string

		result = pCommRIGHT->ReadComm( strIn, 10 );	// Read result in steps

		// Check to ensure that there is a result
		if ( result )
		{
			// Print to debug window
			ATLTRACE("** DPSAMPLE RIGHT PAN = %s\n", strIn );

			// Parse the string
			// the returned command looks like: "* 0", so parse it properly.
			m_plCurrentSample[ RIGHT_PAN] = ParseStringToInteger( strIn );
			
			// ***** GET TILT POSITION *****
			strcpy( strIn, "" );
			strcpy( strOut, "" );

			sprintf( strOut, "%s ", QUERY_TILT );			// Copy command to query right tilt
			SendToPTRight( strOut );						// Send command

			result = pCommRIGHT->ReadComm( strIn, 10 );		// Read result

			// Check to make sure we got result
			if ( result )
			{
				// Print to debug window
				ATLTRACE("** DPSAMPLE RIGHT TILT = %s\n", strIn );

				// Parse string to isolate numerical value
				m_plCurrentSample[ RIGHT_TILT] = ParseStringToInteger( strIn );
			}
			else
				return FALSE;
		}
		else
			return FALSE;
	}
	return TRUE;
}

BOOL CPTCatch::ExceedsThreshold(long Val, long axis_index)
{
		if (abs(Val - m_plCurrentSample[axis_index]) >= m_plAxisThreshold[axis_index])
		return TRUE;
	else
		return FALSE;

}

//////////////////////////////////////////////////////////////////////////
// Function to obtain verge angles and a single pan-tilt 
// angle from two cameras (08/05/03)
// Val = [LP LT RP RT OverallPan Avg Tilt VergeAngles]
// Notes on the mathematical theory can be found in:
// Cis\common\InetPub\wwwroot\IRL\Doc\Head\Head Change\Isac_Vis_Angles
//////////////////////////////////////////////////////////////////////////

bool CPTCatch::CalculateOverallPanTilt(double* Val)
{
	double dtempL, dtempR, Alpha, AA, BB;
	double ThetaLeft, ThetaRight;

	// Collect and Allocate Catch Angles from Input Vector
	dtempL = Val[0];
	dtempR = Val[2];

	// Converting from degrees to radians
	ThetaLeft	= D2R*(90-dtempL);
	ThetaRight	= D2R*(90+dtempR);

	// Calculate overall pan
	// This equation is to find a singular pan from two cameras
	// The document can be found at Cis\common\InetPub\wwwroot\IRL\Doc\Head\Head Change\Finding a Singular Pan

	Alpha = atan (sin(ThetaRight-ThetaLeft)/(2*sin(ThetaLeft)*sin(ThetaRight)));
	
	// Store this in the 5th element of the array  as an overall pan angle in degrees
	Val[4] = R2D * Alpha;    // clockwise angles are negative 

	// Calculate average Tilt
	Val[5] = (Val[1] + Val[3]) / 2;

	// Converting from degrees to radians
	dtempL = D2R*dtempL;
	dtempR = D2R*dtempR;

	// Calculate verge angles	
	AA = sin(dtempR-dtempL);
	BB = pow(cos(dtempR),2)+ pow(cos(dtempL),2) + 2*cos(dtempR)*sin(dtempL)*cos(dtempR-dtempL);
	BB = pow(BB,0.5);
	Val[6] = atan(AA/BB) * R2D;

	// calculate overall pan
	//	Val[4] = atan((tan(dtempL)+tan(dtempR))/2) * R2D;

	return TRUE;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert old commands for the PTV Head (left verge, right verge, pan, and tilt)
// to the form of the PT Head (left pan, left tilt, right pan, right tilt, overall pan, avg. tilt) 
// 
// Notes on the mathematical theory can be found in:
// Cis\common\InetPub\wwwroot\IRL\Doc\Head\Head Change\Isac_Vis_Angles
// Li Sun 11/18/03
////////////////////////////////////////////////////////////////////////////////////////////////////
void CPTCatch::CalculateLeftRightAngles(double* Val1, double* Val2, double VergeAngle)
{
	double dtempV, dtempP, AA, BB,CC;

	// Collect and Allocate Catch Angles from Input Vector
	dtempV = VergeAngle;
	dtempP = Val2[0];		// left pan

	// Converting from degrees to radians
	dtempV = D2R*dtempV;
	dtempP = D2R*dtempP;

	// Calculate the left and right pan angles using the Verge Angle information and Pan angle information provided.
	AA = cos(dtempV) * sin(dtempP) + sin(dtempV);
	CC = cos(dtempV) * sin(dtempP) - sin(dtempV);
	BB = cos(dtempV) * cos(dtempP);

	// We are setting the values of m_dDesiredHeadAngles to left/right pan
	Val1[0] = atan(CC/BB) * R2D;	// Left Pan
	Val1[2] = atan(AA/BB) * R2D;	// Right Pan

	// Left and right tilt angles are equal to the old tilt angle
	Val1[1] = Val2[1];	// Left tilt in new head(Val1[1]) is equal to overall tilt
	Val1[3] = Val2[1];	// Right tilt (Val1[3]) is equal to overall tilt
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Convert commands commands from a single pan (coming from the Sound Localization)
// agent, to LP LT RP RT. Assume verge angles are 15 degrees.
// 
// Notes on the mathematical theory can be found in:
// Cis\common\InetPub\wwwroot\IRL\Doc\Head\Head Change\Isac_Vis_Angles
// Juan Rojas 11/18/03
////////////////////////////////////////////////////////////////////////////////////////////////////
void CPTCatch::CalculatePanTiltAngles(double* Val1, double* Val2)
{
	double dtempV, dtempP, AA, BB,CC;

	// Collect and Allocate Catch Angles from Input Vector
	dtempV = 5;			// This small verge angles helps in having more direct angles w/ cameras
							// Used to be 15 degrees, experimenting with 5 degrees, 3/20/04
	dtempP = Val2[2];		// left pan

	// Converting from degrees to radians
	dtempV = D2R*dtempV;
	dtempP = D2R*dtempP;

	// Calculate the left and right pan angles using the Verge Angle information and Pan angle information provided.
	AA = cos(dtempV) * sin(dtempP) + sin(dtempV);
	CC = cos(dtempV) * sin(dtempP) - sin(dtempV);
	BB = cos(dtempV) * cos(dtempP);

	// We are setting the values of m_dDesiredHeadAngles to left/right pan
	Val1[0] = atan(AA/BB) * R2D;	// This formula is for theta R, and we assigned it to the left pan
									// because it is the left camera looking into them. It would be theta R
									// in the model we used.

	Val1[2] = atan(CC/BB) * R2D;	// Right Pan -  this pan uses the equation for theta L. Look at the file.

	// Left and right tilt angles are equal to the old tilt angle
	Val1[1] = Val2[3];	// Left tilt in new head(Val1[1]) is equal to overall tilt
	Val1[3] = Val2[3];	// Right tilt (Val1[3]) is equal to overall tilt
}


////////////////////////////////////////
// Convert motor steps/pulses to angles
////////////////////////////////////////
HRESULT CPTCatch::HeadPositions2Angles(double *pVal, long Length)
{
		// Position 2 Angle conversion
	if ( pVal != NULL )
	{
		pVal[ LEFT_PAN  ] = pVal[ LEFT_PAN  ] * PULSE_TO_ANG_PAN_LEFT;
		pVal[ LEFT_TILT ] = pVal[ LEFT_TILT ] * PULSE_TO_ANG_TILT;
		pVal[ RIGHT_PAN ] = pVal[ RIGHT_PAN ] * PULSE_TO_ANG_PAN_RIGHT;
		pVal[ RIGHT_TILT] = pVal[ RIGHT_TILT] * PULSE_TO_ANG_TILT;
	}
	else
		return E_POINTER;

	return S_OK;
}

////////////////////////////////////////
// Convert angles to motor steps/pulses 
////////////////////////////////////////
HRESULT CPTCatch::HeadAngles2Positions(double *pVal, long length)
{
	// Angle 2 Position conversion
	if ( pVal != NULL )
	{
		pVal[ LEFT_PAN  ] =  pVal[ LEFT_PAN  ] / PULSE_TO_ANG_PAN_LEFT;
		pVal[ LEFT_TILT ] =  pVal[ LEFT_TILT ] / PULSE_TO_ANG_TILT;
		pVal[ RIGHT_PAN ] =  pVal[ RIGHT_PAN ] / PULSE_TO_ANG_PAN_RIGHT;
		pVal[ RIGHT_TILT] =  pVal[ RIGHT_TILT] / PULSE_TO_ANG_TILT;
	}
	else
		return E_POINTER;

	return S_OK;
}

// The OnConstruct Function sets all the bindings for the component, and \
// also replaces FinalComponentInitialization
STDMETHODIMP CPTCatch::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	IMA2_BindingInfo	m_Binding;
	int numiids=1;
	long x[1];
	x[0]=0;

	// PTV Write Motor - Sends position to motors
/*	m_Binding.Name		= SysAllocString(L"PTVActualAngles");					
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	

	// Free Binding Info
	SysFreeString(m_Binding.Name);
	SysFreeString(m_Binding.Path);
	SafeArrayDestroy(m_Binding.PIDs);
	SafeArrayDestroy(m_Binding.IIDs);
*/	
	// PT Read Motor - Retrieves motor current position
	m_Binding.Name		= SysAllocString(L"DesiredAngles");					
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	

	// Free Binding Info
	SysFreeString(m_Binding.Name);
	SysFreeString(m_Binding.Path);
	SafeArrayDestroy(m_Binding.PIDs);
	SafeArrayDestroy(m_Binding.IIDs);
	
	// PT Write Motor - Sends position to motors
	m_Binding.Name		= SysAllocString(L"ActualAngles");					
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IVectorSignal"));
	m_ConfigureBindings->Add(&m_Binding);										// Set up the clients bindings array.	

	// Free Binding Info
	SysFreeString(m_Binding.Name);
	SysFreeString(m_Binding.Path);
	SafeArrayDestroy(m_Binding.PIDs);
	SafeArrayDestroy(m_Binding.IIDs);
	
	return S_OK;
}

STDMETHODIMP CPTCatch::OnDestruct()			{ return S_OK; }
STDMETHODIMP CPTCatch::Load(VARIANT Data)	{ return S_OK; }
STDMETHODIMP CPTCatch::Save(VARIANT *pData) { return S_OK; }

//////////////////////////////////
// Initialize
// Move head to the home position and set speeds and accelerations to the max
// For more look at the documentation under O:\Documentation\System\PTMotors
//////////////////////////////////
STDMETHODIMP CPTCatch::Initialize()
{
	// Local variables
	double val[4] = {0,0,0,0};

	// If no tilt is desired, set the values to zero
	//if(m_bTiltFlag == FALSE)
	//	for(int i=0; i<4;i++) val[i] = 0.0;

	// Convert angles to motor pulses so that the motors can move
	HRESULT hrAngleConversionStatus = E_FAIL;
	hrAngleConversionStatus = HeadAngles2Positions( val, NUM_AXES );

	// Move the PAN-TILT motos to the desired angle..
	if(SUCCEEDED( hrAngleConversionStatus ))
		CommandHeadAbsolute(val,NUM_AXES);

	return S_OK;
}