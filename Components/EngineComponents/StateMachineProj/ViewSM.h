#if !defined(AFX_VIEWSM_H__BCFCD660_CD6D_476D_BC6D_11546FC57C72__INCLUDED_)
#define AFX_VIEWSM_H__BCFCD660_CD6D_476D_BC6D_11546FC57C72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewSM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ViewSM dialog

class ViewSM : public CDialog
{
// Construction
public:
	ViewSM(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ViewSM)
	enum { IDD = IDD_VIEWSM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ViewSM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ViewSM)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWSM_H__BCFCD660_CD6D_476D_BC6D_11546FC57C72__INCLUDED_)
