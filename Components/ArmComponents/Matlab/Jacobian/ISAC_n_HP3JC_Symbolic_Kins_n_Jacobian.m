%% ISACs Forward Kinematics and Jacobian
%  By Juan Rojas, May 08.

function ISACs_KINEMATICS
%% Description

% This program will produce a symbolic matrix for the DH Parameters, each
% link in ISACs right manipulator, its complete forward kinematics, and its
% manipulator Jacobian. 

% We want the Jacobian in the symbolic form so that we can then use this
% matrix in control computations. 

% For more on Matlab's symbolic toolbox, do help sym.

% The structure of the program is as follows:
% 1) Derive the DH Parameters in symbolic form.
% 2) Derive the link transforms
% 3) Derive the Forward Kinematics (ie the transform from link_0 to link_6
% 4) Derive the Jacobian

% Note: Please note that you might have to consider a BASE transform and an
% end-effector transform for these different robots. For example, ISACs
% origin is in between his camera's eyes. So in code, there needs to be a
% transform that adjusts for this difference. Same for an end-effector.
%% Initialize Symbolic Values
clear all,  clc, clf

a2		=  330.0;
a3      =  0;
d3		= -200.0;			% Right Arm Parameter
d4		=  290.0;

% Alpha angles. The signs of these angles have been verified.
alpha0 =   0;     
alpha1 = -90;
alpha2 =   0;
alpha3 = -90;           
alpha4 =  90;           
alpha5 = -90;           
% 
% thetas
syms theta1 theta2 theta3 theta4 theta5 theta6;
%

% Create transforms by calling the DH-Params
%                  theta,   d,      a,     alpha
T01=DHmatrix_sym(theta1,   0,      0,       0);
T12=DHmatrix_sym(theta2,   0,      0,     -90);
T23=DHmatrix_sym(theta3,  d3,     a2,       0);
T34=DHmatrix_sym(theta4,  d4,     a3,     -90);
T45=DHmatrix_sym(theta5,   0,      0,      90);
T56=DHmatrix_sym(theta6,   0,      0,     -90);

% The commented code is below is for reference. It was hard-coded. The
% above results should match the ones in here.
% % Cosines           Sines
% c1 = sym('c1');     s1 = sym('s1');
% c2 = sym('c2');     s2 = sym('s2');
% c3 = sym('c3');     s3 = sym('s3');
% c4 = sym('c4');     s4 = sym('s4');
% c5 = sym('c5');     s5 = sym('s5');
% c6 = sym('c6');     s5 = sym('s6');
%  
% %% Symbolic representation of ISAC links
% 
% T01 = [c1 -s1 0 0;      s1 c1 0 0;      0 0 1 0;        0 0 0 1];
% T12 = [c2 -s2 0 0;      0 0 1 0;        -s2 -c2 0 0;    0 0 0 1];
% T23 = [c3 -s3 0 330;    s3 c3 0 0;      0  0 1 -200;    0 0 0 1];
% T34 = [c4 -s4 0 0;      0 0 1 290;      -s4 -c4 0 0;    0 0 0 1];
% T45 = [c5 -s5 0 0;      0 0 -1 0;       s5  c5  0 0;    0 0 0 1];
% T56 = [c5 -s5 0 0;      0 0  1 0;       -s5 -c5 0 0;    0 0 0 1];
 
%% Symbolic Computation of ISACs Forward Kinematics
T06_isac = T01*T12*T23*T34*T45*T56;

%% Symbolic Computation of ISACs Manipulator Jacobian.
%  The following equation is open source from matlab\toolbox\robotic\DiProdi.
J_isac = jacobianT6_sym([T01, T12, T23, T34, T45, T56],['R','R','R','R','R','R']);
 

%% Motoman's Kinematics and Jacobian
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
syms theta1 theta2 theta3 theta4 theta5 theta6;
%% Compute the symbolic DH Params

% This computation will generate a non-succint version of the matrix.
% I recommend that after computing the DHmatrix using this method, you
% re-write the matrix transform in succint form before computing the
% base-to-end effector transform.

% Create transforms by calling the DH-Params
%                  theta,   d,      a,     alpha
T01=DHmatrix_sym(theta1,    0,      0,        0);
T12=DHmatrix_sym(theta2,    d2,     0,      -90);
T23=DHmatrix_sym(theta3,    0,      a2,       0);
T34=DHmatrix_sym(theta4,    d4,     0,      -90);
T45=DHmatrix_sym(theta5,    0,      0,       90);
T56=DHmatrix_sym(theta6,    d6,     0,      -90);
%T56=RotZ(theta5)*RotX(theta6);

%% Symbolic Computation of ISACs Forward Kinematics
T06_motoman = T01*T12*T23*T34*T45*T56;

%% Symbolic Computation of ISACs Manipulator Jacobian.
%  The following equation is open source from DiProdi.
J_motoman = jacobianT6_sym([T01, T12, T23, T34, T45, T56],['R','R','R','R','R','R']);

% The result is run then in mathematica for further simplification. Look at
% O:\Documentation\Component Description\ControlBasis\Matlab n Mathematica
% Files
end

 