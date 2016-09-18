#ifndef _SampleAndTrainAll_h
#define _SampleAndTrainAll_h

extern double incrementalVoltage;
extern double incrementalVoltage1;

void SampleForNeuralTrain01Angle0(int leftright)
{
	int count=0,numb=0;

	InitializeCards();
	if (leftright == 1)	InitializeLeftValves(); else InitializeRightValves(); 

	// Precise Sampling Time Initialization		
	LARGE_INTEGER ticksPerSecond,start_ticks, end_ticks, cputime,tick;
	if (!QueryPerformanceFrequency(&ticksPerSecond))
		if (!QueryPerformanceCounter(&tick) ) 
			printf("no go counter not installed");

	FILE *neuralDataForward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataForward = fopen("..\\TrainFiles\\LeftNeuralDataForward01.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataForward = fopen("..\\TrainFiles\\RightNeuralDataForward01.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	
	FILE *neuralDataBackward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\LeftNeuralDataBackward01.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\RightNeuralDataBackward01.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");

	// Homing & Reset Encoders Left
	Sleep(3000);

	if (leftright == 1)	ResetLeftEncoders(); else ResetRightEncoders();	
	if (leftright == 1) vitalSelectBoard(0); else vitalSelectBoard(1);

	//Control loop
	printf("Control Loop Starts!!\n");
	
	while(count<300 && !kbhit())
	{
		QueryPerformanceCounter(&start_ticks);

		// Update the voltage output references
        if( count < 95)
			incrementalVoltage = -0.01;
		if( count >= 95 && count <= 230)
			incrementalVoltage = 0.01;
		if( count > 230 )
			incrementalVoltage = -0.01;

		if (leftright == 1)
		{
			leftValvesOutputs[0] = leftValvesOutputs[0]-incrementalVoltage;
			leftValvesOutputs[1] = leftValvesOutputs[1]+incrementalVoltage;			
			SetLeftArmPressures();
		}else{
			rightValvesOutputs[0] = rightValvesOutputs[0]+incrementalVoltage;
			rightValvesOutputs[1] = rightValvesOutputs[1]-incrementalVoltage;			
			SetRightArmPressures();
		}

		// Sleep 100 ms.   
		QueryPerformanceCounter(&end_ticks); //printf("time pass:%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float) 800)
		QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;	
		
		if (leftright == 1)	{ReadLeftEncoders();RealLeftAngles();} else {ReadRightEncoders();RealRightAngles();}
		
		// Write voltage output references to file
		// In the right arm this can be changed
        if( incrementalVoltage >= 0 && leftright == 1)
			fprintf(neuralDataForward,"%.5f %.3f\n", leftValvesOutputs[1]-InitialleftValvesOutputs[1], leftAngles[0]);
		if( incrementalVoltage < 0 && leftright == 1)
			fprintf(neuralDataBackward,"%.5f %.3f\n", leftValvesOutputs[1]-InitialleftValvesOutputs[1], leftAngles[0]);

		// In the right arm, it is the opposite of the left arm so inside positive
		if( incrementalVoltage <= 0 && leftright == 0)
			fprintf(neuralDataForward,"%.5f %.3f\n",rightValvesOutputs[1]-InitialrightValvesOutputs[1], rightAngles[0]);
		if( incrementalVoltage > 0 && leftright == 0)
			fprintf(neuralDataBackward,"%.5f %.3f\n",rightValvesOutputs[1]-InitialrightValvesOutputs[1], rightAngles[0]);

		count++;
	}
	printf("Control Loop End\n");
	
	CloseValves();Sleep(500);

	//clean up on exit
	vitalQuit();Sleep(500);
	
	fclose(neuralDataForward);fclose(neuralDataBackward);
}

void SampleForNeuralTrain23Angle1(int leftright){
	int count=0,numb=0;

	InitializeCards();
	if (leftright == 1)	InitializeLeftValves(); else InitializeRightValves(); 

	// Precise Sampling Time Initialization		
	LARGE_INTEGER ticksPerSecond,start_ticks, end_ticks, cputime,tick;
	if (!QueryPerformanceFrequency(&ticksPerSecond))
		if (!QueryPerformanceCounter(&tick) ) 
			printf("no go counter not installed");

	FILE *neuralDataForward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataForward = fopen("..\\TrainFiles\\LeftNeuralDataForward23.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataForward = fopen("..\\TrainFiles\\RightNeuralDataForward23.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	
	FILE *neuralDataBackward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\LeftNeuralDataBackward23.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\RightNeuralDataBackward23.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");

	// Homing & Reset Encoders Left
	Sleep(3000);

	if (leftright == 1)	ResetLeftEncoders(); else ResetRightEncoders();	
	if (leftright == 1) vitalSelectBoard(0); else vitalSelectBoard(1);

	//Control loop
	printf("Control Loop Starts!!\n");
	
	while(count<550 && !kbhit())
	{
		QueryPerformanceCounter(&start_ticks);

		// Update the voltage output references
        if( count < 130)
			incrementalVoltage = 0.01;
		if( count >= 130 && count <= 390)
			incrementalVoltage = -0.01;
		if( count > 390 )
			incrementalVoltage = 0.01;

		if (leftright == 1)
		{
			leftValvesOutputs[2] = leftValvesOutputs[2]-incrementalVoltage;
			leftValvesOutputs[3] = leftValvesOutputs[3]+incrementalVoltage;		
			SetLeftArmPressures();
		}else{
			rightValvesOutputs[2] = rightValvesOutputs[2]-incrementalVoltage;
			rightValvesOutputs[3] = rightValvesOutputs[3]+incrementalVoltage;			
			SetRightArmPressures();
		}

		// Sleep 100 ms.   
		QueryPerformanceCounter(&end_ticks); //printf("time pass:%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
		
		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float) 800)
		QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;	
		
		if (leftright == 1)	{ReadLeftEncoders();RealLeftAngles();} else {ReadRightEncoders();RealRightAngles();}

		// Write voltage output references to file
		// Update the voltage output references
        if( incrementalVoltage <= 0 && leftright == 1 )
			fprintf(neuralDataForward,"%.5f %.3f\n", leftValvesOutputs[2]-InitialleftValvesOutputs[2], leftAngles[1]);
		if( incrementalVoltage > 0 && leftright == 1 )
			fprintf(neuralDataBackward,"%.5f %.3f\n", leftValvesOutputs[2]-InitialleftValvesOutputs[2], leftAngles[1]);

		// Update the voltage output references
        if( incrementalVoltage <= 0 && leftright == 0 )
			fprintf(neuralDataForward,"%.5f %.3f\n", rightValvesOutputs[2]-InitialrightValvesOutputs[2], rightAngles[1]);
		if( incrementalVoltage > 0 && leftright == 0 )
			fprintf(neuralDataBackward,"%.5f %.3f\n", rightValvesOutputs[2]-InitialrightValvesOutputs[2], rightAngles[1]);

		count++;
	}
	printf("Control Loop End\n");
	
	CloseValves();
	Sleep(500);

	//clean up on exit
	vitalQuit();
	Sleep(500);
	
	fclose(neuralDataForward);
	fclose(neuralDataBackward);
}

