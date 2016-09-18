// FeatureCollection.h: interface for the CFeatureCollection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FEATURECOLLECTION_H__F0AA7FC3_6ECC_11D1_B308_006097CA1B60__INCLUDED_)
#define AFX_FEATURECOLLECTION_H__F0AA7FC3_6ECC_11D1_B308_006097CA1B60__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CImageFeature;

#include <vector>

using namespace std;

//
//	The purpose of this class to encapsulate the functionality for managing groups of features.
//

class CFeatureCollection  
{
public:
	CFeatureCollection();
	~CFeatureCollection();

	CImageFeature*	GetFeature( long lFeatureLabel );			// query for a feature by its label	
	CImageFeature*	GetFeatureAt( long lIndex );				// query for a feature by its POSITION IN THE LIST	<useful for iteration through the list>
	void			ClearFeatures();							// reset feature collections
	void			RemoveFeature( long lFeatureLabel );		// remove a certain feature	
	long			FeatureIndex( long lFeatureLabel );			// get the index of a certain feature.
	long			AddFeature( CImageFeature*	pNewFeature );	// add a feature
	long			NumFeatures();								// how many?

private:
	// These are indexed by their feature label.
	vector< CImageFeature* >	m_vImageFeatures;			// list of features that have been fully entered into the image rep.
};

#endif // !defined(AFX_FEATURECOLLECTION_H__F0AA7FC3_6ECC_11D1_B308_006097CA1B60__INCLUDED_)
