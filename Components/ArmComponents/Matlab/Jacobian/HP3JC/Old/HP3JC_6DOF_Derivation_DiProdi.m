%% Motoman's Kinematics and Jacobian

function HP3JC_6DOF_Derivation_DiProdi

clear all
clc

% For more refer to O:\Documentation\Arm\Motoman
% DH Parameters. Follows the PUMA 560 derivation closely. The difference is
% in that we have a few more link offsets (d2,d4,d6), a3 = 0, and the home
% position for the motoman and puma is different. Adjustments take place in
% controller.

% Link lengths (all info was obtained from the Dimensions.pdf file).
a2 = 260;       % Length of link 2

% Link offsets
d2 = 290;       % base to 1st joint
d4 = 270;       % joint 3 to joint 4
d6 = 90;        % joint 4,5 to joint 6

% Alpha angles
alpha0 =   0;     
alpha1 = -90;
alpha2 =   0;
alpha3 = -90;
alpha4 =  90;
alpha5 = -90;

% thetas

theta1 = 0;
theta2 = 0;
theta3 = 0;
theta4 = 0;
theta5 = 0;
theta6 = 0;
%% Compute the symbolic DH Params

% This computation will generate a non-succint version of the matrix.
% I recommend that after computing the DHmatrix using this method, you
% re-write the matrix transform in succint form before computing the
% base-to-end effector transform.

% Create transforms by calling the DH-Params
%             theta,    d,      a,     alpha    version
T01=DHmatrix(theta1,    0,      0,      alpha0,       1);
T12=DHmatrix(theta2,    d2,     0,      alpha1,       1);
T23=DHmatrix(theta3,    0,      a2,     alpha2,       1);
T34=DHmatrix(theta4,    d4,     0,      alpha3,       1);
T45=DHmatrix(theta5,    0,      0,      alpha4,       1);
T56=DHmatrix(theta6,    d6,     0,      alpha5,       1);
%T56=RotZ(theta5)*RotX(theta6);

%% Computation of Motoman's Forward Kinematics

% Base to end-effector transform
T06_motoman = T01*T12*T23*T34*T45*T56;

%% This shows how to use the plot system
% plotT(T01);
% pause(2);
% plotT(T01*T12);
% pause(2);
% plotT2(T01*T12,T01*T12*T23);
% pause(2);
% plotT2(T01*T12*T23,T01*T12*T23*T34);
% pause(2);
% plotT2(T01*T12*T23*T34,T01*T12*T23*T34*T45);
% pause(2);
% plotT2(T01*T12*T23*T34*T45,T01*T12*T23*T34*T45*T56);

%%now calculate the jacobian
J6=jacobianT6([T01,T12,T23,T34,T45,T56],['R','R','R','R','R','R'])

end
