// CommPort1.h: interface for the CCommPort class.
//
//				C++ container class to obtain exclusive access to the 
//				Comm. Port ofr simple use such as reading/writing of 
//				ASCII characters. Handles all setup so that the user 
//				can simply call the WriteComm or ReadComm functions to
//				read and write to the Comm. port specified in the constructor.
//
// Author:  Juan Rojas
// Date:	05/2006
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMPORT1_H__52ED6473_DA50_401A_A45F_4AEC610C8E4B__INCLUDED_)
#define AFX_COMMPORT1_H__52ED6473_DA50_401A_A45F_4AEC610C8E4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommPort  
{
public:
	DWORD ReadComm(char* Input, ULONG Bytes);
	BOOL WriteChar(char Output);
	BOOL WriteComm(char *Output, int bytes);
	BOOL SetTimeouts(DWORD dwRdInt, DWORD dwRdMul, DWORD dwRdConst);

	CCommPort(char * Port="\\COM2", ULONG Baud=38400 ); // Constructor with default COM2, 9600 baud
	virtual ~CCommPort();

protected:
	// Variables used in setting up and obtaining COMM port info

DWORD			m_dwError;
DWORD			m_dwNumBytes;
COMMTIMEOUTS	m_ctTimeouts;

BOOL			m_bGetComm;	// Booleans for evaluating successful setup 
BOOL			m_bSetComm; // of COMM port parameters such as baud, parity
BOOL			m_bGetTime;	// stop bits, timeouts, byte size, etc.
BOOL			m_bSetTime;	//

DCB				m_dDcb;		// Device control block for the port
HANDLE			m_hCom;		// Handle for the comm port	

};

#endif // !defined(AFX_COMMPORT1_H__52ED6473_DA50_401A_A45F_4AEC610C8E4B__INCLUDED_)
