// ViewComponentDlg.h : header file
//

#if !defined(AFX_VIEWCOMPONENTDLG_H__B4AAF2E4_8620_414B_A230_6FB4FE40664D__INCLUDED_)
#define AFX_VIEWCOMPONENTDLG_H__B4AAF2E4_8620_414B_A230_6FB4FE40664D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CViewComponentDlg dialog

class CViewComponentDlg : public CDialog
{
// Construction
public:
	CViewComponentDlg(CWnd* pParent = NULL);	// standard constructor
	CString m_filename;

// Dialog Data
	//{{AFX_DATA(CViewComponentDlg)
	enum { IDD = IDD_VIEWCOMPONENT_DIALOG };
	CEdit	m_filebox;
	CEdit	m_cmpbox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewComponentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CString ReadObject(BYTE* objstart,int objlen,int tabcount);


	// Generated message map functions
	//{{AFX_MSG(CViewComponentDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnView();
	afx_msg void OnDestroy();
	afx_msg void OnDropFiles(HDROP);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWCOMPONENTDLG_H__B4AAF2E4_8620_414B_A230_6FB4FE40664D__INCLUDED_)
