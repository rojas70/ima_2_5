// VisualInputRepresentation.cpp : Implementation of CVisualInputRepresentation
#include "stdafx.h"
#include "IMA2_PTVisionLib.h"
#include "VisualInputRepresentation.h"
#include "O:\components\msvbvm60.tlh" // property bag dll
/////////////////////////////////////////////////////////////////////////////
// CVisualInputRepresentation


BOOL CVisualInputRepresentation::GetImageInfo(IComponent *m_Image, long *Width, long *Height, long *Depth)
{

  IImageRep*  pImage = NULL;

  /*** check if componentLink (ImageRep) is not NULL ***/
  if(m_Image != NULL)
	{
	   m_Image->QueryInterface(IID_IImageRep,(void **)&pImage);
	   /*** Query interface ***/
	   if( pImage != NULL)
		{
			pImage->get_Height( Width );
			pImage->get_Width( Height );
			pImage->get_Depth( Depth );
			pImage->Release();
		}
	   else
		return FALSE;  /** Query interface is NULL **/
	 }
	else
		return FALSE;  /** ComponentLink is NULL , return with nothing ***/

  return TRUE;
}
BOOL CVisualInputRepresentation::GetSignalInfo(IComponent* m_Vector, double * Value, long Length)
{
	// Local variables
	SAFEARRAY * mysa;
	IVectorSignal*	pLink = NULL;

	// Check to make sure the Interface pointer to the Centroid Vectors in the Color segmenter is not null
	if( m_Vector != NULL )
	{
		m_Vector->QueryInterface(IID_IVectorSignal,(void **)&pLink);
		if( pLink != NULL )
		{
			// Get values from centroids
			mysa=SafeArrayCreateVector(VT_R8,0,Length);		
			pLink->GetCurrentVector(mysa);
			memcpy(Value,mysa->pvData,sizeof(double)*Length);

			// Release data
			pLink->Release();
			SafeArrayDestroy(mysa);
		}

		else
	     return FALSE;  /** Query interface is NULL **/
	}	
	else
 	 return FALSE; /** ComponentLink is NULL, return with nothing ***/


	return TRUE; /** all succeed **/

}

BOOL CVisualInputRepresentation::SetSignalInfo(IComponent* m_Vector, double * Location, double Length)
{
	// Local variables
	SAFEARRAY * mysa;
	IVectorSignal*	pLink = NULL;

	// Check to make sure the Interface pointer to the Centroid Vectors in the Color segmenter is not null
	if( m_Vector != NULL )
	{
		m_Vector->QueryInterface(IID_IVectorSignal,(void **)&pLink);
		if( pLink != NULL )
		{
			// Set length value
			pLink->put_VectorLength(Length);					// set vector length
			mysa=SafeArrayCreateVector(VT_R8,0,(long)Length);
			memcpy(mysa->pvData,Location,sizeof(double)*Length);
			pLink->SetCurrentVector( mysa );				// set vector signal
			
			// Release data
			pLink->Release();
			SafeArrayDestroy(mysa);
		}

		else
	     return FALSE;  /** Query interface is NULL **/
	}	
	else
 	 return FALSE; /** ComponentLink is NULL, return with nothing ***/


	return TRUE; /** all succeed **/

}



BOOL CVisualInputRepresentation::GetImagePointer(IComponent* m_Image, long* ImagePointer)
{
  IImageRep*  pImage = NULL;
  long lp;

  /*** check if componentLink (ImageRep) is not NULL ***/
  if(m_Image != NULL)
	{
	   m_Image->QueryInterface(IID_IImageRep,(void **)&pImage);
	   /*** Query interface ***/
	   if( pImage != NULL)
		{
			// Get img buffers
			pImage->Data( 0, &lp );
			*ImagePointer = lp;
			/*** have to do this once you wanna cast this pointer back ****/
			// Image = (BYTE*) ImagePointer;	
			pImage->Release();
		}
	   else
		return FALSE;  /** Query interface is NULL **/
	 }
  else
	return FALSE;  /** ComponentLink is NULL , return with nothing ***/

  return TRUE;
}

STDMETHODIMP CVisualInputRepresentation::ObtainTargetLoc()
{
	double buff[2];
	GetTargetLocation(0,buff,9);

	return S_OK;
}

