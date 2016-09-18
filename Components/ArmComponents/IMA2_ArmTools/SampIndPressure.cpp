// SampIndPressure.cpp : Implementation of CSampIndPressure
#include "stdafx.h"
#include "IMA2_ArmTools.h"
#include "SampIndPressure.h"
#include <math.h>
#include <winioctl.h>
#include "O:\Include\IMA2_Softarmioctl.h"
#include "O:\Include\IMA2_BasicComponentsLib.h"

/////////////////////////////////////////////////////////////////////////////
// CSampIndPressure
//
// This class computed Joint Angles, Velocities, and accelerations from raw encoder values
// It also sets valve values from Physical and Logical Angles input. 
// 
// It seems it was originally intended to convert desired filtered desired logical angles to
// desired physical angles, however it does not seems this code does that. Similarly, it was intended
// to send the Pressure commands to the servo valves.
//
// The HW controls are accessed through different byte values (I think represented in HEX)
// Look at O:\Inlcude\IMA2_SoftArmIoctl.h
//
// Z-Masking:
// It seems (though not sure) that every time an encoder has gone through one 
// revolution, a counter is updated to record this event. If Z-Masking is enabled,
// it seems like this flag would be ignored.
// 
// Juan Rojas. Nov 2005.
///////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CSampIndPressure::get_DeviceFilename(BSTR * pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
	{	
		ATLTRACE("CSampIndPressure::GetDeviceFilename\n");
		SysReAllocString(pVal,m_ArmDeviceFilename);
		
		return S_OK;
	}
	else
		return E_FAIL;	
}

STDMETHODIMP CSampIndPressure::put_DeviceFilename(BSTR newVal)
{
	
	// TODO: Add your implementation code here
	m_ArmDeviceFilename = SysAllocString(newVal);
	ATLTRACE("CSampIndPressure::PutDeviceFilename\n");

	return S_OK;
}


