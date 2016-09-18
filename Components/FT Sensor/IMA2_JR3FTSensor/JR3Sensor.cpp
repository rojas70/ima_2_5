// JR3Sensor.cpp : Implementation of CJR3Sensor
// For more info please refer to: O:\Documentation\System Description\FT Sensor\JR3
// 
// Things to note:
//
// Filters
// For many sensor method calls one can select one out of FOUR different types of filter settings. 
// The filter settings are described in detail in the sensor manual. Each filter 
// setting has different pass bandwidths, delays, etc. You should test depending on your 
// needs and see which one works better. 
//
// An offset is also called a zero or tare reading. After you bolt the  
// sensor in place and load all the initial tooling and possibly a part,  
// there will be initial readings on the sensor. Many times we call these  
// readings the offset. If we are only interested in the readings relative to  
// where we start the robot's process, the initial reading is removed by  
// "resetting our offsets".
  
// The full scale is the number in lbs or N that will result in the digital  
// reading from the sensor being equal to 16K counts (16,384). The digital  
// reading from the sensor is divided by 16384 then multiplied by the Full  
// Scale for that axis and the result is the load the sensor measured in the  
// units (lb, inlb or N, NM) that the sensor was programmed with.
// 
// The command_W0 is mainly used to confirm that any low level commands used  
// have been executed by our system. If you are using the C++ library of  
// calls, you do not need to worry about this command.
//
// Juan Rojas. Jan 08.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "IMA2_JR3FTSensor.h"
#include "JR3Sensor.h"

