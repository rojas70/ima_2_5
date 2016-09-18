// FTSensorCom.cpp : Implementation of CFTSensorCom
#include "stdafx.h"
#include "IMA2_FTSensorLib.h"
#include "FTSensorCom.h"

/////////////////////////////////////////////////////////////////////////////
// CFTSensorCom
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
// The OnConstruct Function sets all the bindings for the component
/////////////////////////////////////////////////////////////////////
STDMETHODIMP CFTSensorCom::OnConstruct() {
// TODO: Bindings. Personalize the binding of your component. 

	int					numiids;
	numiids				=1;
	IMA2_BindingInfo	BindInf;


	// 1. FTSensorData
	BindInf.Name		= SysAllocString(L"FTSensorData");					// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets
	BindInf.Path		= SysAllocString(L"");								// This must be the path of our component
	BindInf.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	BindInf.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.	

	// 2. FTSensorDataPeaks
	BindInf.Name		= SysAllocString(L"FTSensorDataPeaks");
	m_ConfigureBindings->Add(&BindInf);

	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);
	
	return S_OK;
}

STDMETHODIMP CFTSensorCom::OnDestruct() {	return S_OK; }

//////////////////////////////
// Load values of saved data
//////////////////////////////
STDMETHODIMP CFTSensorCom::Load(VARIANT Data) {
	
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

		// 1. m_sCommFileName
		ItemName	= SysAllocString(L"CommFileName");
		ItemValue	= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
		SysReAllocString(&m_sCommFileName,ItemValue->bstrVal);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// 2. m_sCommParams
		ItemName	= SysAllocString(L"CommParams");
		ItemValue	= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
		SysReAllocString(&m_sCommParams,ItemValue->bstrVal);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// 3. m_sCommReadTimeouts
		ItemName	= SysAllocString(L"CommReadTimeouts");
		ItemValue	= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
		SysReAllocString(&m_sCommReadTimeouts,ItemValue->bstrVal);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// 4. m_bPeaks
		ItemName	= SysAllocString(L"Peaks");
		ItemValue	= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
		m_bPeaks = (bool)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// 5. m_lAverageLength
		ItemName	= SysAllocString(L"AverageLength");
		ItemValue	= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
		m_lAverageLength = (long)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// 6. m_sFTWristSide
		ItemName	= SysAllocString(L"FTWristSide");
		ItemValue	= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
		m_sFTWristSide = (short)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();

	return S_OK;

}

//////////////////////
// Saved properties
//////////////////////
STDMETHODIMP CFTSensorCom::Save(VARIANT *pData) {
	
	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t				*ItemValue;
	_PropertyBagWrapper		*pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.

	ItemValue = new variant_t;
	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;
		
		// 1. m_sCommFileName
		ItemName = SysAllocString(L"CommFileName");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_sCommFileName);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// 2. m_sCommParams
		ItemName = SysAllocString(L"CommParams");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_sCommParams);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// 3. m_sCommReadTimeouts
		ItemName = SysAllocString(L"CommReadTimeouts");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_sCommReadTimeouts);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// 4. m_bPeaks
		ItemName = SysAllocString(L"Peaks");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_bPeaks);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// 5. m_lAverageLength
		ItemName = SysAllocString(L"AverageLength");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_lAverageLength, VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// 6. m_sFTWristSide
		ItemName = SysAllocString(L"FTWristSide");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_sFTWristSide, VT_I2);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Destroy ItemValue
		delete ItemValue;

		// Returns a pointer to the PropertyBag as a VARIANT
		hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Copy the contents of the property bag to the pData VARIANT
		VariantCopy(pData, &m_VBPropertyBag);

		// Save the size of the data 
		m_lDataSize = pData->parray->rgsabound[0].cElements;		

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);

		// Release
		pIPB->Release();

	return S_OK;
}