STDMETHODIMP CSampIndPressure::get_SamplingPeriod(short * pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal = m_ServoLoopWaitTime;

	ATLTRACE("CSampIndPressure::GetSamplingPeriod\n");

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_SamplingPeriod(short newVal)
{
	
	// TODO: Add your implementation code here
	if (newVal >= 0)
		m_ServoLoopWaitTime = newVal;

	ATLTRACE("CSampIndPressure::PutSamplingPeriod\n");
	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_EncoderGainIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sEncoderGainIndex;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_EncoderGainIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sEncoderGainIndex = newVal;

	return S_OK;
}


STDMETHODIMP CSampIndPressure::get_EncoderGain(double * pVal)
{
	

	// TODO: Add your implementation code here
	if ((pVal != NULL)&&(m_sEncoderGainIndex < NUM_AXES))
		*pVal = m_EncoderGain[m_sEncoderGainIndex];

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_EncoderGain(double newVal)
{
	
	// TODO: Add your implementation code here
	if (m_sEncoderGainIndex < NUM_AXES)
		m_EncoderGain[m_sEncoderGainIndex] = newVal;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_EncoderOffsetIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sEncoderOffsetIndex;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_EncoderOffsetIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sEncoderOffsetIndex = newVal;

	return S_OK;
}


STDMETHODIMP CSampIndPressure::get_EncoderOffset(double * pVal)
{
	// TODO: Add your implementation code here

	if ((pVal != NULL)&&(m_sEncoderOffsetIndex < NUM_AXES))
		*pVal = m_EncoderOffset[m_sEncoderOffsetIndex];


	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_EncoderOffset(double newVal)
{
	// TODO: Add your implementation code here
	if (m_sEncoderOffsetIndex < NUM_AXES)
		m_EncoderOffset[m_sEncoderOffsetIndex] = newVal;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_BiasedPressureIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sBiasedPressureIndex;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_BiasedPressureIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sBiasedPressureIndex = newVal;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_BiasedPressure(double * pVal)
{
	

	// TODO: Add your implementation code here
	if ((pVal != NULL)&&(m_sBiasedPressureIndex < NUM_AXES))
		*pVal = m_BiasedPressure[m_sBiasedPressureIndex];

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_BiasedPressure(double newVal)
{
	
	// TODO: Add your implementation code here
	if (m_sBiasedPressureIndex < NUM_AXES)
		m_BiasedPressure[m_sBiasedPressureIndex] = newVal;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_PressureMaxIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sPressureMaxIndex;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_PressureMaxIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sPressureMaxIndex = newVal;
	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_PressureMax(double * pVal)
{
	
	// TODO: Add your implementation code here
	if ((pVal != NULL)&&(m_sPressureMaxIndex < NUM_AXES))
		*pVal = m_PressureMax[m_sPressureMaxIndex];

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_PressureMax(double newVal)
{
	
	// TODO: Add your implementation code here
	if (m_sPressureMaxIndex < NUM_AXES)
		m_PressureMax[m_sPressureMaxIndex] = newVal;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_EncoderMaxIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sEncoderMinIndex;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_EncoderMaxIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sEncoderMinIndex = newVal;
	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_EncoderMax(double * pVal)
{
	
	// TODO: Add your implementation code here
	if ((pVal != NULL)&&(m_sEncoderMaxIndex < NUM_AXES))
		*pVal = m_EncoderMax[m_sEncoderMaxIndex];

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_EncoderMax(double newVal)
{
	
	// TODO: Add your implementation code here
	if (m_sEncoderMaxIndex < NUM_AXES)
		m_EncoderMax[m_sEncoderMaxIndex] = newVal;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_EncoderMinIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sEncoderMinIndex;
	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_EncoderMinIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sEncoderMinIndex = newVal;
	return S_OK;
}


STDMETHODIMP CSampIndPressure::get_EncoderMin(double * pVal)
{
	
	// TODO: Add your implementation code here
	if ((pVal != NULL)&&(m_sEncoderMinIndex < NUM_AXES))
		*pVal = m_EncoderMin[m_sEncoderMinIndex];

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_EncoderMin(double newVal)
{
	
	// TODO: Add your implementation code here
	if (m_sEncoderMinIndex < NUM_AXES)
		m_EncoderMin[m_sEncoderMinIndex] = newVal;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_HomeAnglesIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sHomeAnglesIndex;
	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_HomeAnglesIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal <= NUM_AXES)
		m_sHomeAnglesIndex = newVal;
	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_HomeAngles(double * pVal)
{
	if ((pVal != NULL)&&(m_sHomeAnglesIndex < NUM_AXES))
		*pVal=m_pdHomeAngles[m_sHomeAnglesIndex];

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_HomeAngles(double newVal)
{
	if (m_sHomeAnglesIndex < NUM_AXES)
		m_pdHomeAngles[m_sHomeAnglesIndex]=newVal;

	return S_OK;
}


STDMETHODIMP CSampIndPressure::get_InvertPressureIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal=m_sInvertPressureIndex;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_InvertPressureIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES)
		m_sInvertPressureIndex = newVal;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_InvertPressure(BOOL * pVal)
{
	
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	if (m_sInvertPressureIndex < NUM_AXES)
	{
			*pVal = m_bInvertPressure[m_sInvertPressureIndex];
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_InvertPressure(BOOL newVal)
{
	
	// TODO: Add your implementation code here
	if (m_sInvertPressureIndex < NUM_AXES)
	{
		m_bInvertPressure[m_sInvertPressureIndex] = newVal;
	}
	else
		return E_INVALIDARG;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_NumAxes(long * pVal)
{
	if (pVal != NULL)
		*pVal = m_lNumAxes;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_NumAxes(long newVal)
{
	m_lNumAxes = newVal;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::get_ZMask(long * pVal)
{
	
	// TODO: Add your implementation code here
	if (pVal == NULL)
		return E_POINTER;

	 *pVal = m_ZMaskFlags;

	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_ZMask(long newVal)
{
	
    // The following parameters are used in the IOCTL call
	BOOL				IoctlResult;
    USHORT				InputBuffer;		// Input buffer for DeviceIoControl	
    LONG                IoctlCode;
    ULONG               DataLength;
    ULONG               ReturnedLength;		// Number of bytes returned in output buffer	

	// TODO: Add your implementation code here
	m_ZMaskFlags = newVal;		// 0x00 Blocks All  Z's //0x3f Passes All Z-Phases 
								// Enabling the mask will AND 0x00 with an incoming byte causing the output to be all 0's
								// Disabling the mask with AND 0x34 (0011 1111) with an incoming byte causing the lowest 6 bits
								// to be passed and the highest 2 bits to be set to 0 (ignored).
								// After looking at Northrup's Thesis (\\cis\crl\ima\documents\master's thesis
								// I will go ahead and say that 0x00 BLOCKS the signals (does not reset the z-phase)
								// b/c the encoder revolution is different than the joint revolution... see thesis for more.

	// Now actually make the hardware have this z-flag setting as well:
	// Disable Z masking for the whole arm
	if (m_ArmDeviceHandle != INVALID_HANDLE_VALUE)
		{
			// Inputs to DeviceIOControl
			IoctlCode	= IOCTL_SOFTARM_WRITE_ZMASK;	// operation to be performed on device driver
			DataLength	= sizeof(USHORT);
			InputBuffer = m_ZMaskFlags;			

			IoctlResult = DeviceIoControl(
                        m_ArmDeviceHandle,		// Handle to device
                        IoctlCode,              // IO Control code for Write
                        &InputBuffer,           // Buffer to driver.  Holds port & data.
                        DataLength,             // Length of buffer in bytes.
                        NULL,                   // Buffer from driver.   Not used.
                        0,                      // Length of buffer in bytes.
                        &ReturnedLength,        // Bytes placed in OUTBUFFER.  Should be 0.
                        NULL                    // NULL means wait till I/O completes.
                        );
		 ATLTRACE(_T("SoftarmSampler::Wrote Z-Mask Registers.\n"));
		}

	return S_OK;
}


STDMETHODIMP CSampIndPressure::get_LeftArm(short *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_LeftArm;
	return S_OK;
}

STDMETHODIMP CSampIndPressure::put_LeftArm(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal  < 0 || newVal > 1)
		return !S_OK;

	m_LeftArm = newVal;

	// RETURN LEFT ARM VALUES
	if (m_LeftArm == 1) 
	{
		// Home XYZRPY Position: Symmetrical but opposite home position for the arm. 
		m_pdXYZRPYPos[1]	=  415.0;		// Only its horizontal (y-axis changes)	

		// Encoder Gain - values for left arm
		m_EncoderGain[1]	= -5092.0;

		// Encoder offset - valudes changed from before. They were: {-580.0, -7398.0, 13332.0, -9832.0, 199.0, -599.0};
		// They were computed by tools found in O:\System\Tools\Softarm Encoder Arm Test in Jan. 2006
		m_EncoderOffset[0]	=  2364.0;
		m_EncoderOffset[1]	=  7833.0;	
		m_EncoderOffset[2]	= 11082.0;
		m_EncoderOffset[3]	= -9832.0;
		m_EncoderOffset[4]	=   833.0;
		m_EncoderOffset[5]	=-29764.0;

	}

	// RETURN RIGHT ARM VALUES
	else if (m_LeftArm == 0) 
	{
		// Home XYZRPY Position: Symmetrical but opposite home position for the arm. 
		m_pdXYZRPYPos[1]	= -415.0;	

		// Encoder Gain value for right arm
		m_EncoderGain[1]	=  5092.0;
	
		// Encoder offset - valudes changed from before. 
		// They were computed by tools found in O:\System\Tools\Softarm Encoder Arm Test in Jan. 2006
		m_EncoderOffset[0]	=  -406.0;
		m_EncoderOffset[1]	= -7113.0;
		m_EncoderOffset[2]	= 12654.0;
		m_EncoderOffset[3]	= -9403.0;
		m_EncoderOffset[4]	=   220.0;
		m_EncoderOffset[5]	=  -671.0;
	}
	else
		return !S_OK;


	return S_OK;
}


STDMETHODIMP CSampIndPressure::Initialize()
{
	// TODO: Add your implementation code here
	INT					Index, Index2, Press_Incr;
	ULONG				DataLength, ReturnedLength;
    LONG                IoctlCode;
	BOOLEAN				IoctlResult;
   	SoftarmSamplingInfo	Info;
	char *str;


	USES_CONVERSION;

// No longer necessary for new Motenc Cards  12/13/07
// Open the device I/O handle and close any existing handles
// Beep(600,100);

	if (m_ArmDeviceHandle != INVALID_HANDLE_VALUE)	// Maybe we are being re-initialized
		CloseHandle(m_ArmDeviceHandle);			

	str = OLE2T((BSTR)m_ArmDeviceFilename);			// Open new file in case this is a new setup

	// Open the Device "file"
	m_ArmDeviceHandle = CreateFile(
                str,             
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ,
                NULL,OPEN_EXISTING,0,NULL);
	

	if (m_ArmDeviceHandle == INVALID_HANDLE_VALUE)
	{
		ATLTRACE(_T("CSoftarmSampler::Unable to open arm device!\n"));
		::MessageBox(NULL,"Invalid device name.\nTest Mode Only.","Softarm Sampler Warning",MB_OK|MB_TOPMOST|MB_SETFOREGROUND);
		Beep(200,600);	// For debugging. Params: freq,duration
		return 0;
	}

// Setup the device driver for timed sampling mode based on sampling freq:
	IoctlCode = IOCTL_ENABLE_SAMPLING_MODE; // operation performed on device driver
	DataLength = sizeof(SoftarmSamplingInfo);
	Info.EnableSampling = TRUE;
	Info.SamplingPeriod =  m_ServoLoopWaitTime;

		IoctlResult = DeviceIoControl(
                        m_ArmDeviceHandle,      // Handle to device driver
                        IoctlCode,              // IO Control code for Write
                        &Info,					// Buffer to driver.  Holds port & data.
                        DataLength,             // Length of buffer in bytes.
                        NULL,                   // Buffer from driver.   Not used.
                        0,                      // Length of buffer in bytes.
                        &ReturnedLength,        // Bytes placed in outbuf.  Should be 0.
                        NULL                    // NULL means wait till I/O completes.        
						);

	if (IoctlResult == 0)
	{
		ATLTRACE(_T("CSoftarmSampler::Setup failed."));
		return E_FAIL;
	}
	else
	{	
		Press_Incr = 10;
		
		// set all the pressures to zero
		for (Index = 0; Index < NUM_AXES ; Index++)
		{
		m_PressureOutputs[0][Index] =  0;
		m_PressureOutputs[1][Index] =  0;
		}
		SampleFunction(0);   // hardware I/O


		// Set the pressures to slowly inflate the arm during initialiazation
		for (Index2 = 0; Index2 < 50; Index2++)
		{	
			m_PressureOutputs[0][0] += 4*Press_Incr;		// right and left rubbertuators - joint 0
			m_PressureOutputs[1][0] += 4*Press_Incr;
			m_PressureOutputs[0][4] += 4*Press_Incr;		// right and left rubbertuators - joint 4...
			m_PressureOutputs[1][4] += 4*Press_Incr;
			m_PressureOutputs[0][5] += 4*Press_Incr;
			m_PressureOutputs[1][5] += 4*Press_Incr;

			m_PressureOutputs[0][1] += 1*Press_Incr;
			m_PressureOutputs[1][1] += 1*Press_Incr;
			m_PressureOutputs[0][2] += 1*Press_Incr;
			m_PressureOutputs[1][2] += 1*Press_Incr;
			m_PressureOutputs[0][3] += 1*Press_Incr;
			m_PressureOutputs[1][3] += 1*Press_Incr;

			SampleFunction(0);  // hardware I/O
			Sleep(100);
		}
	}
	
	return S_OK;
}

STDMETHODIMP CSampIndPressure::Reset()
{
	// TODO: Add your implementation code here

	int					Index;
	ULONG				DataLength, ReturnedLength;
    LONG                IoctlCode;
	BOOLEAN				IoctlResult;
   	SoftarmSamplingInfo	Info;
	char				*str;

	USES_CONVERSION;

// Setup the device driver for timed sampling mode based on sampling freq:
	IoctlCode = IOCTL_ENABLE_SAMPLING_MODE; // operation performed on device driver
	DataLength = sizeof(SoftarmSamplingInfo);
	Info.EnableSampling = TRUE;
	Info.SamplingPeriod =  m_ServoLoopWaitTime;

		IoctlResult = DeviceIoControl(
                        m_ArmDeviceHandle,      // Handle to device driver
                        IoctlCode,              // IO Control code for Write
                        &Info,					// Buffer to driver.  Holds port & data.
                        DataLength,             // Length of buffer in bytes.
                        NULL,                   // Buffer from driver.   Not used.
                        0,                      // Length of buffer in bytes.
                        &ReturnedLength,        // Bytes placed in outbuf.  Should be 0.
                        NULL                    // NULL means wait till I/O completes.        
						);

	if (IoctlResult == 0)
	{
		ATLTRACE(_T("CSoftarmSampler::Setup failed."));
		return E_FAIL;
	}
	else
	{	
		
		// set all the pressures to zero
		for (Index = 0; Index < NUM_AXES ; Index++)
		{
			m_PressureOutputs[0][Index] =  0;
			m_PressureOutputs[1][Index] =  0;
		}
		SampleFunction(0);   // hardware I/O
		Sleep(100);
		
	}

// Open the device I/O handle and close any existing handles
// Beep(600,100);

	if (m_ArmDeviceHandle != INVALID_HANDLE_VALUE)	// Maybe we are being re-initialized
		CloseHandle(m_ArmDeviceHandle);			

	str = OLE2T((BSTR)m_ArmDeviceFilename);			// Open new file in case this is a new seutp

	m_ArmDeviceHandle = CreateFile(
                str,             // Open the Device "file"
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ,
                NULL,OPEN_EXISTING,0,NULL);
	

	if (m_ArmDeviceHandle == INVALID_HANDLE_VALUE)
	{
		ATLTRACE(_T("CSoftarmSampler::Unable to open arm device!\n"));
		::MessageBox(NULL,"Invalid device name.\nTest Mode Only.","Softarm Sampler Warning",MB_OK|MB_TOPMOST|MB_SETFOREGROUND);
		Beep(200,600);
		return 0;
	}

	ATLTRACE(_T("CSoftarmSampler::Opened arm device %s\n"),str);

// Setup the device driver for timed sampling mode based on sampling freq:
	IoctlCode = IOCTL_ENABLE_SAMPLING_MODE;
	DataLength = sizeof(SoftarmSamplingInfo);
	Info.EnableSampling = TRUE;
	Info.SamplingPeriod = m_ServoLoopWaitTime;

		IoctlResult = DeviceIoControl(
                        m_ArmDeviceHandle,      // Handle to device
                        IoctlCode,              // IO Control code for Write
                        &Info,					// Buffer to driver.  Holds port & data.
                        DataLength,             // Length of buffer in bytes.
                        NULL,                   // Buffer from driver.   Not used.
                        0,                      // Length of buffer in bytes.
                        &ReturnedLength,        // Bytes placed in outbuf.  Should be 0.
                        NULL                    // NULL means wait till I/O completes.        
						);

	if (IoctlResult == 0)
	{
		ATLTRACE(_T("CSoftarmSampler::Setup failed."));
		return E_FAIL;
	}
	else
		return S_OK;

	return S_OK;

}


///////////////////////////////////////
// Set a digital signal in (in bytes)
///////////////////////////////////////
long CSampIndPressure::SetDigitalOutput(ULONG lData)
{
	// set digital Out
	if (m_ArmDeviceHandle != INVALID_HANDLE_VALUE)
	{
	    USHORT				Buffer;    // Input buffer for DeviceIoControl
		LONG    IoctlCode,IoctlResult;
		ULONG               DataLength;
		ULONG               ReturnedLength; // Number of bytes returned in output buffer    
		IoctlCode = IOCTL_SOFTARM_WRITE_DIGITAL_OUT;
		DataLength = sizeof(USHORT);

		// copy data to buffer
		Buffer = USHORT (lData & 0x0ffff);		// only get low 16 bits

		IoctlResult = DeviceIoControl(
                        m_ArmDeviceHandle,      // Handle to device
                        IoctlCode,              // IO Control code for Write
                        &Buffer,				// Buffer to driver.  Holds port & data.
                        DataLength,             // Length of buffer in bytes.
                        NULL,                   // Buffer from driver.   Not used.
                        0,                      // Length of buffer in bytes.
                        &ReturnedLength,        // Bytes placed in outbuf.  Should be 0.
                        NULL                    // NULL means wait till I/O completes.
                        );

	}
	return 0l;
}

///////////////////////////////////////
// Get a digital signal in (in bytes)
///////////////////////////////////////
long CSampIndPressure::GetDigitalInput(ULONG * plData)
{
  
  BOOL	  IoctlResult;
  USHORT  Buffer;			// Input buffer for DeviceIoControl
  LONG    IoctlCode;
  ULONG   DataLength;
  ULONG   ReturnedLength;	// Number of bytes returned in output buffer    

  if(plData==NULL) return -1l;  // return -1 if passed a null pointer

	// This code reads the digital inputs
	IoctlCode = IOCTL_SOFTARM_READ_DIGITAL_IN;
	DataLength = sizeof(USHORT);			
	
	IoctlResult = DeviceIoControl(
                        m_ArmDeviceHandle,		// Handle to device
                        IoctlCode,              // IO Control code for Read
                        NULL,					// Buffer to driver.  Holds port & data. Not used
                        0,						// Length of buffer in bytes.
                        &Buffer,                // Buffer from driver.
                        DataLength,             // Length of buffer in bytes.
                        &ReturnedLength,        // Bytes placed in outbuf.  Should be 0.
                        NULL                    // NULL means wait till I/O completes.
                        );

	*plData = Buffer & 0x00FF; // Get new value from the arm  FF = 2^8. Only get low 8 bits

	return 0l;

}

////////////////////////////////////////////////////
// Inputs:	Filtered Desired Logical Angles
//			Pressure
// Outputs:	Logical Angles
//			Physical Angle (Joint Angles)
//			Joint Velocities, Joint Accelerations
// Function:
// The Sampler reads the encoder values from the hardware, and 
// converts them to Physical and Logical angles. 
//
// Finally, it sends the Pressure commands to the servo valves.
////////////////////////////////////////////////////			 
int CSampIndPressure::SampleFunction(int flag)
{
	INT  Index,Index2;
	BOOL IoctlResult;
    
    // The following parameters are used in the IOCTL call
    SoftarmValves		InputBuffer;				// Input buffer for DeviceIoControl
	SoftarmEncoders		OutputBuffer;
    LONG                IoctlCode;
    ULONG               InDataLength,OutDataLength;
    ULONG               ReturnedLength;				// Number of bytes returned in output buffer
	double				SignedAngles[NUM_AXES];
	double				TJointV;
//	struct				_timeb *timeptr;		

	// Lock();	// Critical section of packing variables before sample

	for (Index = 0; Index < NUM_AXES ; Index++)
	{
		// Perform upper bound clamping of the outputs
		if (m_PressureOutputs[0][Index] >  m_PressureMax[Index])
			m_PressureOutputs[0][Index] =  m_PressureMax[Index];
		if (m_PressureOutputs[1][Index] >  m_PressureMax[Index])
			m_PressureOutputs[1][Index] =  m_PressureMax[Index];

		// Perform lower bound clamping of the outputs
		if (m_PressureOutputs[0][Index] <  0)
			m_PressureOutputs[0][Index] =  0;
		if (m_PressureOutputs[1][Index] <  0)
			m_PressureOutputs[1][Index] =  0;		
	}

	// Setup the DATA for the device
	// Write pressures through valves for the different joints (12 total)
	for (Index = 0; Index < NUM_AXES; Index ++)
	{	
		// Fill in values for the 12 actual pressures.
		InputBuffer.Valve[2*Index]   = (WORD) m_PressureOutputs[0][Index];
		InputBuffer.Valve[2*Index+1] = (WORD) m_PressureOutputs[1][Index];
	}

	//Unlock(); // don't block while we're waiting.

	// Pack structure and send new values to the device handle
	if (m_ArmDeviceHandle != INVALID_HANDLE_VALUE)
	{

	// Hardware Interrupt SYNC'd sampling operation
	IoctlCode		= IOCTL_SOFTARM_SAMPLE;
	InDataLength	= sizeof(SoftarmValves);
	OutDataLength	= sizeof(SoftarmEncoders);

/*		IoctlResult = DeviceIoControl(
                        m_ArmDeviceHandle,  // Handle to device
                        IoctlCode,          // IO Control code for Write
                        &InputBuffer,		// Buffer to driver.  Holds port & data.
                        InDataLength,       // Length of buffer in bytes.
                        &OutputBuffer,      // Buffer from driver.   Not used.
                        OutDataLength,      // Length of buffer in bytes.
                        &ReturnedLength,    // Bytes placed in outbuf.  Should be 0.
                        NULL                // NULL means wait till I/O completes.
                        );
		if (IoctlResult == 0)
		{ ATLTRACE(_T("CSampIndPressure::Sample Call Failure.\n"));	}
*/  

			// Read encoder values (logical angles) from the output buffer to LATER calculate the Physical angles. See Arm Manual 1.0 for more on physical angles. 
			IoctlCode = IOCTL_SOFTARM_READ_ENCODERS;	// read encoders from device drivers

			IoctlResult = DeviceIoControl(
                            m_ArmDeviceHandle,	// Handle to device
                            IoctlCode,          // IO Control code for Read
                            NULL,        		// Buffer to driver.
                            0, 					// Length of buffer in bytes.
							&OutputBuffer,      // Buffer from driver.  Holds port & data (encoder values).
							OutDataLength,      // Length of buffer in bytes.
                            &ReturnedLength,    // Bytes placed in DataBuffer.
                            NULL                // NULL means wait till op. completes.
                            );	

			IoctlCode = IOCTL_SOFTARM_WRITE_VALVES;

			// Write pressures to Input Buffer
			IoctlResult = DeviceIoControl(
							m_ArmDeviceHandle,      // Handle to device
							IoctlCode,              // IO Control code for Write
							&InputBuffer,			// Buffer to drive, holds valve pressures. 
                            InDataLength,			// Length of buffer in bytes.
							NULL,                   // Buffer from driver.   Not used.
							0,                      // Length of buffer in bytes.
							&ReturnedLength,        // Bytes placed in outbuf.  Should be 0.
							NULL                    // NULL means wait till I/O completes.
							);

	// Set current time stamp for this input data and calculate sampling interval
		 
		
		/*********Necessary for IMA 2.5?  *****************/

		//m_SampleTime = GetTickCount() - m_TimeIn;
		//m_TimeIn = GetTickCount();
		//m_TimeIn_1 = GetAgentTime();

//		_ftime( timeptr );
		
		
		ATLTRACE(_T("CSampIndPressure::Ran Sampler.\n"));
	}	
	else
	{
	 ATLTRACE(_T("CSampIndPressure::Skipping sample, no valid device!\n"));
	 Sleep(m_ServoLoopWaitTime);	// "Simulated" operation in this mode..../w no handle
	}

	// New value of for encoders. These values will be converted into logical and physical angles later.
	for (Index = 0; Index < NUM_AXES; Index++)
		m_RawEncoders[Index] = OutputBuffer.Encoder[Index];

	// Take raw encoder values and convert them	to physical angles.
	// PhysicalAngles = (RawEncoder- EncoderOffset)/ EncoderGain
	for (Index = 0; Index < NUM_AXES; Index++)
	{
		// Keep historical samples for computation
			for (Index2 = (HISTORY_LENGTH-1); Index2 > 1; Index2--)
			{
				m_JointAngles[Index2][Index]		= m_JointAngles[Index2-1][Index];
				m_JointVelocities[Index2][Index]	= m_JointVelocities[Index2-1][Index];
				m_JointAccelerations[Index2][Index] = m_JointAccelerations[Index2-1][Index];
			}

		// Compute new values for angles, velocities, accelerations:

		if(flag == 0)
		{
		// Get and convert new angles ... watch out for sign flips
			if (m_RawEncoders[Index] > 32768)
				SignedAngles[Index] = - (65535 - m_RawEncoders[Index]);
			else 
				SignedAngles[Index] = m_RawEncoders[Index];
		}
		else if(flag == 1)
		{
			SignedAngles[Index] = (unsigned short) m_RawEncoders[Index];  // Work with only Positive Encoder Values 
		}
		
		if(flag == 2)
		{
			SignedAngles[Index] = (unsigned short) m_RawEncoders[Index];  
			m_EncoderOffset[Index] = SignedAngles[Index];
		}

		if (m_ArmDeviceHandle != INVALID_HANDLE_VALUE)
		{

		 /***** Angles (Physical Angles) *****/
		 // PhysicalAngles = (RawEncoder- EncoderOffset)/ EncoderGain
			m_JointAngles[0][Index] = (float) (SignedAngles[Index] - m_EncoderOffset[Index])/m_EncoderGain[Index];

		 /***** Velocities /w FIR Velocity filter *****/
		 // Filter the differences to reduce quantization noise instead of smoothing the positions:
			TJointV =	(m_JointAngles[0][Index] - m_JointAngles[1][Index])*0.2f + 
						(m_JointAngles[1][Index] - m_JointAngles[2][Index])*0.2f + 
						(m_JointAngles[2][Index] - m_JointAngles[3][Index])*0.2f + 
						(m_JointAngles[3][Index] - m_JointAngles[4][Index])*0.2f +
						(m_JointAngles[4][Index] - m_JointAngles[5][Index])*0.2f;		

			m_JointVelocities[0][Index] = (TJointV) * (float) 1000.0 / m_ServoLoopWaitTime;		

		 /***** Accelerations *****/
		 // Taken from smoothed velocities using smoothed difference equation
		 //	Acceleration(Time i) = Vel(Time i) - 2Vel(Time i-1) + Vel(Time i-2)
			m_JointAccelerations[0][Index] = (m_JointVelocities[0][Index] -2.0*m_JointVelocities[1][Index] + m_JointVelocities[2][Index]);
		}
		else
		{
		 ATLTRACE(_T("CSampIndPressure::Skipping sample, no valid device!\n"));
		 Sleep(m_ServoLoopWaitTime);	// "Simulated" operation in this mode..../w no handle
		}
				
	}
	m_JointAngles[0][NUM_AXES]		= (double) m_TimeIn;
	m_JointAngles[0][NUM_AXES+1]	= m_TimeIn_1;       // this variable is a double already

	ComputeLogicalAngles(m_JointAngles[0], m_LogicalAngles);


// time stamp was here, moved it up to the end of the Device function call

	//Unlock();
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// input is Physical Angles, output is LogicalPhysical Angles
// Logical Angles can be computed directly from physical angles by the following equations:
//
// L1 = p1;
// L2 = p2;
// L3 = 0.5(p3 + p4)
// L4 = p3 - p4
// L5 = 0.5(p5 + p6)
// L6 = p5 - p6
////////////////////////////////////////////////////////////////////////////////////////////////
void CSampIndPressure::ComputeLogicalAngles(double * in, double * out)
{   
	if ((in != NULL) && (out != NULL))
	{
		out[0] = in[0];
		out[1] = in[1];
		out[2] = 0.5*(in[2]+in[3]);
		out[3] = in[2]-in[3];
		out[4] = 0.5*(in[4]+in[5]);
		out[5] = in[4]-in[5];
	}	
}

//	input is Logical Angles, output is Physical Angles
// Physical Angles can be computed by the following equations:

// p1 = L1
// p2 = L2
// p3 = L3 + 0.5 * L4
// p4 = L3 - 0.5 * L4
// p5 = L5 + 0.5 * L6
// p6 = L5 - 0.5 * L6

void CSampIndPressure::ComputePhysicalAngles(double * in, double * out)
{   
	if ((in != NULL) && (out != NULL))
	{
		out[0] = in[0];
		out[1] = in[1];
		out[2] = in[2] + 0.5*in[3];
		out[3] = in[2] - 0.5*in[3];
		out[4] = in[4] + 0.5*in[5];
		out[5] = in[4] - 0.5*in[5];
	}
}


STDMETHODIMP CSampIndPressure::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	int numiids;
	IMA2_BindingInfo BindInf;
	numiids=1;

	// 1. FilteredDesiredLogicalAngles
	BindInf.Name		= SysAllocString(L"FilteredDesiredLogicalAngles");	// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets
	BindInf.Path		= SysAllocString(L"");								// This must be the path of our component
	BindInf.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	BindInf.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.	
	
	// 2. PressureBiasVector
	BindInf.Name		= SysAllocString(L"PressureBiasVector");					
	m_ConfigureBindings->Add(&BindInf);
	
	// 3. LogicalAngles
	BindInf.Name		= SysAllocString(L"LogicalAngles");					
	m_ConfigureBindings->Add(&BindInf);

	// 4. DesiredPhysicalAngles
	BindInf.Name		= SysAllocString(L"DesiredPhysicalAngles");					
	m_ConfigureBindings->Add(&BindInf);

	// 5. PhysicalAngles
	BindInf.Name		= SysAllocString(L"PhysicalAngles");					
	m_ConfigureBindings->Add(&BindInf);

	// 6. Pressure
	BindInf.Name		= SysAllocString(L"Pressure");					
	m_ConfigureBindings->Add(&BindInf);

	// 7. Desired XYZ Position
	BindInf.Name		= SysAllocString(L"DesiredXYZPos");					
	m_ConfigureBindings->Add(&BindInf);



	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);
	
	return S_OK;
}

STDMETHODIMP CSampIndPressure::OnDestruct() {	return S_OK; }

//////////////////////////////
// Load values of saved data
//////////////////////////////
STDMETHODIMP CSampIndPressure::Load(VARIANT Data) {
	
	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	variant_t				*ItemValue;

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;

		// Get the pointer to the real VB property bag (the VB object (defined in msvbvm60.dll (aka VBRUN)) that our wrapper class created)
		// hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Pass Data to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);


		// Constants for angle input conversions

		// Variable m_ServoLoopWaitTime
		// Define strings
		ItemName	= SysAllocString(L"ServoLoopWaitTime");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_ServoLoopWaitTime	= (short)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_EncoderGain
		// Define strings
		ItemName	= SysAllocString(L"EncoderGain");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_EncoderGain, ItemValue->parray->pvData, sizeof(double)*NUM_AXES);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_EncoderOffset
		// Define strings
		ItemName	= SysAllocString(L"EncoderOffset");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_EncoderOffset, ItemValue->parray->pvData, sizeof(double)*NUM_AXES);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_EncoderMin
		// Define strings
		ItemName	= SysAllocString(L"EncoderMin");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_EncoderMin, ItemValue->parray->pvData, sizeof(long)*NUM_AXES);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_EncoderMax
		// Define strings
		ItemName	= SysAllocString(L"EncoderMax");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_EncoderMax, ItemValue->parray->pvData, sizeof(long)*NUM_AXES);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_pdHomeAngles
		// Define strings
		ItemName	= SysAllocString(L"HomeAngles");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_pdHomeAngles, ItemValue->parray->pvData, sizeof(double)*NUM_AXES); 
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Constants for pressure output conversions

		// Variable m_BiasedPressure
		// Define strings
		ItemName	= SysAllocString(L"BiasedPressure");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_BiasedPressure, ItemValue->parray->pvData, sizeof(double)*NUM_AXES); 
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_PressureMax
		// Define strings
		ItemName	= SysAllocString(L"PressureMax");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_PressureMax, ItemValue->parray->pvData, sizeof(double)*NUM_AXES); 	
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_bInvertPressure
		// Define strings
		ItemName	= SysAllocString(L"InvertPressure");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_bInvertPressure, ItemValue->parray->pvData, sizeof(short)*NUM_AXES); 
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_ArmDeviceFilename: Device information
		ItemName	= SysAllocString(L"ArmDeviceFilename");
		ItemValue			= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
		SysReAllocString(&m_ArmDeviceFilename,ItemValue->bstrVal);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_LeftArm
		// Define strings
		ItemName	= SysAllocString(L"LeftArm");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		put_LeftArm((short)*ItemValue);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();

	return S_OK;

}

STDMETHODIMP CSampIndPressure::Save(VARIANT * pData)
{
	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t*				ItemValue;
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class

	// Create Class with CoCreateInstance (definition can be found in MSDN).
	// Create the property bag wrapper class, put pointer to the Interface in pIPB
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

	if (pIPB == NULL)	
		return !S_OK;

		// ServoLoopWaitTime
		ItemName = SysAllocString(L"ServoLoopWaitTime");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t(m_ServoLoopWaitTime, VT_I2);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		// m_EncoderGain
		ItemName = SysAllocString(L"EncoderGain");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_EncoderGain,NUM_AXES*sizeof(double));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// EncoderOffset
		ItemName = SysAllocString(L"EncoderOffset");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_EncoderOffset,NUM_AXES*sizeof(double));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// EncoderMax
		ItemName = SysAllocString(L"EncoderMax");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_EncoderMax,NUM_AXES*sizeof(double));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// EncoderMin
		ItemName = SysAllocString(L"EncoderMin");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_EncoderMin,NUM_AXES*sizeof(double));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// HomeAngles
		ItemName = SysAllocString(L"HomeAngles");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_pdHomeAngles,NUM_AXES*sizeof(double));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// m_BiasedPressure
		ItemName = SysAllocString(L"BiasedPressure");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_BiasedPressure,NUM_AXES*sizeof(double));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// PressureMax
		ItemName = SysAllocString(L"PressureMax");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_PressureMax,NUM_AXES*sizeof(double));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// InvertPressure
		ItemName = SysAllocString(L"InvertPressure");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_I2;
		ItemValue->parray=SafeArrayCreateVector(VT_I2,0,NUM_AXES);
		memcpy(ItemValue->parray->pvData,m_bInvertPressure,NUM_AXES*sizeof(short));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// m_ArmDeviceFilename
		ItemName = SysAllocString(L"ArmDeviceFilename");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_ArmDeviceFilename);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// m_LeftArm
		ItemName = SysAllocString(L"LeftArm");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t(m_LeftArm, VT_I2);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		// Get the pointer to the real VB property bag (the VB object (defined in msvbvm60.dll (aka VBRUN)) that our wrapper class created)
		hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
			
		// Copy the value VB gave to us into the return value of this function (which will be returned to whatever's calling our save function)
		VariantCopy(pData, &m_VBPropertyBag);

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);

	// Release
	pIPB->Release();

	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Inputs:	Desired Logical Angles, Pressures
