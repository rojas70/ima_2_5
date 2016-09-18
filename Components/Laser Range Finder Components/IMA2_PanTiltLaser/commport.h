// C++ container classes for obtaining exclusive access 
//  to the comm port for simple use such as reading/writing 
//  ASCII characters. Handles all setup so the user 
//  simply calls the WriteComm or ReadComm functions to read 
//  and write to comm port specified in the constructor.
//************
// Summer 1996
// Joe Christopher
// MFC parts taken out by Rick Watson 8/5/1997
//************

// Standard library
#include	<stdlib.h>

class CCommPort
{
public:
	CCommPort( char* Port="\\COM3" , ULONG  Baud=9600 );	// Constructor with default COM2, 9600 baud
	~CCommPort();				
	BOOL WriteComm( char* Output);
	BOOL WriteChar( char Output );
	BOOL ReadComm( char* Input, ULONG Bytes );

protected:
	// Vars. used in setting up and obtaining COMM port
	DWORD m_dwError;		
	DWORD m_dwNumBytes;
	COMMTIMEOUTS m_ctTimeouts;

	BOOL	m_bGetComm;	// Booleans for evaluating successful setup 
	BOOL	m_bSetComm;	// of COMM port parameters such as baud, parity
	BOOL	m_bGetTime;	// stop bits, timeouts, byte size, etc.
	BOOL	m_bSetTime;	//

	DCB		m_dDcb;		// device control block for the port
	HANDLE	m_hCom;		// handle for the comm port	

 };
