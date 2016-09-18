// ViewComponent.h : main header file for the VIEWCOMPONENT application
//

#if !defined(AFX_VIEWCOMPONENT_H__C5598DA0_F11E_49F8_9E77_EE40C5433C70__INCLUDED_)
#define AFX_VIEWCOMPONENT_H__C5598DA0_F11E_49F8_9E77_EE40C5433C70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CViewComponentApp:
// See ViewComponent.cpp for the implementation of this class
//

class CViewComponentApp : public CWinApp
{
public:
	CViewComponentApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewComponentApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CViewComponentApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWCOMPONENT_H__C5598DA0_F11E_49F8_9E77_EE40C5433C70__INCLUDED_)