/////////////////////////////////////////////////////////////////////////////
// CJR3Sensor
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
// CJR3Sensor::OnConstruct() 
// OnConstruct() is called when the component is created. In addition to putting in
// whatever initialization code you need, If you are going to connect to another
// component anywhere in your code, you need to set up bindings. 
//
// The following code will create one binding. Change "DescriptiveName" to some
// appropriate string. This string will be visible as the name of the binding from
// DAD. It is *not* the name of the component you will bind to. The name of the
// specific component on the other end of the binding is determined at runtime (in DAD).
//
// If you wish to allow only one component to connect to this binding, make the BindType
// BT_Default. If you wish to allow several components, make the BindType BT_Collection.
//////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::OnConstruct()
{
// TODO: Bindings. Personalize the binding of your component. 
	int					numiids;
	numiids				= 1;
	IMA2_BindingInfo	BindInf;

	// 1. FTData
	BindInf.Name		= SysAllocString(L"FT_Data");						// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets. Could be BT_Default.
	BindInf.Path		= SysAllocString(L"");								// This must be the path of our component
	BindInf.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	BindInf.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.	


	// 2. Offset data
	BindInf.Name		= SysAllocString(L"FT_OffsetData");					// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets. Could be BT_Default.
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.
	
	// 3. FTMaxMinData
	BindInf.Name		= SysAllocString(L"FT_MaxMinData");					// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets. Could be BT_Default.
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.


	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);

  return S_OK;
}
STDMETHODIMP CJR3Sensor::OnDestruct() 
{	
	close_jr3();
	return S_OK; 
}
//////////////////////////////////////////////////////////////////////////////////////////
// CJR3Sensor::Save(VARIANT *pData)
// This method is called by DAD when a component is saved. Items that should be saved are the
// ones that are important to the setup of the code, or user options that should hold over
// from one use of an agent to another. (Example: size of data, filenames, etc.) 
//
// For each variable to be saved, make a copy of the code between **START** and **FINISH**
// (and paste them so that they all appear before the call to GetPropertyBag). Change the
// term "DescriptiveName" to something descriptive of the item you are saving, and make
// sure not to reuse names. In the next line of code, change "m_MyPrivateVariable" to the variable
// you are saving and VarType to the VarType of that value. Valid types and VarTypes are:
// (Note: These are limited by VB/OLE compatibility, not by the list of things that Variants can be.)
// int:		VT_I4
// float:	VT_R4
// double:	VT_R8
// BSTR:	VT_BSTR
// char:	VT_BYTE
// All strings (char*) should be converted to BSTR (see BSTR documentation).
// A CString can be converted to a BSTR using the member function AllocSysString (see CString documentation)
//
// If you want to save an array, you have to assign a SAFEARRAY to the Variant. (Do NOT just
// use a pointer, it will save just one value). replace the line starting "ItemValue =" with the following 
// code (substituting your pointer for "variable", the array length for "numelem", int/float/double, etc. 
// for "Type", and using the VarType of one element of the array--BSTR arrays are not allowed.):
//
//	ItemValue = new variant_t;
//	ItemValue->vt=VT_ARRAY|VarType;
//	ItemValue->parray=SafeArrayCreateVector(VarType,0,numelem);
//  memcpy(ItemValue->parray->pvData,variable,numelem*sizeof(Type));
//
// Note: "delete ItemValue" will take care of destroying the safearray (do *not* call SafeArrayDestroy).
// Because of the nature of a SafeArray, you do not have to explicitly save the length of the array.
// However, due to the nature of property bags, you must call the array version of the Add function:
//
//  hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
//
// (See Load comments for how to extract arrays from the propertybag).
//////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::Save(VARIANT *pData) {
	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t				*ItemValue;
	_PropertyBagWrapper		*pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);
		if (pIPB == NULL)	
			return !S_OK;
		

		// Create string names for items to be saved
		// Max or Min Value for peaks
		ItemName = SysAllocString(L"MaxMinPeak");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_sFTMaxMinPeaksValue,VT_I2);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;
		// **FINISH**
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
//////////////////////////////////////////////////////////////////////////////////////////
// CJR3Sensor::Load(VARIANT Data)
// This function will load in all the data you just saved in the Save function.
// 
// For each variable to be loaded, make a copy of the code between **START** and **FINISH**
// (and paste them so that they all appear before the call to VariantClear). Change the
// term "NameUsedToSave" to the name you gave this item in Save.
// On the line beginning "variable = ", change "variable" to the variable that you saved
// the value from, and change "Type" to the type of that variable (use "long" for "int")
// A CString can be directly set to a BSTR, but in order to get a char* back, you have to 
// use strcpy (I think).
//
// If you made an array, you have to load it back in now.
// Just like in the save function, you must call the array version of the Get function:
//
//  pIPB->GetArrayFromPropertyBag(&ItemName, ItemValue);
//
// If your variable is dynamically allocated, make sure to delete and reallocate it:
//
//  if(variable!=NULL)
//		delete variable;
//  variable=new Type[ItemValue->parray->rgsabound->cElements];	
//
// Then just copy the values from the parray (replace the "variable =" line with this):
//
//  memcpy(variable,ItemValue->parray->pvData,ItemValue->parray->rgsabound->cElements*sizeof(Type));
//
// Note that this means you do not have to separately save the length of the array, although if
// you have a variable that keeps track of the array length you should also set it at this point:
//
//  numelem=ItemValue->parray->rgsabound->cElements;
//
//////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::Load(VARIANT Data) {
	
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

		// Max or Min Value for peaks
		// Define strings
		ItemName		= SysAllocString(L"MaxMinPeak");
		ItemValue		= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_sFTMaxMinPeaksValue	= *ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;
		// **FINISH**
		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();
		
return S_OK;
}

