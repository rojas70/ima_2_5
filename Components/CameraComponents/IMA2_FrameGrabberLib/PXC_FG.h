// PXC_FG.h : Declaration of the CPXC_FG

#ifndef __PXC_FG_H_
#define __PXC_FG_H_

#include "resource.h"							// main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"		// property bag dll

/****************************************/
/* Header for PXC200 PCI frame grabber  */
/****************************************/
#include "I:\Etc\PXC2\iframe.h"
#include "I:\Etc\PXC2\pxc200.h"

/***************************************/
/* Head for ImageRepresentation        */
/***************************************/
#include "O:\Include\IMA2_ImageRepLib.h"

/***************************************/
/* added for frame grabber             */
/***************************************/
/* this program can use either 24 bit color or 8 bit gray frames.
  change the value of PIXEL_TYPE to PBITS_RGB24 or PBITS_Y8 */
#define PIXEL_TYPE PBITS_RGB24
#ifdef _WIN32
#define PXC_NAME	"i:\\etc\\pxc2\\pxc_95.dll"
#define FRAME_NAME  "i:\\etc\\pxc2\\frame_32.dll"
#define PXC_NT		"i:\\etc\\pxc2\\pxc_nt.dll"
#else
#define PXC_NAME	"i:\\etc\\pxc2\\pxc_31.dll"
#define FRAME_NAME  "i:\\etc\\pxc2\\frame_16.dll"
#define PXC_NT		"i:\\etc\\pxc2\\pxc_31.dll"
#endif


/////////////////////////////////////////////////////////////////////////////
// CPXC_FG
class ATL_NO_VTABLE CPXC_FG : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPXC_FG, &CLSID_PXC_FG>,
	public IDispatchImpl<IPXC_FG, &IID_IPXC_FG, &LIBID_IMA2_FRAMEGRABBERLIBLib>,
	public IImageRep,
	//public CRepresentationImpl<CPXC_FG>,	// IMA
	public CComponentImpl 
{
public:
	CPXC_FG()
	{
		// TODO: Initialize all variables
		initflags			= 0;
		fgh					= 0L;
		frh[0] = frh[1]		= 0;
		FrameCount			= 0;
		ErrorCount			= 0;
		frhIdx				= 0;
		tagQ[0]				= 0;
		tagQ[1]				= 1;
		Height				= 240;
		Width				= 320;
		Depth				= 3;
		Left				= 0;
		Top					= 0;
		XResolution			= 0;
		YResolution			= 0;
		Brightness			= 0.1f;
		Camera				= 0;	// There are two FrameGrabbers for e/ camera. Defualt is 0.
		FrameGrabberID		= 0;	// Indicate which board
		Contrast			= 1.4f;	
		FieldCount			= 0;
		Hue					= 0.0f;
		Saturation			= 0.0f;
		Chroma				= 0;
		m_lTimeFlag			= 0;	// IMA 2.5 variables to indicate flag and index.			
		//m_lPointIndex		= 0;


		hBuf				= NULL;
		m_pIUnkImgOut		= NULL;
		FrameGrabberInitial = FALSE;
	}

	// Destructor
	~CPXC_FG() 
	{
		if(IsInitialized())
		{
			delete ImageData;
			CloseDevice();
		}
	}


DECLARE_REGISTRY_RESOURCEID(IDR_PXC_FG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPXC_FG)
	COM_INTERFACE_ENTRY(IPXC_FG)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
	COM_INTERFACE_ENTRY(IImageRep)	  
END_COM_MAP()

// IPXC_FG
public:
	// Main Callable Interface Function
	STDMETHOD(Initialize)();
	STDMETHOD(ObtainImage)();
	STDMETHOD(Reset)();
	STDMETHOD(Close)();

	// FrameGrabber Interface Properties
	STDMETHOD(get_ImageWidth)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ImageWidth)(/*[in]*/ long newVal);
	STDMETHOD(get_ImageHeight)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ImageHeight)(/*[in]*/ long newVal);
	STDMETHOD(get_ImageDepth)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_ImageLeft)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ImageLeft)(/*[in]*/ long newVal);
	STDMETHOD(get_ImageTop)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ImageTop)(/*[in]*/ long newVal);
	STDMETHOD(get_FrameGrabberID)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_FrameGrabberID)(/*[in]*/ long newVal);

	// IImageRep Interface properties
	STDMETHOD(get_Brightness)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Brightness)(/*[in]*/ float newVal);
	STDMETHOD(get_Camera)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_Camera)(/*[in]*/ short newVal);
	STDMETHOD(get_Contrast)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Contrast)(/*[in]*/ float newVal);
	STDMETHOD(get_FieldCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_FieldCount)(/*[in]*/ long newVal);
	STDMETHOD(get_Hue)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Hue)(/*[in]*/ float newVal);
	STDMETHOD(get_Saturation)(/*[out, retval]*/ float *pVal);
	STDMETHOD(put_Saturation)(/*[in]*/ float newVal);
	STDMETHOD(get_FrameCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_FrameCount)(/*[in]*/ long newVal);
	STDMETHOD(get_Chroma)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_Chroma)(/*[in]*/ short newVal);
	STDMETHOD(get_FrameGrabberName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FrameGrabberName)(/*[in]*/ BSTR newVal);
	STDMETHOD(Data)(long lIndex, /*[out, retval]*/ long* pVal);
	STDMETHOD(get_Depth)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Depth)(/*[in]*/ long newVal);
	STDMETHOD(get_Height)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Height)(/*[in]*/ long newVal);
	STDMETHOD(get_Width)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Width)(/*[in]*/ long newVal);
	STDMETHOD(get_Time)(long m_lTimeFlag,/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Time)(long m_lTimeFlag,/*[in]*/ double newVal);
	STDMETHOD(Update)(BYTE* data);
	STDMETHOD(UpdateManager)(BSTR Interface,VARIANT* Data);	// It is through this function that the image is displayed. 
	
	// Private functions
	void ResetDevice();

	// Variables
	short	Chroma;
	short	Camera;
	long	FieldCount;
	long	Depth;
	float	FrameRate;
	float	StopTime;
	float	StartTime;
	float	Saturation;
	float	Contrast;
	float	Brightness;
	float	Hue;

	LPBYTE	ImageData;
	LPBYTE	ImageBuff;

	
	// Interface callable functions
															// This function (along with all other properties are constantly being called).
															// In doing so, data is availabe as an ImgRepresentation.

	// Variables for TimeFlag and Point Index for IMA 2.5
	long	m_lTimeFlag;
	long	m_lPointIndex;
	double m_dPoint[2];

	// Linking variable
	IComponent*	m_pIUnkImgOut;		// 1 output image


