#ifndef __VITAL_H
#define __VITAL_H


// Number of axes in system 
#define VITAL_MAX_AXIS 8

// flags defined bit-exclusive for OR'ing if board can do multiple ways
#define EXT_ENCODER_INDEX_MODEL_MANUAL 0x00000001
#define EXT_ENCODER_INDEX_MODEL_AUTO   0x00000002

long __stdcall vitalInit(void);								// Returns number of boards in system
long __stdcall vitalSelectBoard( long BoardID );				// 0,1,2,3...15

long __stdcall vitalAioReset(void);								// Set all DACs to zero
long __stdcall vitalQuit(void);

// Encoder counter Calls
long __stdcall vitalGetMaxEncoders(void);						// Unsure
long __stdcall vitalEncoderRead(int axis, long * pCounts);		// Reads single encoder
long __stdcall vitalResetCounter( int nAxis );					// Resets the zero position of a given encoder. 

// Encoder Index Model Calls - Internal 
long __stdcall vitalReadIndexLevel(int nAxis, int * flag);
long __stdcall vitalEncoderIndexModel(void);
long __stdcall vitalEncoderSetIndexModel(unsigned int model);
long __stdcall vitalEncoderResetIndex(int nAxis);
long __stdcall vitalEncoderReadLatch(int nAxis, int * flag);

]// Voltage (Analog) Calls
long __stdcall vitalDacNum(void);								// Total number of Digital-Analog channels in a board
long __stdcall vitalDacWrite(int nAxis, double volts);			// Write voltage to a single channel in a board
long __stdcall vitalDacWriteAll(int max, double * volts);		// Write a volage to all channels in a board

// Read voltage
long __stdcall vitalReadAnalogInputs(unsigned long nBank, double *value);	// Read analog voltages, 4 values at a time per bank (2 banks in one board. Index 0 - 1)

// Digital Input/Output functionality not used in current board
long __stdcall vitalDioWrite(int index, int value);
long __stdcall vitalDioReset(void);					// Turn off all outputs (open collector)
long __stdcall vitalDioCheck(int index, int *value);
long __stdcall vitalDioRead(int index, int *value);

// Read or Write Directly from/to the 32bit Registers on the MOTENC Board
long __stdcall vitalReadReg(int nReg, long * pRegData);
long __stdcall vitalWriteReg(int nReg, long RegData);

// Analog Binary Data
long __stdcall vitalAdcReadBinary(unsigned long nBank, int * AdcBinaryData);
long __stdcall vitalDacWriteBinary(int nAxis, int BinData);


#endif /* __VITAL_H */

