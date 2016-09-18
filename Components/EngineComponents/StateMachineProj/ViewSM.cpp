// ViewSM.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ViewSM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ViewSM dialog


ViewSM::ViewSM(CWnd* pParent /*=NULL*/)
	: CDialog(ViewSM::IDD, pParent)
{
	//{{AFX_DATA_INIT(ViewSM)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ViewSM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ViewSM)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ViewSM, CDialog)
	//{{AFX_MSG_MAP(ViewSM)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ViewSM message handlers
