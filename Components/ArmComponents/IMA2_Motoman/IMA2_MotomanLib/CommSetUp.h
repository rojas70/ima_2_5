// CommSetUp.h : Declaration of the CCommSetUp
// Need to include motocom.h, motocom32.dll, motocom32.lib, motolk.dll, and motolkr.dll in IMA2_MotomanLib\Debug
// Information contained in this program can be found in two manuals: Data Transmission and Motocom SDK manuals. 
// Look for them at: M:\Documentation

#ifndef __COMMSETUP_H_
#define __COMMSETUP_H_

#include "resource.h"       					// main symbols
#include "O:\Base Classes\ComponentImpl.h"		// Component Lib file
#include "O:\Components\msvbvm60.tlh"			// property bag dll
#include "O:\Include\IMA2_BasicComponentsLib.h" // Vector signal
#include "O:\Include\Motoman\MotoCom.h"			// Motoman declarations


// Some definitions that should be pretty standard in our lab
#define SERIAL		0x01						// Defines communication type (serial or ethernet). See BscOpen 
#define COM2		2							// Define port number
#define BRATE		9600						// Define baud rate
#define EVEN		2							// Define parity scheme
#define EIGHT_BIT	8							// Define data length for communication transmission
#define ONE_BIT		0							// Define data length for stop bit
												// Value should be 1. (Sometimes it seems that it will only work with 0.
												// Data Transmission Manual p. 37/116
#define NUM_AXES	6
/////////////////////////////////////////////////////////////////////////////
// CCommSetUp
class ATL_NO_VTABLE CCommSetUp : 
	public CComObjectRootEx<CComSingleThreadModel>,	
	public CComCoClass<CCommSetUp, &CLSID_CommSetUp>,
	public IDispatchImpl<ICommSetUp, &IID_ICommSetUp, &LIBID_IMA2_MOTOMANLIBLib>,
	public CComponentImpl 
{
public:
	CCommSetUp()
	{
		// TODO: Initialize all variables in constructor
		m_sComType	= SERIAL;
		m_sPort		= COM2;							
		m_dwBaud	= BRATE;							
		m_sParity	= EVEN;						
		m_sDataLen	= EIGHT_BIT;							
		m_sStopBit	= ONE_BIT;						
		m_sSuccess	= 0;
		m_bConnected= 0;
		m_sComHandle= 0;
		m_bServoOn	= 0;
		
		
	}

DECLARE_REGISTRY_RESOURCEID(IDR_COMMSETUP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCommSetUp)
	COM_INTERFACE_ENTRY(ICommSetUp)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IComponent)
END_COM_MAP()
// ICommSetUp
// This is where all your interface methods will appear and be displayed on DAD
public:
	STDMETHOD(SerialConnect)();											// Connects host computer to NX100
	STDMETHOD(SerialDisconnect)();
	
// Communication Variables
// See M:\Documentation\Programming\Motocom SDK Function Manual p. 207/217
short m_sComType;						// Stores communication type	(Serial or Ethernet)
short m_sPort;							// Stores port number			(Communication port number 1:COM1,2:COM2,3:COM3,4:COM4,...,255:COM255)
DWORD m_dwBaud;							// Stores baud rate				(Baud rate 150, 300, 600, 1200, 2400, 4800, 9600, 19200)
short m_sParity;						// Stores parity				(Parity 0: None, 1: Odd, 2: Even)
short m_sDataLen;						// Stores data bits				(Data length 7: 7 bits, 8: 8 bits)
short m_sStopBit;						// Stores stop bits				(Stop bit 0: 1 bit, 1: 1.5 bits, 2: 2 bits)
bool  m_bConnected;						// Tells if there is an active connection or not

// Local variables					
short	m_sSuccess;						// Used to determine if function calls are successful. 
char	m_cTempBuffer[100];				// Stores temporary char array
short	m_sComHandle;					// Handle to communication. Used by virtually every other fnctn
short	m_bServoOn;

double m_pdCommParams[2];				// Holds the communication handle and a flag

// Binding methods
STDMETHOD(OnConstruct)(void);	// Set bindings
STDMETHOD(OnDestruct)(void);	// Delete them

// Override of IMA base components
virtual STDMETHODIMP Load(VARIANT pData);
virtual STDMETHODIMP Save(VARIANT *pData);		// STDMETHODIMP returns an HRESULT (look at a IMA 1.0 component

// Include IMA Component Bindings of type IComponent *
IComponent *m_pIUnkCommunicationParameters;			// Communication parameters

};


	
#endif //__COMMSETUP_H_
