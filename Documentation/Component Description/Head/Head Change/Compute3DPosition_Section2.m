function Compute3DPosition_Section2()

%% Global Variables
% Lengths
height = 6.4; length = 5; 
% Angle
intrinsic_angle = -atan2(length,height)*180/pi;

%% Define the incoming tilt angle
phi_tilt = -45;
% Compute the overal tilt angle and hypotenuse
tot_tilt_angle = phi_tilt+intrinsic_angle;
tilt_hyp = sqrt(length^2+height^2);

%% Compute X and Z for the tilt
X_tilt = tilt_hyp*sind(tot_tilt_angle);
Z_tilt = tilt_hyp*cosd(tot_tilt_angle);

%% Work with the pan angles
% Define the incoming pan angle
pan_angle = -15;

% Then interestingly enough, the result for the X_tilt become are new
% hypoteneuse for the pan computation, hence:
pan_hyp = abs(X_tilt);

%% Compute X and Y
X_pan = pan_hyp*cosd(pan_angle);
Y_pan = pan_hyp*sind(pan_angle);

%% An overall equation could be obtained as:
x_hat = tilt_hyp*sind(tot_tilt_angle)*cosd(pan_angle);
y_hat = tilt_hyp*sind(tot_tilt_angle)*sind(pan_angle);
