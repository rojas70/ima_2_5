// IntelSPL.cpp : Implementation of CIntelSPL
#include "stdafx.h"
#include "IMA2_ImageProcessingLib.h"
#include "IntelSPL.h"

#define nsp_UsesAll 

#include "resource.h"				// main symbols

#include "O:\Components\CameraComponents\IMA2_ImageProcessingLib\nsp.h"			// Signal processing library

/////////////////////////////////////////////////////////////////////////////
// CIntelSPL

STDMETHODIMP CIntelSPL::fCopy(float * src, float * dst, int n)
{
	// TODO: Add your implementation code here
	nspsbCopy(src, dst, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dCopy(double * src, double * dst, int n)
{
	// TODO: Add your implementation code here
	nspdbCopy(src, dst, n);	
	return S_OK;
}

STDMETHODIMP CIntelSPL::sCopy(short * src, short * dst, int n)
{
	// TODO: Add your implementation code here
	nspwbCopy(src, dst, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fSet(float val, float * dst, int n)
{
	// TODO: Add your implementation code here
	nspsbSet(val, dst, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dSet(double val, double * dst, int n)
{
	// TODO: Add your implementation code here
	nspdbSet(val, dst, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sSet(short val, short * dst, int n)
{
	// TODO: Add your implementation code here
	nspwbSet(val, dst, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fZero(float * dst, int n)
{
	// TODO: Add your implementation code here
	nspsbZero(dst, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dZero(double * dst, int n)
{
	// TODO: Add your implementation code here
	nspdbZero(dst, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sZero(short * dst, int n)
{
	// TODO: Add your implementation code here
	nspwbZero(dst, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fMax(float * vec, int n, float* outval, int * index)
{
	// TODO: Add your implementation code here
	*outval = nspsMaxExt(vec, n, index);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dMax(double * vec, int n, double* outval, int * index)
{
	// TODO: Add your implementation code here
	*outval = nspdMaxExt(vec, n, index);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sMax(short * vec, int n, short* outval, int * index)
{
	// TODO: Add your implementation code here
	*outval = nspwMaxExt(vec, n, index);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fMin(float * vec, int n, float* outval, int * index)
{
	// TODO: Add your implementation code here
	*outval = nspsMinExt(vec, n, index);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dMin(double * vec, int n, double* outval, int * index)
{
	// TODO: Add your implementation code here
	*outval = nspdMaxExt(vec, n, index);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sMin(short * vec, int n, short* outval, int * index)
{
	// TODO: Add your implementation code here
	*outval = nspwMaxExt(vec, n, index);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fMean(float * vec, int n, float* outval)
{
	// TODO: Add your implementation code here
	*outval = nspsMean(vec, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dMean(double * vec, int n, double* outval)
{
	// TODO: Add your implementation code here
	*outval = nspdMean(vec, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sMean(short * vec, int n, short* outval)
{
	// TODO: Add your implementation code here
	*outval = nspwMean(vec, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fNorm(float * srcA, float * srcB, int n, int flag, float * outval)
{
	// TODO: Add your implementation code here
	switch(flag)
	{
	case 0:
		*outval = nspsNorm(srcA, srcB, n, NSP_C);
		break;
	case 1:
		*outval = nspsNorm(srcA, srcB, n, NSP_L1);
		break;
	case 2:
		*outval = nspsNorm(srcA, srcB, n, NSP_L2);
		break;
	}
	return S_OK;
}

STDMETHODIMP CIntelSPL::dNorm(double * srcA, double * srcB, int n, int flag, double * outval)
{
	// TODO: Add your implementation code here
	switch(flag)
	{
	case 0:
		*outval = nspdNorm(srcA, srcB, n, NSP_C);
		break;
	case 1:
		*outval = nspdNorm(srcA, srcB, n, NSP_L1);
		break;
	case 2:
		*outval = nspdNorm(srcA, srcB, n, NSP_L2);
		break;
	}
	return S_OK;
}

STDMETHODIMP CIntelSPL::sNorm(short * srcA, short * srcB, int n, int flag, float * outval)
{
	// TODO: Add your implementation code here
	switch(flag)
	{
	case 0:
		*outval = nspwNorm(srcA, srcB, n, NSP_C);
		break;
	case 1:
		*outval = nspwNorm(srcA, srcB, n, NSP_L1);
		break;
	case 2:
		*outval = nspwNorm(srcA, srcB, n, NSP_L2);
		break;
	}
	return S_OK;
}

STDMETHODIMP CIntelSPL::fAutoCorr(float * src, int len, float * dst, int nLags, int flag)
{
	// TODO: Add your implementation code here
	switch(flag)
	{
	case 0:	nspsAutoCorr(src, len, dst, nLags, NSP_Normal);
		break;
	case 1: nspsAutoCorr(src, len, dst, nLags, NSP_Biased);
		break;
	case 2: nspsAutoCorr(src, len, dst, nLags, NSP_UnBiased);
		break;
	}
	return S_OK;
}

STDMETHODIMP CIntelSPL::dAutoCorr(double * src, int len, double * dst, int nLags, int flag)
{
	// TODO: Add your implementation code here
	switch(flag)
	{
	case 0:	nspdAutoCorr(src, len, dst, nLags, NSP_Normal);
		break;
	case 1: nspdAutoCorr(src, len, dst, nLags, NSP_Biased);
		break;
	case 2: nspdAutoCorr(src, len, dst, nLags, NSP_UnBiased);
		break;
	}
	return S_OK;
}

STDMETHODIMP CIntelSPL::sAutoCorr(short * src, int len, short * dst, int nLags, int flag)
{
	// TODO: Add your implementation code here
	switch(flag)
	{
	case 0:	nspwAutoCorr(src, len, dst, nLags, NSP_Normal, NSP_NO_SCALE, NULL);
		break;
	case 1: nspwAutoCorr(src, len, dst, nLags, NSP_Biased, NSP_NO_SCALE, NULL);
		break;
	case 2: nspwAutoCorr(src, len, dst, nLags, NSP_UnBiased, NSP_NO_SCALE, NULL);
		break;
	}
	return S_OK;
}

STDMETHODIMP CIntelSPL::fCrossCorr(float * srcA, int lenA, float * srcB, int lenB, float * dst, int loLag, int hiLag)
{
	// TODO: Add your implementation code here
	nspsCrossCorr(srcA, lenA, srcB, lenB, dst, loLag, hiLag);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dCrossCorr(double * srcA, int lenA, double * srcB, int lenB, double * dst, int loLag, int hiLag)
{
	// TODO: Add your implementation code here
	nspdCrossCorr(srcA, lenA, srcB, lenB, dst, loLag, hiLag);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sCrossCorr(short * srcA, int lenA, short * srcB, int lenB, short * dst, int loLag, int hiLag)
{
	// TODO: Add your implementation code here
	nspwCrossCorr(srcA, lenA, srcB, lenB, dst, loLag, hiLag, NSP_NO_SCALE, NULL);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fRealFFT(float * samps, int order)
{
	// TODO: Add your implementation code here
	nspsRealFftl(samps, order, NSP_Forw|NSP_OutRCPerm);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fRealFFTip(float * inSamps, float * outSamps, int order)
{
	// TODO: Add your implementation code here
	nspsRealFftlNip(inSamps, outSamps, order, NSP_Forw|NSP_OutRCPerm);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dRealFFT(double * samps, int order)
{
	// TODO: Add your implementation code here
	nspdRealFftl(samps, order, NSP_Forw|NSP_OutRCPerm);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dRealFFTip(double * inSamps, double * outSamps, int order)
{
	// TODO: Add your implementation code here
	nspdRealFftlNip(inSamps, outSamps, order, NSP_Forw|NSP_OutRCPerm);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sRealFFT(short * samps, int order)
{
	// TODO: Add your implementation code here
	nspwRealFftl(samps, order, NSP_Forw|NSP_OutRCPerm, NSP_NO_SCALE, NULL);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sRealFFTip(short * inSamps, short * outSamps, int order)
{
	// TODO: Add your implementation code here
	nspwRealFftlNip(inSamps, outSamps, order, NSP_Forw|NSP_OutRCPerm, NSP_NO_SCALE, NULL);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fRealInvFFT(float * samps, int order)
{
	// TODO: Add your implementation code here
	nspsCcsFftl(samps, order, NSP_Inv|NSP_OutRCPerm);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fRealInvFFTip(float * inSamps, float * outSamps, int order)
{
	// TODO: Add your implementation code here
	nspsCcsFftlNip(inSamps, outSamps, order, NSP_Inv|NSP_OutRCPerm);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dRealInvFFT(double * samps, int order)
{
	// TODO: Add your implementation code here
	nspdCcsFftl(samps, order, NSP_Inv|NSP_OutRCPerm);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dRealInvFFTip(double * inSamps, double * outSamps, int order)
{
	// TODO: Add your implementation code here
	nspdCcsFftlNip(inSamps, outSamps, order, NSP_Inv|NSP_OutRCPerm);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sRealInvFFT(short * samps, int order)
{
	// TODO: Add your implementation code here
	nspwCcsFftl(samps, order, NSP_Inv|NSP_OutRCPerm, NSP_NO_SCALE, NULL);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sRealInvFFTip(short * inSamps, short * outSamps, int order)
{
	// TODO: Add your implementation code here
	nspwCcsFftlNip(inSamps, outSamps, order, NSP_Inv|NSP_OutRCPerm, NSP_NO_SCALE, NULL);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fReal2FFT(float * xSamps, float * ySamps, int order)
{
	// TODO: Add your implementation code here
	nspsReal2Fft(xSamps, ySamps, order, NSP_Forw);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fReal2FFTip(float * xInSamps, float * xOutSamps, float * yInSamps, float * yOutSamps, int order)
{
	// TODO: Add your implementation code here
//	nspsReal2FftNip(xInSamps, xOutSamps, yInSamps, yOutSamps, order, NSP_Forw);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dReal2FFT(double * xSamps, double * ySamps, int order)
{
	// TODO: Add your implementation code here
	nspdReal2Fft(xSamps, ySamps, order, NSP_Forw);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dReal2FFTip(double * xInSamps, double * xOutSamps, double * yInSamps, double * yOutSamps, int order)
{
	// TODO: Add your implementation code here
//	nspdReal2FftNip(xInSamps, xOutSamps, yInSamps, yOutSamps, order, NSP_Forw);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sReal2FFT(short * xSamps, short * ySamps, int order)
{
	// TODO: Add your implementation code here
	nspwReal2Fft(xSamps, ySamps, order, NSP_Forw, NSP_NO_SCALE, NULL);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sReal2FFTip(short * xInSamps, short * xOutSamps, short * yInSamps, short * yOutSamps, int order)
{
	// TODO: Add your implementation code here
//	nspwReal2FftNip(xInSamps, xOutSamps, yInSamps, yOutSamps, order, NSP_Forw, NSP_NO_SCALE, NULL);
	return S_OK;
}


STDMETHODIMP CIntelSPL::fReal2InvFFT(float * xSamps, float* ySamps, int order)
{
	// TODO: Add your implementation code here
	nspsCcs2Fft(xSamps, ySamps, order, NSP_Inv);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dReal2InvFFT(double * xSamps, double * ySamps, int order)
{
	// TODO: Add your implementation code here
	nspdCcs2Fft(xSamps, ySamps, order, NSP_Inv);
	return S_OK;
}


STDMETHODIMP CIntelSPL::sReal2InvFFT(short * xSamps, short * ySamps, int order)
{
	// TODO: Add your implementation code here
	nspwCcs2Fft(xSamps, ySamps, order, NSP_Inv, NSP_NO_SCALE, NULL);
	return S_OK;
}

STDMETHODIMP CIntelSPL::dScalarMultiply(double val, double * dst, int n)
{
	// TODO: Add your implementation code here
	nspdbMpy1(val, dst, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::fScalarMultiply(float val, float * dst, int n)
{
	// TODO: Add your implementation code here
	nspsbMpy1(val, dst, n);
	return S_OK;
}

STDMETHODIMP CIntelSPL::sScalarMultiply(short val, short * dst, int n)
{
	// TODO: Add your implementation code here
	nspwbMpy1(val, dst, n, NSP_NO_SCALE, NULL);
	return S_OK;
}