// MotionCommands.h : Declaration of the CMotionCommands

#ifndef __MOTIONCOMMANDS_H_
#define __MOTIONCOMMANDS_H_

#include "resource.h"       					// main symbols
#include "O:\Base Classes\ComponentImpl.h"		// Component Lib file
#include "O:\Components\msvbvm60.tlh"			// property bag dll
#include "O:\Include\Motoman\MotoCom.h"			// Motoman declarations

#include "O:\Components\ArmComponents\IMA2_Motoman\IMA2_MotomanLib\CommSetUp.h"	// In order to access the Communications Handle

#define NUM_AXES 6
/////////////////////////////////////////////////////////////////////////////
// CMotionCommands
class ATL_NO_VTABLE CMotionCommands : 
	public CComObjectRootEx<CComSingleThreadModel>,	
	public CComCoClass<CMotionCommands, &CLSID_MotionCommands>,
	public IDispatchImpl<IMotionCommands, &IID_IMotionCommands, &LIBID_IMA2_MOTOMANLIBLib>,
	public CComponentImpl
{
public:
	CMotionCommands()
	{
		// TODO: Initialize all variables in constructor
		m_bServoOn	= false;
		m_sSuccess	= 0;
		m_sComHandle=-1;
		m_bMotionType = SysAllocString(L"MOVL");			// Standard motion will be assigned as MOVL
		for(int i=0;i<NUM_AXES*2;i++)	m_pdDesPos[i] = 0;
		m_pdCommParams[0] = m_pdCommParams[1] = 0.0;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_MOTIONCOMMANDS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMotionCommands)
	COM_INTERFACE_ENTRY(IMotionCommands)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()
// IMotionCommands
// This is where all your interface methods will appear and be displayed on DAD
public:
	STDMETHOD(get_MotionType)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_MotionType)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ErrorMessage)(/*[out, retval]*/ BSTR *pVal);
	
	STDMETHOD(move_Incremental)();
	STDMETHOD(move_UsersChoice)();

private:

	bool	m_bServoOn;								// Flag to determine if the servo power is on.
	BSTR	m_bstrError;							// BSTR string that stores error message. 
	short	m_sSuccess;								// Flag to determine outcome
	short	m_sComHandle;
	//CCommSetUp	*pComm;								// Pointer to CommSetUp class
	// char vtype, double spd, char *framename, short toolno, double *p // to be defined in variables and put on DAD's interface

	double m_pdDesPos[NUM_AXES*2];					// Variable to store desired positions.
	double m_pdCommParams[2];						// Variable to store Communication Paramters
	BSTR   m_bMotionType;

	// Binding variables
	IComponent* m_pIUnkDesiredPosition;				// Pointer to position object (VS)
	IComponent* m_pIUnkCommunicationParameters;		// Pointer to CommParams(VS)

	// IMA 2.5 Functions
	STDMETHOD(OnConstruct)(void);					// Set bindings
	STDMETHOD(OnDestruct)(void);					// Delete them
	virtual STDMETHODIMP Load(VARIANT pData);
	virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

};

#endif //__MOTIONCOMMANDS_H_
