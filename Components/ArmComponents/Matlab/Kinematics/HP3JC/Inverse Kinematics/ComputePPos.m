%% This function computes the wrist or P-point position of the robot based
% on the end-effector coordinates. 

% Input: R06 matrix 


function P_Position = ComputePPos(XYZRPY, R06)

%% Initialize
    % DH Parameters d6 for the Motoman HP3JC robot.
    % This number includes the distance from the P-point to the wrist and
    % then the length of the barrett hand.
    d6 = -244.5;

%% Compute the new updated position
    % Subtract from the wrist position the distance d6 x the z-element of the
    % rotation matrix, R06.

    P_Position(1:3) = [XYZRPY(1);XYZRPY(2);XYZRPY(3)] - d6*(R06(1:3,1:3)*[0;0;1]);
    P_Position(4:6) = XYZRPY(4:6);
    
end