STDMETHODIMP CVisualInputRepresentation::GetTargetLocation(long CameraID, double* Location, long Length)
{
	// Choose camera, and then get centroid vector from color segmenter
	switch(CameraID)
	{
	case 0:	/**** left camera *****/
		// Get object pointers
		m_Bindings->get_Pointers(SysAllocString(L"LeftTargetLocation"),&m_pIUnkLeftTargetLocationVector);

		if(!GetSignalInfo(m_pIUnkLeftTargetLocationVector, Location, Length))
			::MessageBox(NULL,"Can't get interface with left camera target vector!","Error",MB_OK);
		break;
	case 1: /**** right camera ****/
	    // Get object pointers
		m_Bindings->get_Pointers(SysAllocString(L"RightTargetLocation"),&m_pIUnkRightTargetLocationVector);

		if(!GetSignalInfo(m_pIUnkRightTargetLocationVector, Location, Length))
			::MessageBox(NULL,"Can't get interface with right camera target vector!","Error",MB_OK);
		break;
	}
	return S_OK;
}

STDMETHODIMP CVisualInputRepresentation::SetTargetLocation(long CameraID, double * Location, double Length)
{
	
    // Bind to the component
    m_Bindings->get_Pointers(SysAllocString(L"LeftTargetLocationVector"),&m_pIUnkLeftTargetLocationVector);
	m_Bindings->get_Pointers(SysAllocString(L"RightTargetLocationVector"),&m_pIUnkRightTargetLocationVector);	
	
	// TODO: Add your implementation code here
	switch(CameraID)
	{
	case 0:	/**** left camera *****/
		if(!SetSignalInfo(m_pIUnkLeftTargetLocationVector, Location, Length))
			::MessageBox(NULL,"Can't get interface with left camera target vector!","Error",MB_OK);
		break;
	case 1: /**** right camera ****/
		if(!SetSignalInfo(m_pIUnkLeftTargetLocationVector, Location, Length))
			::MessageBox(NULL,"Can't get interface with right camera target vector!","Error",MB_OK);
		break;
	}

	return S_OK;
}

STDMETHODIMP CVisualInputRepresentation::GetEyeMovementStatus(double * Status, double Length)
{
	// TODO: Add your implementation code here
	GetSignalInfo(m_pIUnkEyeMovementStatusVector, Status, Length);
	return S_OK;
}

STDMETHODIMP CVisualInputRepresentation::SetEyeMovementStatus(double * Status, double Length)
{
	// TODO: Add your implementation code here
	SetSignalInfo(m_pIUnkEyeMovementStatusVector, Status, Length);
	return S_OK;
}

STDMETHODIMP CVisualInputRepresentation::GetImage(long ImageID, long* ImagePointer)
{

    // Bind to the component
    m_Bindings->get_Pointers(SysAllocString(L"LeftImage"),&m_pIUnkLeftImage);
	m_Bindings->get_Pointers(SysAllocString(L"RightImage"),&m_pIUnkRightImage);

	// TODO: Add your implementation code here
	switch(ImageID)
	{
	case 0: /*** left camera image ***/
		if(!GetImagePointer(m_pIUnkLeftImage, ImagePointer))
			::MessageBox(NULL,"Can't get interface with left image rep!","Error",MB_OK);
		break;
	case 1: /*** right camera image ***/
		if(!GetImagePointer(m_pIUnkRightImage, ImagePointer))
			::MessageBox(NULL,"Can't get interface with right image rep!","Error",MB_OK);
		break;
	}
	return S_OK;
}



// The OnConstruct Function sets all the bindings for the component, and 
// also replaces FinalComponentInitialization
STDMETHODIMP CVisualInputRepresentation::OnConstruct() {

// TODO: Bindings. Personalize the binding of your component. 

	IMA2_BindingInfo	m_Binding;
	int numiids=1;
	long x[1];
	x[0]=0;

	// LeftTargetLocation - sends LeftTargetLocation
	m_Binding.Name		= SysAllocString(L"LeftTargetLocation");					
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

	// RightTargetLocation - sends RightTargetLocation
	m_Binding.Name		= SysAllocString(L"RightTargetLocation");					
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

STDMETHODIMP CVisualInputRepresentation::OnDestruct() { return S_OK; }

STDMETHODIMP CVisualInputRepresentation::Load(VARIANT Data) { return S_OK; }

STDMETHODIMP CVisualInputRepresentation::Save(VARIANT *pData) {	return S_OK; }
