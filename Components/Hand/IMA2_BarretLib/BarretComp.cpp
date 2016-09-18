// BarretComp.cpp : Implementation of CBarretComp
#include "stdafx.h"
#include "IMA2_BarretLib.h"


#include "BarretComp.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "O:\Include\CommPort1.h"

#define PORT "COM4"

/////////////////////////////////////////////////////////////////////////////
// CBarretComp

/*********************************************
* Internal Constructors and Persistance (Saving and Loading)
*********************************************/
// The OnConstruct Function sets all the bindings for the component, and \
// also replaces FinalComponentInitialization
STDMETHODIMP CBarretComp::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 
	HRESULT hRes=S_OK;

	int numiids;
	long x[1];
	IMA2_BindingInfo	m_Binding;

	numiids=1;
	x[0]=0; //specifies first element

	// State Machine
	m_Binding.Name		= SysAllocString(L"StateMachine");						// Assign name to object
	m_Binding.BindType	= BT_Default;											// Condition to accept a single binding
	m_Binding.Path		= SysAllocString(L"");									// This is the path of the component you are connecting to
	m_Binding.PIDs		= SafeArrayCreateVector(VT_BSTR, 0, 1);					// Create an empty string array
	m_Binding.IIDs		= SafeArrayCreateVector(VT_BSTR, 0, numiids);			// Create an empty string array
	//SafeArrayPutElement(m_Binding.IIDs,x,(void *)SysAllocString(L"IIVectorSignal"));
	m_ConfigureBindings->Add(&m_Binding);		

	// Free Binding Info
	SysFreeString(m_Binding.Name);
	SysFreeString(m_Binding.Path);
	SafeArrayDestroy(m_Binding.PIDs);
	SafeArrayDestroy(m_Binding.IIDs);
	
	return S_OK;
}

STDMETHODIMP CBarretComp::OnDestruct() {return S_OK; }

STDMETHODIMP CBarretComp::Load(VARIANT Data) {
/*
	

	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	_PropertyBagWrapper*	pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.
	variant_t				*Var;

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;

		// Get the pointer to the real VB property bag (the VB object (defined in msvbvm60.dll (aka VBRUN)) that our wrapper class created)
		// hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Pass Data to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);

		// Variable 1
		//ItemName	= SysAllocString(L"CenteringCamera");
		//Var			= new variant_t;
		// Read Data from the property bag
		//pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		//m_bCenteringCamera		= (long)*Var;
		// Deallocate
		//SysFreeString(ItemName);
		//delete Var;
	


		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();
*/		
	return S_OK;
}

STDMETHODIMP CBarretComp::Save(VARIANT *pData) {
/*

	// Variables
	BSTR					ItemName = NULL;// The string holding the name of the item to write into the property bag.
	variant_t				*Var;
	_PropertyBagWrapper		*pIPB;			// COM Interface Pointer to the PropertyBag _Wrapper_ Class
	HRESULT					hRes;			// The HRESULT value we get back from COM calls.

	// (1) Create the property bag wrapper class
	// (2) Have the class point to the interface 
	hRes = CoCreateInstance(CLSID_PropertyBagWrapper, NULL, CLSCTX_INPROC_SERVER, IID__PropertyBagWrapper, (LPVOID*)&pIPB);

		if (pIPB == NULL)	
			return !S_OK;
		
		// Variable 1
		// Create string names for items to be saved
		//ItemName = SysAllocString(L"CenteringCamera");
		// Store the data and the type of data into a variant_t type
		//Var = new variant_t((long)m_bCenteringCamera, VT_I4);		// Casting to long, b/c BOOL (which is an int) is not accepted by the variant_t functions
		// Add an item to the property bag via the wrapper class.
		//hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		//SysFreeString(ItemName);
		//delete Var;


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
*/
	return S_OK;
}

/////////////////////////////
/**** Interface Properties ****/
////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Select the motor to be used, either, and/or fingers 1,2,3, or the Spread, S //
/////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CBarretComp::get_HandParamter(BSTR *pVal)
{
	// TODO: Add your implementation code here
	SysReAllocString(pVal,m_bstrHandParameter);
	return S_OK;
}

STDMETHODIMP CBarretComp::put_HandParamter(BSTR newVal)
{
	// TODO: Add your implementation code here
	m_bstrHandParameter = SysAllocString(newVal);
	return S_OK;
}


////////////////////////////////////////////////////////////////////////
// Determine the size of the step to open/close either of the motors. //
////////////////////////////////////////////////////////////////////////
STDMETHODIMP CBarretComp::get_StepSize(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lStepSize;
	return S_OK;
}

STDMETHODIMP CBarretComp::put_StepSize(long newVal)
{
	// TODO: Add your implementation code here
	if ((newVal > 50) && (newVal < 3000))
		m_lStepSize = newVal;
	return S_OK;
}


STDMETHODIMP CBarretComp::get_Position(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lPosition;

	return S_OK;
}