//////////////
// Properties
//////////////
STDMETHODIMP CJR3Sensor::get_FullScales(double *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_dFullScales[m_sFullScaleIndex];
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// put_FullScales()
//
// Allows to change the value of the fullscales by inputing a new value
// for a particular index representing the force or the torque. 
//////////////////////////////////////////////////////////////////////////

STDMETHODIMP CJR3Sensor::put_FullScales(double newVal)
{
	// TODO: Add your implementation code here
	m_dFullScales[m_sFullScaleIndex] = newVal;

	// Copy values over to six_axis_array structure
	m_setFullScales.fx = (short)m_dFullScales[0];
	m_setFullScales.fy = (short)m_dFullScales[1];
	m_setFullScales.fz = (short)m_dFullScales[2];
	m_setFullScales.mx = (short)m_dFullScales[3];
	m_setFullScales.my = (short)m_dFullScales[4];
	m_setFullScales.mz = (short)m_dFullScales[5];

	// Pass the offsets to the DSP
	m_status = set_full_scales(m_setFullScales,0);

	// Check for errors
	if(m_status!=0) return !S_OK;
	ATLTRACE(_T("\nCJR3Sensor::put_FullScales(). Card status = %.5f\n"), m_status);
	
	return S_OK;
}

STDMETHODIMP CJR3Sensor::get_OffsetData(double *pVal)
{
	// TODO: Add your implementation code here
	*pVal= m_dOffsets[m_sOffsetsIndex];

	return S_OK;
}

STDMETHODIMP CJR3Sensor::put_OffsetData(double newVal)
{
	// TODO: Add your implementation code here
	short status = 0;
	m_dOffsets[m_sOffsetsIndex] = newVal;

	// Copy values over to six_axis_array structure
	m_OS.fx = (short)m_dFTData[0];
	m_OS.fy = (short)m_dFTData[1];
	m_OS.fz = (short)m_dFTData[2];
	m_OS.mx = (short)m_dFTData[3];
	m_OS.my = (short)m_dFTData[4];
	m_OS.mz = (short)m_dFTData[5];

	// Pass the offsets to the DSP
	status = set_offsets(m_OS,0);

	// Check for errors
	if(status!=0) return !S_OK;
	ATLTRACE(_T("\nCJR3Sensor::put_OffsetData(). Card status = %.5f\n"), status);


	return S_OK;
}

STDMETHODIMP CJR3Sensor::get_OffsetDataIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL) *pVal=m_sOffsetsIndex;
	return S_OK;
}

STDMETHODIMP CJR3Sensor::put_OffsetDataIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES) m_sOffsetsIndex = newVal;
	return S_OK;
}

//////////////////////////////////////////////////////////////////
// Displays the FTData in the IMA interface.
// Read_FTData()
//////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::get_FTData(double *pVal)
{
	// Copy the value of FTData saved in the private variable
	*pVal= m_dFTData[m_sFTDataIndex];
	return S_OK;
}

STDMETHODIMP CJR3Sensor::get_FTDataIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL) *pVal=m_sFTDataIndex;
	return S_OK;
}

STDMETHODIMP CJR3Sensor::put_FTDataIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES) m_sFTDataIndex = newVal;
	return S_OK;
}

//////////////////////////////////////////////////////////////////
// get/put_MaxMinPeakIndex()
//
// Sets the index to retrieve data from the m_dFTPeaks member variable
//////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::get_MaxMinPeakIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if (pVal != NULL) *pVal=m_sFTMaxMinPeaksIndex;
	return S_OK;
}

STDMETHODIMP CJR3Sensor::put_MaxMinPeakIndex(short newVal)
{
	// TODO: Add your implementation code here
	if (newVal >= 0 && newVal < NUM_AXES) m_sFTMaxMinPeaksIndex = newVal;
	return S_OK;
}

//////////////////////////////////////////////////////////////////
// MaxMinPeakData()
//
// Retrieve the actual data stored in the private member variable.
//////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::get_MaxMinPeakData(double *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_dFTPeaks[m_sFTMaxMinPeaksIndex];
	return S_OK;
}

//////////////////////////////////////////////////////////////////
// MaxMinValue()
// 
// Select whether you want to retrive the maximum or 
// minimum valus by typing either "max" or "min" in the
// DAD interface.
//////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::get_MaxMinValue(BSTR *pVal)
{
	// TODO: Add your implementation code here
	if (m_sFTMaxMinPeaksValue == 0)
		*pVal = SysAllocString(L"min");
	else if (m_sFTMaxMinPeaksValue == 1)
		*pVal = SysAllocString(L"max");
	else
		*pVal = SysAllocString(L"invalid");
	return S_OK;
}

STDMETHODIMP CJR3Sensor::put_MaxMinValue(BSTR newVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;

	// Make lower case letters before comparing
	if(strcmp(strlwr(OLE2T(newVal)),"min")==0)
		m_sFTMaxMinPeaksValue=0;
	else if(strcmp(strlwr(OLE2T(newVal)),"max")==0)
		m_sFTMaxMinPeaksValue=1;
	else
		return E_FAIL;
	
	return S_OK;
}



////////////////////
/***  Methods  ****/
////////////////////

//////////////////////////////////////////////////////////////////////////
// Initialize()
//
// Initializes the DSP Hardware
// If there is an error, it returns !S_OK
// ATLTRACE can return code to the dump.
// Return Values:
// 0: if running under Windows_NT
// 1: If running under Windows_95
// 2: If running under Windows_311 with win32s
// 3: if running under other operating system -> ERROR: STOP OPERATION.

