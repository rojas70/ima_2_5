// ColorSegmenter.h : Declaration of the CColorSegmenter

#ifndef __COLORSEGMENTER_H_
#define __COLORSEGMENTER_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh" // property bag dll

/************* Component Link *****************/
#include "O:\Include\IMA2_BasicComponentsLib.h"
/**********************************************/

/********** Joe's Color component **********/
#include "O:\Include\IMA2_ImageRepLib.h"
/*******************************************/

/********** JJ's Image Processing component ****/
#include "O:\Include\IMA2_ImageProcessingLib.h"
/*********************************************/

/*********************************************/
// Structure to hold ellipse data for RG Model:
	typedef struct RGNORMELLIPSEtag {
		float fCorr;						// correllation coefficient
		float fVarR;						// variance of r
		float fVarG;						// variance of g
		float fNumPts;						// number of points in this ellipsoid
		float fStdDevR;						// std. dev. r
		float fStdDevG;						// std. dev. g
		float fMR;							// E(U) - r
		float fMG;							// E(V) - g
		float fRGpW2;						// For slice precalculations
	} RGNORMELLIPSE;

// Structure to hold ellipse data for L*u*v* Model:
typedef struct LUVSLICEtag {
	float fCorr;						// correllation coefficient
	float fVarU;						// variance of U
	float fVarV;						// variance of  dL
	float fNumPts;						// number of points in this ellipsoid
	float fStdDevU;						// std. dev. U
	float fStdDevV;						// std. dev. V
	float fMU;							// E(U) - U
	float fMV;							// E(V) - V
	float fLUVW1,fLUVpW2;				// For slice precalculations
} LUVSLICE;

/********************* Event constant for state machine ********************/
#define			BLOB_EXIST		0
#define			BLOB_FAIL		1
#define			TELL_ME_BLOB    2
/*********************************************/

