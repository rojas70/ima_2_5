% This m_file computes delineates the limits of the right arm workspace.
% The workspace has five stages. We will parse each of the stages in four
% parts: upper-front: uf, upper-back: ub, lower-front: lf, lower back: lb
%
% It's uses meshgrid, griddata, and surf to find the surface of the object.
% We also find the surface by transforming cartesian coords into spherical.
%
% We might explore an approach that in order to find the workspace limits 
% it was deemed that finding spheres that roughly encapuslate the space would 
% be the best method. In c++ it % will be necessary to convert cartesian to 
% spherical coords and then test to see if the point is withing a sphere(theta,phi,r).

%% Clear all
clear all;
close all;
clc;

%% Load the data
load 'O:\Agents\TestAgents\Characterization of the RightArm Workspace\Sphere Fitting\RightArm_DexterousWorkspace_Map_5.mat'
% Round the matrix, make sure only integers are there.
xyz=round(xyz);

%% Plot the data
x = xyz(:,1,1);
y = xyz(:,2,1);
z = xyz(:,3,1);
figure, plot3(x,y,z);
grid on;
xlabel('x-axis'); ylabel('y-axis'); zlabel('z-axis');
title('Dexterous Workspace for the RightArm');
view(-103,12);                                      %Adjust the view

%% UPPER-FRONT/LOWER AND BACK-FRONT/LOWER HEMISPHERES WITH GRIDPLOT AND SURF FUNCS

% Given that the interpolation that is occuring with gridplot and surf is
% not working quite well because of the connection between high z values
% and low z-values, we will partition our original data in an upper-front/lower and
% back-front/lower hemisphere. The data points were selected by inspection of the
% plot, and the the indeces pertaining to divisios were searched.

% Fill the upper and lower hemispheres by sections (each section pertains
% to stages in the overal motion. There are a total of 5 stages in our
% motions).

% *** 1st stage ***
% Upper back: ub
xyz_ub(1:54,1,1) = xyz(1:54,1,1)';              % 54 entries
xyz_ub(1:54,2,1) = xyz(1:54,2,1)';
xyz_ub(1:54,3,1) = xyz(1:54,3,1)';

% upper front: uf
xyz_uf(1:29,1,1) = xyz(55:83,1,1)';             % 29  
xyz_uf(1:29,2,1) = xyz(55:83,2,1)'; 
xyz_uf(1:29,3,1) = xyz(55:83,3,1)';

% lower front: lf
xyz_lf(1:41,1,1) = xyz(84:124,1,1)';            % 41
xyz_lf(1:41,2,1) = xyz(84:124,2,1)';
xyz_lf(1:41,3,1) = xyz(84:124,3,1)';

% lower back: lb
xyz_lb(1:37,1,1) = xyz(125:161,1,1)';           % 37    
xyz_lb(1:37,2,1) = xyz(125:161,2,1)'; 
xyz_lb(1:37,3,1) = xyz(125:161,3,1)';

% *** 2nd stage ***
% Upper back: ub
xyz_ub(55:115,1,1) = xyz(162:222,1,1)';         % 61  
xyz_ub(55:115,2,1) = xyz(162:222,2,1)';
xyz_ub(55:115,3,1) = xyz(162:222,3,1)';

% upper front: uf
xyz_uf(30:50,1,1) = xyz(223:243,1,1)';          % 21         
xyz_uf(30:50,2,1) = xyz(223:243,2,1)'; 
xyz_uf(30:50,3,1) = xyz(223:243,3,1)';

% lower front: lf
xyz_lf(42:81,1,1) = xyz(244:283,1,1)';          % 40
xyz_lf(42:81,2,1) = xyz(244:283,2,1)';
xyz_lf(42:81,3,1) = xyz(244:283,3,1)';

% lower back: lb
xyz_lb(38:75,1,1) = xyz(284:321,1,1)';          % 38
xyz_lb(38:75,2,1) = xyz(284:321,2,1)'; 
xyz_lb(38:75,3,1) = xyz(284:321,3,1)';

% *** 3rd stage ***
% Upper back: ub
xyz_ub(116:168,1,1) = xyz(322:374,1,1)';       % 53  
xyz_ub(116:168,2,1) = xyz(322:374,2,1)';
xyz_ub(116:168,3,1) = xyz(322:374,3,1)';

% upper front: uf
xyz_uf(51:77,1,1) = xyz(375:401,1,1)';          % 27         
xyz_uf(51:77,2,1) = xyz(375:401,2,1)'; 
xyz_uf(51:77,3,1) = xyz(375:401,3,1)';

