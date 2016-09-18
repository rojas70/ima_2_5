// Image.cpp : Implementation of CImage
#include "stdafx.h"
#include "IMA2_CaptureManager.h"
#include "I:\Include\ComponentManager.h"
#include "I:\Include\BasicIMA.h"
#include "I:\Include\coreobj.h"
#include "Image.h"

/////////////////////////////////////////////////////////////////////////////
// CImage

STDMETHODIMP CImage::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IImage,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


// This is called by the managed component to indicate a change
HRESULT CImage::OnNotifyNewVisualState(ULONG ulFlags) 
{
	// Find out something about managed component
	if (m_pManagedIUnk != NULL)
	{
	}
	// Tell container to redraw us!
	FireViewChange(); 
	return S_OK;
}

// This default drawing code writes the name of the managed component
// inside its square
HRESULT CImage::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
	HGDIOBJ hOld,hNew;
	IComponent *pIC = NULL;
	BSTR	bstrName=NULL;
	char	*str = NULL;
	USES_CONVERSION;
	// Get component name to put on screen
	if (m_pManagedIUnk != NULL)
	{
			m_pManagedIUnk->QueryInterface(IID_IComponent,(void**)&pIC);
			if (pIC != NULL)
			{
				pIC->GetComponentName(0,&bstrName);
				pIC->Release();
			}
			str = OLE2T(bstrName);
			if (bstrName != NULL)
				SysFreeString(bstrName);
	}
	// Draw rounded rectangle around the manager bounds:
	hNew = GetStockObject(NULL_BRUSH);
	hOld = SelectObject(di.hdcDraw,hNew);	// Select in a "blank brush"
	RoundRect(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom,5,5);
	SelectObject(di.hdcDraw,hOld);			// Put old one back.
	
	// Shrink the drawing rectangle for text just a bit
	InflateRect(&rc,-5,-5);
	if (str != NULL)
		DrawText(di.hdcDraw,str,-1,&rc,DT_SINGLELINE| DT_CENTER);
	return S_OK;
}

// Mouse button message handlers
LRESULT CImage::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CImage::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}
