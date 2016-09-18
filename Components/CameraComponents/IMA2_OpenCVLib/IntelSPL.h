// IntelSPL.h : Declaration of the CIntelSPL

#ifndef __INTELSPL_H_
#define __INTELSPL_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh" // property bag dll

/////////////////////////////////////////////////////////////////////////////
// CIntelSPL
class ATL_NO_VTABLE CIntelSPL : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIntelSPL, &CLSID_IntelSPL>,
	public IDispatchImpl<IIntelSPL, &IID_IIntelSPL, &LIBID_IMA2_IMAGEPROCESSINGLIBLib>,
	public CComponentImpl 
{
public:
	CIntelSPL()	{}

DECLARE_REGISTRY_RESOURCEID(IDR_INTELSPL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CIntelSPL)
	COM_INTERFACE_ENTRY(IIntelSPL)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IIntelSPL
public:
	STDMETHOD(sScalarMultiply)(short val, short* dst, int n);
	STDMETHOD(fScalarMultiply)(float val, float* dst, int n);
	STDMETHOD(dScalarMultiply)(double val, double* dst, int n);
	STDMETHOD(sReal2InvFFT)(short* xSamps, short* ySamps, int order);
	STDMETHOD(dReal2InvFFT)(double* xSamps, double* ySamps, int order);
	STDMETHOD(fReal2InvFFT)(float* xSamps, float* ySamps, int order);
	STDMETHOD(sReal2FFTip)(short* xInSamps, short* xOutSamps, short* yInSamps, short* yOutSamps, int order);
	STDMETHOD(sReal2FFT)(short* xSamps, short* ySamps, int order);
	STDMETHOD(dReal2FFTip)(double* xInSamps, double* xOutSamps, double* yInSamps, double* yOutSamps, int order);
	STDMETHOD(dReal2FFT)(double *xSamps, double *ySamps, int order);
	STDMETHOD(fReal2FFTip)(float* xInSamps, float* xOutSamps, float* yInSamps, float* yOutSamps, int order);
	STDMETHOD(fReal2FFT)(float* xSamps, float* ySamps, int order);
	STDMETHOD(sRealInvFFTip)(short* inSamps, short* outSamps, int order);
	STDMETHOD(sRealInvFFT)(short* samps, int order);
	STDMETHOD(dRealInvFFTip)(double* inSamps, double* outSamps, int order);
	STDMETHOD(dRealInvFFT)(double* samps, int order);
	STDMETHOD(fRealInvFFTip)(float* inSamps, float* outSamps, int order);
	STDMETHOD(fRealInvFFT)(float* samps, int order);
	STDMETHOD(sRealFFTip)(short* inSamps, short* outSamps, int order);
	STDMETHOD(sRealFFT)(short* samps, int order);
	STDMETHOD(dRealFFTip)(double* inSamps, double* outSamps, int order);
	STDMETHOD(dRealFFT)(double* samps, int order);
	STDMETHOD(fRealFFTip)(float* inSamps, float* outSamps, int order);
	STDMETHOD(fRealFFT)(float* samps, int order);
	STDMETHOD(sCrossCorr)(short* srcA, int lenA, short* srcB, int lenB, short* dst, int loLag, int hiLag);
	STDMETHOD(dCrossCorr)(double* srcA, int lenA, double* srcB, int lenB, double* dst, int loLag, int hiLag);
	STDMETHOD(fCrossCorr)(float* srcA, int lenA, float* srcB, int lenB, float* dst, int loLag, int hiLag);
	STDMETHOD(sAutoCorr)(short* src, int len, short* dst, int nLags, int flag);
	STDMETHOD(dAutoCorr)(double* src, int len, double* dst, int nLags, int flag);
	STDMETHOD(fAutoCorr)(float* src, int len, float* dst, int nLags, int flag);
	STDMETHOD(sNorm)(short* srcA, short* srcB, int n, int flag, float* outval);
	STDMETHOD(dNorm)(double* srcA, double* srcB, int n, int flag, double* outval);
	STDMETHOD(fNorm)(float* srcA, float* srcB, int n, int flag, float* outval);
	STDMETHOD(sMean)(short* vec, int n, short* outval);
	STDMETHOD(dMean)(double* vec, int n, double* outval);
	STDMETHOD(fMean)(float* vec, int n, float* outval);
	STDMETHOD(sMin)(short* vec, int n, short* outval, int* index);
	STDMETHOD(dMin)(double* vec, int n, double* outval, int* index);
	STDMETHOD(fMin)(float* vec, int n, float* outval, int* index);
	STDMETHOD(sMax)(short* vec, int n, short* outval, int* index);
	STDMETHOD(dMax)(double* vec, int n, double* outval, int* index);
	STDMETHOD(fMax)(float* vec, int n, float* outval, int* index);
	STDMETHOD(sZero)(short* dst, int n);
	STDMETHOD(dZero)(double* dst, int n);
	STDMETHOD(fZero)(float* dst, int n);
	STDMETHOD(sSet)(short val, short* dst, int n);
	STDMETHOD(dSet)(double val, double* dst, int n);
	STDMETHOD(fSet)(float val, float* dst, int n);
	STDMETHOD(sCopy)(short* src, short* dst, int n);
	STDMETHOD(dCopy)(double* src, double* dst, int n);
	STDMETHOD(fCopy)(float* src, float* dst, int n);

};

#endif //__INTELSPL_H_
