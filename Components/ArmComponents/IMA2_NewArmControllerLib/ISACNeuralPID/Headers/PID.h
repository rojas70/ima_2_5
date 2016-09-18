#ifndef _PID_h
#define _PID_h

// Joint Angle declaration
extern double m_dleftAngles[6],			m_drightAngles[6];
extern double m_dLeftPValue[6],			m_dRightPValue[6];
extern double m_dLeftAngleError[6],		m_dRightAngleError[6];
extern float m_fDesiredLeftAngle[6],	m_fDesiredRightAngle[6];

// Computed P-value for "Left joint angles".
double& leftPID()
{
	for(int i=0; i<6; i++)	
	{
		m_dLeftAngleError[i] = m_fDesiredLeftAngle[i] - m_dleftAngles[i];
		m_dLeftAngleError[i] = m_dLeftAngleError[i] * m_dLeftPValue[i];
	}
	return *m_dLeftAngleError;
}

// Computed P-value for "Right joint angles".
double& rightPID()
{
	for(int i=0; i<6; i++)	
	{
		m_dRightAngleError[i] = m_fDesiredRightAngle[i] - m_drightAngles[i];
		m_dRightAngleError[i] = m_dRightAngleError[i] * m_dRightPValue[i];
	}
	return *m_dRightAngleError;
}

#endif