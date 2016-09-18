// Function declarations for CommPort class
// Summer 1996
// Joe Christopher
// MFC parts taken out by Rick Watson 8/5/1997

#include "stdafx.h"
#include "commport.h"

// Constructor
CCommPort::CCommPort( char* Port, ULONG Baud )
{

	// Putting COM port handle creation here
	m_hCom = CreateFile( Port,
			GENERIC_READ | GENERIC_WRITE,
			0,				// comm devices must be opened w/exclusive access
			NULL,			// no security attributes
			OPEN_EXISTING,	// comm devices must use OPEN_EXISTING
			0,				// not overlapped I/O
			NULL			// hTemplate must be NULL for comm devices
			);

	if( m_hCom == INVALID_HANDLE_VALUE)	// Valid comm port handle
	{
		m_dwError = GetLastError();		// Get error
		MessageBeep( MB_OK );
		MessageBeep( MB_OK );
	}
	else
	{
		// GetCommState function retrieves the current control settings for a specified communications device. 
		if(m_bGetComm = GetCommState(m_hCom, &m_dDcb)) // Get comm states into m_dDcb
		{	
			m_dDcb.BaudRate		= Baud;										// User-passed baud rate
			m_dDcb.ByteSize		= 8;										// 8 bits / byte
			m_dDcb.StopBits		= ONESTOPBIT;								// 1 stop bit
			m_dDcb.Parity		= NOPARITY;									// No parity
			m_bSetComm			= SetCommState(m_hCom, (LPDCB) &m_dDcb);	// Set comm port for new settings
		}
		if(m_bGetTime = GetCommTimeouts(m_hCom, &m_ctTimeouts))	// Get comm timeouts into m_ctTimeouts
		{
		/*	m_ctTimeouts.ReadIntervalTimeout			= MAXDWORD;
			m_ctTimeouts.ReadTotalTimeoutMultiplier		= MAXDWORD;
			m_ctTimeouts.ReadTotalTimeoutConstant		= 5000;
			m_ctTimeouts.WriteTotalTimeoutMultiplier	= MAXDWORD;
			m_ctTimeouts.WriteTotalTimeoutConstant		= 5000;*/
		//	m_ctTimeouts.ReadIntervalTimeout			= 100;		// 1 sec between char rxd
			m_ctTimeouts.ReadIntervalTimeout			= 1;		// in order to decrease interval of sample time, change it from 100 to 1 // Li Sun 10/24/03
			m_ctTimeouts.ReadTotalTimeoutMultiplier		= 0;		// No multiplier
			m_bSetTime = SetCommTimeouts( m_hCom, &m_ctTimeouts );	// Set new timeout values

		}
		// Check for failure in getting or setting parameters for comm ports
		// Print appropriate message
		if( !m_bGetComm || !m_bSetComm || !m_bGetTime || !m_bSetTime )	
			MessageBox( NULL,
				"Error initializing comm port",
				NULL,
				MB_ICONEXCLAMATION
				);
	} // end if valid handle

} // end constructor

// Destructor
CCommPort::~CCommPort()
{
	CloseHandle(m_hCom); // Close comm port upon exit
} 

// WriteComm function takes a CString as a parameter and
// writes it as ASCII chars to the comm port
BOOL CCommPort::WriteComm( char* Output )
{
	BOOL result = FALSE;

	// Purge any data contained in the COM device
	result = PurgeComm( 
					m_hCom,				/* handle				*/
					PURGE_TXABORT |		/* terminates write ops */
					PURGE_TXCLEAR |		/* clears output buffer */
					PURGE_RXABORT |		/* terminates read ops  */
					PURGE_RXCLEAR		/* clears input buffer  */
					);
	
	if ( result )
	{
		WriteFile( 
			m_hCom,					/* handle to file			*/
			Output,					/* data buffer				*/
			strlen(Output),			/* number of bytes to write */
			&m_dwNumBytes,			/* num. of bytes written	*/
			NULL					/* overlapped buffer		*/
			);

		ATLTRACE("*-*-*-*-* CCommPort::Num Bytes Sent = %d\n", m_dwNumBytes );

		if ( m_dwNumBytes <= 0 )
			result = FALSE;
	}

	return result;
} 

//  WriteChar function takes a character and waits for its successful transmission
//  Use this when you need to transmit ASCII 0x00 because char* see as NULL char
BOOL CCommPort::WriteChar( char Output )
{
	// Wait for successful transmission
	BOOL result = FALSE;
	result = TransmitCommChar( m_hCom, Output );

	return result;
}


// ReadComm function takes a LPCTSTR pointer as a param
// and reads in from the comm port the specified number of bytes.
BOOL CCommPort::ReadComm( char* Input, ULONG Bytes )
{
	// Read in data
	BOOL result = FALSE;
	result = ReadFile(
			m_hCom,					/* handle to file			*/
			Input,					/* data buffer				*/
			Bytes,					/* number of bytes to write */
			&m_dwNumBytes,			/* num. of bytes written	*/
			NULL					/* overlapped buffer		*/
			);
		
	ATLTRACE("*-*-*-*-* CCommPort::Num Bytes Received = %d\n", m_dwNumBytes );

	if ( m_dwNumBytes <= 0 )
		result = FALSE;

	return result;
} // end ReadComm 