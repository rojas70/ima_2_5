// WinShell_MotomanLib.cpp : Defines the entry point for the console application.
//
// Motoman declarations
#include "stdafx.h"
#include <iostream>
#include <direct.h>
#include <windows.h>
#include "O:\Include\Motoman\MotoCom.h"	
using namespace std;

// Definitions
#define SERIAL		0x01						// Defines communication type (serial or ethernet). See BscOpen 
#define COM1		1							// Define port number
#define BRATE		9600						// Define baud rate
#define EVEN		2							// Define parity scheme
#define EIGHT_BIT	8							// Define data length for communication transmission
#define ONE_BIT		0							// Define data length for stop bit
												// !! For more on this see: Data Transmission Manual p. 37/116
#define NUM_AXES	6


//------------------------------------------
// Function headers
void Connect();
void Disconnect(){}
void Move_Incremental() {}
//------------------------------------------

int main()
{
	printf("\nThis project control the HP3JC manipulator.\n");
	printf("\nThe different functions can connect the robot, move it, read alarms and status, and do jobs.\n");
	
	// Assign local variables
	short m_sChoice = 0;

		// Get input for arm 
	printf("\n\nChoose one of the following options: \n");
	printf("1. Connect to the robot\n");
	printf("2. Disconnect from the robot\n");
	printf("3. Motion - Move robot with incremental motion\n");

	cin >> m_sChoice;
	cout << m_sChoice << endl;

	switch (m_sChoice)
	{

	case 1:
	   Connect(); 
	   break;

	case 2:
	   Disconnect(); 
	   break;

	case 3:
		Move_Incremental();
		break;

	default:
		printf("\nThat choice is not valid\n");

	}

	cin.ignore(256,'\n');
	cout << "\nPress enter to EXIT..." << endl;
	cin.get();
	return 0;
}

void Connect(void)
{
	// Local variables
	short	m_sComType;						// Stores communication type	(Serial or Ethernet)
	short	m_sPort;						// Stores port number			(Communication port number 1:COM1,2:COM2,3:COM3,4:COM4,...,255:COM255)
	short	m_dwBaud;						// Stores baud rate				(Baud rate 150, 300, 600, 1200, 2400, 4800, 9600, 19200)
	short	m_sParity;						// Stores parity				(Parity 0: None, 1: Odd, 2: Even)
	short	m_sDataLen;						// Stores data bits				(Data length 7: 7 bits, 8: 8 bits)
	short	m_sStopBit;						// Stores stop bits				(Stop bit 0: 1 bit, 1: 1.5 bits, 2: 2 bits)
	bool	m_bConnected;					// Tells if there is an active connection or not				
	short	m_sSuccess;						// Used to determine if function calls are successful. 
	char	m_cTempBuffer[100];				// Stores temporary char array
	short	m_sComHandle;					// Handle to communication. Used by virtually every other fnctn
	short	m_bServoOn;
	double  m_pdDesPos[12];

	m_sComType	= SERIAL;
	m_sPort		= COM1;							
	m_dwBaud	= BRATE;							
	m_sParity	= EVEN;						
	m_sDataLen	= EIGHT_BIT;							
	m_sStopBit	= ONE_BIT;						
	m_sSuccess	= 0;
	m_bConnected= 0;
	m_sComHandle= 0;
	m_bServoOn	= 0;
	m_sComHandle=-1;

	for (int i=0;i<NUM_AXES*2;i++)
		m_pdDesPos[i]=0;

	m_pdDesPos[0]=20.0;
	
	// TODO:

	// Create a string with the path where the local .dll is located.
	strcpy(m_cTempBuffer,"O:\\Components\\ArmComponents\\IMA2_Motoman\\Winshell_MotomanLib"); 
	
	// If we have not connected before, proceed:
	if (m_bConnected == 0)
	{
		try {
			// **Call BscOpen**
			m_sComHandle = BscOpen(m_cTempBuffer, m_sComType);

			
			if (m_sComHandle != -1)			// BscOpen: success is other than -1, error is -1
			{
				// For Serial Communications
				// **Call BscSetCom**
				if(m_sComType == 1)
					m_sSuccess=BscSetCom(m_sComHandle,m_sPort,m_dwBaud,m_sParity,m_sDataLen,m_sStopBit);
				
				// For Ethernet Communications
				//else
					//Set Ethernet Conditions (currently has not been set-up. Feb 08)
					//m_sSuccess=BscSetEther(m_sComHandle,cIpAddr,sEtherMode,m_hWnd);
			}
			else
			{
				printf("\n **BscOpen failed**\n");
				return;
			}

			
			if(m_sSuccess != 0)				// BscSetCom: success is 1, error is 0
			{	
				// **Call BscSetCond**
				m_sSuccess = BscSetCondBSC(m_sComHandle,3000,20000,3,3); // Could be 10000, 30000,3,3
				
				
				if (m_sSuccess != -1)		// BscSetCondBSC: success is 0, error is -1
				{	
					// ***Call BscConnect***
					// Connect communication lines
					m_sSuccess = BscConnect(m_sComHandle);

					// If Connection fails:
					if(m_sSuccess == 0)
					{
						printf("\n **BscSetCondBSC failed**\n");
						return;
					}

					// If communication succeeds
					else
					{
						m_bConnected = true;
						printf("\n **Serial Connect Succeeded**\n");

						// test
						m_sSuccess = BscServoOn(m_sComHandle);
						m_sSuccess = BscImov(m_sComHandle,"V",0.23,"ROBOT",0,m_pdDesPos);

					}
				}


				else	// BscSetCom
				{
					printf("\n **BscSetCom failed**\n");
					return;
				}
				
			}

			// Set serial communication or ethernet communication to failure
			else	// BscOpen
			{
				printf("\n **BscOpen failed**\n");
				return;
			}

			}	// End try

		catch(char *)	// need to change this paramter
		{
			printf("\nBscOpen threw an exception\n");
		}

	}	// End m_bConnected

	return;
}