void SampleForNeuralTrain4567Angle2(int leftright){
	int count=0,numb=0;

	InitializeCards();
	if (leftright == 1)	InitializeLeftValves(); else InitializeRightValves(); 

	// Precise Sampling Time Initialization		
	LARGE_INTEGER ticksPerSecond,start_ticks, end_ticks, cputime,tick;
	if (!QueryPerformanceFrequency(&ticksPerSecond))
		if (!QueryPerformanceCounter(&tick) ) 
			printf("no go counter not installed");

	FILE *neuralDataForward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataForward = fopen("..\\TrainFiles\\LeftNeuralDataForward4567Angle2.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataForward = fopen("..\\TrainFiles\\RightNeuralDataForward4567Angle2.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	
	FILE *neuralDataBackward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\LeftNeuralDataBackward4567Angle2.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\RightNeuralDataBackward4567Angle2.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");

	// Homing & Reset Encoders Left
	Sleep(3000);

	if (leftright == 1)	ResetLeftEncoders(); else ResetRightEncoders();	
	if (leftright == 1) vitalSelectBoard(0); else vitalSelectBoard(1);

	//Control loop
	printf("Control Loop Starts!!\n");
	
	while(count<420 && !kbhit())
	{
		QueryPerformanceCounter(&start_ticks);

		// Update the voltage output references
        if( count < 130)
			incrementalVoltage = 0.01;
		if( count >= 130 && count <= 340)
			incrementalVoltage = -0.01;
		if( count > 340 )
			incrementalVoltage = 0.01;

		if (leftright == 1)
		{
			leftValvesOutputs[4] = leftValvesOutputs[4]+incrementalVoltage;
			leftValvesOutputs[5] = leftValvesOutputs[5]-incrementalVoltage;			
			leftValvesOutputs[6] = leftValvesOutputs[6]-incrementalVoltage;
			leftValvesOutputs[7] = leftValvesOutputs[7]+incrementalVoltage;			
			SetLeftArmPressures();
		}else{
			rightValvesOutputs[4] = rightValvesOutputs[4]+incrementalVoltage;
			rightValvesOutputs[5] = rightValvesOutputs[5]-incrementalVoltage;			
			rightValvesOutputs[6] = rightValvesOutputs[6]-incrementalVoltage;
			rightValvesOutputs[7] = rightValvesOutputs[7]+incrementalVoltage;					
			SetRightArmPressures();
		}

		// Sleep 100 ms.   
		QueryPerformanceCounter(&end_ticks); //printf("time pass:%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
		
		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float) 800)
		QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;	

		if (leftright == 1)	{ReadLeftEncoders();RealLeftAngles();} else {ReadRightEncoders();RealRightAngles();}

		// Write voltage output references to file
		// Update the voltage output references
        if( incrementalVoltage > 0 && leftright == 1)
			fprintf(neuralDataForward,"%.5f %.3f\n", -leftValvesOutputs[5]+InitialleftValvesOutputs[5], leftAngles[2]);
		if( incrementalVoltage < 0 && leftright == 1)
			fprintf(neuralDataBackward,"%.5f %.3f\n",-leftValvesOutputs[5]+InitialleftValvesOutputs[5], leftAngles[2]);

		if( incrementalVoltage > 0 && leftright == 0)
			fprintf(neuralDataForward,"%.5f %.3f\n", -rightValvesOutputs[5]+InitialrightValvesOutputs[5], rightAngles[2]);
		if( incrementalVoltage < 0 && leftright == 0)
			fprintf(neuralDataBackward,"%.5f %.3f\n",-rightValvesOutputs[5]+InitialrightValvesOutputs[5], rightAngles[2]);

		count++;
	}
	printf("Control Loop End\n");
	
	CloseValves();
	Sleep(500);

	//clean up on exit
	vitalQuit();
	Sleep(500);
	
	fclose(neuralDataForward);
	fclose(neuralDataBackward);
}

