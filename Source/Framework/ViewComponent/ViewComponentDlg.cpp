// ViewComponentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ViewComponent.h"
#include "ViewComponentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewComponentDlg dialog

CViewComponentDlg::CViewComponentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewComponentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewComponentDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CViewComponentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewComponentDlg)
	DDX_Control(pDX, IDC_FileBox, m_filebox);
	DDX_Control(pDX, IDC_CmpBox, m_cmpbox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CViewComponentDlg, CDialog)
	//{{AFX_MSG_MAP(CViewComponentDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Browse, OnBrowse)
	ON_BN_CLICKED(IDC_View, OnView)
	ON_WM_DESTROY()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewComponentDlg message handlers

BOOL CViewComponentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	DragAcceptFiles();
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_filebox.SetWindowText(m_filename);
	if(!m_filename.IsEmpty())
		OnView();
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CViewComponentDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CViewComponentDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CViewComponentDlg::OnBrowse() 
{
	CFileDialog dlg(TRUE,"*.cmp");

	if(dlg.DoModal()==IDOK)
	{
		m_filename=dlg.GetPathName();
		m_filebox.SetWindowText(m_filename);
	}
	
}

void CViewComponentDlg::OnView() 
{
	CFile file;
	int filelen;

	int i;
	CString txt="";
	int objlen;
	BYTE *buffer;

	m_filebox.GetWindowText(m_filename);
	if(!file.Open(m_filename,CFile::modeRead))
	{
		MessageBox("Error opening file","Error");
		return;
	}
	filelen=file.GetLength();

	buffer=new BYTE[filelen];

	file.Read(buffer,filelen);
	file.Close();

	i=8;
	objlen=1;
	while(i<filelen && objlen>0)
	{	
		objlen=*(int*)&buffer[i+8];
		if(objlen<0)  //for some reason the last item gives a real screwy number, so...
			objlen=filelen-i;
		txt+=ReadObject(&buffer[i],objlen,0);
		i+=objlen;
	}

	delete buffer;

	m_cmpbox.SetWindowText(txt);
}

CString CViewComponentDlg::ReadObject(BYTE *buffer,int objlen,int tabcount)
{
	int i;
	short namelen;
	int strlen;
	int objlen2;
	short vt;
	CString txt2;
	wchar_t *fieldname;
	wchar_t *fieldvalue;
	double dnum;
	float fnum;
	int inum;
	short snum;

		vt=*(short*)&buffer[0];
		namelen=*(short*)&buffer[2];
		fieldname=new wchar_t[namelen+1];
		memcpy(fieldname,&buffer[12],namelen*sizeof(wchar_t));
		fieldname[namelen]='\0';
		if(vt==8)
		{
			strlen=*(int*)&buffer[12+namelen*sizeof(wchar_t)];
			if(strlen>0)
			{
				fieldvalue=new wchar_t[strlen+1];
				memcpy(fieldvalue,&buffer[16+namelen*sizeof(wchar_t)],strlen*sizeof(wchar_t));
				fieldvalue[strlen]='\0';

				txt2.Format("%S: %S\r\n",fieldname,fieldvalue);
				delete fieldvalue;
			}
			else
				txt2.Format("%S: (null string)\r\n",fieldname);
		}
		else if(vt==2)
		{
			snum=*(short*)&buffer[12+namelen*sizeof(wchar_t)];
			txt2.Format("%S: %d\r\n",fieldname,snum);
		}
		else if(vt==3)
		{
			inum=*(int*)&buffer[12+namelen*sizeof(wchar_t)];
			txt2.Format("%S: %d\r\n",fieldname,inum);
		}
		else if(vt==4)
		{
			fnum=*(float*)&buffer[12+namelen*sizeof(wchar_t)];
			txt2.Format("%S: %.3f\r\n",fieldname,fnum);
		}
		else if(vt==5)
		{
			dnum=*(double*)&buffer[12+namelen*sizeof(wchar_t)];
			txt2.Format("%S: %.6f\r\n",fieldname,dnum);
		}
		else if(vt==9)
		{
			txt2.Format("%S: (object)\r\n",fieldname);
			i=36+namelen*sizeof(wchar_t);
			objlen2=1;
			while(i<objlen && objlen2>0)
			{
				objlen2=*(int*)&buffer[i+8];
				txt2+=ReadObject(&buffer[i],objlen2,tabcount+1);
				i+=objlen2;
			}
		}
		else if(vt==8209)
		{
			txt2.Format("%S:\r\n",fieldname);
			i=30+namelen*sizeof(wchar_t);
			objlen2=1;
			while(i<objlen && objlen2>0)
			{
				objlen2=*(int*)&buffer[i+8];
				txt2+=ReadObject(&buffer[i],objlen2,tabcount+1);
				i+=objlen2;
			}

		}
		else if(vt==11)
		{
			if(*(short*)&buffer[12+namelen*sizeof(wchar_t)])
				txt2.Format("%S: TRUE\r\n",fieldname);
			else
				txt2.Format("%S: FALSE\r\n",fieldname);
		}
		else
		{
			txt2.Format("%S: (unknown)\r\n",fieldname);
		}

		delete fieldname;

		for(i=0;i<tabcount;i++)
			txt2="\t"+txt2;
		return txt2;
}

void CViewComponentDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CViewComponentDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CViewComponentDlg::OnDropFiles(HDROP hdropInfo)
{
	char* filename;
	int filenamesize;

	filenamesize=DragQueryFile(hdropInfo,0,NULL,0);

	filename=new char[filenamesize+1];
	DragQueryFile(hdropInfo,0,filename,filenamesize+1);

	if(strcmp(&filename[filenamesize-3],"cmp")==0)
	{
		m_filename=filename;
		m_filebox.SetWindowText(m_filename);
		OnView();
	}
	delete filename;
}