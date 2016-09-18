///////////////////////////////////////////////////////////////////////////////////
// NetImgRep.cpp: Implementation of CNetImgRep									 //
//																				 //
//				  The program was created to act as a buffer/container			 //
//				  to hold image data. It serves as the basic Image				 //
//				  "Representation" in the IMA system. A FrameGrabber			 //
//				  often sends its output image to an ImageRep. Similarly,		 //
//				  the color segmenter takes in and outputs ImageRepresentations. //
//																				 //
//				  Additional code for IFeratureInfo and INetImageRep are included//
//				  as part of porting code from IMA 1.0. Not currently used in 2.5//
//																				 //
//	Author:		  Juan Rojas													 //
//	Date:		  July 2005														 //
///////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "IMA2_ImageRepLib.h"
#include "NetImgRep.h"
#include "ImageFeature.h"
#include "FeatureCollection.h"
#include "Default.h"	// Initialization values for images

/////////////////////////////////////////////////////////////////////////////
// CNetImgRep

//////////////////////////////////////////////////////////
//
// IImageRep method implementations
// 
// Allows uniform access to all types of images
//
STDMETHODIMP CNetImgRep::get_Width( /*[out, retval]*/ long *pVal)
{ 
	// get
	if( pVal == NULL ) return E_POINTER;

	*pVal = m_lWidth;

	// DEBUG
	ATLTRACE("CNetImgRep::get_Width assigned %d\n", m_lWidth);

	return S_OK;
}

STDMETHODIMP CNetImgRep::put_Width( /*[in]*/ long newVal)
{ 
	// set
	m_lWidth = newVal;

	// DEBUG
	ATLTRACE("CNetImgRep::put_Width set to %d\n", m_lWidth);
	

	return Initialize();
}

STDMETHODIMP CNetImgRep::get_Height( /*[out, retval]*/ long *pVal)
{ 
	// get
	if( pVal == NULL ) return E_POINTER;
	
	*pVal = m_lHeight;

	// DEBUG
	ATLTRACE("CNetImgRep::get_Height assigned %d\n", m_lHeight);

	return S_OK;
}

STDMETHODIMP CNetImgRep::put_Height(/*[in]*/ long newVal)
{ 
	// set
	m_lHeight = newVal;

	// DEBUG
	ATLTRACE("CNetImgRep::put_Height set to %d\n", m_lHeight);

	return Initialize();
}

STDMETHODIMP CNetImgRep::Data(long lIndex, /*[out, retval]*/ long* pVal )
{ 
	// get
	if( pVal == NULL ) return E_POINTER;
	
	*pVal = (long) m_pImage;

	return S_OK;
}

// GetAgentTime is an IMA 1 specific command
STDMETHODIMP CNetImgRep::Update(/*[in]*/ BYTE* pVal)
{

	//Note: lots of libraries call this with Update(0), which
	//means the pointer is effectively null (and nothing happens
	//in the update).
	if(pVal!=NULL)
	{
		Lock();
		memcpy(m_pImage,pVal,m_lHeight*m_lWidth*m_lDepth);
		Unlock();
	}

	return S_OK;

	//OLD CODE (IMA1):
	//Update(long lFlags)
//	double delta2 = 0.0f;
	//double now;

	// GetAgentTime is an IMA 1 specific command
	//now = GetAgentTime();		// Current time

	//delta2 = now - m_dLastProxyTime; 

	//if( delta2 >= m_dProxyDelay )
	//{
		// Notify proxies
		//SendProxyUpdates();	

		// Update last update time
		//m_dLastProxyTime = now;

		// added by Anthony, 19Jan1997
//		DispatchAgentEvent(HUDL_DLG_IN, HUDL_ID_IMAGEREP);

	//}

	// DEBUG	
	//ATLTRACE("INetImgRep: IImageRep::Update notified.\n");
	
}

STDMETHODIMP CNetImgRep::get_Depth(/*[out, retval]*/ long *pVal)
{ 
	// get
	if( pVal == NULL ) return E_POINTER;

	*pVal = m_lDepth;

	// DEBUG
	ATLTRACE("CNetImgRep::get_Depth assigned %d\n", m_lDepth);

	return S_OK;
}

STDMETHODIMP CNetImgRep::put_Depth(/*[in]*/ long newVal)
{ 
	// set
	m_lDepth = newVal;

	// DEBUG
	ATLTRACE("CNetImgRep::put_Depth set to %d\n", m_lDepth);

	return Initialize();
}

