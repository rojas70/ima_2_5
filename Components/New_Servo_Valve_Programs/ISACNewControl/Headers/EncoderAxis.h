#ifndef _EncoderAxis_h
#define _EncoderAxis_h

//#include "Headers\AdsEP.h"

class encoder
{
public:

	int channel;

	MotorAxis(int wChannel);
	void MotorServoOn();
	void MotorServoOff();
	void SetMotorSpeed(float fvoltage);

};

#endif