void SampleForNeuralTrain4567Angle3(int leftright){
	int count=0,numb=0;

	InitializeCards();
	if (leftright == 1)	InitializeLeftValves(); else InitializeRightValves(); 

	// Precise Sampling Time Initialization		
	LARGE_INTEGER ticksPerSecond,start_ticks, end_ticks, cputime,tick;
	if (!QueryPerformanceFrequency(&ticksPerSecond))
		if (!QueryPerformanceCounter(&tick) ) 
			printf("no go counter not installed");

	FILE *neuralDataForward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataForward = fopen("..\\TrainFiles\\LeftNeuralDataForward4567Angle3.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataForward = fopen("..\\TrainFiles\\RightNeuralDataForward4567Angle3.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	
	FILE *neuralDataBackward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\LeftNeuralDataBackward4567Angle3.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\RightNeuralDataBackward4567Angle3.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");

	// Homing & Reset Encoders Left
	Sleep(3000);

	if (leftright == 1)	ResetLeftEncoders(); else ResetRightEncoders();	
	if (leftright == 1) vitalSelectBoard(0); else vitalSelectBoard(1);

	//Control loop
	printf("Control Loop Starts!!\n");
	
	while(count<280 && !kbhit())
	{
		QueryPerformanceCounter(&start_ticks);

		// Update the voltage output references
        if( count < 60)
			incrementalVoltage = 0.01;
		if( count >= 60 && count <= 170)
			incrementalVoltage = -0.01;
		if( count > 170 )
			incrementalVoltage = 0.01;

		if (leftright == 1)
		{
			leftValvesOutputs[4] = leftValvesOutputs[4]-incrementalVoltage;
			leftValvesOutputs[5] = leftValvesOutputs[5]-incrementalVoltage;			
			leftValvesOutputs[6] = leftValvesOutputs[6]+incrementalVoltage;
			leftValvesOutputs[7] = leftValvesOutputs[7]+incrementalVoltage;				
			SetLeftArmPressures();
		}else{
			rightValvesOutputs[4] = rightValvesOutputs[4]-incrementalVoltage;
			rightValvesOutputs[5] = rightValvesOutputs[5]-incrementalVoltage;			
			rightValvesOutputs[6] = rightValvesOutputs[6]+incrementalVoltage;
			rightValvesOutputs[7] = rightValvesOutputs[7]+incrementalVoltage;					
			SetRightArmPressures();
		}
		// Sleep 100 ms.   
		QueryPerformanceCounter(&end_ticks); //printf("time pass:%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
		
		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float) 800)
			QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;	
	
		if (leftright == 1)	{ReadLeftEncoders();RealLeftAngles();} else {ReadRightEncoders();RealRightAngles();}

		// Write voltage output references to file		
		if( count > 60 ){
			// Update the voltage output references
			if( incrementalVoltage < 0 && leftright == 1)
				fprintf(neuralDataForward,"%.5f %.3f\n", leftValvesOutputs[6]-InitialleftValvesOutputs[6], leftAngles[3]);
			if( incrementalVoltage > 0 && leftright == 1)
				fprintf(neuralDataBackward,"%.5f %.3f\n", leftValvesOutputs[6]-InitialleftValvesOutputs[6], leftAngles[3]);
			if( incrementalVoltage > 0 && leftright == 0)
				fprintf(neuralDataForward,"%.5f %.3f\n", rightValvesOutputs[6]-InitialrightValvesOutputs[6], rightAngles[3]);
			if( incrementalVoltage < 0 && leftright == 0)
				fprintf(neuralDataBackward,"%.5f %.3f\n", rightValvesOutputs[6]-InitialrightValvesOutputs[6], rightAngles[3]);
		}
		count++;
	}

	printf("Control Loop End\n");
	
	CloseValves();
	Sleep(500);

	//clean up on exit
	vitalQuit();
	Sleep(500);
	
	fclose(neuralDataForward);
	fclose(neuralDataBackward);
}

