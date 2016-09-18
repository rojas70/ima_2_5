// MovementDetect.h : Declaration of the CMovementDetect

#ifndef __MOVEMENTDETECT_H_
#define __MOVEMENTDETECT_H_

#include "resource.h"				// main symbols
#include "I:\Include\BasicIMA.h"	// IMA Stuff
#include "I:\Include\coreobj.h"		// IMA Stuff
#include "I:\Include\Component.h"	// IMA Stuff

#include "I:\Include\BasicComponents.h"			// Basic components
#include "I:\Include\ImageRepresentations.h"	// Image Reps

#include "I:\Include\cv.h"
/////////////////////////////////////////////////////////////////////////////
// CMovementDetect
class ATL_NO_VTABLE CMovementDetect : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMovementDetect, &CLSID_MovementDetect>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMovementDetect>,
	public IDispatchImpl<IMovementDetect, &IID_IMovementDetect, &LIBID_MOVEMENTDETECTORLib>,
	public CMechanismImpl<CMovementDetect>
{
public:
	CMovementDetect()
	{

	// TODO: Initialize all variables
	m_FirstFrameReady = false;
	m_pbPreviousFrame = NULL;
	m_bDifferenceThresh = 17;
	m_bPixelMotionThresh = 3;
	m_dHSlambda = 0.5;

	// Initialize phase correlation variables
	m_FCFirstFrameReady = false;
	m_pfFFTPrevious = NULL;
	m_pIUnkImgInput = NULL;
	m_pIUnkImgOutput = NULL;
	m_pIUnkVSpos = NULL;

	// string that holds pixel threshold information
//	m_bPixelThreshold = 100;

	// TODO: Call SetupMechanism(ops, flags)

	// TODO: Setup component links
	SetupComponentLink(&IID_IUnknown, &m_pIUnkImgInput);
	SetupComponentLink(&IID_IUnknown, &m_pIUnkImgOutput);	
	SetupComponentLink(&IID_IUnknown, &m_pIUnkVSpos);

	}

	// Destructor
	~CMovementDetect()
	{
		if ( m_pbPreviousFrame ) delete m_pbPreviousFrame;

		// for phase correlation
		if ( m_pfFFTPrevious ) delete m_pfFFTPrevious;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_MOVEMENTDETECT)

BEGIN_COM_MAP(CMovementDetect)
	COM_INTERFACE_ENTRY(IMovementDetect)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	// IMA Interface entries
	COM_INTERFACE_ENTRY(IComponent)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY(IMechanismActivate)
END_COM_MAP()
// support for outgoing interfaces, if necessary

BEGIN_CONNECTION_POINT_MAP(CMovementDetect)
END_CONNECTION_POINT_MAP()


	HRESULT FinalConstruct()
	{
		// if your component aggregates other COM objects,
		//  create them here.
	

		return S_OK;
	}

	void FinalRelease()
	{
		// if your component aggregates other COM objects,
		//  releasethem here.
	}


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

public:
// Overridable IMA Component functionality:
//

	virtual ULONG	MechanismActivate(ULONG flags, ULONG operation);
	virtual HRESULT MechanismReset(ULONG flags);

	virtual HRESULT FinalComponentInitialization(ULONG ulFlags, IUnknown *pIUnkAManager);
	virtual HRESULT SaveComponentToStream(LPSTREAM pStm);
	virtual HRESULT InitComponentFromStream(LPSTREAM pStm);
	virtual ULONG	GetMaxStreamSize();


public:
	STDMETHOD(SegByPhaseCorrelation)();
	STDMETHOD(SegByOpticalFlowLK)();
	STDMETHOD(SegByOpticalFlowHS)();
	STDMETHOD(SegByOpticalFlowBM3)();
	STDMETHOD(SegByOpticalFlowBM2)();
	STDMETHOD(SegByOpticalFlowBM)();
	STDMETHOD(SegByDifference)();
	STDMETHOD(get_VSMotionPosition)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_VSMotionPosition)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_PixelMotion)(/*[out, retval]*/ BYTE *pVal);
	STDMETHOD(put_PixelMotion)(/*[in]*/ BYTE newVal);
	STDMETHOD(get_ImageOutput)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ImageOutput)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ImageInput)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ImageInput)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_HSlambda)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_HSlambda)(/*[in]*/ double newVal);
	STDMETHOD(get_DifferenceThresh)(/*[out, retval]*/ BYTE *pVal);
	STDMETHOD(put_DifferenceThresh)(/*[in]*/ BYTE newVal);

// %%INTERFACE: IMovementDetect

private:
	void FindPeak(BYTE * pArray, const int height, const int width, BYTE &peak, int &row, int &col);
	void Normalize(float * RCPack2D, const int height, const int width);
	void Conjugate(float * RCPack2D, const int height, const int width);

	void MedianFilter(float *image, float *image1, int N, int Height, int Width);

	long m_lWidth;		// image width
	long m_lHeight;		// image height
	
	bool m_FirstFrameReady;		// flag to show if the first frame is ready
	BYTE* m_pbPreviousFrame;	// last frame

	// phase correlation variables
	bool m_FCFirstFrameReady;		// flag for phase correlation method
	float * m_pfFFTPrevious;		// data array to hold the FFT of previous frame, IPL RCPack2D format

	IUnknown*	m_pIUnkImgInput;	// input image
	IUnknown*	m_pIUnkImgOutput;	// output image
	IUnknown*	m_pIUnkVSpos;		// output position

	BYTE m_bDifferenceThresh;	// to hold the SegByDifference Threshold property value
	BYTE m_bPixelMotionThresh;	// to hold the PixelMotionThresh property value
	double m_dHSlambda;			// to hold lambda parameter for H&S method

//	BYTE m_bPixelThreshold;		// holds data to determine if enough pixels are segmented to continue

};

#endif //__MOVEMENTDETECT_H_
