          
%% Numerical example
clear all, clc

% Length values chosen at random.
a2 = 260;       % Length of link 2
a3 =  30;       % originally not considered, now considered

% Link offsets
d2 = 0; %151.5;   % base to 1st joint, when looking at TP results, not considered.
d4 = 270;       % joint 3 to joint 4
d3 = 30;

% Alpha angles
alpha0 =    0;     
alpha1 =  -90;
alpha2 =    0;
alpha3 =  -90;   
alpha4 =   90;
alpha5 =  -90;   

% Theta angles at home position 
Angle0 =   0;
Angle1 =   0;
Angle2 =   0;
Angle3 =   0;
Angle4 =   0;
Angle5 =   0;

%                   theta,      d,    a,     alpha, version
T01 = DHmatrix_sym(Angle0,      0,    0,    alpha0,  1 );
T12 = DHmatrix_sym(Angle1,      0,    0,    alpha1,  1 );
T23 = DHmatrix_sym(Angle2,      d3,   a2,    alpha2,  1 );
T34 = DHmatrix_sym(-Angle3,     d4,   a3,    alpha3,  1 );
T45 = DHmatrix_sym(Angle4,       0,    0,    alpha4,  1 );
T56 = DHmatrix_sym(Angle5,       0,    0,    alpha5,  1 );

T06_Puma = T01*T12*T23*T34*T45*T56