void SampleForNeuralTrain891011Angle4(int leftright){
	int count=0,numb=0;

	InitializeCards();
	if (leftright == 1)	InitializeLeftValves(); else InitializeRightValves(); 

	// Precise Sampling Time Initialization		
	LARGE_INTEGER ticksPerSecond,start_ticks, end_ticks, cputime,tick;
	if (!QueryPerformanceFrequency(&ticksPerSecond))
		if (!QueryPerformanceCounter(&tick) ) 
			printf("no go counter not installed");

	FILE *neuralDataForward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataForward = fopen("..\\TrainFiles\\LeftNeuralDataForward891011Angle4.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataForward = fopen("..\\TrainFiles\\RightNeuralDataForward891011Angle4.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	
	FILE *neuralDataBackward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\LeftNeuralDataBackward891011Angle4.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\RightNeuralDataBackward891011Angle4.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");

	// Homing & Reset Encoders Left
	Sleep(3000);

	if (leftright == 1)	ResetLeftEncoders(); else ResetRightEncoders();	
	if (leftright == 1) vitalSelectBoard(0); else vitalSelectBoard(1);

	//Control loop
	printf("Control Loop Starts!!\n");

	while(count<500 && !kbhit())
	{
		QueryPerformanceCounter(&start_ticks);

		// Update the voltage output references
        if( count < 100)
			incrementalVoltage = 0.01;
		if( count >= 100 && count <= 300)
			incrementalVoltage = -0.01;
		if( count > 300 )
			incrementalVoltage = 0.01;

		if (leftright == 1)
		{
			leftValvesOutputs[8] = leftValvesOutputs[8]-incrementalVoltage;
			leftValvesOutputs[9] = leftValvesOutputs[9]+incrementalVoltage;
			leftValvesOutputs[10] = leftValvesOutputs[10]-incrementalVoltage;
			leftValvesOutputs[11] = leftValvesOutputs[11]+incrementalVoltage;			
			SetLeftArmPressures();
		}else{
			rightValvesOutputs[8] = rightValvesOutputs[8]-incrementalVoltage;
			rightValvesOutputs[9] = rightValvesOutputs[9]+incrementalVoltage;
			rightValvesOutputs[10] = rightValvesOutputs[10]-incrementalVoltage;
			rightValvesOutputs[11] = rightValvesOutputs[11]+incrementalVoltage;
			SetRightArmPressures();
		}

		// Sleep 100 ms.   
		QueryPerformanceCounter(&end_ticks); //printf("time pass:%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
		
		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float) 800)
		QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;	
		
		if (leftright == 1)	{ReadLeftEncoders();RealLeftAngles();} else {ReadRightEncoders();RealRightAngles();}

		// Write voltage output references to file
		if( count > 100 && leftright == 1){
			// Update the voltage output references
			if( incrementalVoltage < 0 )
				fprintf(neuralDataForward,"%.5f %.3f\n",  -leftValvesOutputs[10]+InitialleftValvesOutputs[10], leftAngles[4]);
			if( incrementalVoltage > 0 )
				fprintf(neuralDataBackward,"%.5f %.3f\n", -leftValvesOutputs[10]+InitialleftValvesOutputs[10], leftAngles[4]);
		}
		if( count > 100 && leftright == 0){
			// Update the voltage output references
			if( incrementalVoltage < 0 )
				fprintf(neuralDataForward,"%.5f %.3f\n",  -rightValvesOutputs[10]+InitialrightValvesOutputs[10], rightAngles[4]);
			if( incrementalVoltage > 0 )
				fprintf(neuralDataBackward,"%.5f %.3f\n", -rightValvesOutputs[10]+InitialrightValvesOutputs[10], rightAngles[4]);
		}
		count++;
	}

	printf("Control Loop End\n");
	
	CloseValves();
	Sleep(500);

	//clean up on exit
	vitalQuit();
	Sleep(500);
	
	fclose(neuralDataForward);
	fclose(neuralDataBackward);
}