/////////////////////////////////////////////////////////////////////////////
// CColorSegmenter
class ATL_NO_VTABLE CColorSegmenter : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CColorSegmenter, &CLSID_ColorSegmenter>,
	public IDispatchImpl<IColorSegmenter, &IID_IColorSegmenter, &LIBID_IMA2_COLORSEGMENTERLIBLib>,
	public CComponentImpl 
{
public:
	CColorSegmenter()
	{
		for(int i=0;i<2;i++) 
		{
			m_dCentroidVector[i] = 0.0f;
			m_dPreviousCentroidVector[i] = 0.0f;
			m_dAveragedCentroidVector[i] = 0.0f;
		}
		m_dAlpha = 0.5;
		m_sIterations = 1;

		// Segmentation Data
		m_fLambda				= 1.2f;	// Number of standard deviations for color model. This value works best with Barney.
		m_lBlobArea				= 0;
		
		SkipX					= 1;
		SkipY					= 1;
		m_iObjectCenterX		= 0;	// The pixel position for the center of the object in x-coordinates
		m_iObjectCenterY		= 0;	// The pixel position for the center of the object in y-coordinates
		
		// Image Properties
		WindowLeft				= 0;
		WindowTop				= 0;

		ImageHeight				= 240;
		ImageWidth				= 320;

		WindowHeight			= 240;
		WindowWidth				= 320;

		// Variables to find the center of the object of interest
		x_Mean					= 0.0f;
		y_Mean					= 0.0f;
		x_StandardDev			= 0.0f;
		y_StandardDev			= 0.0f;
		m_dNoSegmentedPixels	= 0.0;		
		BlobArea				= 0;		// Describes the number of pixels that have been segmented.
		filt_StdDevGain				= 1;

		// LUV model
		m_fUn		= (float) 0.0;
		m_fVn		= (float) 0.0;			// Precalculations
		m_fDenom	= (float) 0.0;			// precalculated denominator
		m_fXn		= (float) (0.412453 + 0.357580 + 0.180423);  	// 0.950456 
		m_fYn		= (float) (0.212671 + 0.715160 + 0.072169);  	// 1.000000 
		m_fZn		= (float) (0.019334 + 0.119193 + 0.950227);  	// 1.088754 
		m_nULimit	= 255;
		m_nLLimit	= 0.0;

		// Color Model
		m_sColorModelType		= "rgn";
		m_iColorModelType		= 0;
		m_sColorModelFileName	= SysAllocString(L"");

		// Flags
		m_bColorModelReady		= FALSE;
		m_bInitialFlag			= FALSE;
		m_bCentroidFlag			= FALSE;
		m_bDrawCrossMarker		= TRUE;   // default drawing box at the target
		m_sFilterOutput			= 1;

		// IComponent pointers
		m_pIUnkImgIn			= NULL;		// for input image
		m_pIUnkImgOut			= NULL;		// for output image
		m_pIUnkVectorOut		= NULL;		// for vector holding center of the object being tracked
		m_pIUnkVectorIn			= NULL;		// for vector containing information of window to segment
		m_pIUnkIPL				= NULL;		// for Image Processing 
		m_pIUnkNumSegmentedPixels=NULL;		// for number of segmented pixels
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COLORSEGMENTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CColorSegmenter)
	COM_INTERFACE_ENTRY(IColorSegmenter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IColorSegmenter
public:
	STDMETHOD(get_stat_StdDev_Y_Blob)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_stat_StdDev_Y_Blob)(/*[in]*/ double newVal);
	STDMETHOD(get_stat_Average_Y_BlobPosition)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_stat_Average_Y_BlobPosition)(/*[in]*/ double newVal);
	STDMETHOD(get_stat_StdDev_X_Blob)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_stat_StdDev_X_Blob)(/*[in]*/ double newVal);
	STDMETHOD(get_stat_Average_X_BlobPosition)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_stat_Average_X_BlobPosition)(/*[in]*/ double newVal);
	STDMETHOD(get_filter_NumIterations)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_filter_NumIterations)(/*[in]*/ short newVal);
	STDMETHOD(get_filter_StdDevGain)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_filter_StdDevGain)(/*[in]*/ double newVal);

	STDMETHOD(get_CIEWhitePointX)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_CIEWhitePointX)(/*[in]*/ float newVal);
	STDMETHOD(get_CIEWhitePointY)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_CIEWhitePointY)(/*[in]*/ float newVal);
	STDMETHOD(get_CIEWhitePointZ)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_CIEWhitePointZ)(/*[in]*/ float newVal);

	STDMETHOD(get_ColorModelFileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ColorModelFileName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ColorModelName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ColorModelType)(/*[out, retval]*/ BSTR *pVal);

	STDMETHOD(get_display_CrossMarker)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_display_CrossMarker)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_display_FilterOutputImage)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_display_FilterOutputImage)(/*[in]*/ short newVal);

	STDMETHOD(get_LuminenceLowerLimit)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_LuminenceLowerLimit)(/*[in]*/ float newVal);
	STDMETHOD(get_LuminenceUpperLimit)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_LuminenceUpperLimit)(/*[in]*/ float newVal);	

	STDMETHOD(get_seg_NumOfStdDevs)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_seg_NumOfStdDevs)(/*[in]*/ float newVal);
	STDMETHOD(get_seg_SkipPixels)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_seg_SkipPixels)(/*[in]*/ short newVal);
	STDMETHOD(get_seg_NumSegmentedPixels)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_seg_NumSegmentedPixels)(/*[in]*/ double newVal);

	STDMETHOD(get_WindowHeight)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_WindowHeight)(/*[in]*/ short newVal);
	STDMETHOD(get_WindowLeft)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_WindowLeft)(/*[in]*/ short newVal);
	STDMETHOD(get_WindowTop)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_WindowTop)(/*[in]*/ short newVal);
	STDMETHOD(get_WindowWidth)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_WindowWidth)(/*[in]*/ short newVal);

	// Callable Methods
	STDMETHOD(DoSegment)();
	STDMETHOD(Initialize)();
	STDMETHOD(LoadColorModel)();