% lower front: lf
xyz_lf(82:123,1,1) = xyz(402:443,1,1)';         % 42
xyz_lf(82:123,2,1) = xyz(402:443,2,1)';
xyz_lf(82:123,3,1) = xyz(402:443,3,1)';

% lower back: lb
xyz_lb(76:113,1,1) = xyz(444:481,1,1)';          % 38
xyz_lb(76:113,2,1) = xyz(444:481,2,1)'; 
xyz_lb(76:113,3,1) = xyz(444:481,3,1)';

% 4th stage
% Upper back: ub
xyz_ub(167:220,1,1) = xyz(482:535,1,1)';         % 54  
xyz_ub(167:220,2,1) = xyz(482:535,2,1)';
xyz_ub(167:220,3,1) = xyz(482:535,3,1)';

% upper front: uf
xyz_uf(78:104,1,1) = xyz(536:562,1,1)';          % 27         
xyz_uf(78:104,2,1) = xyz(536:562,2,1)'; 
xyz_uf(78:104,3,1) = xyz(536:562,3,1)';

% lower front: lf
xyz_lf(124:164,1,1) = xyz(563:603,1,1)';         % 41
xyz_lf(124:164,2,1) = xyz(563:603,2,1)';
xyz_lf(124:164,3,1) = xyz(563:603,3,1)';

% lower back: lb
xyz_lb(114:151,1,1) = xyz(604:641,1,1)';          % 38
xyz_lb(114:151,2,1) = xyz(604:641,2,1)'; 
xyz_lb(114:151,3,1) = xyz(604:641,3,1)';

% 5th stage
% Upper back: ub
xyz_ub(221:274,1,1) = xyz(642:695,1,1)';         % 54  
xyz_ub(221:274,2,1) = xyz(642:695,2,1)';
xyz_ub(221:274,3,1) = xyz(642:695,3,1)';

% upper front: uf
xyz_uf(105:131,1,1) = xyz(696:722,1,1)';          % 27         
xyz_uf(105:131,2,1) = xyz(696:722,2,1)'; 
xyz_uf(105:131,3,1) = xyz(696:722,3,1)';

% lower front: lf
xyz_lf(165:205,1,1) = xyz(723:763,1,1)';         % 41
xyz_lf(165:205,2,1) = xyz(723:763,2,1)';
xyz_lf(165:205,3,1) = xyz(723:763,3,1)';

% lower back: lb
xyz_lb(152:189,1,1) = xyz(764:801,1,1)';          % 38
xyz_lb(152:189,2,1) = xyz(764:801,2,1)'; 
xyz_lb(152:189,3,1) = xyz(764:801,3,1)';

%% Plot the data
xub = xyz_ub(:,1,1);
yub = xyz_ub(:,2,1);
zub = xyz_ub(:,3,1);

xuf = xyz_uf(:,1,1);
yuf = xyz_uf(:,2,1);
zuf = xyz_uf(:,3,1);

xlf = xyz_lf(:,1,1);
ylf = xyz_lf(:,2,1);
zlf = xyz_lf(:,3,1);

xlb = xyz_lb(:,1,1);
ylb = xyz_lb(:,2,1);
zlb = xyz_lb(:,3,1);

figure, plot3(xub,yub,zub); hold
        plot3(xuf,yuf,zuf); 
        plot3(xlf,ylf,zlf); 
        plot3(xlb,ylb,zlb); grid on;
xlabel('x-axis'); ylabel('y-axis'); zlabel('z-axis');
title('Reconstruction fo the partitioned workspace for the RightArm');
view(-103,12);            

%% SPHERICAL COORDS TO IMPLEMENT GRID PLOT

% This next portion of code has been implemented in the following way to
% assit with 'gridplot'. Due to the nature of the data, the way that the
% points are being interpolated is not working. But it seems that in
% spherical coordinates the nature of the problem is overcome.

% Convert xyz to spherical coords
[th,  phi,  r]  = cart2sph(x,y,z);
[th1, phi1, r1] = cart2sph(xub,yub,zub);
[th2, phi2, r2] = cart2sph(xuf,yuf,zuf);
[th3, phi3, r3] = cart2sph(xlf,ylf,zlf);
[th4, phi4, r4] = cart2sph(xlb,ylb,zlb);

% Find the max and min for each of the variables, to get an idea of how
% fine the mesh should be. 
% Select the max and min values for the theta
max_th = max( th );
min_th = min( th );
%Select the max and min values for the r
max_r = max(r);
min_r = min(r);
%Select the max and min values for the phi
max_phi = max(phi);
min_phi = min(phi);