// Outputs: DesiredPhysicalAngles and Physcial Angles, Logical Angles  
// Function:By reading encoder values it is able to compute the JointAngles, Logical Angles, and 
//			DesiredPhysicalAngles
//			
//			By using the Pressures value, it writes the stream of data to the input buffer that 
//			goes to the servo valves to move the arm
////////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CSampIndPressure::HW_IO_6()
{
	// TODO: Add your implementation code here

	SAFEARRAY *mysa;
	
	double	PressBuff[NUM_AXES];
	double	DesLogAngles[NUM_AXES];
	double	DesPhysAngles[NUM_AXES];
	bool	NotInitialLoop = true;
	ULONG Index;

	IVectorSignal *pIVSIn				=NULL;	// Input  Vector signal, Pressure Vector (6 values if deltaP or 12 values if direct Pressure)
	IVectorSignal *pIVSDesLogAngles		=NULL;  // Input  Vector signal, Desired Logical Angles
	IVectorSignal *pIVSOut				=NULL;	// Output Vector signal, Actual Physical Angles
	IVectorSignal *pIVSLogAngles		=NULL;	// Output Vector signal, Actual Logical	Angles
	IVectorSignal *pIVSDesPhysAngles	=NULL;	// Output Vector signal, Desired Physical Angles
	IVectorSignal *pIVSPressBias		=NULL;	// Vector signal for Pressure Bias

	// Get pointers to objects and interfaces
	m_Bindings->get_Pointers(SysAllocString(L"Pressure"),				&m_pIUnkInput);	
	m_Bindings->get_Pointers(SysAllocString(L"PhysicalAngles"),			&m_pIUnkOutput);
	m_Bindings->get_Pointers(SysAllocString(L"LogicalAngles"),			&m_pIUnkActualLogicalAngles);
	m_Bindings->get_Pointers(SysAllocString(L"FilteredDesiredLogicalAngles"),	&m_pIUnkDesiredLogicalAngles);
	m_Bindings->get_Pointers(SysAllocString(L"DesiredPhysicalAngles"),	&m_pIUnkDesiredPhysicalAngles);
	m_Bindings->get_Pointers(SysAllocString(L"PressureBiasVector"),		&m_pIUnkBiasedPressureState);

	if(m_pIUnkOutput != NULL && m_pIUnkInput != NULL && m_pIUnkActualLogicalAngles != NULL && m_pIUnkDesiredLogicalAngles != NULL &&
		m_pIUnkDesiredPhysicalAngles != NULL && m_pIUnkBiasedPressureState != NULL)
	{
		m_pIUnkInput->QueryInterface(IID_IVectorSignal,(void **)&pIVSIn);
		m_pIUnkOutput->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);
		m_pIUnkActualLogicalAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSLogAngles);
		m_pIUnkDesiredLogicalAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSDesLogAngles);
		m_pIUnkDesiredPhysicalAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSDesPhysAngles);
		m_pIUnkBiasedPressureState->QueryInterface(IID_IVectorSignal,(void**)&pIVSPressBias);
		
		if ((pIVSIn != NULL)&&(pIVSOut != NULL)&&(pIVSLogAngles != NULL)
			   &&(pIVSDesLogAngles != NULL)&&(pIVSDesPhysAngles != NULL) &&(pIVSPressBias != NULL))
		{
			ATLTRACE(_T("\nCSampIndPressure::Sample Arm Data"));
		
			// Setup OUTPUT values from: input vector
			// Get Desired Logical Angles
			mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
			pIVSDesLogAngles->GetCurrentVector(mysa);
			memcpy(DesLogAngles, mysa->pvData, sizeof(double)*NUM_AXES);

			// Get Input Pressures to pass to the SampleFunction()
			pIVSIn->GetCurrentVector(mysa);
			memcpy(PressBuff, mysa->pvData, sizeof(double)*NUM_AXES);

			// Get Pressure Bias
			pIVSPressBias->GetCurrentVector(mysa);  // read pressure bias to member variable
			memcpy(m_BiasedPressure, mysa->pvData, sizeof(double)*NUM_AXES);
			SafeArrayDestroy(mysa);

			// Currently being done to try to replicate a behavior in the IMA1 agent not understood
			// where after the initial loop the Bias Pressures are all set to 0.
			//if (NotInitialLoop == 1)
			//	for(Index=0;Index<NUM_AXES;Index++)
			//		m_BiasedPressure[Index]=0.0;
	
			// Put pressure values in the right places using the old time differential pressure hack
	 		for (Index = 0; Index < NUM_AXES; Index++)
			{
				// Perform pressure differential operation:
				if (m_bInvertPressure[Index] == TRUE)
				{		
					m_PressureOutputs[0][Index] = m_BiasedPressure[Index] + PressBuff[Index];
					m_PressureOutputs[1][Index] = m_BiasedPressure[Index] - PressBuff[Index];
				}
				else
				{
					m_PressureOutputs[0][Index] = m_BiasedPressure[Index] - PressBuff[Index];						
					m_PressureOutputs[1][Index] = m_BiasedPressure[Index] + PressBuff[Index];
				}				
			}
		
			SampleFunction(0);													// This calls the hardware to get / set values
			ComputePhysicalAngles(DesLogAngles,DesPhysAngles);			

			// Set Physical Angles
			// For 1st element of history: m_JointAngles[HISTORY_LENGTH][NUM_AXES+2];
			mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES+2);	
			memcpy(mysa->pvData,m_JointAngles[0],sizeof(double)*(NUM_AXES+2));	// Set the Actual Physical Angles
			pIVSOut->SetCurrentVector(mysa);
			SafeArrayDestroy(mysa);
						
			// Set Desired Physical Angles
			mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);	
			memcpy(mysa->pvData,DesPhysAngles,sizeof(double)*NUM_AXES);			// Set the Desired Physical Angles
			pIVSDesPhysAngles->SetCurrentVector(mysa);							

			// Set Logical Angles
			memcpy(mysa->pvData,m_LogicalAngles,sizeof(double)*NUM_AXES);		// Set the Actual Logical Angles
			pIVSLogAngles->SetCurrentVector(mysa);								

			// Destroy SafeArray
			SafeArrayDestroy(mysa);

			pIVSIn->Release();
			pIVSOut->Release();
			pIVSLogAngles->Release();
			pIVSDesLogAngles->Release();
			pIVSDesPhysAngles->Release();
			pIVSPressBias->Release();

		}
		else
		{
			if (pIVSIn != NULL)
				pIVSIn->Release();

			if (pIVSOut != NULL)
				pIVSOut->Release();
			
			if (pIVSLogAngles != NULL)
				pIVSLogAngles->Release();

			if (pIVSDesLogAngles != NULL)
				pIVSDesLogAngles->Release();

			if (pIVSDesPhysAngles != NULL)
				pIVSDesPhysAngles->Release();

			if (pIVSPressBias != NULL)
				pIVSPressBias->Release();

			ATLTRACE(_T("CSampIndPressure::Sample Failure!"));
			return S_OK;					// Fail/end.
		}
	}
	return S_OK;
}

