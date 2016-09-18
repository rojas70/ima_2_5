// NetImgRep.h : Declaration of the CNetImgRep

#ifndef __NETIMGREP_H_
#define __NETIMGREP_H_

#include "resource.h"       // main symbols
#include "Default.h"
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh" // property bag dll

class CImageFeature;
class CFeatureCollection;
/////////////////////////////////////////////////////////////////////////////
// CNetImgRep
class ATL_NO_VTABLE CNetImgRep : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CNetImgRep, &CLSID_NetImgRep>,
	public IDispatchImpl<INetImgRep, &IID_INetImgRep, &LIBID_IMA2_IMAGEREPLIBLib>,
	public CComponentImpl,
//	public CRepresentationImpl<CNetImgRep>,	// IMA reps
	public IImageRep,	// Abstract interface
	public IFeatureInfo // Feature information
{
public:
CNetImgRep()
{
	// Init
	m_pImage			= NULL;
	m_pCurrentFeatures	= NULL;

	m_lWidth			= WIDTH;
	m_lHeight			= HEIGHT;
	m_lDepth			= DEPTH;

	m_dPoint[0]			= 0.0;
	m_dPoint[1]			= 0.0;

	m_dTime				= 0.0;
	m_lTimeFlag			= 0;
	m_lPointIndex		= 0;

	m_dLastProxyTime	= 0.0f;	
	m_dProxyDelay		= 0.2f;	// 0.2 seconds between proxy updates
}

~CNetImgRep()
{
	// Cleanup
//	delete	m_pCurrentFeatures;

	// Release allocated image memory
	if( m_pImage != NULL ) delete[] m_pImage;
}

DECLARE_REGISTRY_RESOURCEID(IDR_NETIMGREP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNetImgRep)
	COM_INTERFACE_ENTRY(INetImgRep)
	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY2(IDispatch, IFeatureInfo)					// This line won't allow you to load the component in DAD. It was originally used b/c 
																	// the first line was giving a compile error
	COM_INTERFACE_ENTRY(IImageRep)		// Abstract interface
	COM_INTERFACE_ENTRY(IFeatureInfo)	// Feature information
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()


public:

// IImageRep
	STDMETHOD(get_Width)( /*[out, retval]*/ long *pVal);
	STDMETHOD(put_Width)( /*[in]*/ long newVal);
	STDMETHOD(get_Height)( /*[out, retval]*/ long *pVal);
	STDMETHOD(put_Height)(/*[in]*/ long newVal);
	STDMETHOD(Data)(long lIndex, /*[out, retval]*/ long* pVal );
	STDMETHOD(Update)(/*[in]*/ BYTE* pVal);
	STDMETHOD(get_Depth)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Depth)(/*[in]*/ long newVal);
	STDMETHOD(get_Time)(long m_lTimeFlag,/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Time)(long m_lTimeFlag,/*[in]*/ double newVal);
	STDMETHOD(UpdateManager)(/*[in]*/BSTR Interface,/*[out,retval]*/ VARIANT* Data);
	//STDMETHOD(get_TimeFlag)(/*[out, retval]*/ long *pVal);
	//STDMETHOD(put_TimeFlag)(/*[in]*/ long newVal);


// IFeatureInfo
	STDMETHOD(get_FeatureWidth)(long lIndex,/*[out, retval]*/ long *pVal);
	STDMETHOD(put_FeatureWidth)(long lIndex,/*[in]*/ long newVal);
	STDMETHOD(get_FeatureHeight)(long lIndex,/*[out, retval]*/ long *pVal);
	STDMETHOD(put_FeatureHeight)(long lIndex,/*[in]*/ long newVal);
	STDMETHOD(get_FeatureCentroid)( long lIndex,/* [out, retval]*/ long* pX,/* [out, retval]*/ long* pY );
	STDMETHOD(put_FeatureCentroid)( long lIndex, /*[in]*/ long newX, /*[in]*/ long newY);
	STDMETHOD(get_FeatureArea)(long lIndex,/* [out, retval]*/ long *pVal);
	STDMETHOD(put_FeatureArea)(long lIndex, /*[in] */long newVal);
	STDMETHOD(get_FeatureLabel)(long lIndex, /*[out, retval]*/ long *pVal);
	STDMETHOD(put_FeatureLabel)(long lIndex, /*[in]*/ long newVal);
	STDMETHOD(get_FeatureLocation)( long lIndex, /*[out, retval]*/ long* pLeft, /*[out, retval]*/ long* pTop );
	STDMETHOD(put_FeatureLocation)( long lIndex, /*[in]*/ long newLeft, /*[in]*/ long newTop);
	STDMETHOD(AddFeature)(long lFeatureLabel, /*[out]*/ long* plFeatureIndex );
	STDMETHOD(ClearFeatures)();
	STDMETHOD(get_FeatureIndex)(long lFeatureLabel, /*[out, retval]*/ long *pVal);
	STDMETHOD(put_FeatureIndex)(long lFeatureLabel, /*[in]*/ long newVal);
	STDMETHOD(get_FeatureName)( long lIndex, /*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FeatureName)( long lIndex, /*[in]*/ BSTR newVal);
	STDMETHOD(get_FeatureOrientation)( long lIndex, /*[out, retval]*/ long *pVal);
	STDMETHOD(put_FeatureOrientation)( long lIndex, /*[in]*/ long newVal);
	STDMETHOD(NumFeatures)(long* pVal);
	STDMETHOD(get_FeatureLength)(long lIndex, /*[out, retval]*/ long *pVal);
	STDMETHOD(put_FeatureLength)(long lIndex, /*[in]*/ long newVal);

// INetImgRep	
	STDMETHOD(get_Point)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Point)(/*[in]*/ double newVal);
	STDMETHOD(get_PointIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_PointIndex)(/*[in]*/ long newVal);
	STDMETHOD(get_ImgDepth)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ImgDepth)(/*[in]*/ long newVal);
	STDMETHOD(get_ImgHeight)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ImgHeight)(/*[in]*/ long newVal);
	STDMETHOD(get_ImgWidth)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ImgWidth)(/*[in]*/ long newVal);
	STDMETHOD(get_ProxyDelay)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_ProxyDelay)(/*[in]*/ double newVal);

	virtual HRESULT UpdateRepresentationProxy(/*UpdateHeader *pUH,*/double dTime,ULONG ulData,unsigned char *DataBuffer); // IMA 1 specific identifier
	virtual HRESULT GetRepUpdateBuffer(unsigned char **ppDataBuffer,ULONG *pulLength);
	virtual HRESULT	OnAttachedToSource(IUnknown *pIUnkSource);


// Attributes
protected:

// IFeatureInfo
	CFeatureCollection*	m_pCurrentFeatures;

// bah ( for clicking )
	double m_dPoint[2];

// IImageRep
	long	m_lWidth;
	long	m_lHeight;
	long	m_lDepth;
	long	m_lTimeFlag;
	double	m_dTime;

// INetImgRep
	LPBYTE	m_pImage;
	long	m_lPointIndex;
	double	m_dLastProxyTime;	// last time proxy updates sent
	double	m_dProxyDelay;

	HRESULT Initialize();

// Internal constuctor/destructor
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT

};

#endif //__NETIMGREP_H_
