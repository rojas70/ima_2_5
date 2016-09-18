#ifndef _AnalogOutputFunctions_h
#define _AnalogOutputFunctions_h

#include <math.h>

ULONG  lDevNumOutput =1 ;
long   lDriverHandleOutput;
PT_AOVoltageOut tAOVoltageOut;
long lIndexCounterBuffer1=0,lIndexCounterBuffer2=0;
//DWORD  dwErrCde;
extern float  AO[4];

void InitAnalogOutputs()
{
	//Step : Open device
    DRV_DeviceOpen(lDevNumOutput, &lDriverHandleOutput);     

    // Step : Enable synchronous output by DRV_EnableSyncAO
	DRV_EnableSyncAO(lDriverHandleOutput, 1);
}

void SetAnalogOutput(float fVoltageBuf[])
{ 
	// Step : Output values by DRV_AOCurrentOut or DRV_AOVoltageOut
	// voltage output
	if (fVoltageBuf[0]<=0.0) 
		fVoltageBuf[0] = 0.0 ;

	if (fVoltageBuf[1]<=0.0) 
		fVoltageBuf[1] = 0.0 ;

	if (fVoltageBuf[2]<=0.0) 
		fVoltageBuf[2] = 0.0 ;

	if (fVoltageBuf[3]<=0.0) 
		fVoltageBuf[3] = 0.0 ;
	
	if ( (fVoltageBuf[0]<=8) && (fVoltageBuf[1]<=8) && (fVoltageBuf[2]<=8) && (fVoltageBuf[3]<=8) )

		for (int nChan = 0; nChan < 4; nChan ++)
		{
			tAOVoltageOut.chan = nChan;
			tAOVoltageOut.OutputValue = fVoltageBuf[nChan];
			DRV_AOVoltageOut(lDriverHandleOutput,&tAOVoltageOut);		
		}
	else
	printf("Too Maniac Pressure!!??ppppppppppppppppppppppppppppppppppppppppppppp\n");
	// Step : Synchronous output by DRV_WriteSyncAO
	DRV_WriteSyncAO(lDriverHandleOutput);
//	printf("Output1: %f, Output2: %f, Output3: %f,Output4: %f \n",fVoltageBuf[0],fVoltageBuf[1],fVoltageBuf[2],fVoltageBuf[3]);

}

void CloseAnalogOutputs()
{
	  // Step : Disable synchronous output by DRV_EnableSyncAO
    DRV_EnableSyncAO(lDriverHandleOutput, 0);
    
    // Step : Close device
    DRV_DeviceClose(&lDriverHandleOutput);

}

void GoHomeMuscle()
{
	AO[0] = 5.0f; // 1. kas
	AO[1] = 5.6f;	// 2. kas
	AO[2] = 5.6f; // 3. kas
	AO[3] = 5.0f;
						
	SetAnalogOutput(AO);Sleep(2000);
	
	EP_ClearENCCounter(3,CARD_INDEX);
	EP_ClearENCCounter(4,CARD_INDEX);
/*
	int i = 0,k=1,c=0;
	bool flag = true;

	SetAnalogOutput(AO);

	startTime=clock();while(clock()-startTime <2000){}

	EP_ClearENCCounter(3,CARD_INDEX);
	EP_ClearENCCounter(4,CARD_INDEX);

	while((lIndexCounterBuffer1 == 0 ) || (lIndexCounterBuffer2 == 0 ) )
	{
		// Emergency Stop Check
		EP_GetEmgcStopStatus(&wEmgc,CARD_INDEX);
		if ( wEmgc ==1)	break;

		printf("---------------------------------------\n");
								
		EP_GetENCIndexStatus(&wStatus1,3,CARD_INDEX);
		EP_GetENCIndexStatus(&wStatus2,4 ,CARD_INDEX);
		CounterRead();

		if(wStatus1 == 0)
			lIndexCounterBuffer1 = lCounter[3];
		if(wStatus2 == 0)
			lIndexCounterBuffer2 = lCounter[4];
			
		if(c<50 )
		{
			AO[0] -= 0.01f; // 1. kas
			AO[1] += 0.01f;	// 2. kas					
			AO[2] += 0.01f; // 3. kas
			AO[3] -= 0.01f; // 4. kas
			c+=1;
		}
		/*
		if(c>=50 && c<160 )
		{
			AO[0] -= 0.005f; // 1. kas
			AO[1] += 0.005f;	// 2. kas
			AO[2] += 0.005f; // 3. kas
			AO[3] -= 0.005f; // 4. kas
			c+=1;
		}
		*/
		/*
		SetAnalogOutput(AO);
			
		startTime=clock();while(clock()-startTime <200){}
			
		if(c==50)	
		{	c=0;
			AO[0] = 4.1f; // 1. kas
			AO[1] = 4.0f;	// 2. kas					
			AO[2] = 4.0f; // 3. kas
			AO[3] = 4.1f; // 4. kas
		}
		
				
		printf("Status1 : %d  Status2: %d \n",wStatus1,wStatus2);
		printf(" lIndexCounterBuffer1: %d  lIndexCounterBuffer2: %d \n",lIndexCounterBuffer1,lIndexCounterBuffer2);
		//printf("%d",c);	

	}
/*
	AO[0] = 4.0f; // 1. kas
	AO[1] = 4.0f;	// 2. kas
	AO[2] = 4.0f; // 3. kas
	AO[3] = 4.0f;
						
	SetAnalogOutput(AO);
*/
/*
	while(( abs(lCounter[3] - lIndexCounterBuffer1) >= 2 ) || ( abs(lCounter[4] - lIndexCounterBuffer2) >= 2 ) )
	{	
		// Emergency Stop Check
		EP_GetEmgcStopStatus(&wEmgc,CARD_INDEX);
		if ( wEmgc ==1)	break;
			printf("***************************************\n");
				
		if( lCounter[3] - lIndexCounterBuffer1 < 0 )
		{
			AO[0] -= 0.003f; // 1. kas
			AO[1] += 0.003f; // 2. kas
			AO[2] += 0.003f; // 3. kas
			AO[3] -= 0.003f; // 4. kas
		}
		else
		{
			AO[0] += 0.003f; // 1. kas
			AO[1] -= 0.003f; // 2. kas
			AO[2] -= 0.003f; // 3. kas
			AO[3] += 0.003f; // 4. kas
		}
		if( lCounter[4] - lIndexCounterBuffer2  < 0 )
		{
			AO[0] -= 0.003f; // 1. kas
			AO[1] += 0.003f; // 2. kas
			AO[2] -= 0.003f; // 3. kas
			AO[3] += 0.003f; // 4. kas
		}
		else
		{
			AO[0] += 0.003f; // 1. kas
			AO[1] -= 0.003f; // 2. kas
			AO[2] += 0.003f; // 3. kas
			AO[3] -= 0.003f; // 4. kas
		}

		SetAnalogOutput(AO);

		startTime=clock();while(clock()-startTime <200){}
				
		CounterRead();
		printf(" lIndexCounterBuffer1: %d  lIndexCounterBuffer2: %d \n",lIndexCounterBuffer1,lIndexCounterBuffer2);			
	}
	*/
}	

#endif