STDMETHODIMP CNetImgRep::get_Time(long m_lTimeFlag, /*[out, retval]*/ double *pVal)
{ 
	// get
	if( pVal == NULL ) return E_POINTER;
	
	*pVal = m_dTime;

	// DEBUG
	ATLTRACE("CNetImgRep::get_Time assigned %f\n", m_dTime);

	return S_OK;
}

STDMETHODIMP CNetImgRep::put_Time(long m_lTimeFlag, /*[in]*/ double newVal)
{ 
	// set
	m_dTime = newVal;

	// DEBUG
	ATLTRACE("CNetImgRep::put_Time set to %f\n", m_dTime);

	return S_OK;
}

//STDMETHODIMP CNetImgRep::get_TimeFlag(/*[out, retval]*/ long *pVal)
//{ 
	// get
//	if( pVal == NULL ) return E_POINTER;
	
//	*pVal = m_lTimeFlag;

	// DEBUG
//	ATLTRACE("CNetImgRep::get_Time assigned %f\n", m_dTime);

//	return S_OK;
//}

//STDMETHODIMP CNetImgRep::put_TimeFlag(/*[in]*/ long newVal)
//{ 
	// set
//	m_lTimeFlag = newVal;

	// DEBUG
//	ATLTRACE("CNetImgRep::put_Time set to %f\n", m_dTime);

//	return S_OK;
//}

/////////////////////////////////////////////////
//
//	INetImgRep
//
STDMETHODIMP CNetImgRep::get_Point(double * pVal)
{
	// DEBUG
	ATLTRACE("CNetImgRep::get_Point\n");

	// get
	if( pVal == NULL ) return E_POINTER;
	if( m_lPointIndex < 0 || m_lPointIndex > 1 ) return E_FAIL;

	*pVal = m_dPoint[ m_lPointIndex ];

	// DEBUG
	ATLTRACE("CNetImgRep::get_Point returned %f\n", m_dPoint[m_lPointIndex] );
	
	return S_OK;
}

STDMETHODIMP CNetImgRep::put_Point(double newVal)
{
	// set
	if( m_lPointIndex < 0 || m_lPointIndex > 1 ) return E_FAIL;

	m_dPoint[m_lPointIndex] = newVal;

	// DEBUG
	ATLTRACE("CNetImgRep::put_Point set %d to %f\n", m_lPointIndex, m_dPoint[m_lPointIndex] );

	// added by Anthony, 19Jan1997
//	DispatchAgentEvent(HUDL_DLG_IN, HUDL_ID_IMAGEREP);		// **Does not work for IMA 2.5. How is behavior affected??
															// Juan Rojas 5/05

	return S_OK;
}

STDMETHODIMP CNetImgRep::get_PointIndex(long * pVal)
{
	*pVal = m_lPointIndex;
	return S_OK;
}

STDMETHODIMP CNetImgRep::put_PointIndex(long newVal)
{
	m_lPointIndex = newVal;
	return S_OK;
}

STDMETHODIMP CNetImgRep::get_ProxyDelay(double * pVal)
{
	// get
	if( pVal == NULL ) return E_POINTER;

	*pVal = m_dProxyDelay;

	// DEBUG
	ATLTRACE("CNetImgRep::get_ProxyDelay assigned %f\n", m_dProxyDelay );

	return S_OK;
}

STDMETHODIMP CNetImgRep::put_ProxyDelay(double newVal)
{
	// set
	m_dProxyDelay = newVal;

	// DEBUG
	ATLTRACE("CNetImgRep::m_dProxyDelay set %f\n", m_dProxyDelay );

	return S_OK;
}


///////////////////////////////////////////////////////////////////
//
// IFeatureInfo
//


