% Forward kinematics of HP3 (according to DH table)
% Program implemented by Dr. Peters.

function J_motoman = Motoman_Symbolic_Kins_n_Jacobian
     
clear all, clc
%% Numerical examples
%% Using Version 0 of the DH Parameters, the Classical Version

a2 = 260;       % Length of link 2
a3 =  30;       % originally not considered, now considered

d2 = 0; %151.5;   % base to 1st joint, when looking at TP results, not considered.
d5 =  -270;       % joint 3 to joint 4
%d6 =  -90;       % joint 4,5 to joint 6
dt =  -244.5;     % length of the barret hand + distance from joint 4,5 to 6.

% Alpha angles
alpha0 =    0;     
alpha1 =  -90;
alpha2 =    0;
alpha3 =   90;   
alpha4 =  -90;
alpha5 =   90;   

% Theta angles at home position.
% Note!!!!! Make sure that whatever function you are calling with these
% manipulates the data correctly, that is, make sure you handle degrees or
% radians appropriately
Angle0 =   0;
Angle1 =   0;
Angle2 = -90;
Angle3 =   0;
Angle4 = -90;
Angle5 =   0;
%               alpha,     a,    theta,    d    
T01 = DHMatrix( alpha0,    0,   Angle0,    0 );
T12 = DHMatrix( alpha1,    0,   Angle1,    0 );
T23 = DHMatrix( alpha2,   a2,   Angle2,    0 );
T34 = DHMatrix( alpha3,   a3,  -Angle3,    0 );
T45 = DHMatrix( alpha4,    0,   Angle4,   d5 );
T56 = DHMatrix( alpha5,    0,   Angle5,    0 );
TT  = DHMatrix(    0,      0,        0,   dt );

M = T01*T12*T23*T34*T45*T56*TT;

%% Using Version 1 of the DH Paramters, Craig's Version

% July 27, 2008.
% Recently I realized that the use of version 1 was not working b/c I was
% passing degrees to sin/cos functions that required radians. I modified
% the DHmatrix_sym function to convert degrees to radians. After doing
% that, Craig's DH parameters were making sense. I realized that the frame
% assignment for joint 5 was 180 degrees off for x. I also saw that in
% the spherical wrist theta5 or Angle4 is zero (there may be an assumption
% about the sphirical wrist I am not sure about). The pose of the
% end-effector now is completely correct and the barret hand offset can be
% well integrated into the offset parameter, d6. This will allow us to
% compute the Jacobian Matrix appropriately without the need for an
% additional transformation!

a2 = 260;       % Length of link 2
a3 =  30;       % originally not considered, now considered

d4 = 270;
d6 = 244.5;     % length of the barret hand + distance from joint 4,5 to 6.

% Alpha angles
alpha0 =    0;     
alpha1 =  -90;
alpha2 =    0;
alpha3 =  -90;   
alpha4 =  -90;
alpha5 =   90; 

% Theta angles at home position.
% Note!!!!! Make sure that whatever function you are calling with these
% manipulates the data correctly, that is, make sure you handle degrees or
% radians appropriately
Angle0 =   0;
Angle1 =  -90;
Angle2 =   0;
Angle3 =   0;
Angle4 =  0;
Angle5 =   0;
%                   theta,      d,    a,     alpha, version
T01 = DHmatrix_sym(Angle0,      0,    0,    alpha0,  1 );
T12 = DHmatrix_sym(Angle1,      0,    0,    alpha1,  1 );
T23 = DHmatrix_sym(Angle2,      0,   a2,    alpha2,  1 );
T34 = DHmatrix_sym(Angle3,     d4,   a3,    alpha3,  1 );
T45 = DHmatrix_sym(Angle4,      0,    0,    alpha4,  1 );
T56 = DHmatrix_sym(Angle5,     d6,    0,    alpha5,  1 );

M = T01*T12*T23*T34*T45*T56%*TT

%% Symbolic Computations Using Craig's DH Paramters

% Symbolic thetas. Notation is used to simplify transfer over to C++.
syms Angle0;
syms Angle1;
syms Angle2;
syms Angle3;
syms Angle4;
syms Angle5;

% Note!!!
% As of July 28th, 2008, I have resolved how to do the Kinematic's using
% Craig's approach instead of the original DH parameter approach. The
% latter is also the one that Dr. Peter's used. I am commenting out that
% approach.
%
% The derivation using Craig's approach is more intuitive and has
% integrated the extension of the barret hand into the normal forward
% kinematic's derivation. Hence, this is the simplest transform matrix to
% use to derive the Jacobian, given that no additional transforms are
% needed later to adjust for the linear/angular velocity of the
% end-effector. 
% 
% %                   theta,      d,    a,     alpha, version
% T01 = DHmatrix_sym(Angle0,      0,    0,    alpha0,  0 );
% T12 = DHmatrix_sym(Angle1,      0,    0,    alpha1,  0 );
% T23 = DHmatrix_sym(Angle2,      0,   a2,    alpha2,  0 );
% T34 = DHmatrix_sym(-Angle3,      0,   a3,    alpha3,  0 );
% T45 = DHmatrix_sym(Angle4,     d5,    0,    alpha4,  0 );
% T56 = DHmatrix_sym(Angle5,      0,    0,    alpha5,  0 );
% TEE = DHmatrix_sym(0,          dt,    0,         0,  0 );

% We are using Craig's DH parameters. We call version 3 which represents
% the symbolic derivation of the DHmatrix. 
%                   theta,      d,    a,     alpha, version
T01 = DHmatrix_sym(Angle0,      0,    0,    alpha0,  3 );
T12 = DHmatrix_sym(Angle1,      0,    0,    alpha1,  3 );
T23 = DHmatrix_sym(Angle2,      0,   a2,    alpha2,  3 );
T34 = DHmatrix_sym(Angle3,     d4,   a3,    alpha3,  3 );
T45 = DHmatrix_sym(Angle4,      0,    0,    alpha4,  3 );
T56 = DHmatrix_sym(Angle5,     d6,    0,    alpha5,  3 );

% Base to end-effector transform
T06_motoman = T01*T12*T23*T34*T45*T56;

% Simplification routines
T06_motoman = simplify(T06_motoman);   
T06_motoman = simple(T06_motoman)

%% Symbolic Computation of the Jacobian

% The symbolic derivation of the Jacobian will take place just as
% conventional texts propose it (Craig/Cooke's class notes/Sponge).

J_motoman=jacobianT6_sym(T06_motoman, [T01 T12 T23 T34 T45 T56])

end