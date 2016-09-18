// FeatureCollection.cpp: implementation of the CFeatureCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageFeature.h"
#include "FeatureCollection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFeatureCollection::CFeatureCollection() {}

CFeatureCollection::~CFeatureCollection()
{
	ClearFeatures();
}


/*-------------------------------------------------------------------------------

	Name:			ClearFeatures()

	Purpose:		Reset all of the features managed by this class.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

void			
CFeatureCollection::ClearFeatures()
{
	ATLTRACE("CFeatureCollection::ClearFeatures() -- Erasing Features.\n");
	m_vImageFeatures.erase( m_vImageFeatures.begin(), m_vImageFeatures.end() );
	ATLTRACE("CFeatureCollection::ClearFeatures() -- Features Erased.\n");
}

/*-------------------------------------------------------------------------------

	Name:			GetFeature()

	Purpose:		Query for a specific feature given a certain label.

	Returns:		A feature. NULL if not found.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

CImageFeature*	
CFeatureCollection::GetFeature( long lFeatureLabel )
{
	CImageFeature*	pRetFeature = NULL;

	vector< CImageFeature* >::iterator itFeature = m_vImageFeatures.begin(); 
	while ( ( itFeature != m_vImageFeatures.end() ) && ( pRetFeature == NULL ) )
	{
		CImageFeature* pCurrentFeature = (*itFeature);

		if ( lFeatureLabel == pCurrentFeature->Label() )
		{
			// found it
			pRetFeature = pCurrentFeature;
		}

		itFeature++;
	}

	// if you didn't find it, pRetFeature is already NULL, indicating failure.

	return pRetFeature;
}


/*-------------------------------------------------------------------------------

	Name:			GetFeatureAt()

	Purpose:		Query for a specific feature given a POSITION IN THE LIST.
					Useful for iteration.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

CImageFeature*	
CFeatureCollection::GetFeatureAt( long lIndex )
{
	CImageFeature*	pRetFeature = NULL;

	if ( lIndex < m_vImageFeatures.size() )
	{
		// valid index detected. now return the proper value.

		pRetFeature = m_vImageFeatures[ lIndex ];
	}

	return pRetFeature;
}


/*-------------------------------------------------------------------------------

	Name:			AddFeature()

	Purpose:		Add a feature to the collection.  Returns its index.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

long
CFeatureCollection::AddFeature( CImageFeature*	pNewFeature )
{
	long lIndex = -1;

	if ( pNewFeature != NULL )
	{
		// if the new feature is valid

		long vector_size = m_vImageFeatures.size();

		m_vImageFeatures.push_back( pNewFeature );

		lIndex = vector_size;
	}

	// if the feature is invalid, lIndex is already -1 which indicates an error.

	return lIndex;
}


/*-------------------------------------------------------------------------------

	Name:			NumFeatures()

	Purpose:		 how many features are we managing?

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

long
CFeatureCollection::NumFeatures()
{
	return m_vImageFeatures.size();
}


/*-------------------------------------------------------------------------------

	Name:			RemoveFeature()

	Purpose:		Remove a feature to the collection

	Returns:		A pointer to the feature (if found)
					or NULL if not.

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

void
CFeatureCollection::RemoveFeature( long lFeatureLabel )
{
	CImageFeature*	pRetFeature = NULL;

	vector< CImageFeature* >::iterator itFeature = m_vImageFeatures.begin(); 

	vector< CImageFeature* >::iterator itNextFeature = itFeature;

	while ( ( itFeature != m_vImageFeatures.end() ) && ( pRetFeature == NULL ) )
	{
		if ( lFeatureLabel == pRetFeature->Label() )
		{
			// found it
			itNextFeature = itFeature++;

			m_vImageFeatures.erase( itFeature );

			itFeature = itNextFeature;
		}
		else
			itFeature++;
	}
}


/*-------------------------------------------------------------------------------

	Name:			FeatureIndex()

	Purpose:		Return the index of a feature given its label

	Created By:		RMW - watson@vuse.vanderbilt.edu
	Date Modified:	Sunday, December 07, 1997

-------------------------------------------------------------------------------*/

long
CFeatureCollection::FeatureIndex( long lFeatureLabel )
{
	vector< CImageFeature* >::iterator itFeature = m_vImageFeatures.begin(); 
	long	lFeatureIndex = -1;

	long	lCurrentIndex = 0;

	while ( ( itFeature != m_vImageFeatures.end() ) && ( lFeatureIndex == -1 ) )
	{
		CImageFeature* pCurrentFeature = (*itFeature);

		if ( lFeatureLabel == pCurrentFeature->Label() )
		{
			// found it
			lFeatureIndex = lCurrentIndex;
		}

		itFeature++;
		lCurrentIndex++;
	}

	return lFeatureIndex;
}