/*-------------------------------------------------------------------------------

	Name:			get_FeatureWidth()

	Purpose:		Get the width of a feature

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::get_FeatureWidth(long lIndex,long *pVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( pVal == NULL )
		return E_POINTER;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now set the width
		*pVal = pNewFeature->Width();
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			put_FeatureWidth()

	Purpose:		Set the width of a feature.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::put_FeatureWidth(long lIndex, long newVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the height
		pNewFeature->Width( newVal );
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			get_FeatureHeight()

	Purpose:		get the height of a feature.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::get_FeatureHeight(long lIndex,long *pVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( pVal == NULL )
		return E_POINTER;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now set the height
		*pVal = pNewFeature->Height();
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			put_FeatureHeight()

	Purpose:		Get the height of a feature

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::put_FeatureHeight(long lIndex,long newVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the height
		pNewFeature->Height( newVal );
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}

STDMETHODIMP CNetImgRep::get_FeatureLength(long lIndex,long * pVal)
{
// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( pVal == NULL )
		return E_POINTER;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now set the height
		*pVal = pNewFeature->Length();
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}

STDMETHODIMP CNetImgRep::put_FeatureLength(long lIndex, long newVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the height
		pNewFeature->Length( newVal );
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			get_FeatureCentroid()

	Purpose:		Get the centroid of a feature.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::get_FeatureCentroid( long lIndex,/* [out, retval]*/ long* pX,/* [out, retval]*/ long* pY )
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( ( pX == NULL ) || ( pY == NULL ) )
		return E_POINTER;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the centroid
		*pX = pNewFeature->XCentroid();
		*pY = pNewFeature->YCentroid();
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			put_FeatureCentroid

	Purpose:		Set the centroid of a feature.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::put_FeatureCentroid( long lIndex, /*[in]*/ long newX, /*[in]*/ long newY)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now set the centroid
		pNewFeature->XCentroid( newX );
		pNewFeature->YCentroid( newY );
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			get_FeatureArea()

	Purpose:		Get # pixels associated with a feature.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::get_FeatureArea(long lIndex,/* [out, retval]*/ long *pVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( pVal == NULL )
		return E_POINTER;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the area.
		*pVal = pNewFeature->Area();
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			put_FeatureArea()

	Purpose:		Set the # pixels (area) of a feature.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::put_FeatureArea(long lIndex, /*[in]*/ long newVal)
{
	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now set the area.
		pNewFeature->Area( newVal );
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			get_FeatureLabel()

	Purpose:		Get the label value associated with an index.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::get_FeatureLabel(long lIndex, /*[out, retval]*/ long *pVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( pVal == NULL )
		return E_POINTER;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the label.
		*pVal = pNewFeature->Label();
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			put_FeatureLabel()

	Purpose:		Set the label value of a component.

	Note:			This ISN'T ADVISED *unless* you have already changed all of the affected labels IN THE IMAGE ITSELF also.
					But if you want to do this, I won't stop you.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::put_FeatureLabel(long lIndex, /*[in]*/ long newVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now change the label.
		pNewFeature->Label( newVal );
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			get_FeatureLocation()

	Purpose:		Get the location of the feature given by the index.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::get_FeatureLocation( long lIndex, /*[out, retval]*/ long* pLeft, /*[out, retval]*/ long* pTop )
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( ( pLeft == NULL ) || ( pTop == NULL ) )
		return E_POINTER;

	//  is the feature label is already present in the list of completed features.

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the feature location.
		*pLeft = pNewFeature->LeftFeatureLocation();
		*pTop = pNewFeature->TopFeatureLocation();
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			put_FeatureLocation()

	Purpose:		Set the Location of a Feature.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::put_FeatureLocation( long lIndex, /*[in]*/ long newLeft, /*[in]*/ long newTop)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	// check and see if this feature is in the list of new features.

	CImageFeature*	pNewFeature  = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now modify the feature location.
		pNewFeature->LeftFeatureLocation( newLeft );
		pNewFeature->TopFeatureLocation( newTop );
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			AddFeature()

	Purpose:		Tell the rep. that you want to begin working on a new feature.
					If the feature label you want is already done, notify the user with an E_INVALIDARG.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::AddFeature( long lFeatureLabel, long* plFeatureIndex )
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( plFeatureIndex == NULL )
		return E_POINTER;

	// check and see if this feature is already in the list of features that are completed.
	CImageFeature*	pNewFeature = m_pCurrentFeatures->GetFeature( lFeatureLabel );

	if ( pNewFeature == NULL )
	{
			pNewFeature = new CImageFeature( lFeatureLabel );

			Lock();

			*plFeatureIndex = m_pCurrentFeatures->AddFeature( pNewFeature );

			Unlock();
	}
	else
	{
		// this feature is already present in the current list. notify the client

		return E_INVALIDARG;
	}
	
	return S_OK;

}


/*-------------------------------------------------------------------------------

	Name:			Reset all of the features you have now.

	Purpose:		

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::ClearFeatures()
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;
	
	Lock();

	m_pCurrentFeatures->ClearFeatures();

	Unlock();

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			Given a label, return the index to a feature.

	Purpose:		

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::get_FeatureIndex(long lFeatureLabel, long * pVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( pVal != NULL )
	{
		// get the index of the feature you're asking about.

		*pVal = m_pCurrentFeatures->FeatureIndex( lFeatureLabel );
	}
	else
		return E_POINTER;

	return S_OK;
}


STDMETHODIMP CNetImgRep::put_FeatureIndex(long lFeatureLabel, long newVal)
{

	return E_NOTIMPL;
}


/*-------------------------------------------------------------------------------

	Name:			NumFeatures

	Purpose:		How many features have been described in this image?

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::NumFeatures(long * pVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( pVal != NULL )
	{
			*pVal = m_pCurrentFeatures->NumFeatures();
	}
	else
	{
		return E_POINTER;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			get_FeatureOrientation

	Purpose:		At what angle is this feature from the center axis?

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::get_FeatureOrientation(long lIndex, long * pVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( pVal != NULL )
		return E_POINTER;

	//  is the feature label is already present in the list of completed features.

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the feature location.
		*pVal = pNewFeature->OrientationAngle();
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			put_FeatureOrientation()

	Purpose:		How many features have been described in this image?

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::put_FeatureOrientation(long lIndex, long newVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	//  is the feature label is already present in the list of completed features.

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the feature location.
		pNewFeature->OrientationAngle( newVal );
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			get_FeatureName()

	Purpose:		How many features have been described in this image?

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::get_FeatureName(long lIndex, BSTR * pVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	if ( pVal != NULL )
		return E_POINTER;

	//  is the feature label is already present in the list of completed features.

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the feature location.
		*pVal = pNewFeature->Name();
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}


/*-------------------------------------------------------------------------------

	Name:			put_FeatureName()

	Purpose:		How many features have been described in this image?

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

STDMETHODIMP CNetImgRep::put_FeatureName(long lIndex, BSTR newVal)
{
	// idiot proofing
	if (  m_pCurrentFeatures == NULL )
		return E_FAIL;

	//  is the feature label is already present in the list of completed features.

	CImageFeature* pNewFeature = m_pCurrentFeatures->GetFeatureAt( lIndex );

	if ( pNewFeature != NULL )
	{
		// found the feature the client asked for. now get the feature location.
		pNewFeature->Name( newVal );
	}
	else
	{
		// could not find the feature you're looking for
		// inform the client.
		
		return E_INVALIDARG;
	}

	return S_OK;
}

//////////////////////////////////////////////////////////
//
// INetImageRep method implementations
// 
// Allows uniform access to all types of images
//
STDMETHODIMP CNetImgRep::get_ImgWidth(long * pVal)
{
	// get
	return get_Width( pVal );
}

STDMETHODIMP CNetImgRep::put_ImgWidth(long newVal)
{
	// set
	return put_Width( newVal );

}

STDMETHODIMP CNetImgRep::get_ImgHeight(long * pVal)
{
	// get
	return get_Height( pVal );
}

STDMETHODIMP CNetImgRep::put_ImgHeight(long newVal)
{
	// set
	return put_Height( newVal );
}

STDMETHODIMP CNetImgRep::get_ImgDepth(long * pVal)
{
	// get
	return get_Depth( pVal );
}

STDMETHODIMP CNetImgRep::put_ImgDepth(long newVal)
{
	// set
	return	put_Depth( newVal );

}

HRESULT CNetImgRep::UpdateRepresentationProxy(/*UpdateHeader *pUH,*/double dTime,ULONG ulData,unsigned char *DataBuffer) // IMA 1 specific identifier
{
	if( DataBuffer != NULL )
	{
		// copy data in from rep core to rep proxy
		// buffer starts with m_pfAcquireTime

		// use only relevant part of image buffer
		memcpy((unsigned char*) m_pImage,DataBuffer,m_lHeight*m_lWidth*m_lDepth );

	}

	// DEBUG
	ATLTRACE("***NetImgRep: UpdateRepresentationProxy\n");

	return S_OK;
}