/*STDMETHODIMP CFTSensorCom::SampleFTDataPeaks()
{
	// TODO: Add your implementation code here
	if(m_pdMax==NULL) return E_POINTER;
	if(m_pdMin==NULL) return E_POINTER;

	SAFEARRAY*		 mysa;
	IVectorSignal*	 pIVSOut	= NULL;	

	// Get object and interface pointer
	m_Bindings->get_Pointers(SysAllocString(L"FTSensorData"),&m_pIUnkFTSensorDataPeaks);	

	if(m_pIUnkFTSensorDataPeaks != NULL)	
		m_pIUnkFTSensorDataPeaks->QueryInterface(IID_IVectorSignal,(void **)&pIVSOut);
		
	if (pIVSOut != NULL)
	{
		// Get Fx, Fy, Fz, Tx, Ty, Tz
		m_pftSensor->SampleFTPeaks(m_pdMax,m_pdMin);
		mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES*2);
		memcpy(mysa->pvData,m_pdData,sizeof(double)*(NUM_AXES*2));	// Set the Actual Physical Angles
		pIVSOut->SetCurrentVector(mysa);
		// Destroy SafeArray
		SafeArrayDestroy(mysa);
		pIVSOut->Release();
	}

	else
	{
		if (pIVSOut != NULL)
		{
			pIVSOut->Release();
			ATLTRACE(_T("CFTSensorCom::SampleAxes failed!"));

			return S_OK;
		}
	}

	return S_OK;
}
*/

/********************************************************************************************
/* Initialize will help us get our FT Sensor ready
/* to make measurements in ISACs environment.
/* Intialize() should only be called after ISACs arm 
/* is in the home position.
/*
/* (1) Coordinate Transform
/* Uses a right hand rule. All rotations reference the original sensor frame.
/* At the home position the sensor is installed so that Y is upwards, X to the right, 
/* and Z out of the sensor. 
/* 
/* A rotation of the type: Tx: -90, Ty:0, Tz:-90 is necessary
/* to create a frame where Z points upwards, Y to the right, and Z out of the page.
/* An array has be created with the following values: m_dSensorTransofm = [0,0,0,-90,0,-90];
/*
/* (2) Set the printing of values to lbs
/* The sensor has the abilitiy to print the results in a variety of formats. 
/* We want to see the results in pounds - lbs.
/*
/* (3) Biasing
/* At this time, we want to bias the sensor, i.e. have the 
/* FT sensor record 0's accross its sensors even when there is
/* an end-effector tool on it. 
/*
/* (4) Moving Average
/* Also we want to set the sensor to do a moving average accross 
/* samples. This will help us mitigate the effect of noise generated 
/* by the jerking of the arm (which is caused by the arm's instability,
/* and also its interactions with objects that it will try to hold).
/* The moving average commands can average over 0,2,4,8, and 16 samples.
********************************************************************************************/
STDMETHODIMP CFTSensorCom::Initialize()
{
	// String macro used to convert a BSTR to a const char*
	USES_CONVERSION;
//	BSTR bstr_szRet;

	// Perform only when the Initialize() method has not been previously called.
	if(m_bInitialized == 0)
	{
	
		// 1) Initialize the Port
		m_pftSensor->m_pPort = new CCommPort(OLE2T(m_sCommFileName), 38400);

		// 2) Initialize szCmd to a carriage return a new line. 
		// And then send a warm startup
		char szCmd[100]="\r\n", szRet[SZLen];	
		m_pftSensor->SendCommand(szCmd,szRet);	// Looking to get a ">" response in szRet.
		
		// 3) Set data readings to display in units of lbs (not gauge counts or resolved counts).
		// Command is "CD R"
		m_pftSensor->SetForceFormat();

		// 4) Frame rotation
		// Designed to have X-axis point away from sensor, Y to the right, and Z upwards following a right hand rule.
		// Comand is "TC 1,ISAC,0,0,0,-90,0,-90"
		//m_pftSensor->SetFrame(m_pdFrame);
		
		/*strcpy(szCmd,"TC 1,ISAC,0,0,0,-90,0,-90\r\n");
		m_pftSensor->SendCommand(szCmd,szRet);
		bstr_szRet = bstr_t(szRet);
		SysReAllocString(&m_bstrError,bstr_szRet);
		SysFreeString(bstr_szRet);

		strcpy(szCmd,"TF\r\n");
		m_pftSensor->SendCommand(szCmd,szRet);
		bstr_szRet = bstr_t(szRet);
		SysReAllocString(&m_bstrError,bstr_szRet);
		SysFreeString(bstr_szRet);

		strcpy(szCmd,"TF 0\r\n");
		m_pftSensor->SendCommand(szCmd,szRet);
		bstr_szRet = bstr_t(szRet);
		SysReAllocString(&m_bstrError,bstr_szRet);
		SysFreeString(bstr_szRet);

		strcpy(szCmd,"TF 1\r\n");
		m_pftSensor->SendCommand(szCmd,szRet);
		bstr_szRet = bstr_t(szRet);
		SysReAllocString(&m_bstrError,bstr_szRet);
		SysFreeString(bstr_szRet);

		strcpy(szCmd,"RS\r\n");
		m_pftSensor->SendCommand(szCmd,szRet);
		bstr_szRet = bstr_t(szRet);
		SysReAllocString(&m_bstrError,bstr_szRet);
		SysFreeString(bstr_szRet);
		*/

		// 5) Average readings	
		// Set Avg sampling length to 4
		m_pftSensor->SetAverageLength(m_lAverageLength);	// normally 4

		// 6) Set the EnablePeaks option on, to record the highest and lowest values of the FT Sensor
		m_pftSensor->EnablePeaks((BOOL)1);

		// 7) Call FTReadData once
		m_pftSensor->SampleFT(m_pdData);

		// 8) Bias the sensor so it reads "0's".
		// Should be done after arms are in home positions.
		// Command is "SB"
		m_pftSensor->BiasSensor(TRUE);
		m_pftSensor->BiasSensor(TRUE);
		m_pftSensor->BiasSensor(TRUE);

		// Prepare Timing Variables

		// 1) Get CPU's frequency
		QueryPerformanceFrequency(&ticksPerSecond);		// Gets CPU frequency, ie. how many ticks in one second.
		QueryPerformanceCounter(&start_ticks);			// Store initial value for counter.

		// Change Initialized Flag
		m_bInitialized = 1;
	}


	return S_OK;
}

