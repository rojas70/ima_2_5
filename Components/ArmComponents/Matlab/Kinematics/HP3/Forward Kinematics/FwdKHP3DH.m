% Forward kinematics of HP3 (according to DH table)

function M = FwdKHP3DH( theta )
%               alpha, a,    theta,          d                
T01 = DHMatrix(    0,    0,              0,  110 );
T12 = DHMatrix(  -90,  100,  theta(1) +   0,    0 );
T23 = DHMatrix(    0,  290,  theta(2) -  90,    0 );
T34 = DHMatrix(   90,   85, -theta(3) +   0,    0 );
T45 = DHMatrix(  -90,    0,  theta(4) +   0, -300 );
T56 = DHMatrix(   90,    0,  theta(5) +   0,    0 );
TT  = DHMatrix(    0,    0,  theta(6) +   0,  -90 );

M = T01*T12*T23*T34*T45*T56*TT;