// -91: Failled to open Handle to Windriver ... run wdreg
// -92: Windriver version error
// -93: PCI Card Not Found
// -94: Card Not In Range
// -95: Failed Locking PCI Card (already in use)
// -96: Download Error
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::Initialize()
{
	if(m_status == NOT_INITIALIZED)
	{
	// Start Sensor
		m_status = init_jr3(0x1762,0x1111,1,1,1);
		ATLTRACE(_T("\nCJR3Sensor::Initialize(). Card status = %.5f\n"), m_status);
		
		// Read FTData once for testing
		m_FT = read_ftdata(FILTER6,0);

		// Get the Recommended Minimum Full Scales to be used when we read FTData
		// Full scales is the range in lbs that the sensor can measure.
		// We are using the MAX full scales to have a greater degree of accuracy in the sensor.
		m_FS = get_recommended_full_scales(MAX_F_S,0);
		set_full_scales(m_FS,0);

		/* ROTATION TRANSFORM
		* The home position as is mounted on the barret hand after a 45 degree rotation about z is the following:
		*
		*	|	0	0	 1 |	ie. If the HP3JC is at the home position and you look  into the palm of the barrett hand,
		*	|	1   0	 0 |	Z - is pointint out of the sensor; Y - up; and X - to the left.
		*	|   0	1	 0 |
		*
		* So a rotation about the current y-axis by 90 degrees followed
		* by a rotation about the new x-axis by 90 degrees will allow us 
		* to align the coordinate axes of the FT sensor with that of the HP3JC
		* manipulator.
		*
		* The rotation structure used by the JR3 requires us to multiply by (32768/180)
		* when using degrees.
		*/

		transform std_tf;
		// Use RIGHT HAND RULE
		/* Goal:    z
		*			|
		*			|
		*			|
		*			-------y
		*/
		// Pre-aligning of axes by rotating about z. 
		//	|	0	0	-1 |
		//	|  -1   0	 0 |
		//	|   0	1	 0 |
		std_tf.link[0].link_type	= rz;
		std_tf.link[0].link_amount	= 45 * (32768/180);	// rotate CLOCK-WISE (z-direction is pointing into the manipulator).
		set_transforms(std_tf,0,0);						// Adds transform to the queue. It's implemented when USE_TRANSFORM is called.

		// Y-rotation of 90 degrees: puts X-poiting out of the plane.
		//	|	1	0	 0 |
		//	|	0   0	 1 |
		//	|   0	1	 0 |
		std_tf.link[1].link_type	= ry;
		std_tf.link[1].link_amount	= 90 * (32768/180);
		set_transforms(std_tf,0,0);						
			

		// X-rotation of -90 degrees: puts z-poiting up.
		//	|	1	0	 0 |
		//	|	0   1	 0 |
		//	|   0	0	 1 |
		std_tf.link[2].link_type	= rx;
		std_tf.link[2].link_amount	= -90 * (32768/180);
		set_transforms(std_tf,0,0);			
		
		// Activate all transforms
		use_transform(0,0);								
		
		// Reset other variables:
		peak_data_reset(FILTER6,0); // Reseat peak data
		Sleep(200);

		// Read again for testing
		m_FT = read_ftdata(FILTER6,0);
		reset_offsets(0);			// Reset offsets
		reset_offsets(0);			// Reset offsets
		Sleep(1000);
		m_FT = read_ftdata(FILTER6,0);

		// Wait for a second to let sensor stabilize
		Sleep(500);

		// Prepare Timing Variables

		// 1) Get CPU's frequency
		QueryPerformanceFrequency(&ticksPerSecond);		// Gets CPU frequency, ie. how many ticks in one second.
		QueryPerformanceCounter(&start_ticks);			// Store initial value for counter.

		// Change flag
		m_status = INITIALIZED;
	}	

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Read_FTData()
// 
// This function will call the command to read the force
// torque data from the JR3 sensor and store it in the 
// private member variable of type struc force_array.
// The data is then compied to a local double array to be
// passed to the Vector Signal for further processing.
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::Read_FTData()
{
	// Declare Variables
	int					i;
	SAFEARRAY*		 mysa;
	IVectorSignal*	 pIVS_FTData	= NULL;	

	if(m_status == NOT_INITIALIZED)
		Initialize();

	// Read the force/torque Data
	m_FT = read_ftdata(FILTER6,0);

	// Need to convert the data into lbs.
	// When you divide,  you must have the 0.0 (at least 1d.p.).
	m_dCurrentFTData[0] = m_FT.fx / 16384.0 * m_FS.fx; 
	m_dCurrentFTData[1] = m_FT.fy / 16384.0 * m_FS.fy;
	m_dCurrentFTData[2] = m_FT.fz / 16384.0 * m_FS.fz;
	m_dCurrentFTData[3] = m_FT.mx / 16384.0 * m_FS.mx;
	m_dCurrentFTData[4] = m_FT.my / 16384.0 * m_FS.my;
	m_dCurrentFTData[5] = m_FT.mz / 16384.0 * m_FS.mz;

	// Average Data by using a low-pass frequency filter equation.
	// We use alpha as a parameter to establish the weight of old or new data
	// It creates an averaging filter over time.
	for (i=0; i<NUM_AXES; i++)
		m_dFTData[i] = (1 - alpha) * m_dPreviousFTData[i] + alpha * m_dCurrentFTData[i];

	// Copy our outgoing data into our PreviousFTData structre
	memcpy(m_dPreviousFTData,m_dFTData,sizeof(double)*NUM_AXES);

	// TIMING
	// Read timing data
	QueryPerformanceCounter(&end_ticks);
	// Compute time between sample readings
	sample_time = (double)(end_ticks.QuadPart - start_ticks.QuadPart)/(double)ticksPerSecond.QuadPart;
	// Copy end_ticks time to start_ticks time, to compute the difference for the next run.
	end_ticks.QuadPart = start_ticks.QuadPart;

	// Write the controller output to a file(title, data, filename).
	if(m_bWrite2File == TRUE)
		Write2File("Force Data", sample_time, m_dFTData, FORCE);

	// Get object and interface pointer
	m_Bindings->get_Pointers(SysAllocString(L"FT_Data"),&m_pIUnkFTData);	

	if(m_pIUnkFTData != NULL)	
		m_pIUnkFTData->QueryInterface(IID_IVectorSignal,(void **)&pIVS_FTData);
		
	if (pIVS_FTData != NULL)
	{
		// Save data into the SAFEARRAY structure to pass to vector signal.
		mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(mysa->pvData,m_dFTData,sizeof(double)*(NUM_AXES));	
		pIVS_FTData->SetCurrentVector(mysa);
		// Write to the dump/debug window
		ATLTRACE(_T("\nCJR3Sensor::Read_FTData(). Fx = %.5f, Fy = %.5f, Fz = %.5f, Mx = %.5f, My = %.5f, Mz = %.5f.\n"),m_dFTData[0],m_dFTData[1],m_dFTData[2],m_dFTData[3],m_dFTData[4],m_dFTData[5]);

		// Destroy SafeArray
		SafeArrayDestroy(mysa);
		pIVS_FTData->Release();


	}

	else
	{
		if (pIVS_FTData != NULL)
		{
			pIVS_FTData->Release();
			ATLTRACE(_T("\nCFTJR3::Read_FTData() failed!"));

			return S_OK;
		}
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// ReadOffsets()
//
// Helps to remove tare loads. This means that the sensor 
// can be biased so that it registers no forces or moments 
// upon original mounting. 
//
// An offset is also called a zero or tare reading. After you bolt the  
// sensor in place and load all the initial tooling and possibly a part,  
// there will be initial readings on the sensor. Many times we call these  
// readings the offset. If we are only interested in the readings relative to  
// where we start the robot's process, the initial reading is removed by  
// "resetting our offsets".
//
// I.e. The end-effecter tool will always induce a force and moment in the 
// sensor that we do not want to register. In this case, we would use
// the original FT readings as the offset so that the FT sensor reads zero's
// with the end-effecter.
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::Read_Offsets()
{
	// Declare Variables
	SAFEARRAY*		 mysa;
	IVectorSignal*	 pIVS_Offset	= NULL;	

	// Read Offsets (Input is processor number).
	m_OS = read_offsets(0);

	// Get object and interface pointer
	m_Bindings->get_Pointers(SysAllocString(L"FT_OffsetData"),&m_pIUnkOffsetData);	

	if(m_pIUnkFTData != NULL)	
		m_pIUnkFTData->QueryInterface(IID_IVectorSignal,(void **)&pIVS_Offset);
		
	if (pIVS_Offset != NULL)
	{
		// Save data into the SAFEARRAY structure to pass to vector signal.
		mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(mysa->pvData,m_dOffsets,sizeof(double)*(NUM_AXES));	
		pIVS_Offset->SetCurrentVector(mysa);
		// Write to the dump/debug window
		ATLTRACE(_T("\nCJR3Sensor::ReadOffsets(). Fx = %.5f, Fy = %.5f, Fz = %.5f, Mx = %.5f, My = %.5f, Mz = %.5f.\n"),m_OS.fx,m_OS.fy,m_OS.fz,m_OS.mx,m_OS.my,m_OS.mz);

		// Destroy SafeArray
		SafeArrayDestroy(mysa);
		pIVS_Offset->Release();
	}

	else
	{
		if (pIVS_Offset != NULL)
		{
			pIVS_Offset->Release();
			ATLTRACE(_T("CFTJR3::Read_FTData() failed!"));

			return S_OK;
		}
	}

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// ResetOffsets()
//
// Resets the NUMERICAL value of this variable. It does not set it??  
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::ResetOffsets()
{
	short status = reset_offsets(0);
	ATLTRACE(_T("\nCJR3Sensor::ResetOffsets(). Offset status = %.5f\n"), status);

	// If not zero, NOT successful
	if (status != 0) return !S_OK;
	else
		return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Read_Max_or_MinPeaks()
//
// This function will read either the maximum or minimum peaks.
// This call is meaningful only when the user has read FT values several 
// times. 
//
// As part of a serpate index function, the user will have to 
// decide whether to measure the maximum or minimum peaks.
// Maximum peaks = 1 or "max". Minimum peaks = 0 or "min"
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::Read_FTMax_or_MinPeaks()
{
	// Declare Variables
	short			 status = 0;
	SAFEARRAY*		 mysa;
	IVectorSignal*	 pIVS_FTPeaks	= NULL;	

	// Reset peak information.Input parameters: (filter address, processor number).
	//	peak_data_reset(FILTER6,0); 

	// Read peaks 
	// Input parameters: a) (0) for Minimum or (1) for Maximum, and b) processor number
	// Return Value: Peak data in a force_array format
	//m_FTPeaks = read_peaks(m_sFTMaxMinPeaksIndex,0);

		// Copy to double array
	/*	m_dFTPeaks[0] = m_FTPeaks.fx;
		m_dFTPeaks[1] = m_FTPeaks.fy;
		m_dFTPeaks[2] = m_FTPeaks.fz;
		m_dFTPeaks[3] = m_FTPeaks.mx;
		m_dFTPeaks[4] = m_FTPeaks.my;
		m_dFTPeaks[5] = m_FTPeaks.mz;
	*/

	// Get Peak data
	status = peak_data(FILTER6,0);
	// Check for errors
	ATLTRACE(_T("\nCJR3Sensor::Read_FTMax_or_MinPeaks(). Offset status = %.5f\n"), status);
	if (status!= 3072) return !S_OK;		// 3072 is associated with success.

	// Store values

	// Maximum values
	if (m_sFTMaxMinPeaksIndex == 1)
	{
		m_dFTPeaks[0] = read_jr3(MAXIMUM_D+0,0);
		m_dFTPeaks[1] = read_jr3(MAXIMUM_D+1,0);
		m_dFTPeaks[2] = read_jr3(MAXIMUM_D+2,0);
		m_dFTPeaks[3] = read_jr3(MAXIMUM_D+3,0);
		m_dFTPeaks[4] = read_jr3(MAXIMUM_D+4,0);
		m_dFTPeaks[5] = read_jr3(MAXIMUM_D+5,0);
	}
	else // Minimum values
	{
		m_dFTPeaks[0] = read_jr3(MINIMUM_D+0,0);
		m_dFTPeaks[1] = read_jr3(MINIMUM_D+1,0);
		m_dFTPeaks[2] = read_jr3(MINIMUM_D+2,0);
		m_dFTPeaks[3] = read_jr3(MINIMUM_D+3,0);
		m_dFTPeaks[4] = read_jr3(MINIMUM_D+4,0);
		m_dFTPeaks[5] = read_jr3(MINIMUM_D+5,0);
	}

	// Get object and inter	face pointer
	m_Bindings->get_Pointers(SysAllocString(L"FT_MaxMinData"),&m_pIUnkFTPeaks);	

	if(m_pIUnkFTPeaks != NULL)	
		m_pIUnkFTPeaks->QueryInterface(IID_IVectorSignal,(void **)&pIVS_FTPeaks);
		
	if (pIVS_FTPeaks != NULL)
	{
		// Save data into the SAFEARRAY structure to pass to vector signal.
		mysa = SafeArrayCreateVector(VT_R8,0,NUM_AXES);
		memcpy(mysa->pvData,m_dFTPeaks,sizeof(double)*(NUM_AXES));	
		pIVS_FTPeaks->SetCurrentVector(mysa);
		// Write to the dump/debug window
		ATLTRACE(_T("\nCJR3Sensor::Read_Max_or_MinPeaks(). Fx = %.5f, Fy = %.5f, Fz = %.5f, Mx = %.5f, My = %.5f, Mz = %.5f.\n"),m_FTPeaks.fx,m_FTPeaks.fy,m_FTPeaks.fz,m_FTPeaks.mx,m_FTPeaks.my,m_FTPeaks.mz);

		// Destroy SafeArray
		SafeArrayDestroy(mysa);
		pIVS_FTPeaks->Release();
	}

	else
	{
		if (pIVS_FTPeaks != NULL)
		{
			pIVS_FTPeaks->Release();
			ATLTRACE(_T("CFTJR3::Read_FTMax_or_MinPeaks() failed!"));

			return S_OK;
		}
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////////
// Read_FullScales()
// 
// It reads the current values set for FullScales and saves them into the private
// member array m_dFullScales.
//
// The full scale is the number in lbs or N that will result in the digital  
// reading from the sensor being equal to 16K counts (16,384). The digital  
// reading from the sensor is divided by 16384 then multiplied by the Full  
// Scale for that axis and the result is the load the sensor measured in the  
// units (lb, inlb or N, NM) that the sensor was programmed with.
/////////////////////////////////////////////////////////////////////////////////////1
STDMETHODIMP CJR3Sensor::Read_FullScales()
{
	// Store values retrieved by function call into a struct six_axis_array
	m_FullScales = get_full_scales(0);

	/**** Need to add code to check that operation was successful ***/

	// Copy values over to six_axis_array_structure so that it can be retried in the get function
	m_dFullScales[0] = m_FullScales.fx;
	m_dFullScales[1] = m_FullScales.fy;
	m_dFullScales[2] = m_FullScales.fz;
	m_dFullScales[3] = m_FullScales.mx;
	m_dFullScales[4] = m_FullScales.my;
	m_dFullScales[5] = m_FullScales.mz;
	// Should we consider V1 and V2. Probably not until you understand these better. 
	
	ATLTRACE(_T("\nCJR3Sensor::Read_FullScales(). Fx = %.5f, Fy = %.5f, Fz = %.5f, Mx = %.5f, My = %.5f, Mz = %.5f.\n"),m_FullScales.fx,m_FullScales.fy,m_FullScales.fz,m_FullScales.mx,m_FullScales.my,m_FullScales.mz);

	return S_OK;
}
//////////////////////////////////////////////////////////////////////////
// Set_FullScales()
//
// Sets/Writes the existing values of private array m_dFullScales
// into the sensor DSP. 
// Note: These values could come through 3 different ways:
// (1) Reading the Full Scales
// (2) Reading Recommended Maximum Scales
// (3) Reading Recommended Minimum Scales
//////////////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::Set_FullScales()
{
	// Similar to put_FullScales
	short status = 0;

	// Copy values over to six_axis_array structure
	m_setFullScales.fx = (short)m_dFullScales[0];
	m_setFullScales.fy = (short)m_dFullScales[1];
	m_setFullScales.fz = (short)m_dFullScales[2];
	m_setFullScales.mx = (short)m_dFullScales[3];
	m_setFullScales.my = (short)m_dFullScales[4];
	m_setFullScales.mz = (short)m_dFullScales[5];

	// Pass the offsets to the DSP
	status = set_full_scales(m_setFullScales,0);
	ATLTRACE(_T("\nCJR3Sensor::Set_FullScales(). Fx = %.5f, Fy = %.5f, Fz = %.5f, Mx = %.5f, My = %.5f, Mz = %.5f.\n"),m_FullScales.fx,m_FullScales.fy,m_FullScales.fz,m_FullScales.mx,m_FullScales.my,m_FullScales.mz);

	/**** Need to add code to check that operation was successful ***/

	// Check for errors
	if(status!=0) return !S_OK;


	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////
// Read_RecommendedMaxScales()
//
// The values provided by this function are automatically calculated based on 
// optimum margins for full scales. See manual for more information.
/////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CJR3Sensor::Read_RecommendedMaxScales()
{
	// Store values retrieved by function call into a struct six_axis_array
	m_RecFullScales = get_recommended_full_scales(MAX_F_S,0); // max FS

	/**** Need to add code to check that operation was successful ***/

	// Copy values over to six_axis_array_structure so that it can be retried in the get function
	m_dFullScales[0] = m_RecFullScales.fx;
	m_dFullScales[1] = m_RecFullScales.fy;
	m_dFullScales[2] = m_RecFullScales.fz;
	m_dFullScales[3] = m_RecFullScales.mx;
	m_dFullScales[4] = m_RecFullScales.my;
	m_dFullScales[5] = m_RecFullScales.mz;
	// Should we consider V1 and V2. Probably not until you understand these better. 
	
	ATLTRACE(_T("\nCJR3Sensor::Read_RecommendedMaxScales(). Fx = %.5f, Fy = %.5f, Fz = %.5f, Mx = %.5f, My = %.5f, Mz = %.5f.\n"),m_RecFullScales.fx,m_RecFullScales.fy,m_RecFullScales.fz,m_RecFullScales.mx,m_RecFullScales.my,m_RecFullScales.mz);

	return S_OK;
}

STDMETHODIMP CJR3Sensor::Read_RecommendedMinScales()
{
	// Store values retrieved by function call into a struct six_axis_array
	m_RecFullScales = get_recommended_full_scales(MIN_F_S,0); // max FS

	/**** Need to add code to check that operation was successful ***/

	// Copy values over to six_axis_array_structure so that it can be retried in the get function
	m_dFullScales[0] = m_RecFullScales.fx;
	m_dFullScales[1] = m_RecFullScales.fy;
	m_dFullScales[2] = m_RecFullScales.fz;
	m_dFullScales[3] = m_RecFullScales.mx;
	m_dFullScales[4] = m_RecFullScales.my;
	m_dFullScales[5] = m_RecFullScales.mz;
	// Should we consider V1 and V2. Probably not until you understand these better. 
	
	ATLTRACE(_T("\nCJR3Sensor::Read_RecommendedMinScales(). Fx = %.5f, Fy = %.5f, Fz = %.5f, Mx = %.5f, My = %.5f, Mz = %.5f.\n"),m_RecFullScales.fx,m_RecFullScales.fy,m_RecFullScales.fz,m_RecFullScales.mx,m_RecFullScales.my,m_RecFullScales.mz);

	return S_OK;
}

// Closes the sensor.
STDMETHODIMP CJR3Sensor::Close()
{
	// TODO: Add your implementation code here
	if(m_status == INITIALIZED)
	{
		close_jr3();
		m_status = NOT_INITIALIZED;
	}

	return S_OK;
}

// Alpha serves as an averaging weight parameter used in the Read_FTData() function
STDMETHODIMP CJR3Sensor::get_AveragingWeight_FTData(double *pVal)
{
	// TODO: Add your implementation code here
	if(pVal != NULL)
		*pVal = alpha;
	return S_OK;
}

STDMETHODIMP CJR3Sensor::put_AveragingWeight_FTData(double newVal)
{
	// TODO: Add your implementation code here
	if(newVal > 0 && newVal <= 1)
		alpha = newVal;
	return S_OK;
}

STDMETHODIMP CJR3Sensor::get_status(short *pVal)
{
	// TODO: Add your implementation code here
	if(pVal != NULL)
		*pVal = m_status;
	return S_OK;
}

// Will write to a file the values passed to the input argument.
void CJR3Sensor::Write2File(char * title, double time, double * positions , char * textfile)
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