STDMETHODIMP CBarretComp::put_Position(long newVal)
{
	// TODO: Add your implementation code here
	if ((newVal > 50) && (newVal < 17500))
		m_lPosition = newVal;

	return S_OK;
}
//////////////////////////////////////////////////
// Get/Set the velocity for the indicated motor //
//////////////////////////////////////////////////
STDMETHODIMP CBarretComp::get_Velocity(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lVelocity;
	return S_OK;
}

STDMETHODIMP CBarretComp::put_Velocity(long newVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;								// Macro to enable use of OLE2T which converts a BSTR											// to a char* string
	
	// Velocity must be within limits
	if ( (newVal>0) || (newVal<256))
		m_lVelocity = newVal;

	// Get motorflag
	char* motorflag = OLE2T(m_bstrHandParameter);


	if( result=bh.Get( motorflag, "MOV", m_lVelocity ) )				// Def. vel. for opening fingers
		Error();
	if( result=bh.Get( motorflag, "MCV", m_lVelocity ) )				// Def. vel. for closing fingers
		Error();				
				

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////
// Get the value of the strain gauge registered by the indicated motor //
/////////////////////////////////////////////////////////////////////////
STDMETHODIMP CBarretComp::get_StrainGauge(long *pVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	char* motorflag = OLE2T(m_bstrHandParameter);

	if( result=bh.Get( motorflag, "SG", m_lStrainGauge ) )				// Straing gauge
		Error();

	*pVal = m_lStrainGauge;

	return S_OK;
}


//////////////////////////////////////////////////////////
// Get/Set the default position for the indicated motor //
//////////////////////////////////////////////////////////
STDMETHODIMP CBarretComp::get_DefaultPosition(long *pVal)
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	char* motorflag = OLE2T(m_bstrHandParameter);

	// Make sure there is only one motor selected at a time in the interface!!!!
	if( result=bh.Get( motorflag, "DP", m_lDefaultPosition ) )				// Def. position for an individual motor
		Error();

	*pVal = m_lDefaultPosition;

	return S_OK;
}

