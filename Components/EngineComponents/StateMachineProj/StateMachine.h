// StateMachine.h : Declaration of the CStateMachine

/******************************************************** 
/********************* PLEASE READ *********************/
/********************************************************
* This code is designed to work with Matlab R2007 or earlier.
* The R2008 versions write the state machine under a different format.
* The state machine component will not run. 
* The difference is small and could be easily fixed. When Matlab 2008
* writes the text file representing the statemachine in state flow,
* all the calls to different routines are found in the same line of text.
* In earlier versions each call would be in a new line. 
* Compare the text file between how a new state machine would look like and
* how an old one would look like. 
**********************************************************/
#ifndef __STATEMACHINE_H_
#define __STATEMACHINE_H_

#include "resource.h"								 // main symbols
#include <comdef.h>
#include <process.h>
#include "O:\Base Classes\ComponentImpl.h"
#include "O:\Components\msvbvm60.tlh"				// property bag dll

class conn
{
public:
	int startnum;
	int endnum;
	int shapeid;
	CString trigger;
};

class command
{
public:
	command(CString txt);
	~command();
	CString componentname;
	CString function;
	CString fnname;
//	IComponent *component;
};


class state
{public:
	~state();
	state(CString name,int id);
	state(conn *trans,int id);
	int shapeid;
	CArray<conn*,conn*> transitions;
	CArray<command*,command*> commands;
	CString name;
};

/////////////////////////////////////////////////////////////////////////////
// CStateMachine
class ATL_NO_VTABLE CStateMachine : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CStateMachine, &CLSID_StateMachine>,
	public IDispatchImpl<IStateMachine, &IID_IStateMachine, &LIBID_STATEMACHINEPROJLib>,
	public CComponentImpl
{
public:
	CStateMachine()
	{
	};
	~CStateMachine()
	{
	};

DECLARE_REGISTRY_RESOURCEID(IDR_STATEMACHINE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStateMachine)
	COM_INTERFACE_ENTRY(IStateMachine)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()

// IStateMachine
public:
	STDMETHOD(UpdateManager)(/*[in]*/ BSTR Interface, /*[out,retval]*/ VARIANT *DATA);
	STDMETHOD(Wait)(/*[in]*/ int time);
	STDMETHOD(ManualSignal)();
	STDMETHOD(get_ManualSignalString)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ManualSignalString)(/*[in]*/ BSTR newVal);
//	STDMETHOD(Reconnect)();
	STDMETHOD(Stop)();
	STDMETHOD(Signal)(BSTR signal);
	STDMETHOD(get_CurrentState)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(Reset)();
	STDMETHOD(Start)();
	STDMETHOD(LoadSM)();
	static UINT RunSM(LPVOID param);
	void LocalRunSM();
	void LoadFile();
	CString CreateParams(CString incomm, ELEMDESC* paramdesc, ELEMDESC retvaldesc, int numparams, DISPPARAMS* params, variant_t* returnval);
	CString UpdateReturnVars(CString param, ELEMDESC* paramdesc, DISPPARAMS params, variant_t retval);

	STDMETHOD(get_NumStates)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_FileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FileName)(/*[in]*/ BSTR newVal);
	CString m_filename;
	BOOL m_playing;

	BOOL m_reset;
	CString m_manualsignal;


	void DeleteVars();
	void DeleteInternal(VARIANTARG *val);
	void DeleteOneVar(VARIANTARG* val, CString key);
	void HiddenSetup();
	int ReadState(CStdioFile *filein);
	int ReadConn(CStdioFile *filein);
	int ReadData(CStdioFile *filein);
	void UpdateVars(conn* cn);
	void ResetVars();
	BOOL ReadOneVar(variant_t *val,CString txt,VARTYPE vt,int& arraycount);
	BOOL ReadOneVar(VARIANT& val,CString txt,VARTYPE vt,int& arraycount);
	CString *SeparateVars(CString in, int& count, CString sep=",");
	CString InsertVars(CString in,int flag=0);
	int FindNextState();
//	int FindNextTask();
//	int FindNextAction();
	int FindNext(conn *cn);
	void ChangeType(variant_t *in,VARTYPE vt,int& arraycount,int arridx);
	void ChangeType(variant_t *in,variant_t *out, VARTYPE vt,int& arraycount,int arridx);
	void ChangeType(variant_t *in,VARIANT& out,VARTYPE vt,int& arraycount,int arridx);
	void ChangeType(VARIANT in,variant_t* out,VARTYPE vt,int&arraycount,int arridx);
	CString VarTypeToText(VARTYPE vt);
	variant_t TextToMath(CString eqn,VARTYPE vt,CString& returntxt);
	variant_t MakeString(CString eqn, CString& returntxt);

	int FindState(int shapeid);
//	int FindTask(int shapeid, int *parentidx);
//	int FindTask(int shapeid, int parentid, int* parentidx);
//	int FindAction(int shapeid, int parentid, int stateidx, int* parentidx);
	CArray<state*,state*> m_fsm;
//	int m_baseid;
	int *m_idxs;
	int m_currstate;
//	int m_currtask;
//	int m_curraction;
//	int m_numstates;
	int m_stopstate;
	conn *m_firstconn;
	CMapStringToPtr* m_vars;
	BOOL m_wait;
	CString m_signal;
	IStream *m_LocStream; //Used for threadsafe m_Locator

//	void DisplayStates();
	
//	NewDomainDlg m_newDomain;

//	static void CtrlCmdCallback(void *param, RecvStatus *status);
//	void LocalCtrlCmdCallback(RecvStatus *status);
//	void SendMsg(CString msg,int type=-1,int to=-1);
//	RobonautAPI *m_CtrlCmd;

	//Overrriden inherited functions
	STDMETHODIMP OnConstruct();
	STDMETHODIMP OnDestruct();
	STDMETHODIMP Load(VARIANT Data);
	STDMETHODIMP Save(VARIANT* Data);
//	void OnActivate();
};

#endif //__STATEMACHINE_H_
