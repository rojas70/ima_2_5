// Image.h : Declaration of the CImage

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImage
class ATL_NO_VTABLE CImage : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CImage, &CLSID_CImage>,
	public CComControl<CImage>,
	public IDispatchImpl<IImage, &IID_IImage, &IMA2_CAPTUREMANAGERLib>,
	public IProvideClassInfo2Impl<&CLSID_CImage, NULL, &IMA2_CAPTUREMANAGERLib>,
//	public IPersistStreamInitImpl<CImage>,
	public IPersistStorageImpl<CImage>,
	public IQuickActivateImpl<CImage>,
	public IOleControlImpl<CImage>,
	public IOleObjectImpl<CImage>,
	public IOleInPlaceActiveObjectImpl<CImage>,
	public IViewObjectExImpl<CImage>,
	public IOleInPlaceObjectWindowlessImpl<CImage>,
	public IDataObjectImpl<CImage>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CImage>,
	public ISpecifyPropertyPagesImpl<CImage>,
	public CComponentManagerImpl<CImage>
{
public:
	CImage()
	{
		// TODO: Initialize all variables
	}

DECLARE_REGISTRY_RESOURCEID(IDR_IMAGE)

BEGIN_COM_MAP(CImage)
	COM_INTERFACE_ENTRY(IImage)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	// IMA interfaces
	COM_INTERFACE_ENTRY(IComponentManager)
	COM_INTERFACE_ENTRY(IComponent)
	COM_INTERFACE_ENTRY(IComponentContainer)
	COM_INTERFACE_ENTRY(IComponentManagerEventSink)
END_COM_MAP()

// Property pages, if desired
BEGIN_PROPERTY_MAP(CImage)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	PROP_PAGE(CLSID_StockColorPage)
END_PROPERTY_MAP()
// support for outgoing interfaces, if necessary

BEGIN_CONNECTION_POINT_MAP(CImage)
END_CONNECTION_POINT_MAP()

// Windows messages
BEGIN_MSG_MAP(CImage)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown )
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown )
END_MSG_MAP()

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

	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	// TEMPLATE METHODS FOR IMA BASE CLASS USE:
	// This method must provide a class id for the managed
	// component to support initialization of the manager obejct.
	HRESULT InitNewManagedComponent(CLSID *m_ManagedCLSID)
	{
		if (m_ManagedCLSID != NULL)
		// be sure to put the CLSID of your managed component here!!
		memcpy(m_ManagedCLSID,&CLSID_MyManagedCLSID,sizeof(CLSID));  
		return S_OK;
	}
	// This method must provide some name for the managed
	// object, but can be based on looking at manager's name
	// or just a default like below:
	HRESULT GetManagedComponentName(wchar_t *SubName)
	{
		if (SubName != NULL)
		// be sure to put the CLSID of your managed component here!!
		wcscpy(SubName,L"MyManagedComponent");   
		return S_OK;
	}
	// Base class callback for visual updates:
	HRESULT OnNotifyNewVisualState(ULONG ulFlags);
	// Called when time to redraw the manager
	HRESULT OnDraw(ATL_DRAWINFO& di);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

public:

// %%INTERFACE: IImage

};

#endif //__IMAGE_H_
