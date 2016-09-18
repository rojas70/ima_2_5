% Forward kinematics of HP3 (TP control angles)
% revised 15 July 2008

function M = FwdKHP3TP( theta )

T0 = DHMatrix(    0,    0,             0,  110 );
T1 = DHMatrix(  -90,  100, theta(1) +  0,    0 );
T2 = DHMatrix(  180,  290, theta(2) - 90,    0 );
T3 = DHMatrix(  -90,   85, theta(3) +  0,    0 );
T4 = DHMatrix(   90,    0, theta(4) +  0, -300 );
T5 = DHMatrix(  -90,    0, theta(5) +  0,    0 );
T6 = DHMatrix(    0,    0, theta(6) +  0,  -90 );

M = T1*T2*T3*T4*T5*T6;