void SampleForNeuralTrain891011Angle5(int leftright){
	int count=0,numb=0;

	InitializeCards();
	if (leftright == 1)	InitializeLeftValves(); else InitializeRightValves(); 

	// Precise Sampling Time Initialization		
	LARGE_INTEGER ticksPerSecond,start_ticks, end_ticks, cputime,tick;
	if (!QueryPerformanceFrequency(&ticksPerSecond))
		if (!QueryPerformanceCounter(&tick) ) 
			printf("no go counter not installed");

	FILE *neuralDataForward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataForward = fopen("..\\TrainFiles\\LeftNeuralDataForward891011Angle5.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataForward = fopen("..\\TrainFiles\\RightNeuralDataForward891011Angle5.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	
	FILE *neuralDataBackward;
	if (leftright == 1) //--> 1 corresponds to left arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\LeftNeuralDataBackward891011Angle5.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");
	if (leftright == 0) //--> 0 corresponds to right arm
		if((neuralDataBackward = fopen("..\\TrainFiles\\RightNeuralDataBackward891011Angle5.txt","w")) == NULL)
			printf("Dosya Acilmadý EncoderValues\n");

	// Homing & Reset Encoders Left
	Sleep(3000);

	if (leftright == 1)	ResetLeftEncoders(); else ResetRightEncoders();	
	if (leftright == 1) vitalSelectBoard(0); else vitalSelectBoard(1);

	//Control loop
	printf("Control Loop Starts!!\n");
	
	while(count<510 && !kbhit())
	{
		QueryPerformanceCounter(&start_ticks);

		// Update the voltage output references
        if( count < 100)
			incrementalVoltage = 0.01;
		if( count >= 100 && count <= 300) //burasi yeni !!!
			incrementalVoltage = -0.01;
		if( count > 300 )
			incrementalVoltage = 0.01;

		if (leftright == 1)
		{
			leftValvesOutputs[8] = leftValvesOutputs[8]-incrementalVoltage;
			leftValvesOutputs[9] = leftValvesOutputs[9]+incrementalVoltage;
			leftValvesOutputs[10] = leftValvesOutputs[10]+incrementalVoltage;
			leftValvesOutputs[11] = leftValvesOutputs[11]-incrementalVoltage;			
			SetLeftArmPressures();
		}else{
			rightValvesOutputs[8] = rightValvesOutputs[8]-incrementalVoltage;
			rightValvesOutputs[9] = rightValvesOutputs[9]+incrementalVoltage;
			rightValvesOutputs[10] = rightValvesOutputs[10]+incrementalVoltage;
			rightValvesOutputs[11] = rightValvesOutputs[11]-incrementalVoltage;
			SetRightArmPressures();
		}
			
		// Sleep 100 ms.   
		QueryPerformanceCounter(&end_ticks); //printf("time pass:%f\n",(float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000);
		
		while(((float)(end_ticks.QuadPart-start_ticks.QuadPart)/ticksPerSecond.QuadPart*1000) < (float) 800)
			QueryPerformanceCounter(&end_ticks); cputime.QuadPart = end_ticks.QuadPart- start_ticks.QuadPart;
	
		if (leftright == 1)	{ReadLeftEncoders();RealLeftAngles();} else {ReadRightEncoders();RealRightAngles();}

		if( count > 100 && leftright == 1){
			// Update the voltage output references
			if( incrementalVoltage < 0 )
				fprintf(neuralDataForward,"%.5f %.3f\n", leftValvesOutputs[10]-InitialleftValvesOutputs[10], leftAngles[5]);
			if( incrementalVoltage > 0 )
				fprintf(neuralDataBackward,"%.5f %.3f\n", leftValvesOutputs[10]-InitialleftValvesOutputs[10], leftAngles[5]);
		}
		if( count > 100 && leftright == 0){
			// Update the voltage output references
			if( incrementalVoltage > 0 )
				fprintf(neuralDataForward,"%.5f %.3f\n", rightValvesOutputs[10]-InitialrightValvesOutputs[10], rightAngles[5]);
			if( incrementalVoltage < 0 )
				fprintf(neuralDataBackward,"%.5f %.3f\n", rightValvesOutputs[10]-InitialrightValvesOutputs[10], rightAngles[5]);
		}
		count++;
	}

	printf("Control Loop End\n");
	
	CloseValves();
	Sleep(500);

	//clean up on exit
	vitalQuit();
	Sleep(500);
	
	fclose(neuralDataForward);
	fclose(neuralDataBackward);
}

void Train01(int m, int leftright)
{
	if ( m ==1)
		printf("Please Enter the Values to train the muscles 0&1 (for data number look samples) (forward)\n");
	else 
		printf("Please Enter the Values to train the muscles 0&1 (for data number look samples) (backward)\n");

	CNNMuscles01 myTrainF(m,leftright);
	myTrainF.Allocator();
	myTrainF.IsExist();
	myTrainF.Input();

	myTrainF.Process();
	myTrainF.WeightsWrite();
}
// Not being Used
void Train23(int m, int leftright)
{
	if ( m ==1)
		printf("Please Enter the Values to train the muscles 2&3 (for data number look samples) (forward)\n");
	else 
		printf("Please Enter the Values to train the muscles 2&3 (for data number look samples) (backward)\n");

	CNNMuscles23 myTrainF(m,leftright);
	myTrainF.Allocator();
	myTrainF.IsExist();
	myTrainF.Input();

	myTrainF.Process();
	myTrainF.WeightsWrite();
}
// Not being Used
void Train4567Angle2(int m, int leftright)
{
	if ( m ==1)
		printf("Please Enter the Values to train the muscles 4&5&6&7 (for data number look samples) (forward)\n");
	else 
		printf("Please Enter the Values to train the muscles 4&5&6&7 (for data number look samples) (backward)\n");
	
	CNNMuscles4567Angle2 myTrainF(m,leftright);

	myTrainF.Allocator();
	myTrainF.IsExist();
	myTrainF.Input();

	myTrainF.Process();
	myTrainF.WeightsWrite();
}


void Train4567Angle3(int m, int leftright)
{
	if ( m ==1)
		printf("Please Enter the Values to train the muscles 4&5&6&7 (for data number look samples) (forward)\n");
	else 
		printf("Please Enter the Values to train the muscles 4&5&6&7 (for data number look samples) (backward)\n");
	
	CNNMuscles4567Angle3 myTrainF(m,leftright);

	myTrainF.Allocator();
	myTrainF.IsExist();
	myTrainF.Input();

	myTrainF.Process();
	myTrainF.WeightsWrite();
}

void Train891011Angle4(int m, int leftright)
{
	if ( m ==1)
		printf("Please Enter the Values to train the muscles 8&9&10&11 (for data number look samples) (forward)\n");
	else 
		printf("Please Enter the Values to train the muscles 8&9&10&11 (for data number look samples) (backward)\n");
	
	CNNMuscles891011Angle4 myTrainF(m,leftright);

	myTrainF.Allocator();
	myTrainF.IsExist();
	myTrainF.Input();

	myTrainF.Process();
	myTrainF.WeightsWrite();
}


void Train891011Angle5(int m, int leftright)
{
	if ( m ==1)
		printf("Please Enter the Values to train the muscles 8&9&10&11 (for data number look samples) (forward)\n");
	else 
		printf("Please Enter the Values to train the muscles 8&9&10&11 (for data number look samples) (backward)\n");
	
	CNNMuscles891011Angle5 myTrainF(m,leftright);

	myTrainF.Allocator();
	myTrainF.IsExist();
	myTrainF.Input();

	myTrainF.Process();
	myTrainF.WeightsWrite();
}
#endif