STDMETHODIMP CSampIndPressure::HW_IO_12()
{
	// TODO: Add your implementation code here
	SAFEARRAY *mysa;
	
	double PressBuff2[NUM_AXES*2];   // Added on 05JAN2000 for 12 separate pressure control, Steve Northrup
	double DesLogAngles[NUM_AXES];
	double DesPhysAngles[NUM_AXES];
	ULONG Index;

	IVectorSignal *pIVSIn				=NULL;	// Input  Vector signal, Pressure Vector (6 values if deltaP or 12 values if direct Pressure)
	IVectorSignal *pIVSOut				=NULL;	// Output Vector signal, Actual Physical Angles
	IVectorSignal *pIVSLogAngles		=NULL;	// Output Vector signal, Actual Logical	Angles
	IVectorSignal *pIVSDesLogAngles		=NULL;  // Input  Vector signal, Desired Logical Angles
	IVectorSignal *pIVSDesPhysAngles	=NULL;	// Output Vector signal, Desired Physical Angles

	// Get pointers to objects and interfaces
	m_Bindings->get_Pointers(SysAllocString(L"Pressure"),				&m_pIUnkInput);	
	m_Bindings->get_Pointers(SysAllocString(L"PhysicalAngles"),			&m_pIUnkOutput);
	m_Bindings->get_Pointers(SysAllocString(L"LogicalAngles"),			&m_pIUnkActualLogicalAngles);
	m_Bindings->get_Pointers(SysAllocString(L"FilteredDesiredLogicalAngles"),	&m_pIUnkDesiredLogicalAngles);
	m_Bindings->get_Pointers(SysAllocString(L"DesiredPhysicalAngles"),	&m_pIUnkDesiredPhysicalAngles);

	if(m_pIUnkOutput != NULL && m_pIUnkInput != NULL && m_pIUnkActualLogicalAngles != NULL && m_pIUnkDesiredLogicalAngles != NULL &&
		m_pIUnkDesiredPhysicalAngles != NULL)
	{
		m_pIUnkInput->QueryInterface(IID_IVectorSignal,(void **)&pIVSIn);
		m_pIUnkOutput->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);
		m_pIUnkActualLogicalAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSLogAngles);
		m_pIUnkDesiredLogicalAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSDesLogAngles);
		m_pIUnkDesiredPhysicalAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSDesPhysAngles);
		
		if ((pIVSIn != NULL)&&(pIVSOut != NULL)&&(pIVSLogAngles != NULL)
			   &&(pIVSDesLogAngles != NULL)&&(pIVSDesPhysAngles != NULL))
		{
			ATLTRACE(_T("\nCSampIndPressure::Sample Arm Data"));
		
			// Setup output values from input vector
			// Desired Logical Angles
			mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
			pIVSDesLogAngles->GetCurrentVector(mysa);
			memcpy(DesLogAngles, mysa->pvData, sizeof(double)*NUM_AXES);
			SafeArrayDestroy(mysa);

			// Input Pressures
			//  PressBuff is organized as a vector with 12 values:
			mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES*2);
			pIVSIn->GetCurrentVector(mysa);
			memcpy(PressBuff2, mysa->pvData, sizeof(double)*NUM_AXES*2);
			SafeArrayDestroy(mysa);

			// Put pressure values in the right places using the old time differential pressure hack
			// 12 different pressures for each one of the rubbertuators in the six joints
	 		for (Index = 0; Index < NUM_AXES*2; Index += 2)
			{
				// Perform pressure differential operation:
					m_PressureOutputs[0][Index/2] = PressBuff2[Index];
					m_PressureOutputs[1][Index/2] = PressBuff2[Index+1];  
			}
		
			// Move the arm and read encoder values
			SampleFunction(0);					
			
			// Compute DesPhysAngles to be used by the Controller
			ComputePhysicalAngles(DesLogAngles,DesPhysAngles);			

			// Set the Actual Physical Angles 
			mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES+2);	
			memcpy(mysa->pvData,m_JointAngles[0],sizeof(double)*(NUM_AXES+2));	
			pIVSOut->SetCurrentVector(mysa);
			SafeArrayDestroy(mysa);
			
			// Set the Actual Logical Angles
			mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);	
			memcpy(mysa->pvData,m_LogicalAngles,sizeof(double)*NUM_AXES);
			pIVSLogAngles->SetCurrentVector(mysa);								
			
			// Set the Desired Physical Angles
			memcpy(mysa->pvData,DesPhysAngles,sizeof(double)*NUM_AXES);
			pIVSDesPhysAngles->SetCurrentVector(mysa);						

			// Destroy SafeArray
			SafeArrayDestroy(mysa);

			pIVSIn->Release();
			pIVSOut->Release();
			pIVSLogAngles->Release();
			pIVSDesLogAngles->Release();
			pIVSDesPhysAngles->Release();

		}
		else
		{
			if (pIVSIn != NULL)
				pIVSIn->Release();

			if (pIVSOut != NULL)
				pIVSOut->Release();
			
			if (pIVSLogAngles != NULL)
				pIVSLogAngles->Release();

			if (pIVSDesLogAngles != NULL)
				pIVSDesLogAngles->Release();

			if (pIVSDesPhysAngles != NULL)
				pIVSDesPhysAngles->Release();

			ATLTRACE(_T("CSampIndPressure::Sample Failure!"));
			return S_OK;					// Fail/end.
		}
	}
	return S_OK;
}