/**************************************************************************************************/
/* SampleFTData()
/*
/* This function reads force and torque readings from the ATI force sensor.
/* Depending on the side provided for the sensor (right/left) it will call 
/* that serial port to get the information.
/*
/* The ATI sensor is not very effective currently when trying to perform
/* a rotation transform on the axis of the sensor. Hence, instead of calling
/* a rotation transform the sensory input is copied such that the readings
/* reflect a rotated axis. Originally x points to the right of the sensor (looking into ISAC)
/* but we want X to point out of the sensor. More details are below.
/*
/* Also, to reduce the effect of noise we perform a running average of the incoming sensory data.
/* We average each signal with it's previous one using a weight averaging parameter, alpha. 
/**************************************************************************************************/
STDMETHODIMP CFTSensorCom::SampleFTData()
{
	// Local variables
	int				 i;
	HRESULT			 hRes;
	SAFEARRAY*		 mysa;
	IVectorSignal*	 pIVSOut	= NULL;	

	// Make sure the initialization routine has been called before executing this method.
	if(m_bInitialized == 0)
		hRes = Initialize();

	// Get object and interface pointers
	m_Bindings->get_Pointers(SysAllocString(L"FTSensorData"),&m_pIUnkFTSensorData);	
	if(m_pIUnkFTSensorData != NULL)	
		m_pIUnkFTSensorData->QueryInterface(IID_IVectorSignal,(void **)&pIVSOut);
		
	// Get FT data, ie: Fx, Fy, Fz, Tx, Ty, Tz
	if (pIVSOut != NULL)
	{		
		// Call function to read force-torque data
		SampleAxes(m_pdData);

		// The readings are in counts per pound. There are 80 COUNTS_PER_POUND, so must divide
		// Juan turned this off b/c he started experiments without this. Turn it on when you see this.
		// March 2009.
		m_pdData[i] = m_pdData[i]/(double)COUNTES_PER_POUND;

		// Given that rotating the frame of the sensor is so hard, here we will 
		// copy the values of the array such that:
		// Fx = m_pdData[2]; originally the Z-axes.
		// Fy = m_pdData[0]; originally the X-axes
		// Fz = m_pdData[1]; originally the Y-axes
		// Tx = m_pdData[5]; originally the Tx-axes
		// Ty = m_pdData[3]; originally the Tz-axes
		// Tz = m_pdData[4]; originally the Ty-axes

		m_dCorrectedFTAxes[0] =			m_pdData[2];
		m_dCorrectedFTAxes[1] =			m_pdData[0];
		m_dCorrectedFTAxes[2] =			m_pdData[1];
		m_dCorrectedFTAxes[3] = -1.0 *  m_pdData[3];
		m_dCorrectedFTAxes[4] =         m_pdData[5];
		m_dCorrectedFTAxes[5] =			m_pdData[4];

		// Average Data by using a low-pass frequency filter equation.
		// We use alpha as a parameter to establish the weight of old or new data
		// It creates an averaging filter over time.
		for (i=0; i<NUM_AXES; i++)
		{
			m_dFTAveragedData[i] = (1 - alpha) * m_dPreviousFTData[i] + alpha * m_dCorrectedFTAxes[i];

			// Copy current data into PreviousFTData array
			m_dPreviousFTData[i] = m_dFTAveragedData[i];
		}

		// TIMING
		// Read timing data
		QueryPerformanceCounter(&end_ticks);
		// Compute time between sample readings
		sample_time = (double)(end_ticks.QuadPart - start_ticks.QuadPart)/(double)ticksPerSecond.QuadPart;
		// Copy end_ticks time to start_ticks time, to compute the difference for the next run.
		end_ticks.QuadPart = start_ticks.QuadPart;

		// Write the controller output to a file(title, data, filename).
		if(m_bWrite2File == TRUE)
		{
			if(m_sFTWristSide == 0)	// LEFT
				Write2File("Force Data", sample_time, m_dFTAveragedData, FORCE_DATA_LEFT);
			if(m_sFTWristSide == 1)	// LEFT
				Write2File("Force Data", sample_time, m_dFTAveragedData, FORCE_DATA_RIGHT);
		}

		// Pass it to the VS on the interface
		mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(mysa->pvData,m_dFTAveragedData,sizeof(double)*(NUM_AXES));	// Set the Actual Physical Angles
		pIVSOut->SetCurrentVector(mysa);

		// Destroy SafeArray
		SafeArrayDestroy(mysa);
		pIVSOut->Release();
	}

	else
	{
		if (pIVSOut != NULL)
		{
			pIVSOut->Release();
			ATLTRACE(_T("CFTSensorCom::SampleAxes failed!"));

			return S_OK;
		}
	}

	return S_OK;
}

