// TrajectoryGen.cpp : Implementation of CTrajectoryGen
#include "stdafx.h"
#include "IMA2_TrajectoryLib.h"
#include "TrajectoryGen.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CTrajectoryGen
// 
// Input: VectorSignal  RowVector[i]	= Ending position in  XYZRPY or JointAngle information (this is due to the VectorSignal history buffer nature)
//						RowVector[i+1]	= Preceding position
//						RowVector[i+n]	= Starting position in XYZRPY or angle information
// 
//						Note: One could have up to MAX_STOPS number of points to create
//							  in between positions. It is the number of steps in between one point and the next
// 
// Output:	Written file with the step trajectory going from the ending position to the preceding positions
//			until the starting position is reached.
//			Each line contains a Time Increment accompanied by an incrementing/decrementing step related to position.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTrajectoryGen::get_NumElements(long *pVal)
{
	if(pVal==NULL)
		return E_POINTER;

	*pVal=m_lNumElements;

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::put_NumElements(long newVal)
{
	if(newVal>0 && newVal<7)
		m_lNumElements=newVal;

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::get_NumStepsIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if(pVal==NULL)
		return E_POINTER;
	
	*pVal=m_sNumStepsIndex;
	return S_OK;
}

STDMETHODIMP CTrajectoryGen::put_NumStepsIndex(short newVal)
{
	// TODO: Add your implementation code here
	if(newVal>0)
		m_sNumStepsIndex=newVal;
	return S_OK;
}

STDMETHODIMP CTrajectoryGen::get_NumSteps(long *pVal)
{
	if(pVal==NULL)
		return E_POINTER;

	*pVal=m_lNumSteps[m_sNumStepsIndex];

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::put_NumSteps(long newVal)
{
	m_lNumSteps[m_sNumStepsIndex]=newVal;

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::get_TravelPeriodIndex(short *pVal)
{
	// TODO: Add your implementation code here
	if(pVal==NULL)
		return E_POINTER;
	
	*pVal=m_sTravelPeriodIndex;

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::put_TravelPeriodIndex(short newVal)
{
	// TODO: Add your implementation code here
	if(newVal>=0)
		m_sTravelPeriodIndex=newVal;

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::get_TravelPeriod(double *pVal)
{
	if(pVal==NULL)
		return E_POINTER;

	*pVal=m_dTravelPeriod[m_sTravelPeriodIndex];

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::put_TravelPeriod(double newVal)
{
	m_dTravelPeriod[m_sTravelPeriodIndex]=newVal;

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::get_NumberTrajectoryPoints(long *pVal)
{
	if(pVal==NULL)
		return E_POINTER;

	*pVal=m_lNumberTrajectoryPoints;

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::put_NumberTrajectoryPoints(long newVal)
{
	if(newVal>0)
		m_lNumberTrajectoryPoints=newVal;

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::get_StartTime(double *pVal)
{
	if(pVal==NULL)
		return E_POINTER;

	*pVal=m_dStartTime;
	return S_OK;
}

STDMETHODIMP CTrajectoryGen::put_StartTime(double newVal)
{
	if(m_dStartTime>0)
		m_dStartTime=newVal;

	return S_OK;
}

STDMETHODIMP CTrajectoryGen::get_OutputFile(BSTR *pVal)
{
	*pVal = SysAllocString(m_bstrOutputFile);
	ATLTRACE("get_ColorModelFileName: getting color model file name. \n");
	return S_OK;
}

STDMETHODIMP CTrajectoryGen::put_OutputFile(BSTR newVal)
{
	SysReAllocString(&m_bstrOutputFile,newVal);
	ATLTRACE("put_ColorModelFileName: setting color model file name. \n");
	return S_OK;
}

STDMETHODIMP CTrajectoryGen::get_SegmentedPixelThreshold(double *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_dSegmentedPixelThreshold;
	return S_OK;
}

STDMETHODIMP CTrajectoryGen::put_SegmentedPixelThreshold(double newVal)
{
	// TODO: Add your implementation code here
	
	if (newVal >0)
		m_dSegmentedPixelThreshold = newVal;
	return S_OK;
}


STDMETHODIMP CTrajectoryGen::OnConstruct()
{
// TODO: Bindings. Personalize the binding of your component. 

	int numiids;
	IMA2_BindingInfo	BindInf;
	numiids=1;

	// 1. PressureBias
	BindInf.Name		= SysAllocString(L"TrajectoryPoints");					// Assign name to object
	BindInf.BindType	= BT_Collection;									// Condition to accept multiple targets
	BindInf.Path		= SysAllocString(L"");								// This must be the path of our component
	BindInf.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	BindInf.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);		// Create and empty string array
	m_ConfigureBindings->Add(&BindInf);										// Set up the clients bindings array.	

	// 2. State Machine
	BindInf.Name		= SysAllocString(L"StateMachine");
	m_ConfigureBindings->Add(&BindInf);

	// 3. Left Color Segmenter - to check for object existance
	BindInf.Name		= SysAllocString(L"LeftNumSegmentedPixels");
	m_ConfigureBindings->Add(&BindInf);

	// 4. Right Color Segmenter - to check for object existance
	BindInf.Name		= SysAllocString(L"RightNumSegmentedPixels");
	m_ConfigureBindings->Add(&BindInf);

	// Deallocate storage
	SysFreeString(BindInf.Name);
	SysFreeString(BindInf.Path);
	SafeArrayDestroy(BindInf.PIDs);
	SafeArrayDestroy(BindInf.IIDs);

  return S_OK;
}

STDMETHODIMP CTrajectoryGen::OnDestruct() {	return S_OK; }

///////////////////////////////////////////////////////////////////
// Load data from file through data saved to the PropertyBag in VB
///////////////////////////////////////////////////////////////////
STDMETHODIMP CTrajectoryGen::Load(VARIANT Data) {
	
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

		// Variable m_lNumElements
		// Define strings
		ItemName		= SysAllocString(L"NumElements");
		ItemValue		= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_lNumElements	= (long)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_lNumberTrajectoryPoints
		// Define strings
		ItemName		= SysAllocString(L"NumberTrajectoryPoints");
		ItemValue		= new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		m_lNumberTrajectoryPoints		= (long)*ItemValue;
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_lNumSteps
		// Define strings
		ItemName	= SysAllocString(L"NumSteps");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_lNumSteps, ItemValue->parray->pvData, sizeof(long)*m_lNumberTrajectoryPoints);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_dTravelPeriod
		// Define strings
		ItemName	= SysAllocString(L"TravelPeriod");
		ItemValue			= new variant_t;
		// Read Data from the property bag
		pIPB->GetArrayFromPropertyBag(&ItemName,ItemValue);  //2nd argument is return value (look retval for help)
		memcpy(m_dTravelPeriod, ItemValue->parray->pvData, sizeof(double)*m_lNumberTrajectoryPoints);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Variable m_bstrOutputFile
		ItemName	= SysAllocString(L"FileName");
		ItemValue	= new variant_t;
		pIPB->GetFromPropertyBag(&ItemName,ItemValue);	//2nd argument is return value (look retval for help)
		SysReAllocString(&m_bstrOutputFile,ItemValue->bstrVal);
		// Deallocate
		SysFreeString(ItemName);
		delete ItemValue;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();
		
return S_OK;
}


////////////////////////////////////////////////////////////////////////
// Called by the framework to serialize the component to binary sotrage 
// in a file.
////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTrajectoryGen::Save(VARIANT *pData) {

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
		// Number of Elements
		ItemName = SysAllocString(L"NumElements");
		// Store the data and the type of data into a variant_t type
 		ItemValue = new variant_t(m_lNumElements,VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		// m_lNumberTrajectoryPoints
		ItemName = SysAllocString(L"NumberTrajectoryPoints");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t(m_lNumberTrajectoryPoints, VT_I4);
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		// m_dTravelPeriod
		ItemName = SysAllocString(L"TravelPeriod");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_R8;
		ItemValue->parray=SafeArrayCreateVector(VT_R8,0,m_lNumberTrajectoryPoints);
		memcpy(ItemValue->parray->pvData,m_dTravelPeriod,m_lNumberTrajectoryPoints*sizeof(double));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		// m_lNumSteps
		ItemName = SysAllocString(L"NumSteps");
		// Store the data and the type of data into a variant_t type
		ItemValue = new variant_t;
		ItemValue->vt=VT_ARRAY|VT_I4;
		ItemValue->parray=SafeArrayCreateVector(VT_I4,0,m_lNumberTrajectoryPoints);
		memcpy(ItemValue->parray->pvData,m_lNumSteps,m_lNumberTrajectoryPoints*sizeof(long));
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddArrayToPropertyBag(&ItemName, ItemValue);
		// Free the strings memory location
		SysFreeString(ItemName);
		// Delete our variants
		delete ItemValue;

		// Variable m_bstrOutputFile****
		ItemName = SysAllocString(L"FileName");
		ItemValue = new variant_t(m_bstrOutputFile);				// Variant stores variable as a BSTR 
		hRes = pIPB->AddToPropertyBag(&ItemName, ItemValue);
		/*	m_sColorModelFileName.WriteToStream(pStm);*/
		// Deallocate
		SysFreeString(ItemName);
		// Delete our variants
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
///////////////////////////////////////////////////
// Open a text file 
// OLE2T does string conversion
// w+t allows to write in the file in text mode 
///////////////////////////////////////////////////
void CTrajectoryGen::OpenFile()
{
	USES_CONVERSION;
	m_fp = fopen(OLE2T(m_bstrOutputFile), "w+t");
}

void CTrajectoryGen::CloseFile()
{
	if(m_fp!=NULL) {
		fclose(m_fp);
		m_fp=NULL;
	}
}


STDMETHODIMP CTrajectoryGen::GenerateTrajectory()
{
	// TODO: Add your implementation code here
	// Variables
	int i,j,k;
	double *traj[MAX_PTS];							// Trajectory array for XYZRPY or JointAngles
	double step, ssec, tsec;
	double pdPointsVS[MAX_STOPS][MAX_PTS];			// Contains actual data
	double pdSVecTmp[MAX_PTS];						// A backup copy of values will be stored here

	IVectorSignal	*IPointsVS	= NULL;
	IStateMachine	*pISM		= NULL;

	SAFEARRAY		*mysa;

	// Get object and interface
	m_Bindings->get_Pointers(SysAllocString(L"TrajectoryPoints"),&m_pIUnkPoints);
	if(m_pIUnkPoints == NULL) return E_POINTER;
	m_pIUnkPoints->QueryInterface(IID_IVectorSignal,(void**)&IPointsVS);
	if(IPointsVS != NULL)
	{
		OpenFile();							// open a text file
		tsec = m_dStartTime;				// time to be inserted in file

		// Get the first points wheter XYZRPY or Joint-Angles from the VectorSignal
		mysa = SafeArrayCreateVector(VT_R8, 0, m_lNumElements);
		IPointsVS->GetVector(0, mysa); 
		memcpy(pdPointsVS[0],mysa->pvData,sizeof(double)*m_lNumElements);

		// Write the starting point first and the time interval strings: 0.0, 0.2, ...
		fprintf(m_fp,"%.1f   ", tsec); 
		for(i=0;i<m_lNumElements;i++)	// XYZRPY/JointAngles	
		{
			fprintf(m_fp,"%.2f ", pdPointsVS[0][i]);	// Write actual data values for each of the elements 
														// (0-m_lNumElements) (XYZ) to 2 d.p.

			pdSVecTmp[i]=pdPointsVS[0][i];				// Create a copy of original positions to compare later
		}
		fprintf(m_fp,"%\n");
		

		// Get the rest of the potential points in a trajectory...
		for(k=0;k<m_lNumberTrajectoryPoints;k++)			// simplest case is where m_lNumberTrajectoryPoints = 1
											// the would be the GOAL position.
		{
			// Get the next ViaPoint in the loop
			IPointsVS->GetVector(k+1, mysa);
			memcpy(pdPointsVS[k+1],mysa->pvData,sizeof(double)*m_lNumElements);
			// Destroy SafeArray
			SafeArrayDestroy(mysa);
			
			// Generate the trajectory
			// Check to see if we are going in terms of XYZRPY or JointAngles from:
			// (1) a smaller value to a larger value
			// (2) a larger value to a smaller value
			// (3) or if it is the same position
			for(i=0;i<m_lNumElements;i++)				// Num Elements normally stands for: XYZRPY, or 6 joint angles
			{
				traj[i]=new double[m_lNumSteps[k]];		// Create a Traj Array for XYZRPY that is (i.e) a 20x1 double array
				if(pdSVecTmp[i]<pdPointsVS[k+1][i])		// Check to see if the XYZRPY or JointAngle for the next iteration
														// is not larger than the previous one
				{
					// Each step = (Final Position - Starting Position) / Tot. Num of Steps)
					step=(pdPointsVS[k+1][i]-pdSVecTmp[i])/m_lNumSteps[k];	

					traj[i][0]=pdSVecTmp[i]+step;		// add the step to the trajectory for that variable, i.e. XYZ
					for(j=1;j<m_lNumSteps[k];j++)
						traj[i][j]=traj[i][j-1]+step;	// Add the step to the next iteration/step of the array
				}

				else if(pdSVecTmp[i]>pdPointsVS[k+1][i]) // Here we are going from larger to smaller
				{
					step=(pdSVecTmp[i]-pdPointsVS[k+1][i])/m_lNumSteps[k];
					traj[i][0]=pdSVecTmp[i]-step;
					for(j=1;j<m_lNumSteps[k];j++)
						traj[i][j]=traj[i][j-1]-step;
				}
				
				// Both locations are equal
				else /* equal */
				{
					for(j=0;j<m_lNumSteps[k];j++)
						traj[i][j]=pdSVecTmp[i];
				}
			}
		
			// We are going to write the time increments and then each respective positions XYZRPY... for that time
			// Calculate the time increments = total time/toal num. of steps
			ssec=(double)m_dTravelPeriod[k]/m_lNumSteps[k];
			
			for(j=0;j<m_lNumSteps[k];j++)
			{
				// Add time increments to time counter
				tsec+=ssec;

				// Print each time lapse to file
				fprintf(m_fp,"%.1f   ", tsec);

				// Print the rest of the positions for XYZRPY or JointAngles saved in the traj array
				for(i=0;i<m_lNumElements;i++)
				{
					fprintf(m_fp,"%.2f ", traj[i][j]);
					pdSVecTmp[i]=pdPointsVS[k+1][i];
				}
				fprintf(m_fp,"%\n");
			}

			// Clear Memeory
			for(i=0;i<m_lNumElements;i++)
				delete[] traj[i];
		}
		CloseFile();

		
		// Tell State Machine to go to next state
		// Pass a BSTR to the StateMachine "Signal" call.
		// By comparing strings the SM will know to move to the next state.

		m_Bindings->get_Pointers(SysAllocString(L"StateMachine"), &m_pIUnkStateMachine);
		if (m_pIUnkStateMachine != NULL)
			m_pIUnkStateMachine->QueryInterface(IID_IStateMachine,(void **)&pISM);
		if (pISM != NULL)
			pISM->Signal(SysAllocString(L"Go to next state"));
		pISM->Release();


	}

	IPointsVS->Release();
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// CheckForObject()
//
// Input: ColorSegmenter.NoSegmentedPixels;
// Output: Flag to the state machine to go to the next state.
//
// This function will read the number of segmented pixels from both the right
// and left color segmenters. From tests it was determined that a reachable object
// of medium size should have at least 1250 pixels. This number can be modified if 
// deemed appropriate. 
//
// A connection is made to both ColorSegmenter components and this number is retrieved.
// If greater than 1250, then we pass the TrajectoryAgent State Machine to move to the next
// state. This of course is reflected in the state machines for both the right and the left
// trajectory agents. 
///////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTrajectoryGen::CheckForObject()
{
	// TODO: Add your implementation code here
	IVectorSignal	*pILCS		= NULL;
	IVectorSignal	*pIRCS		= NULL;
	IStateMachine	*pISM		= NULL;

	SAFEARRAY		*mysa;
	
	double LNoPixels = 0;
	double RNoPixels = 0;

	

	// Get objects
	m_Bindings->get_Pointers(SysAllocString(L"StateMachine"),&m_pIUnkStateMachine);
	m_Bindings->get_Pointers(SysAllocString(L"LeftNumSegmentedPixels"),&m_pIUnkLeftCS);
	m_Bindings->get_Pointers(SysAllocString(L"RightNumSegmentedPixels"),&m_pIUnkRightCS);

	if(m_pIUnkStateMachine == NULL || m_pIUnkLeftCS == NULL || m_pIUnkRightCS == NULL) return E_POINTER;

	// Get Interfaces
	m_pIUnkStateMachine->QueryInterface(IID_IStateMachine,(void**)&pISM);
	m_pIUnkLeftCS->QueryInterface(IID_IVectorSignal,(void**)&pILCS);
	m_pIUnkRightCS->QueryInterface(IID_IVectorSignal,(void**)&pIRCS);

	// Check for the condition
	if(pISM != NULL || pILCS != NULL || pIRCS != NULL)
	{

		// Run an indefinite for-loop and break only when the threshold for the number of 
		// segmented pixels for the desired object is achieved.
		// In this way, the arm, a trajectory will only be generated and achieved once the 
		// desired object is in place.
		for(;;)
		{
			// Retrieve number of segmented pixels for the left color segmenter
			mysa = SafeArrayCreateVector(VT_R8,0,1); 
			pILCS->GetCurrentVector(mysa);							// Always need to pass/retrieve doubles
			memcpy(&LNoPixels, mysa->pvData, sizeof(double)*1);
			SafeArrayDestroy(mysa);

			// Retrieve number of segmented pixels for the right and left color segmenter
			mysa = SafeArrayCreateVector(VT_R8,0,1);
			pIRCS->GetCurrentVector(mysa);							// Always need to pass/retrieve doubles
			memcpy(&RNoPixels, mysa->pvData, sizeof(double)*1);
			SafeArrayDestroy(mysa);

			// If the number surpasses the threshold, then tell the state machine to move on to the next state
			// i.e. to generate the trajectory and play it.
			if (LNoPixels > m_dSegmentedPixelThreshold && RNoPixels > m_dSegmentedPixelThreshold)
			{
				pISM->Signal(SysAllocString(L"Next"));
				Sleep(5000);
				break;
			}
		}
		
		pISM->Release();
		pILCS->Release();
		pIRCS->Release();
	}

	else
	{
		MessageBox(NULL,"TrajGen::Failed to connect to bindings","Bindings failed",MB_OK);
		pISM->Release();
		pILCS->Release();
		pIRCS->Release();
	}

	return S_OK;
}