STDMETHODIMP CSampIndPressure::Enable_ZMasking()
{
	// TODO: Add your implementation code here
	put_ZMask(0x00);			// Call own interface to turn off z masking.
	ATLTRACE(_T("\nCSampIndPressure::Z-Phase Passed"));

	return S_OK;
}

STDMETHODIMP CSampIndPressure::Disable_ZMasking()
{
	// TODO: Add your implementation code here
		put_ZMask(0x3f);			// Call own interface to turn on z masking
		ATLTRACE(_T("\nCSampIndPressure::Z-Phase Blocked"));

	return S_OK;
}

STDMETHODIMP CSampIndPressure::WriteHomePositions()
{
	// TODO: Add your implementation code here
	SAFEARRAY *mysa;
	
	double DesLogAngles[NUM_AXES];
	double DesPhysAngles[NUM_AXES];
	ULONG Index;

	IVectorSignal *pIVSIn				=NULL;	// Input  Vector signal, Pressure Vector (6 values if deltaP or 12 values if direct Pressure)
	IVectorSignal *pIVSOut				=NULL;	// Output Vector signal, Actual Physical Angles
	IVectorSignal *pIVSLogAngles		=NULL;	// Output Vector signal, Actual Logical	Angles
	IVectorSignal *pIVSDesLogAngles		=NULL;  // Input  Vector signal, Desired Logical Angles
	IVectorSignal *pIVSDesPhysAngles	=NULL;	// Output Vector signal, Desired Physical Angles
	IVectorSignal *pIVSPressBias		=NULL;	// Vector signal for Pressure Bias
	IVectorSignal *pIVSDesXYZPos		=NULL;	// Vector signal for Pressure Bias

	// Get pointers to objects and interfaces
	m_Bindings->get_Pointers(SysAllocString(L"Pressure"),				&m_pIUnkInput);
	m_Bindings->get_Pointers(SysAllocString(L"PhysicalAngles"),			&m_pIUnkOutput);
	m_Bindings->get_Pointers(SysAllocString(L"LogicalAngles"),			&m_pIUnkActualLogicalAngles);
	m_Bindings->get_Pointers(SysAllocString(L"FilteredDesiredLogicalAngles"),	&m_pIUnkDesiredLogicalAngles);
	m_Bindings->get_Pointers(SysAllocString(L"DesiredPhysicalAngles"),	&m_pIUnkDesiredPhysicalAngles);
	m_Bindings->get_Pointers(SysAllocString(L"PressureBiasVector"),		&m_pIUnkBiasedPressureState);
	m_Bindings->get_Pointers(SysAllocString(L"DesiredXYZPos"),			&m_pIUnkDesiredXYZPos);

	if(m_pIUnkOutput != NULL && m_pIUnkInput != NULL && m_pIUnkActualLogicalAngles != NULL && m_pIUnkDesiredLogicalAngles != NULL &&
		m_pIUnkDesiredPhysicalAngles != NULL && m_pIUnkBiasedPressureState != NULL && m_pIUnkDesiredXYZPos != NULL)
	{
		m_pIUnkInput->QueryInterface(IID_IVectorSignal,(void **)&pIVSIn);
		m_pIUnkOutput->QueryInterface(IID_IVectorSignal,(void**)&pIVSOut);
		m_pIUnkActualLogicalAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSLogAngles);
		m_pIUnkDesiredLogicalAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSDesLogAngles);
		m_pIUnkDesiredPhysicalAngles->QueryInterface(IID_IVectorSignal,(void**)&pIVSDesPhysAngles);
		m_pIUnkBiasedPressureState->QueryInterface(IID_IVectorSignal,(void**)&pIVSPressBias);
		m_pIUnkDesiredXYZPos->QueryInterface(IID_IVectorSignal,(void**)&pIVSDesXYZPos);
		
		if ((pIVSIn != NULL)&&(pIVSOut != NULL)&&(pIVSLogAngles != NULL)
			   &&(pIVSDesLogAngles != NULL)&&(pIVSDesPhysAngles != NULL)&&(pIVSPressBias != NULL) && (pIVSDesXYZPos != NULL))
		{
			for(Index = 0; Index < NUM_AXES; Index++)
				DesLogAngles[Index] = m_pdHomeAngles[Index];
			
			// Compute the Desired Physical Angles from the Home Angles (DesLogAngles)
			ComputePhysicalAngles(DesLogAngles,DesPhysAngles);  

			// Set the Desired Physical Angles
			mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);	
			memcpy(mysa->pvData,DesPhysAngles,sizeof(double)*NUM_AXES);						
			pIVSDesPhysAngles->SetCurrentVector(mysa);	
			
			// Set the Desired Logical Angles
			memcpy(mysa->pvData,DesLogAngles,sizeof(double)*NUM_AXES);	
			pIVSDesLogAngles->SetCurrentVector(mysa);

			// Set the Desired XYZRPY Position
			memcpy(mysa->pvData,m_pdXYZRPYPos,sizeof(double)*NUM_AXES);	
			pIVSDesXYZPos->SetCurrentVector(mysa);

			// Destroy SafeArray
			SafeArrayDestroy(mysa);

			pIVSIn->Release();
			pIVSOut->Release();
			pIVSLogAngles->Release();
			pIVSDesLogAngles->Release();
			pIVSDesPhysAngles->Release();
			pIVSPressBias->Release();
			pIVSDesXYZPos->Release();

		}
		else
		{
			if (pIVSIn != NULL)
				pIVSIn->Release();

			if (pIVSOut != NULL)
				pIVSOut->Release();
			
			if (pIVSLogAngles != NULL)
				pIVSLogAngles->Release();

			if (pIVSDesLogAngles != NULL)
				pIVSDesLogAngles->Release();

			if (pIVSDesPhysAngles != NULL)
				pIVSDesPhysAngles->Release();

			if (pIVSPressBias != NULL)
				pIVSPressBias->Release();

			if (pIVSDesXYZPos != NULL)
				pIVSDesXYZPos->Release();
			
			ATLTRACE(_T("CSampIndPressure::Sample Failure!"));
			return S_OK;					// Fail/end.
		}
	}

	return S_OK;
}