/*************************************************************
/* SampleAxes(pdData[6])
/* 
/* Calls SampleFT, where six values of force-torque data are 
/* placed in the six elements of the double array pdData[].
*************************************************************/
STDMETHODIMP CFTSensorCom::SampleAxes(double pdData[NUM_AXES])
{
	// TODO: Add your implementation code here
 	if(pdData == NULL) return !S_OK;

	m_pftSensor->SampleFT(pdData);

	return S_OK;

}

STDMETHODIMP CFTSensorCom::get_CurrentFrameIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal = m_sCurrentFrameIndex;
	return S_OK;
}

STDMETHODIMP CFTSensorCom::put_CurrentFrameIndex(short newVal)
{
	// TODO: Add your implementation code here
	if ((newVal >= 0) && (newVal < 6))
		m_sCurrentFrameIndex = newVal;
	return S_OK;
}

STDMETHODIMP CFTSensorCom::get_CurrentFrame(double *pVal)
{
	// Get actual frame from WrapperClass
	m_pftSensor->GetFrame(m_pdFrame);

	// Pass value to interface parameter
	if (pVal != NULL)
		*pVal = m_pdFrame[m_sCurrentFrameIndex];
	return S_OK;
}

STDMETHODIMP CFTSensorCom::put_CurrentFrame(double newVal)
{
	// TODO: Add your implementation code here
	m_pdFrame[m_sCurrentFrameIndex] = newVal;
	m_pftSensor->SetFrame(m_pdFrame);
	

	return S_OK;
}

STDMETHODIMP CFTSensorCom::get_AverageLength(long *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal = m_lAverageLength;
	return S_OK;
}

STDMETHODIMP CFTSensorCom::put_AverageLength(long newVal)
{
	// TODO: Add your implementation code here
	if( (newVal == 2) || (newVal == 4) || (newVal ==8) || (newVal == 16) || (newVal == 32))
	{
		m_lAverageLength = newVal;
		return S_OK;
	}
	else
		return S_OK;
	
}

// only take strings that are either: COM1 or COM2
STDMETHODIMP CFTSensorCom::get_DeviceFilename(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_sCommFileName);

	return S_OK;
}

STDMETHODIMP CFTSensorCom::put_DeviceFilename(BSTR newVal)
{
	// String conversion macro
	USES_CONVERSION;

	// Only accept \\COM1 or \\COM2
	if( !strcmp(OLE2T(newVal),"\\COM1") || !strcmp(OLE2T(newVal),"\\COM2"))
		SysReAllocString(&m_sCommFileName, newVal);
	else 
		m_sCommFileName = SysAllocString(L"Please enter either \\COM1 or \\COM2");

	ATLTRACE("put_m_sCommFileName: setting Comm Timeout. \n");

	return S_OK;
}


