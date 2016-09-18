#ifndef _AnalogInputFunctions_
#define _AnalogInputFunctions_

ULONG  lDevNum=0;
long   lDriverHandle;
float  fVoltage[12];

DEVFEATURES     DevFeatures;			// structure for device features
DEVCONFIG_AI    DevCfg;					// structure for DEVCONFIG_AI table
PT_MAIConfig        ptMAIConfig;        // structure for MAIConfig table
PT_MAIVoltageIn     ptMAIVoltageIn;     // structure for MAIVoltageIn table
PT_DeviceGetFeatures  ptDevFeatures;    // structure for DeviceGetFeatures
PT_AIGetConfig  ptAIGetConfig;          // structure for AIGetConfig table
USHORT      usStartChan = 0;            // start channel
USHORT      usNumChan = 12 ;            // Number of channel
USHORT      usGainCode[12];             // varied input range array

void InitAnalogInputs()
{

    //Step 3: Open device

    DRV_DeviceOpen(lDevNum, &lDriverHandle);   
    
    //Step 4: Config device

    ptDevFeatures.buffer = (LPDEVFEATURES)&DevFeatures;
    ptDevFeatures.size = sizeof(DEVFEATURES);
    DRV_DeviceGetFeatures(lDriverHandle,(LPT_DeviceGetFeatures)&ptDevFeatures);

    // configures the gain for the specifed analog input channel

    ptAIGetConfig.buffer = (LPDEVCONFIG_AI)&DevCfg;
    ptAIGetConfig.size = sizeof(DEVCONFIG_AI);
	DRV_AIGetConfig(lDriverHandle,(LPT_AIGetConfig)&ptAIGetConfig);

    // check start and stop channel if expansion board ?

	ptMAIConfig.NumChan   = usNumChan;
	ptMAIConfig.StartChan = usStartChan;
	for (int i=0 ; i< 12 ; i++)
		usGainCode[i] =0; 
	ptMAIConfig.GainArray = (USHORT far *) &usGainCode[usStartChan];
	DRV_MAIConfig(lDriverHandle,(LPT_MAIConfig)&ptMAIConfig);
	ptMAIVoltageIn.NumChan   = usNumChan ;
	ptMAIVoltageIn.StartChan = usStartChan;
	ptMAIVoltageIn.GainArray = (USHORT far *) &usGainCode[usStartChan];
	ptMAIVoltageIn.TrigMode = 0;            // internal trigger
	
	
}

void GetAnalogInputs(float AverageVoltage[])
{
	 // Step 5: Read data
	for(int i=0;i<12;i++)
		AverageVoltage[i] = 0;

	ptMAIVoltageIn.VoltageArray = (FLOAT far *)&fVoltage[usStartChan];
	DRV_MAIVoltageIn(lDriverHandle,(LPT_MAIVoltageIn)&ptMAIVoltageIn);
		
	for( i=0;i<12;i++)
	{
		AverageVoltage[i] = (fVoltage[i] -1.0)/0.2038+1; // 4V / 9.81 / 2
		//printf("Data[%d] = %f\n",i,AverageVoltage[i]);
	}
	 
}

void CloseAnalogInputs()
{
	// Step 7: Close device
    DRV_DeviceClose(&lDriverHandle);	
}

#endif