private:
	// Internal Functions
	HRESULT	DoCenteringObject(int* x,int* y,BYTE* pbDataIn);	
	HRESULT DrawBorder(int x,int y,int width,int height,int depth,BYTE* image);	
	HRESULT LUVSegment(BYTE* pbDataIn,BYTE* pbDataOut);
	HRESULT RGNormSegment(BYTE* pbDataIn,BYTE* pbDataOut);
	HRESULT UpdateWindow();
	
	// Private functions
	void FilterOutput(long lIn, long lOut);
	void AdjustParameters();
	long SetCentroid(double* OutputVector);
	long GetInputVector(double* InputVector,long length);


	// Member variables
	// Images
	BYTE*				InputImage;			// Type: unsigned CHAR
	BYTE*				OutputImage;
	BITMAPINFOHEADER	m_pHeaderOut;
	BITMAPINFOHEADER	m_pHeaderIn;

	short ImageWidth;
	short ImageHeight;
	short WindowWidth;
	short WindowHeight;
	short WindowTop;
	short WindowLeft;	

	// Filtering
	double m_dAlpha;						// Parameter used to average actual and previous values of the centroid vector.
	double filt_StdDevGain;						// Gain that indicates number of standard deviations used to zero out noise in an image
	short  m_sFilterOutput;					// Flag to indicate whether or not to filter the image output.

	// Segmentation parameters
	short  SkipY;
	short  SkipX;
	long   BlobArea;						// Num of segmented pixels
	long   m_lBlobArea;						// Used as a threshold representing min number of pixels to activate returning the centroid vector value
	double m_dNoSegmentedPixels;			// Num of segmented pixels (redundant)

	RGNORMELLIPSE	m_RGNormEllipse;
	LUVSLICE		m_LUVSlice;
	// Colors
	int				m_iColorModelType;
	CComBSTR		m_csColorModelName;
	CComBSTR		m_sColorModelType;	
	BSTR			m_sColorModelFileName;
	//long m_lChannel;

	// Centroid Parameters
	int		m_iImageCenterY;					// The Y-coordinate of the exact center of the image
	int		m_iImageCenterX;					// The X-coordinate
	int		m_iObjectCenterY;					// The Y-coordinate of the centroid of the segmented blob
	int		m_iObjectCenterX;					// The X-coordinate of the centroid of the segmented blob

	double	m_dCentroidVector[2];				
	double	m_dPreviousCentroidVector[2];
	double	m_dAveragedCentroidVector[2];
	double	InputVector[9];
	double	OutputVector[9];

	// Statistical parameters to determine color characteristics
	float m_fLambda;						// Number of Std Dev's to include
	short m_sIterations;					// Number of iterations for morphological operators
	
	// These are used by LUV model ONLY!
	float m_nLLimit, m_nULimit;				// Luminence limits
	float m_fUn, m_fVn;						// Precalculations
	float m_fXn, m_fYn, m_fZn;				// White point in CIE XYZ
	float m_fDenom;							// precalculated denominator

	double x_StandardDev;
	double y_StandardDev;
	double y_Mean;
	double x_Mean;

	// Flags
	BOOL				m_bDrawCrossMarker;			// Draw a marker on segmented blob
	BOOL				m_bColorModelReady;			// Indicate whether the color model has been loaded
	BOOL				m_bInitialFlag;				// Indicate whether or not the initialization routine has been called
	BOOL				m_bCentroidFlag;			// Indicates whether this is the first run

	// IMA Component Links		
	IComponent*			m_pIUnkImgIn;				// Supports at one input images
	IComponent*			m_pIUnkImgOut;				// 1 output image
	IComponent*			m_pIUnkVectorIn;			// Input vector containing 
	IComponent*			m_pIUnkVectorOut;			// Output vector containing center and weight
	IComponent*			m_pIUnkIPL;					// Image Processing 
	IComponent*			m_pIUnkNumSegmentedPixels;	// holds num of segmented pixels by color segmentation

	// IMA 2.5 Specific
	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT
};

#endif //__COLORSEGMENTER_H_