STDMETHODIMP CFTSensorCom::get_FTWristSide(BSTR *pVal)
{
	// TODO: Add your implementation code here
	if(m_sFTWristSide==0)
		*pVal=SysAllocString(L"Left");
	else if (m_sFTWristSide==1)
		*pVal=SysAllocString(L"Right");
	else
		*pVal=SysAllocString(L"Invalid");


	return S_OK;
}

STDMETHODIMP CFTSensorCom::put_FTWristSide(BSTR newVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;

	if(strcmp(strlwr(OLE2T(newVal)),"left")==0)		// do a string compare of lower cases
		m_sFTWristSide=0;
	else if(strcmp(strlwr(OLE2T(newVal)),"right")==0)
		m_sFTWristSide=1;
	else
		return E_FAIL;

	return S_OK;
}

/*****************************************************************************
* ErrorMessage()
* Prints error message in DAD. The error message comes from the currently
* running method. The goal is to ease debugging.
*****************************************************************************/
STDMETHODIMP CFTSensorCom::get_ErrorMessage(BSTR *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL)
		*pVal = m_bstrError;			// Other functions will copy error msg to m_bstrError

	return S_OK;
}

STDMETHODIMP CFTSensorCom::put_ErrorMessage(BSTR newVal)
{
	// TODO: Add your implementation code here
	m_bstrError = SysAllocString(L"Please make sure that COM2 is associated w/ right wrist and COM1 w/ left wrist");
	
	return S_OK;
}


/************************************************************************************/
/* Bias sensor
/* Normally done when arm is at home positions so sensor reads 0 accross FxFyFzTxTyTz
/************************************************************************************/

// Use wrapper class to enable this call
STDMETHODIMP CFTSensorCom::BiasSensor()
{
	m_pftSensor->BiasSensor(m_bBiasSensor);
	m_bstrError = SysAllocString(L"Sensor was biased.");

	return S_OK;
}

STDMETHODIMP CFTSensorCom::EnablePeaks()
{
	m_pftSensor->EnablePeaks(m_bPeaks);

	return S_OK;
}


// Closes Serial Port
STDMETHODIMP CFTSensorCom::Close()
{
	// Call only if class has been initialize
	if(m_bInitialized == 1)
	{
		// Call the destructor of the CComPort class which calls the CloseHandle() routine for the port.
		m_pftSensor->m_pPort->~CCommPort();

		// Change flag
		m_bInitialized = 0;
	}

	return S_OK;
}


// Will write to a file the values passed to the input argument.
void CFTSensorCom::Write2File(char * title, double time, double * positions , char * textfile)
{
	int i;
	USES_CONVERSION;

	// Save directory file
	char Path[200] = PATH;					// PATH is saved as a #define

	// Copy directory path
	strcat(Path,textfile);	

	// Open the file. Mode is to append and create a text file.
	stream = fopen(Path,"a+t");

	// Write result to the file

	// Title of data - not necessary.
	//fprintf(stream, "%s\t", title);
	// Two new line characters
	//fprintf(stream, "\n\n");

	// Time
	fprintf(stream, "%.2f\t", time);

	// Data
	for(i=0;i<NUM_AXES;i++)
		fprintf(stream,"%.2f\t", positions[i]);

	// Newline
	fprintf(stream, "\n");

	// Close the file
	fclose(stream);
	stream = NULL;

}










/*
STDMETHODIMP CFTSensorCom::get_CommReadTimeout(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_sCommReadTimeouts);
	return S_OK;
}

STDMETHODIMP CFTSensorCom::put_CommReadTimeout(BSTR newVal)
{
	// TODO: Add your implementation code here
	SysReAllocString(&m_sCommReadTimeouts, newVal);
	ATLTRACE("put_m_sCommReadTimeouts: setting Comm Timeout. \n");

	return S_OK;
}

STDMETHODIMP CFTSensorCom::get_CommParams(BSTR *pVal)
{
	// TODO: Add your implementation code here
	*pVal = SysAllocString(m_sCommParams);

	return S_OK;
}

STDMETHODIMP CFTSensorCom::put_CommParams(BSTR newVal)
{
	// TODO: Add your implementation code here
	SysReAllocString(&m_sCommParams, newVal);
	ATLTRACE("put_m_sCommParams: setting Comm Timeout. \n");

	return S_OK;
}
*/


