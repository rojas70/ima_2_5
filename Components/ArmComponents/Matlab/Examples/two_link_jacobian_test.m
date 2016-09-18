function two_link_jacobian_test

% The purpose of this function is to test the process of builing the
% forward kinematics and the jacobian of a two-link manipulator by
% comparing the results to those found in a lecutre.
% 
% Please refer to "Robot and Modelling Control" by
% Spong/Hutchigson/Vydyasagar.
% Example 4.5, p134.

% Functionality of Program
% 1st DH parameters will be established according to the problem,
% 2nd The forward kinematics will be built, by multiplying the link
% homogeneous transforms,
% 3rd The Jacobian will be built by calling the symbolic Jacobian method.

%% (1) DH Parameters following Craig's convention.

clear all 
clc

% All lengths are to be '1' for simplicity.
a0 = 0;
a1 = 1;
a2 = 1;

% Link offsets
d1 = 0;
d2 = 0;
d3 = 0;

% Alpha angles
alpha0 = 0;     
alpha1 = 0;
alpha2 = 0;

% thetas (Theta was changed to Angle so it is easier to code in C++
% later).
syms Angle0; % theta1
syms Angle1; % theta2
%syms Angle2; % theta3
%% Compute the symbolic DH Params

% This computation will generate a non-succint version of the matrix.
% I recommend that after computing the DHmatrix using this method, you
% re-write the matrix transform in succint form before computing the
% base-to-end effector transform.

% Create transforms by calling the DH-Params
%                  theta,     d,      a,     alpha,     version
T01 = DHmatrix_sym(Angle0,    d1,    a0,     alpha0,     2) % symbolic derivation
T12 = DHmatrix_sym(Angle1,    d2,    a1,     alpha1,     2)
T23 = DHmatrix_sym(0,    d3,    a2,     0,          2)

%% Symbolic Computation of Forward Kinematics
T03 = T01*T12*T23;
T03 = simple(T03)
% Before passing to jacobian method, fill T02 with 4 other identity
% matrices to make six total.
I = eye(4,4);

%% Symbolic Computation of ISACs Manipulator Jacobian.
%  The following equation is open source from DiProdi.
J = jacobianT6_sym(T03, [T01, T12, T23]);

%% Numerical Test

% The forward kinematics of a 2-link manipulator are shown in Fig 1.20 /
% Equations 1.1 in the book Robot Modelling and Control. 
%
% The equations are as follow:
% Link lengths
a1 = 1, a2 = 1;
Angle0 = 0;
Angle1 = 0;

% Equations
X1 = a1*cosd(Angle0) + a2*cosd(Angle0+Angle1);
Y1 = a1*sind(Angle0) + a2*sind(Angle0+Angle1);

% The first column of the jacobian is the derivative of the forward
% kinematics by Angle0. That would be, how does the end-eff vel change when
% only joint1 changes. The second column of the Jacobian is the derivative
% of the forward kinematics wrt Angle1, how does Vee change when only the
% second joint changes. 

% The Manipulator Jacobian looks like:

J = [ -sind(Angle0+Angle1)-sind(Angle0), -sind(Angle0+Angle1), 0;
       cosd(Angle0+Angle1)+cosd(Angle0),  cosd(Angle0+Angle1), 0;
       0,                                 0,                   0;
       0,                                 0,                   0;
       0,                                 0,                   0;
       1,                                 1,                   1]

%% Test 
% Testing to see the position and then the velocity.
% Where Xvel = Jacobian * joint_vel
% {0,0}
Angle0=0; Angle1=0;                             % Current position
X0 = a1*cosd(Angle0) + a2*cosd(Angle0+Angle1)   % X and Y value
Y0 = a1*sind(Angle0) + a2*sind(Angle0+Angle1)
J0 = Jnum(Angle0,Angle1)                        % Jacobian for cur. pos.
Velocity0 = J0*[10; 10; 0]                       % EE vel given joint vel.

%{0,45}
Angle0=0; Angle1=45;
X1 = a1*cosd(Angle0) + a2*cosd(Angle0+Angle1)
Y1 = a1*sind(Angle0) + a2*sind(Angle0+Angle1)
J1 = Jnum(Angle0,Angle1)
Velocity1 = J1*[10; 10; 0]

% {0,90}
Angle0=0; Angle1=90;
X2 = a1*cosd(Angle0) + a2*cosd(Angle0+Angle1)
Y2 = a1*sind(Angle0) + a2*sind(Angle0+Angle1)
J2 = Jnum(Angle0,Angle1)
Velocity2 = J2*[1; 1; 0]

% {45,45}
Angle0=45; Angle1=45;
X3 = a1*cosd(Angle0) + a2*cosd(Angle0+Angle1)
Y3 = a1*sind(Angle0) + a2*sind(Angle0+Angle1)
J3 = Jnum(Angle0,Angle1)
Velocity3 = J3*[-10; -20; 0]

% {90,90}
Angle0=90; Angle1=0;
X4 = a1*cosd(Angle0) + a2*cosd(Angle0+Angle1)
Y4 = a1*sind(Angle0) + a2*sind(Angle0+Angle1)
J4 = Jnum(Angle0,Angle1)
Velocity4 = J4*[1; 1; 0]


%% Jacobian Transpose Control vs Jacobian Inverse Control
% In this section we will compare results for both techniques.

