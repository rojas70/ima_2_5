// IntelIPL.h : Declaration of the CIntelIPL

#ifndef __INTELIPL_H_
#define __INTELIPL_H_

#include "assert.h"
#include "resource.h"							// main symbols
#include "I:\include\ipl.h"						// Intel IP library header

#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"			// property bag dll
//#include "O:\Components\Representations\IMA2_ImageRepLib\IMA2_ImageRepLib.h"
//*** This project has two additional libraries included in the link Tab of the Project Settings under the Project Menu ***/


// CONSTANTS
const int N				= 2;
const int MAX_KERNELS	= 8;

/////////////////////////////////////////////////////////////////////////////
// CIntelIPL
class ATL_NO_VTABLE CIntelIPL : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIntelIPL, &CLSID_IntelIPL>,
	public IDispatchImpl<IIntelIPL, &IID_IIntelIPL, &LIBID_IMA2_IMAGEPROCESSINGLIBLib>,
	public CComponentImpl 
{
public:
	CIntelIPL();
	~CIntelIPL();

DECLARE_REGISTRY_RESOURCEID(IDR_INTELIPL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIntelIPL)
	COM_INTERFACE_ENTRY(IIntelIPL)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IIntelIPL
public:
	// Main Interface callable functions
	STDMETHOD(aaNot)(ULONG ulFlags);
	STDMETHOD(aaCopy)(ULONG ulFlags);
	STDMETHOD(aaDecimate)(ULONG ulFlags);
	STDMETHOD(aaConvolve2D)(ULONG ulFlags);
	STDMETHOD(aaColortoGray)(ULONG ulFlags);
	STDMETHOD(aaErode)(ULONG ulFlags);
	STDMETHOD(aaDilate)(ULONG ulFlags);
	STDMETHOD(aaOpen)(ULONG ulFlags);
	STDMETHOD(aaClose)(ULONG ulFlags);
	STDMETHOD(aaSubtract)(ULONG ulFlags);
	STDMETHOD(aaBlur)(ULONG ulFlags);
	STDMETHOD(aaMedianFilter)(ULONG ulFlags);
	STDMETHOD(aaMinFilter)(ULONG ulFlags);
	STDMETHOD(aaMaxFilter)(ULONG ulFlags);
	STDMETHOD(aaThreshold)(ULONG ulFlags);
	STDMETHOD(aaInitialize)(ULONG ulFlags);

	// Interface properties
	STDMETHOD(RGBToHSV)(long InputRGB, long OutputHSV);
	STDMETHOD(MultiplyImageScale)(long InputA, long InputB, long Output);
	STDMETHOD(MultiplyImage)(long InputA, long InputB, long Output);
	STDMETHOD(MultiplyScale)(long Input, long Output, long value);
	STDMETHOD(Multiply)(long Input, long Output, long value);
	STDMETHOD(Square)(long Input, long Output);
	STDMETHOD(XOR)(long InputA, long InputB, long Output);
	STDMETHOD(OR)(long InputA, long InputB, long Output);
	STDMETHOD(AND)(long InputA, long InputB, long Output);
	STDMETHOD(Threshold)(long Input, long Output, long threshold);
	STDMETHOD(get_ThresholdValue)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ThresholdValue)(/*[in]*/ long newVal);
	STDMETHOD(MaxFilter)(long Input, long Output, long nRows, long nCols, long anchorX, long anchorY);
	STDMETHOD(MinFilter)(long Input, long Output, long nRows, long nCols, long anchorX, long anchorY);
	STDMETHOD(MedianFilter)(long Input, long Output, long nRows, long nCols, long anchorX, long anchorY);
	STDMETHOD(Blur)(long Input, long Output, long nRows, long nCols, long anchorX, long anchorY);
	STDMETHOD(get_AnchorY)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_AnchorY)(/*[in]*/ long newVal);
	STDMETHOD(get_AnchorX)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_AnchorX)(/*[in]*/ long newVal);
	STDMETHOD(get_NumberRows)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumberRows)(/*[in]*/ long newVal);
	STDMETHOD(get_NumberColumns)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumberColumns)(/*[in]*/ long newVal);
	STDMETHOD(Convolve2D)(long Input, long Output, long nKernels, long combineMethod);
	STDMETHOD(CreateConvolutionKernel)(long* Values, long Rows, long Columns, long AnchorX, long AnchorY, long nShiftR, long Number);
	STDMETHOD(Subtract)(long InputA, long InputB, long Output, long FlipAxis);
	STDMETHOD(Close)(long Input, long Output, long Iteration);
	STDMETHOD(Open)(long Input, long Output, long Iteration);
	STDMETHOD(Dilate)(long Input, long Output, long Iteration);
	STDMETHOD(Erode)(long Input, long Output, long Iteration);
	STDMETHOD(ColorToGray)(long Input, long Output);
	STDMETHOD(Not)(long Input, long Output);
	STDMETHOD(Mirror)(long Input, long Output, long FlipAxis);
	STDMETHOD(Initial)(int InputWidth, int InputHeight, int InputDepth);
	STDMETHOD(get_ConvKernel)( /*[out, retval]*/ long *pVal);
	STDMETHOD(put_ConvKernel)( /*[in]*/ long newVal);
	STDMETHOD(get_FlipAxis)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_FlipAxis)(/*[in]*/ long newVal);
	STDMETHOD(get_InputIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_InputIndex)(/*[in]*/ long newVal);


/*
	HRESULT Threshold(long uFlags);
	HRESULT MinFilter(long uFlags);
	HRESULT MaxFilter(long uFlags);
	HRESULT MedianFilter(long uFlags);	
	HRESULT Blur(long uFlags);
	HRESULT Subtract(long uFlags);
	HRESULT Open(long uFlags);
	HRESULT Dilate(long uFlags);
	HRESULT Close(long uFlags);
	HRESULT Erode(long uFlags);
	HRESULT ColorToGray(long Flags);
	HRESULT Convolve2D(long lFlags);
	HRESULT Not(long lFlags);
	HRESULT Initialize(long lFlags);
	HRESULT Copy(long lFlags);
	HRESULT Mirror(long lFlags);
	HRESULT Decimate(long lFlags);
*/

// Attributes
protected:

	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT
	// Component links
	IComponent*	m_pIUnkImgInput[N];
	IComponent*	m_pIUnkImgOutput;

	// IPL image vars.
	IplImage*		m_pImgInput[N];		
	IplImage*		m_pImgOutput;	
	IplImage*		m_pImgOutputGray;	
	IplImage*		m_pImgOutputColor;	
	IplConvKernel*	m_pConvKernel[MAX_KERNELS];

	long		m_lConvKernel;
	BOOL		m_bInitialized;

	// Changed the following variables to long to be able to save them as variants.
	long		m_lFlipAxis;
	long		m_lCols;
	long		m_lRows;
	long		m_lAnchorX;
	long		m_lAnchorY;
	long		m_lThreshold;

	// Index for IMA 2.5
	long m_lInputIndex;
};

#endif //__INTELIPL_H_
