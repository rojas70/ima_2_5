% calculates classical DH parameter matrix 
% (Like Spong, not Craig)

function M = DHMatrix(alpha,a,theta,d)

% Ralpha = [RotX(pi*alpha/180) [0 0 0]' ; 0 0 0 1];
% Ta = [eye(3) [a 0 0] ; 0 0 0 1];
% Rtheta = [RotZ(pi*theta/180) [0 0 0]' ; 0 0 0 1];
% Td = [eye(3) [0 0 d] ; 0 0 0 1];
%
% M = Td*Rtheta*Ta*Ralpha;
%
% DH-parameters for HP3 in home position 
% This set preserves the actuation directions 
% as controlled by the teach pendant
%
% T01 = DHMatrix(    0,    0,    0,  110 );
% T12 = DHMatrix(  -90,  100,    0,    0 );
% T23 = DHMatrix(  180,  290,  -90,    0 )
% T34 = DHMatrix(   90,  -85,  180,    0 );
% T45 = DHMatrix(  -90,    0,    0, -300 );
% T56 = DHMatrix(   90,    0,    0,    0 );
% TT  = DHMatrix(    0,    0,    0,  -90 );

%
% DH-parameters for HP3 in home position 
% This set is taken from the parameter table
%
% T01 = DHMatrix(    0,    0,    0,  110 );
% T12 = DHMatrix(  -90,  100,    0,    0 );
% T23 = DHMatrix(    0,  290,  -90,    0 )
% T34 = DHMatrix(   90,  -85,    0,    0 );
% T45 = DHMatrix(  -90,    0,    0,  300 );
% T56 = DHMatrix(   90,    0,    0,    0 );
% TT  = DHMatrix(    0,    0,    0,   90 );

% Compute variables in radians.
ca = cos(pi*alpha/180);
sa = sin(pi*alpha/180);
ct = cos(pi*theta/180);
st = sin(pi*theta/180);

% DH original homogeneous transform matrix
M = [ ct -st*ca  st*sa  a*ct ;
      st  ct*ca -ct*sa  a*st ;
       0     sa     ca     d ;
       0      0      0     1 ];

