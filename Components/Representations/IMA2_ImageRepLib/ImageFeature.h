// ImageFeature.h: interface for the CImageFeature class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEFEATURE_H__F0AA7FC2_6ECC_11D1_B308_006097CA1B60__INCLUDED_)
#define AFX_IMAGEFEATURE_H__F0AA7FC2_6ECC_11D1_B308_006097CA1B60__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//
//	This class is designed to hold information about a feature.
//

class CImageFeature  
{
public:
	CImageFeature( long lLabelValue = 1 );
	virtual ~CImageFeature();

	// accessor functions
	long	Label()	const			{ return m_lLabelValue; }
	void	Label( long newVal )	{ m_lLabelValue = newVal; }
	
	long	Width() const			{ return m_lWidth; }
	void	Width( long newVal )	{ m_lWidth = newVal; }

	long	Height() const			{ return m_lHeight; }
	void	Height( long newVal )	{ m_lHeight = newVal; }
	
	long	XCentroid() const		{ return m_lXCentroid; }
	void	XCentroid( long newVal ){ m_lXCentroid = newVal; }

	long	YCentroid() const		{ return m_lYCentroid; }
	void	YCentroid( long newVal ){ m_lYCentroid = newVal; }
	
	long	Area() const			{ return m_lArea; }
	void	Area( long newVal )		{ m_lArea = newVal; }

	long	Length() const			{ return m_lLength; }
	void	Length( long newVal )		{ m_lLength = newVal; }

	long	TopFeatureLocation() const			{ return m_lTopFeatureLocation; }
	void	TopFeatureLocation( long newVal )	{ m_lTopFeatureLocation = newVal; }

	long	LeftFeatureLocation() const			{ return m_lLeftFeatureLocation; }
	void	LeftFeatureLocation( long newVal )	{ m_lLeftFeatureLocation = newVal; }

	long	OrientationAngle() const			{ return m_lOrientationAngle; }
	void	OrientationAngle( long newVal )		{ m_lOrientationAngle = newVal; }

	CComBSTR	Name() const					{ return m_sName; }
	void		Name( CComBSTR newVal )			{ m_sName = newVal; }

private:
	// feature information
	long	m_lLabelValue;		// the pixel value that this feature is labelled

	long	m_lWidth;			// width of feature
	long	m_lHeight;			// height of feature
	long	m_lXCentroid;		// (x,y) Centroid
	long	m_lYCentroid;
	long    m_lLength;   // Length
	long	m_lArea;			// # pixels (area) of feature
	long	m_lTopFeatureLocation;	// the line of the topmost pixel of the feature
	long	m_lLeftFeatureLocation;	// the line of the leftmost pixel of the feature
	long	m_lOrientationAngle;	// orientation of feature
	CComBSTR	m_sName;				// human-readable name of feature
};

#endif //__IMAGEFEATURE_H_
