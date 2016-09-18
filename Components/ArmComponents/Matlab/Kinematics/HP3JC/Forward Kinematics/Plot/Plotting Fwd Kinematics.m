% Plot of Forward Kinematics of HP3JC
% Uses link functions from Corke's Robotic Toolkit
% August 2008
% Juan Rojas

% Uses modified DH Parameters. These values come from the derivation of the
% forward kinematics and jacobian for the HP3JC. 

clear L
%           alpha       a       theta   d       convention
L{1} = link( [    0      0       0       0],     'modified' );
L{2} = link( [-pi/2      0       0       0],     'modified' );
L{3} = link( [   pi      260     0       0],     'modified' );
L{4} = link( [-pi/2      30      0    -270],     'modified' );
L{5} = link( [ pi/2      0       0       0],     'modified' );
L{6} = link( [-pi/2      0       0  -244.5],     'modified' );

HP3JC = robot(L, 'HP3JC', 'Aug 2008');

% Now plot the home configuration. Theta's are different.
plot(HP3JC, [0 -pi/2 0 0 0 0])



