// SesManager.h : Declaration of the CSesManager

#ifndef __SESMANAGER_H_
#define __SESMANAGER_H_

#include "resource.h"       // main symbols
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"			// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h" // Vector Signal
#include "O:\Components\Representations\IMA2_TextQueueLib\IMA2_TextQueueLib.h"  //Text Queue

#include <ctime>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <winsock.h>
//mysql includes
#include "mysql++"
#include "custom.hh"

/////////////////////////////////////////////////////////////////////////////
// CSesManager
class ATL_NO_VTABLE CSesManager : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSesManager, &CLSID_SesManager>,
	public IDispatchImpl<ISesManager, &IID_ISesManager, &LIBID_IMA2_SESMANAGERLib>,
	public CComponentImpl 
{
public:
	CSesManager()
	{
		//Initalize all variables
		m_lTessFreq				= 14;
		m_DBname				= SysAllocString(L"dbses_kat");
		dbName					= "dbses_kat";

		//identifier
		cpIdentifier			= "image";

		//pcpRetTypes				= NULL;
		//pcpRetNames				= NULL;


		//Connect to database --SALLY for now
		m_connSES = new Connection(dbName, "localhost", "user");
	
		//head angles
		m_pdHeadAngles	= new double[6];
		for (int i=0;i<6;i++)
			m_pdHeadAngles[i]=0.0;	
		
		m_pIUnkDataVS	= NULL;
		m_pIUnkDataVS	= NULL;
		m_pIUnkTypesTQ	= NULL;
		m_pIUnkNamesTQ	= NULL;

	}

DECLARE_REGISTRY_RESOURCEID(IDR_SESMANAGER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSesManager)
	COM_INTERFACE_ENTRY(ISesManager)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// ISesManager
public:
	STDMETHOD(RetrieveFromSES)();
//	STDMETHOD(get_Type)(/*[out, retval]*/ BSTR *pVal);
//	STDMETHOD(put_Type)(/*[in]*/ BSTR newVal);
//	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
//	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
	STDMETHOD(PostSESInfo)();										//for posting and updating
	STDMETHOD(ResetSES)();
	STDMETHOD(get_DatabaseName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_DatabaseName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Tessellation)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Tessellation)(/*[in]*/ long newVal);
	virtual STDMETHODIMP Load(VARIANT Data);
	virtual STDMETHODIMP Save(VARIANT *pData);

	//these don't need to be seen from DAD --Internal functions
	void(Disconnect)();
	void(Connect)(char* dbNameTemp, char* ServerTemp, char* UsernameTemp);
	bool(DumpAllData)();
	int(Post)(double dPan, double dTilt, char* name, char* type, char* identifier);
	int*(AnglesToIndices)(float AnglePhi, float AngleTheta);
	bool(RetrieveAtAngles)(float Phi, float Theta, char* Identifier, char* Time);
	int(RetrieveByName)(char* Name);
	int(RetrieveByType)(char* Type);	
	double*(ConvertToPanTilt)(double dPhi, double dTheta);
	double*(ConvertToPhiTheta)(double dPan, double dTilt);


	IComponent*	m_pIUnkDataVS;
	IComponent*	m_pIUnkDataVS2;
	IComponent*	m_pIUnkTypesTQ;
	IComponent*	m_pIUnkNamesTQ;


	long		m_lTessFreq;
	char*		dbName; //Database name (char pointer)


private:

	STDMETHOD(OnConstruct)(void);					// Set bindings
	STDMETHOD(OnDestruct)(void);					// Delete them

	BSTR				m_DBname;					//Database name
	char				pcpRetTypes[10][40];		//Retrieved Tyes
	char				pcpRetNames[10][40];		//Retrieved Names
	double				pdRetPans[10];				//Retrieved Pan Angles
	double				pdRetTilts[10];				//Retrieved Tilt Angles
	double*				m_pdHeadAngles;
	char*				cpIdentifier;


protected:
	
	Connection		*m_connSES;

};

#endif //__SESMANAGER_H_
