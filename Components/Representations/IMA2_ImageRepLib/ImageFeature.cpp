// ImageFeature.cpp : Implementation of CImageFeature
#include "stdafx.h"
#include "ImageFeature.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageFeature::CImageFeature( long lLabelValue )
:
	m_lLabelValue( lLabelValue ),
	m_lLength( -1 ),
	m_lWidth( -1 ),
	m_lHeight( -1 ),
	m_lXCentroid( -1 ),
	m_lYCentroid( -1 ),
	m_lArea( -1 ),
	m_lTopFeatureLocation( -1 ),
	m_lLeftFeatureLocation( -1 ),
	m_lOrientationAngle( -1 ),
	m_sName("Object")
{

}

CImageFeature::~CImageFeature()
{

}