STDMETHODIMP CBarretComp::put_DefaultPosition(long newVal)
{
	// TODO: Add your implementation code here
	if ( (newVal>0) || (newVal<18000) )
		m_lDefaultPosition = newVal;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////
// Indicate the flag in order to retrieve the value of the desired parameter.			 //
// I.e. velocity, position, strain gauge, along with many others.						 //
// Look at the Barret Interface under Supervisor mode to see the different flag options. //
///////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CBarretComp::get_ParameterFlag(BSTR *pVal)
{
	// TODO: Add your implementation code here
	SysReAllocString(pVal,m_bstrParameterFlag);
	
	return S_OK;
}

STDMETHODIMP CBarretComp::put_ParameterFlag(BSTR newVal)
{
	// TODO: Add your implementation code here
	m_bstrParameterFlag = SysAllocString(newVal);

	return S_OK;
}

STDMETHODIMP CBarretComp::get_ParameterValue(long *pVal)
{
	// TODO: Add your implementation code here
	*pVal = m_lParameterValue;
	return S_OK;
}

STDMETHODIMP CBarretComp::put_ParameterValue(long newVal)
{
	// TODO: Add your implementation code here
	m_lParameterValue = newVal;
	return S_OK;
}

/////////////////////////////
/**** Interface Methods ****/
/////////////////////////////
STDMETHODIMP CBarretComp::Initialize()
{

	// Automatically generated code by Barrett GUI
	if( result=bh.InitSoftware(/*1,THREAD_PRIORITY_TIME_CRITICAL*/) )
		Error();
	
	// Set Default position for fingers and spread
	if( result=bh.Set( "123",	"DP", DEFAULT_FINGER_POSITION ) )					// Def. pos. for fingers
		Error();				
	if( result=bh.Set( "S",		"DP", DEFAULT_SPREAD_POSITION ) )					// Def. pos. for spread
		Error();

	// Set Default velocity for fingers and spread (half of it's regular value)
	if( result=bh.Set( "123",	"MOV", DEFAULT_FINGER_VELOCITY ) )					// Def. vel. for opening fingers
		Error();				
	if( result=bh.Set( "S",		"MOV", DEFAULT_SPREAD_VELOCITY ) )					// Def.	vel. for opening spread
		Error();
	if( result=bh.Set( "123",	"MCV", DEFAULT_FINGER_VELOCITY ) )					// Def. vel. for closing fingers
		Error();				
	if( result=bh.Set( "S",		"MCV", DEFAULT_SPREAD_VELOCITY ) )					// Def.	vel. for closing spread
		Error();

	// Automatically generated code by Barrett GUI
	if( result=bh.InitHand() )
		Error();


	return S_OK;
}

STDMETHODIMP CBarretComp::Close()
{
	// TODO: Add your implementation code here
	USES_CONVERSION;								// Macro to enable use of OLE2T which converts a BSTR											// to a char* string
	char* motorflag = OLE2T(m_bstrHandParameter);
	
	if( result=bh.Close( motorflag) )
		Error();

	return S_OK;
}

STDMETHODIMP CBarretComp::Open()
{
	// TODO: Add your implementation code here
	USES_CONVERSION;								// Macro to enable use of OLE2T which converts a BSTR											// to a char* string
	char* motorflag = OLE2T(m_bstrHandParameter);

	if( result=bh.Open( motorflag ) )
		Error();

	return S_OK;
}

STDMETHODIMP CBarretComp::GoHome()
{
	// TODO: Add your implementation code here
	if( result=bh.GoToHome() )
		Error();

	return S_OK;
}

STDMETHODIMP CBarretComp::GoToDefaultPosition()
{
	// TODO: Add your implementation code here
	USES_CONVERSION;							// Macro to enable use of OLE2T which converts a BSTR											// to a char* string
	char* motorflag = OLE2T(m_bstrHandParameter);

	if( result=bh.Default( motorflag ) )
		Error();

	return S_OK;
}

STDMETHODIMP CBarretComp::GoToPosition()
{
	// TODO: Add your implementation code here
	USES_CONVERSION;							// Macro to enable use of OLE2T which converts a BSTR											// to a char* string
	char* motorflag = OLE2T(m_bstrHandParameter);

	if( result=bh.GoToPosition( motorflag , m_lPosition) )
		Error();

	return S_OK;
}

STDMETHODIMP CBarretComp::StepOpen()
{
	// TODO: Add your implementation code here
	USES_CONVERSION;							// Macro to enable use of OLE2T which converts a BSTR											// to a char* string
	char* motorflag = OLE2T(m_bstrHandParameter);

	if( result=bh.StepOpen( motorflag , m_lStepSize) )
		Error();

	return S_OK;
}

STDMETHODIMP CBarretComp::StepClose()
{
	// TODO: Add your implementation code here
	USES_CONVERSION;							// Macro to enable use of OLE2T which converts a BSTR											// to a char* string
	char* motorflag = OLE2T(m_bstrHandParameter);

	if( result=bh.StepClose( motorflag, m_lStepSize) )
		Error();
	
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generic function that allows the user from the interface to set a Parameter Flag and a Paramter value. //
// This is useful to set and retrieve more uncommon paramters.											  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CBarretComp::Get()
{
	// TODO: Add your implementation code here
	USES_CONVERSION;
	char *motorflag = OLE2T(m_bstrHandParameter);
	char *parameter = OLE2T(m_bstrParameterFlag);

	if( result=bh.Get( motorflag, parameter, m_lParameterValue ) )				// Def. position for an individual motor
		Error();

	return S_OK;
}

STDMETHODIMP CBarretComp::Set()
{
	// TODO: Add your implementation code here
	// TODO: Add your implementation code here
	USES_CONVERSION;
	char *motorflag = OLE2T(m_bstrHandParameter);
	char *parameter = OLE2T(m_bstrParameterFlag);

	if( result=bh.Set( motorflag, parameter, m_lParameterValue ) )				// Def. position for an individual motor
		Error();

	return S_OK;
}

STDMETHODIMP CBarretComp::_ThreeFingerGrasp()
{
	// TODO: Add your implementation code here

	// Make sure you open the hand
	if (result = bh.Open("123S") )
		Error();
	// Spread the hand to position 1000
	if ( result = bh.GoToPosition("S",750) )
		Error();
	// Close finger 3 first
	if (result = bh.GoToPosition("3",10250) )
		Error();
	// Close fingers 1,2 half-way
	if ( result = bh.GoToPosition("12",11000) )
		Error();

	return S_OK;
}

STDMETHODIMP CBarretComp::_ClosedHandGrasp()
{
	// TODO: Add your implementation code here
	
	// First open the fingers all the way
	if (result = bh.Open("123") )
		Error();
	// Rotate the fingers around
	if ( result = bh.Close("S") )
		Error();
	// Close the fingers
	if ( result = bh.Close("123") )
		Error();
	return S_OK;
}

STDMETHODIMP CBarretComp::_IndexFingerPointing()
{
	// TODO: Add your implementation code here
	
	// Make sure it is home.
	if ( result = bh.GoToHome() )
		Error();

	// Close fingers #2 and #3
	if ( result = bh.Close("23") )
		Error();
	return S_OK;
}

/////////////////////////////////////////////////////////
// MessageBox discplayed due to an error ina function  //
/////////////////////////////////////////////////////////
void CBarretComp::Error(void)
{
//	printf( "ERROR: %d\n%s\n", result, bh.ErrorMessage(result) );
	//exit(0);
	MessageBox(NULL,"ERROR: %result\n","CBarretComp::Error()",MB_OK);
	ATLTRACE("\nCBarretComp::Error()\n");
}


STDMETHODIMP CBarretComp::StopMotors()
{
	// TODO: Add your implementation code here
	if ( result = bh.StopMotor("123S") )
		Error();

	return S_OK;
}
