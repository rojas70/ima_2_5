// VectorSignal.h : Declaration of the CVectorSignal

#ifndef __VECTORSIGNAL_H_
#define __VECTORSIGNAL_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CVectorSignal
class ATL_NO_VTABLE CVectorSignal : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVectorSignal, &CLSID_VectorSignal>,
	public IDispatchImpl<IVectorSignal, &IID_IVectorSignal, &LIBID_IMA2_BASICCOMPONENTSLIBLib>,
	public CComponentImpl 
{
public:
	CVectorSignal()
	{
		// New member variable to replace the index functionality in IMA 1.0
		m_lIndex					= 0;		// Serves to change values manually -  2/18/05 by Christina Campbell
		m_vecData					= NULL;		
		m_lSignalLength				= 10;		// Represents the last 10 vectors used - for history purposes.
		m_lVectorLength				= 20;		// Holds up to 20 values. It can hold transforms AND pressures for SoftArm.
		m_lRowVector				= 0;		// Stores which vector is active.
		m_pUnkMarshaler				= NULL;
		m_UpCount					= 0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VECTORSIGNAL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVectorSignal)
	COM_INTERFACE_ENTRY(IVectorSignal)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

 	CComPtr<IUnknown> m_pUnkMarshaler;	


// IVectorSignal
public:
	STDMETHOD(UpdateManager)(/*[in]*/BSTR Interface,/*[out,retval]*/ VARIANT *Data);
	STDMETHOD(SetVector)(/*[in]*/ long index,/*[in]*/ SAFEARRAY* data);
	STDMETHOD(SetCurrentVector)(SAFEARRAY* data);
	STDMETHOD(GetVector)(/*[in]*/ long index, SAFEARRAY* data);
	STDMETHOD(TestSetup)(long Index);
	STDMETHOD(GetCurrentVector)(/*[in,out]*/ SAFEARRAY* data);
	STDMETHOD(get_VectorLength)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_VectorLength)(/*[in]*/ long newVal);
	STDMETHOD(get_SignalLength)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_SignalLength)(/*[in]*/ long newVal);
	STDMETHOD(get_RowVector)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_RowVector)(/*[in]*/ long newVal);
	STDMETHOD(get_IndexValue)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_IndexValue)(/*[in]*/ double newVal);
	STDMETHOD(get_Index)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Index)(/*[in]*/ long newVal);


		long m_UpCount;

// Create one entry for each binding that this component will support.
	IMA2_BindingInfo		m_BindingVectorSignal;		// BindingInfo for the VS binding

// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT Data);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT

// Vector Signal Data
private:
	double	**m_vecData;		// Vector sample i

	long	m_lVectorLength;	// Persistent properties for length
	long	m_lSignalLength;	// and for signal length (history) kept by signal

	long	m_lRowVector;		// Used to implement a circular buffer
	long	m_lIndex;			// Used to increment CurrentValue index (CLC 2/18/05)

	HRESULT ReallocateData(long oldsiglen,long oldveclen);

	// Binding methods
	STDMETHOD(OnConstruct)(void);	// Set bindings
	STDMETHOD(OnDestruct)(void);	// Delete them
	};

#endif //__VECTORSIGNAL_H_
