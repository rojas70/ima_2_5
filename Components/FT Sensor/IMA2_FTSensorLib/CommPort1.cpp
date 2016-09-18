// CommPort1.cpp: implementation of the CCommPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommPort1.h"
//////////////////////////////////////////////////////////////////////
// Constructors
//////////////////////////////////////////////////////////////////////

// Default constructor
CCommPort::CCommPort(char* Port, ULONG Baud)
{
	// COMM Port handle creation 
	m_hCom = CreateFile( 
			Port,							/* File Name										*/
			GENERIC_READ | GENERIC_WRITE,	/* Desired Access									*/
			0,								/* Share mode set to exclusive						*/
			NULL,							/* Security attributes								*/
			OPEN_EXISTING,					/* Creation Disposition - always open existing		*/
			0,								/* Flags and attributes	- none						*/
			NULL							/* Template Devices -must be NULL for comm devices	*/
			);

	if (m_hCom == INVALID_HANDLE_VALUE)	// Valid comm port handle
	{
		MessageBox(NULL, "CommPort::CommPort() Error", "Check the string used for a port and the baud rate", MB_OK);
		ATLTRACE("********** Invalid COMM Handle! **********\n");
		m_dwError = GetLastError();						// Get error
	}
	else
	{
		// Get Comm states into m_dDcb
		if(m_bGetComm = GetCommState(m_hCom,&m_dDcb))	
		{
			// Device control block for the port
			m_dDcb.BaudRate			= Baud;						// User-passed baud rate
			m_dDcb.ByteSize			= 8;						// 8 bits / byte
			m_dDcb.StopBits			= ONESTOPBIT;				// 1-stop bit
			m_dDcb.Parity			= NOPARITY;					// No parity
			m_dDcb.fOutxCtsFlow		= FALSE;					// CTS output flow control
			m_dDcb.fOutxDsrFlow		= FALSE;					// DSR output flow control
			m_dDcb.fDtrControl		= DTR_CONTROL_DISABLE;		// DTR flow control type
			m_dDcb.fDsrSensitivity	= FALSE;					// DSR sensitivity
			m_dDcb.fTXContinueOnXoff= TRUE;						// XOff continues Tx
			m_dDcb.fOutX			= FALSE;					// Xon/Xoff out flow control
			m_dDcb.fInX				= FALSE;					// XOn/XOff in flow control
			m_dDcb.fErrorChar		= FALSE;					// Enable error replacement
			m_dDcb.fNull			= FALSE;					// Enable null stripping
			m_dDcb.fRtsControl		= RTS_CONTROL_DISABLE;		// RTS flow control
			m_dDcb.fAbortOnError	= FALSE;					// Abort read/write on error

			m_bSetComm = SetCommState(m_hCom, (LPDCB) &m_dDcb);			// Set comm port for new settings
		}

		// Get comm timeouts into m_ctTimeouts
		if (m_bGetTime = GetCommTimeouts(m_hCom, &m_ctTimeouts))		
		{
			m_ctTimeouts.ReadIntervalTimeout		= 1000;				// 1 sec between char rxd
			m_ctTimeouts.ReadTotalTimeoutConstant	= 1000;				// No multiplier
			m_ctTimeouts.ReadTotalTimeoutConstant	= 1000;				// 
			m_bSetTime = SetCommTimeouts(m_hCom, &m_ctTimeouts);		// Set new timeout values
		}

		// Check for failure in getting or setting parameters for Comm ports
		if (!m_bGetComm || !m_bSetComm || !m_bGetTime || !m_bSetTime)
		{
			MessageBox( NULL, "Error initializing comm port", NULL, MB_OK);
			ATLTRACE("*************** Error Initializing Comm Port! ***************\n");
		}
	}
}		// End of Constructor

CCommPort::~CCommPort()
{
	// Close the handle upon exit
	CloseHandle(m_hCom);
}
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL CCommPort::SetTimeouts(DWORD dwRdInt, DWORD dwRdMul, DWORD dwRdConst)
{
	// Get comm timeouts into m_ctTimeouts
	if(m_bGetTime = GetCommTimeouts(m_hCom, &m_ctTimeouts))	
	{
			m_ctTimeouts.ReadIntervalTimeout = dwRdInt;				// # msec between char rxd
			m_ctTimeouts.ReadTotalTimeoutMultiplier = dwRdMul;
			m_ctTimeouts.ReadTotalTimeoutConstant = dwRdConst;

			m_bSetTime = SetCommTimeouts( m_hCom, &m_ctTimeouts );	// Set new timeout values

	}

	return (m_bGetTime && m_bSetTime);
}

BOOL CCommPort::WriteComm(char *Output, int bytes)
{
	// Write out data
	WriteFile( 
	/*HANDLE hFile,					*/	m_hCom,							   
	/*LPVOID lpBuffer,				*/	Output, 
	/*DWORD nNumberOfBytesToRead,	*/	bytes, 
	/*LPDWORD lpNumberOfBytesRead,	*/	&m_dwNumBytes, 
	/*LPOVERLAPPED lpOverlapped		*/	NULL
			);

	return TRUE;
}

BOOL CCommPort::WriteChar(char Output)
{
	// Wait for successful transition. 
	// Return TRUE when the transmission has succeeded
	while( TransmitCommChar( m_hCom, Output ) != TRUE );

	return TRUE;
}

DWORD CCommPort::ReadComm(char *Input, ULONG Bytes)
{
	// Takes a LPCTSTR pointer & reads from the port the specified number of bytes.
	ReadFile(
	/*HANDLE hFile,					*/	m_hCom,							   
	/*LPVOID lpBuffer,				*/	Input, 
	/*DWORD nNumberOfBytesToRead,	*/	Bytes, 
	/*LPDWORD lpNumberOfBytesRead,	*/	&m_dwNumBytes, 
	/*LPOVERLAPPED lpOverlapped		*/	NULL
			);
	
	return m_dwNumBytes;
}