/*********************************************************************
* Implementation of IMechanismActivate Interface					 *
*																	 *
* NOTE: I implemented this interface personally b/c we are NOT		 *
* a true mechanism interface but other functions call us as such.	 *									 *
*********************************************************************/
	STDMETHOD(ResetMechanism)(/*[in]*/ ULONG ulFlags)
	{
		// Call the normally derived class' implementation
		
		// Replace the call to MechanismReset(ulFlags) with actual function call
		if(IsInitialized())
			CloseDevice();	
	   
		return S_OK;	
	}

	STDMETHOD(GetExecTime)(/*[out]*/ double *ExecTime)
	{
		// Return our tracked execution time.
		if (ExecTime != NULL)
			*ExecTime = m_dPeriod;	// Not implemented here

		return S_OK;
	}
	
	STDMETHOD(InvokeMechanism)(/*[in]*/ ULONG ulFlags, /*[in]*/ ULONG ulOperation, /*[out]*/ ULONG *pulStatus)
	{
		// DEBUG
		ATLTRACE("CDTDevice::InvokeMechanism Flags=%d  Operation=%d\n", ulFlags, ulOperation );

		//ULONG Status;
		
		// NOTE: Todd has GetAgentTime surrounding this call
		// to give the user info about how long the operation took

		m_dTimeStart = 0.0;	// GetAgentTime(); Do not know if this will affect
							// IMA 2.5 performance. Juan Rojas 5/05

		// Perform the specified operation
		//Status = MechanismActivate( ulFlags, ulOperation );		// Retunrs HRESULTS
		
		m_dTimeEnd = 1.0;	// GetAgentTime(); Do not know if this will affect
							// IMA 2.5 performance, Juan Rojas
		
		// IIR Filter of timinig to smooth out transients and get a
		//	a "filtered" running time.

		m_dPeriod = 0.5*m_dPeriod + 0.5*(m_dTimeEnd - m_dTimeStart);

		// Return mechanism status
		//if (pulStatus != NULL)
		//	*pulStatus = Status;
	
		// DEBUG
		ATLTRACE("CDTDevice::InvokeMechanism complete\n" );

		return S_OK;

	}
	
	STDMETHOD(Activate)(/*[in]*/ ULONG ulFlags, /*[in]*/ ULONG ulOperation,/*[in]*/ ULONG ulLevels, /*[in,size_is(ulLevels)]*/ double *pdLevel,/*[out]*/ULONG *pulStatus)
	{

		// Return mechanism status
		if (pulStatus != NULL)
			 *pulStatus = 0;
		
		return S_OK;
	}

	STDMETHOD(GetNumOperations)(/*[out]*/ ULONG *pulNumOps)
	{
		// get number of supported operations
		if (pulNumOps != NULL)
		{
			*pulNumOps = m_ulOps;
			return S_OK;
		}
		else
			return E_FAIL;
	}
protected:
	BOOL FrameGrabberInitial;
	long FrameCount;
	long ErrorCount;
	long YResolution;
	long XResolution;
	long Width;
	long Height;
	long Top;
	long Left;
	long FrameGrabberID;   //0=Right, 1=Left
	struct {
	  BITMAPINFOHEADER head;
	  RGBQUAD colors[256];
	} maphead;

	void    GrabImage();
	void    SetBitMapHead();
	BOOL    AllocBuffer();
	HRESULT Initial(int FrameGrabberID,int left,int top,int width,int height);
	HRESULT SetCamera(int channel);
	HRESULT CloseDevice();
	HRESULT GetImage(LPBYTE Image);
	BOOL    IsInitialized();

	/***************************************/
	/* Variables for frame grabber library */
	/***************************************/
	HANDLE hBuf;
	BYTE __PX_HUGE *gpBits;

    //FRAME __PX_FAR *frh;
	FRAME __PX_FAR *frh[2];
	int tagQ[2];
	int frhIdx;        /* frhIdx, indexes both frh[] and tagQ[] */

	
    FRAMELIB frame;

	long iBoardRev;
	long ImageMaxY;
	long ImageMaxX;
	long fgh;
	long initflags;
	PXC200 pxc200;

	// IMechanismActivate 
	double	m_dTimeStart;
	double	m_dTimeEnd;
	double	m_dPeriod;
	ULONG	m_ulOps;

private: 
	// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT

};

#endif //__PXC_FG_H_
