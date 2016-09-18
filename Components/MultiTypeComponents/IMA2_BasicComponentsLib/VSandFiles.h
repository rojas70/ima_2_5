// VSandFiles.h : Declaration of the CVSandFiles

#ifndef __VSANDFILES_H_
#define __VSANDFILES_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh" // property bag dll
#define AXIS_MAX 6
/////////////////////////////////////////////////////////////////////////////
// CVSandFiles
class ATL_NO_VTABLE CVSandFiles : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVSandFiles, &CLSID_VSandFiles>,
	public IDispatchImpl<IVSandFiles, &IID_IVSandFiles, &LIBID_IMA2_BASICCOMPONENTSLIBLib>,
	public CComponentImpl
{
public:
	CVSandFiles()
	{
		m_fp				= NULL;	
		m_pIUnkOut			= NULL;
		m_hDataFile			= NULL;
		
		nFileStat			= ~EOF;							// Used to check the end of the file

		m_lNumAxes			= 6;
		m_dTemp				= 0.0;
		m_dTrajTime			= 0.0;
		
		m_bstrFileName = SysAllocString(L"");

		for (int i=0;i<(AXIS_MAX);i++)
			m_dData[i]=0.0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VSANDFILES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVSandFiles)
	COM_INTERFACE_ENTRY(IVSandFiles)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IVSandFiles
public:

	STDMETHOD(Write2File)();
	STDMETHOD(get_NumAxes)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_NumAxes)(/*[in]*/ long newVal);
	STDMETHOD(get_FileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FileName)(/*[in]*/ BSTR newVal);
	STDMETHOD(Initialize)();
	STDMETHOD(Write2VS)();
private:
		// Binding methods
	STDMETHOD(OnConstruct)(void);					// Set bindings
	STDMETHOD(OnDestruct)(void);					// Delete them

	// Override of IMA base components
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

	// Internal Functions
	void OpenFile();
	void CloseFile();
	void InitFile(bool bOverwrite);
	void WriteDoubles(long len,double *pdData);

	// Internal Variable
	int			nFileStat;
	long		m_lNumAxes;

	double		m_dTemp;							// Dummy variable to store trash
	double		m_dData[AXIS_MAX];
	double		m_dTrajTime;

	char szFileName[200];
	
	// File Variables
	HANDLE		m_hDataFile;						// Handle needed for WriteFile function
	BSTR		m_bstrFileName;						// To read/write string for text file
	FILE *		m_fp;								// To do string opens and scans

	// Binding Variable
	IComponent	*m_pIUnkOut;						// IComponent variable to connect to the VS that will read data

};

#endif //__VSANDFILES_H_
