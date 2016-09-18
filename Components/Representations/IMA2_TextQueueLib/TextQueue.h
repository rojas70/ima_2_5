// TextQueue.h : Declaration of the CTextQueue

#ifndef __TEXTQUEUE_H_
#define __TEXTQUEUE_H_

#include "resource.h"						// main symbols
#include "O:\Components\msvbvm60.tlh"		// property bag dll
#include "O:\Base Classes\ComponentImpl.h"

#define  MAX_Q_LEN		10
#define  MAX_STR_LEN	1024
/////////////////////////////////////////////////////////////////////////////
// CTextQueue

class ATL_NO_VTABLE CTextQueue : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTextQueue, &CLSID_TextQueue>,
	public IDispatchImpl<ITextQueue, &IID_ITextQueue, &LIBID_IMA2_TEXTQUEUELIBLib>,
	public CComponentImpl 
{
public:
	CTextQueue()
	{
		int i;
		for(i=0;i<MAX_Q_LEN;i++) 
			m_textData[i] = SysAllocString(L"");

		// Indeces
		m_lStringIndex		= 0;			// 
		
		// Queue length
		m_lQueueLength	= 10;			// Number of strings in the queue

		// Event and Data variables
		m_lThrowEvent	= 0;			//m_bUpdateAgentEventFlag
		m_lSaveData		= 0;			//m_lDataPersistent;

	}

DECLARE_REGISTRY_RESOURCEID(IDR_TEXTQUEUE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTextQueue)
	COM_INTERFACE_ENTRY(ITextQueue)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// ITextQueue
public:
	STDMETHOD(get_SaveData)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_SaveData)(/*[in]*/ long newVal);
	STDMETHOD(get_ThrowEvent)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_ThrowEvent)(/*[in]*/ long newVal);
	STDMETHOD(get_QueueLength)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_QueueLength)(/*[in]*/ long newVal);
	STDMETHOD(get_CurrentText)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_CurrentText)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_StringIndex)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_StringIndex)(/*[in]*/ long newVal);

	STDMETHOD(SetText)(long index, BSTR text);
	STDMETHOD(GetText)(long index, BSTR *text);
	STDMETHOD(SetCurrentText)(/*[in]*/ BSTR text);
	STDMETHOD(GetCurrentText)(/*[out, retval]*/BSTR *text);


	STDMETHOD(UpdateManager)(/*[in]*/BSTR Interface,/*[out,retval]*/ VARIANT *Data);	// For the Manager Book




protected:
	// Text
	BSTR	m_textData[MAX_Q_LEN];		// Internal variable that holds strings of text

	// Index
	long m_lStringIndex;
	
	// Queue length
	long m_lQueueLength;		// Number of strings in the queue

	// Event and Data variables
	long m_lThrowEvent;			// Flag to indicate if event should be triggered through state machine. Used to be m_lUpdateAgentEventFlag
	long m_lSaveData;			// Flag to indicated if data in the text queue should be saved for later use. Used to be m_lDataPersistent;

private:
	STDMETHOD(OnConstruct)(void);
	STDMETHOD(OnDestruct)(void);

// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT Data);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component
													// This would be equivalent to returning a virtual HRESULT
													// STDMETHOD returns a virtual HRESULT

	
};

#endif //__TEXTQUEUE_H_