%% Create the mesh
[THETA_I,Phi_I] = meshgrid(min_th:(max_th-min_th)/200:max_th);
% Get the 
RI1=griddata(th1,phi1,r1,THETA_I,Phi_I);
RI2=griddata(th2,phi2,r2,THETA_I,Phi_I);
RI3=griddata(th3,phi3,r3,THETA_I,Phi_I);
RI4=griddata(th4,phi4,r4,THETA_I,Phi_I);

% Once we have our sampling points, transform back to cartesian coords
% before plotting
[x1,y1,z1]=sph2cart(THETA_I,Phi_I,RI1);
[x2,y2,z2]=sph2cart(THETA_I,Phi_I,RI2);
[x3,y3,z3]=sph2cart(THETA_I,Phi_I,RI3);
[x4,y4,z4]=sph2cart(THETA_I,Phi_I,RI4);

%% Plot it
figure, surf(x1,y1,z1); hold
        surf(x2,y2,z2); 
        surf(x3,y3,z3); 
        surf(x4,y4,z4); grid on;
% Add labels
xlabel('x-axis'); ylabel('y-axis'); zlabel('z-axis');
title('Meshgrid plot of the Workspace for the RightArm from its 4-subdivisions in spherical coords');
view(80,12); 

%% Fit spheres to data to later compute if a coord is within the workspace

% Declare a global variable 'coords' that cotains the sample points in our
% sphere:

global coords

% Upper sphere, cx n cy don't change. 
cx  =  -58;
cy  = -300;
cz1 = -605;
r1 =   690;
x0 = [cx,cy,cz1,r1];

% Given that some of the interpolation vectors are empty, we can examine for
% those points that are valied. Once found, assign them to coords, and then
% estimate (least-squares method) the cardinal variables of the sphere (cx, cy, cz, r).

% Upper-Back
validx1 = find(~isnan(x1)); 
coords=[x1(validx1), y1(validx1), z1(validx1)];
sphere_estimates = lsqnonlin(@spherefit,x0)

% Upper-Front
validx2 = find(~isnan(x2)); 
coords=[x2(validx2), y2(validx2), z2(validx2)];
sphere_estimates = lsqnonlin(@spherefit,x0)

% Lower-Front
validx3 = find(~isnan(x3)); 
coords=[x3(validx3), y3(validx3), z3(validx3)];
sphere_estimates = lsqnonlin(@spherefit,x0)

% Lower-Back
validx4 = find(~isnan(x4)); 
coords=[x4(validx4), y4(validx4), z4(validx4)];
sphere_estimates = lsqnonlin(@spherefit,x0)

% Results
% for ub -> -55.7715 -270.2463 -283.4564  382.6570**
% for uf -> -33.8050 -253.8355 -731.4016  838.7972
% for lf -> -28.6385 -259.9589 -270.9206  735.5516**
% for lb -> -94.1739 -248.3646 -639.4602  357.5320

%% Test:
% By bringing up the first plot in this .m file, i will test the limits of
% the curves and see if the fall within the stared results above.
clc
xi=  670;
yi= -472;
zi= -365;

% upper-front sphere values
if( sqrt((xi--33.80)^2+(yi--253.83)^2+(zi--731.40)^2) < 838.7972 )
    uf_results = sqrt((xi--33.80)^2+(yi--253.83)^2+(zi--731.40)^2)
    disp('true, < 838.7972');
else
    uf_results = sqrt((xi--33.80)^2+(yi--253.83)^2+(zi--731.40)^2)
    disp('false, > 838.7972');
end

% Lower-front sphere values
if( sqrt((xi--28.63)^2+(yi--259.95)^2+(zi--270.92)^2) < 735.55 )
    lf_results = sqrt((xi--28.63)^2+(yi--259.95)^2+(zi--270.92)^2)
    disp('true, < 735.55');
else
    lf_results = sqrt((xi--28.63)^2+(yi--259.95)^2+(zi--270.92)^2)
    disp('false, > 735.55');
end

% upper-back sphere values
if( sqrt((xi--55.77)^2+(yi--270.24)^2+(zi--283.45)^2) < 382.65 )
    ub_results = sqrt((xi--55.77)^2+(yi--270.24)^2+(zi--283.45)^2)
    disp('true, < 382.25');
else
    ub_results = sqrt((xi--55.77)^2+(yi--270.24)^2+(zi--283.45)^2)
    disp('false, > 382.25');
end

% Lower-back sphere values
if( sqrt((xi--94.17)^2+(yi--248.36)^2+(zi--639.46)^2) < 357.53 )
    lb_results = sqrt((xi--94.17)^2+(yi--248.36)^2+(zi--639.46)^2)
    disp('true, < 357.53');
else
    lb_results = sqrt((xi--94.17)^2+(yi--248.36)^2+(zi--639.46)^2)
    disp('false, > 357.53');
end