HRESULT CNetImgRep::GetRepUpdateBuffer(unsigned char **ppDataBuffer,ULONG *pulLength)
{
	m_dTime = 0.0; // Changed it since IMA 2.5 does not use time... GetAgentTime();

	// send out new image
	if (ppDataBuffer != NULL)
		*ppDataBuffer = (unsigned char*) m_pImage;	// start of contiguous memory

	// only send image dimensions and relevant pixel data
	// i.e. downsampling so send only new pixels
	if (pulLength != NULL)
		*pulLength = m_lHeight*m_lWidth*m_lDepth;

	// DEBUG
	ATLTRACE("***NetImgRep: GetRepUpdateBuffer\n");

	return S_OK;
}

HRESULT CNetImgRep::OnAttachedToSource(IUnknown *pIUnkSource)
{
	// Do something here if attached to source?

	// DEBUG
	ATLTRACE("***NetImgRep: OnAttachedToSource\n" );

	return S_OK;
}	

// FinalComponentInitialization
STDMETHODIMP CNetImgRep::OnConstruct()
{


	return Initialize();
}

STDMETHODIMP CNetImgRep::OnDestruct() { return S_OK; }

STDMETHODIMP CNetImgRep::Load(VARIANT Data) {

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
		//hRes = pIPB->GetPropertyBag(&m_VBPropertyBag);
		
		// Pass Data to PropertyBag
		hRes = pIPB->SetPropertyBag(&Data);

		// Load 1st variable
		// Define strings
		ItemName = SysAllocString(L"ProxyDelay");
		Var=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_dProxyDelay = (double)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Load 2nd variable
		// Define strings
		ItemName = SysAllocString(L"Width");
		Var=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_lWidth = (long)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Load 3rd variable
		// Define strings
		ItemName = SysAllocString(L"Height");
		Var=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_lHeight = (long)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Load 4th variable
		// Define strings
		ItemName = SysAllocString(L"Depth");
		Var=new variant_t;
		// Read Data from the property bag
		pIPB->GetFromPropertyBag(&ItemName,Var);  //2nd argument is return value (look retval for help)
		m_lDepth = (long)*Var;
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Decrement the pointer reference count from our member variable. 
		VariantClear(&m_VBPropertyBag);
		
		// Release
		pIPB->Release();
		
	
	
	return Initialize();

}