% (0,45) -> (45,45)
Desired_Cartesian_Position = [0.7071,1.7071,0,0,0,1];
Actual_Cartesian_Position =  [1.7071,0.7071,0,0,0,1];
Error=Desired_Cartesian_Position - Actual_Cartesian_Position
alpha = 1.00
J_Actual = Jnum(0,45)       % Angles for position 1.7,0.7

% Transpose matrix
Updated_Joint_Pos = alpha*J_Actual'*Error'
% With inv matrix
Updated_Joint_Pos = alpha*pinv(J_Actual)*Error'

% (45,45) -> (90,0)
Desired_Cartesian_Position = [0.0,2.0,0,0,0,1];
Actual_Cartesian_Position =  [0.7071,1.7071,0,0,0,1];
Error=Desired_Cartesian_Position - Actual_Cartesian_Position
alpha = 1.00
J_Actual = Jnum(45,45)       % Angles for position 0.7,1.7

% Transpose matrix
Updated_Joint_Pos = alpha*J_Actual'*Error'
% With inv matrix
Updated_Joint_Pos = alpha*pinv(J_Actual)*Error'

% (0,90) -> (0,0)
Desired_Cartesian_Position = [2,0,0,0,0,1];
Actual_Cartesian_Position =  [1,1,0,0,0,1];
Error=Desired_Cartesian_Position - Actual_Cartesian_Position
alpha = 1.00
J_Actual = Jnum(0,90)       % Angles for position 0.7,1.7

% Transpose matrix
Updated_Joint_Pos = alpha*J_Actual'*Error'
% With inv matrix
Updated_Joint_Pos = alpha*pinv(J_Actual)*Error'

%% Jacobian Transpose Control
% This example uses a typical two-link manipulator with an end-effector
% pointing in the z-direction. The Jacobian result is well known in text
% books and hard coded in this example. The Jacobian is computed using
% the actual angles of the joints. 
%
% We computed a current cartesian position and a desired cartesian position
% both using the forward kinematics. 
%
% A loop is used to update the new desired angles and then compare to see
% if the desired position is reached.
%
% We find that using Jacobian Transpose, the desired position is never
% reached. Using the (Pseudo)Inverse Jacobian, the position is reached,
% although sometimes the links move in an undesired direction for a given
% amount of time. 

% Link lengths
a1 = 1; a2 = 1;
% Actual Angles
Angle0_A = -11.0; Angle1_A = 0;
% Desired Angles
Angle0_D = -13.0; Angle1_D = 0.0;
% Gain
alpha = 22.415;  %It seems that depending on the gain, you might get circular motions or 
                % hit the target pretty close.
                % A good number is 22.415

while(abs(Angle0_A - Angle0_D) > 0.01)
    [Joint_Change Error] = JTC(Angle0_A, Angle1_A, Angle0_D, Angle1_D, alpha);
    Angle0_A = Angle0_A + Joint_Change(1,1)
    Angle1_A = Angle1_A + Joint_Change(2,1)
end

Angle0_A
Angle1_A



%% Local Functions

function J = Jnum(Angle0, Angle1)
    J = [ -sind(Angle0+Angle1)-sind(Angle0), -sind(Angle0+Angle1), 0;
           cosd(Angle0+Angle1)+cosd(Angle0),  cosd(Angle0+Angle1), 0;
           0,                                 0,                   0;
           0,                                 0,                   0;
           0,                                 0,                   0;
           1,                                 1,                   1];

end

function [Joint_Change_T Error] = JTC(Angle0_A,Angle1_A,Angle0_D,Angle1_D,alpha)

    X3_actual  = a1*cosd(Angle0_A) + a2*cosd(Angle0_A+Angle1_A);
    Y3_actual  = a1*sind(Angle0_A) + a2*sind(Angle0_A+Angle1_A);
    
    X3_des = a1*cosd(Angle0_D) + a2*cosd(Angle0_D+Angle1_D);
    Y3_des = a1*sind(Angle0_D) + a2*sind(Angle0_D+Angle1_D);    

    Des_XYZ     = [X3_des,Y3_des,0,0,0,1];           
    Actual_XYZ  = [X3_actual,Y3_actual,0,0,0,1];     
    
    Error = Des_XYZ - Actual_XYZ;
    J_Actual = Jnum(Angle0_A,Angle1_A);       % Actual Angles

    % Transpose matrix
    Joint_Change_T = alpha*J_Actual'*Error';
    %Joint_Change_I = alpha*pinv(J_Actual)*Error';        

end

%% Numerical Derivation
% From Peter Corke's work.

% these results don't agree... need revision.

% The numerical test is carried out using Peter Corke's code. 
% We will create the links using the code 'link' and then compile the robot
% using these links... and at the end calling jacob0.
%             alpha a   theta   d   type
% L{1} = link([ 0     1   0       0], 'modified');
% L{2} = link([ 0     1   0       0], 'modified');
% 
% q1    = [0      0];
% q2    = [pi/2   0];
% q3    = [pi     0];
% q4    = [0      pi/2];
% q5    = [0      pi/4];
% q6    = [pi/2   -pi/2];
% 
% p2L = robot(L, '2-link manipulator', 'std', 'juan');
% 
% J1 = jacob0(p2L, q1)
% J2 = jacob0(p2L, q2)
% J3 = jacob0(p2L, q3) 
% J4 = jacob0(p2L, q4)
% J5 = jacob0(p2L, q5)
% J6 = jacob0(p2L, q6)
% 
% clear L
% p560.name = '2-Link';
% p560.manuf = 'Example';

end
 