HRESULT CNetImgRep::Initialize()
{
	////////////////////////////////////
	// Final Component Initialization //
	////////////////////////////////////
	if(m_pImage !=NULL)
	{
		delete m_pImage;
		m_pImage=NULL;
	}

	// DEBUG
	ATLTRACE("***NetImgRep: allocated buffer\n" );

	// Allocate image buffer here
	m_pImage = new BYTE[ m_lWidth*m_lHeight*m_lDepth ];

	if( m_pImage == NULL ) return E_FAIL;


	// Temporarily init buffer for verification
	for( int i=0; i < m_lWidth*m_lHeight*m_lDepth; i++ )
		m_pImage[i] = 0x00;	// Black

	if ( m_pCurrentFeatures == NULL )
		m_pCurrentFeatures = new CFeatureCollection;

	// DEBUG
	ATLTRACE("***NetImgRep: initialization complete\n" );

	return S_OK;

}

STDMETHODIMP CNetImgRep::Save(VARIANT *pData) {
	
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
		
		// Create string names for items to be saved

		// First variable
		ItemName = SysAllocString(L"ProxyDelay");
		// Store the data and the type of data into a variant_t type
 		Var = new variant_t(m_dProxyDelay, VT_R8);	// double
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Second variable
		ItemName = SysAllocString(L"Width");
		// Store the data and the type of data into a variant_t type
 		Var = new variant_t(m_lWidth, VT_I4);	// double
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Third variable
		ItemName = SysAllocString(L"Height");
		// Store the data and the type of data into a variant_t type
 		Var = new variant_t(m_lHeight, VT_I4);	// double
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;

		// Fourth variable
		ItemName = SysAllocString(L"Depth");
		// Store the data and the type of data into a variant_t type
 		Var = new variant_t(m_lDepth, VT_I4);	// double
		// Add an item to the property bag via the wrapper class.
		hRes = pIPB->AddToPropertyBag(&ItemName, Var);
		// Deallocate
		SysFreeString(ItemName);
		delete Var;


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


STDMETHODIMP CNetImgRep::UpdateManager(BSTR Interface,VARIANT *Data)
{
	USES_CONVERSION;
	VARIANT * arrayptr;

	Lock();
	if(strcmp(OLE2T(Interface),"IImageRep")==0)
	{

		Data->vt=VT_ARRAY|VT_VARIANT;
		Data->parray=SafeArrayCreateVector(VT_VARIANT,0,4);

		//4 elements: depth, width, height, data
		arrayptr = (VARIANT*)Data->parray->pvData;
		arrayptr[0].vt=VT_I4;
		arrayptr[0].lVal=m_lDepth;

		arrayptr[1].vt=VT_I4;
		arrayptr[1].lVal=m_lHeight;

		arrayptr[2].vt=VT_I4;
		arrayptr[2].lVal=m_lWidth;

		arrayptr[3].vt=VT_ARRAY|VT_UI1;
		arrayptr[3].parray=SafeArrayCreateVector(VT_UI1,0,m_lDepth*m_lHeight*m_lWidth);
		memcpy(arrayptr[3].parray->pvData,m_pImage,m_lDepth*m_lHeight*m_lWidth);
	}
	else if(strcmp(OLE2T(Interface),"IFeatureInfo")==0)
	{
		//haven't done this yet...	
	}
	else if(strcmp(OLE2T(Interface),"INetImgRep")==0)
	{
		//should probably do both...
	}
	Unlock();

	return S_OK;
}
