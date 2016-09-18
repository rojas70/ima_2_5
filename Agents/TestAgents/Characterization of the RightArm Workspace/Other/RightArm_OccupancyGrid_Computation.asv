% This m_file computes the "occupancy grid" of the right arm.
% Based on the empirical data obtained from the Characterization of the
% RightArm Workspace Component in IMA 2.5 (see
% O:\Agents\TestAgents\Characterization of the RightArm Workspace).
% To do so, we must:
% (1) identify the max and min for all dimensions of the recorded xyz
% coordinates
% (2) Create a matrix that will fit all possible values in the grid
% (3) For those spaces in the workspace that are within reach, i.e. within 
% the limits of the workspace, fill them in with a value of "1" in the
% occupancy grid workspace matrix, otherwise fill it up with a "0".

clear all;
close all;
clc;

% Load the empirical data
% Simpler model, less data, composed of three main montions
% load 'O:\Agents\TestAgents\Characterization of the RightArm Workspace\RightArm_DexterousWorkspace_Map.mat' 
% More data, composed of five main motions
load 'O:\Agents\TestAgents\Characterization of the RightArm Workspace\Sphere Fitting\RightArm_DexterousWorkspace_Map_5.mat'
five_slices = 1;    %flag for 5 slices
% Round the matrix, make sure only integers are there.
xyz=round(xyz);

%--------------------------------------------------------------------------
%Plot the data
x = xyz(:,1,1);
y = xyz(:,2,1);
z = xyz(:,3,1);
figure, plot3(x,y,z);
grid on;
xlabel('x-axis'); ylabel('y-axis'); zlabel('z-axis');
title('Dexterous Workspace for the RightArm');
view(-103,12);                                      %Adjust the view

%--------------------------------------------------------------------------
% Plot the same data in a MESH GRID

% Estabilsh the granularity of the mesh
[XI,YI] = meshgrid(-1000:2:800);
% Interpolate the data at every XI, YI
ZI=griddata(x,y,z,XI,YI);

% Create the mesh, holding it in the figure, to then add the 3D-plot
figure, surf(XI,YI,ZI)
%figure, plot3(x,y,z,'o')

% Add labels
xlabel('x-axis'); ylabel('y-axis'); zlabel('z-axis');
title('Meshgrid plot of the Workspace for the RightArm');
view(-103,12);                                      %Adjust the view
%--------------------------------------------------------------------------
% MAX AND MIN VALUES

%Select the max and min values for the x-axis
max_x = max( xyz(:,1,1) );
min_x = min( xyz(:,1,1) );

%Select the max and min values for the y-axis
max_y = max(xyz(:,2,1));
min_y = min(xyz(:,2,1));

%Select the max and min values for the z-axis
max_z = max(xyz(:,3,1));
min_z = min(xyz(:,3,1));
%--------------------------------------------------------------------------
% DISPLACED MATRIX AND PLOT 

% Before we can copy our data to our workspace_matrix we need to shift the
% data to all positive quadrants in order to copy the values into the
% indeces of the workspace_matrix. I,.e. if xyz[1,1,1] = -147, we are going
% to have to make this 'xyz[1,1,1] = 3. I.e. a discplacement of 3

% We will displace x by 150, y by 1000, z by 1000.
displaced_x = x+150;
displaced_y = y+1000;
displaced_z = z+1000;

%Plot it
figure, plot3(displaced_x,displaced_y,displaced_z);
grid on;
xlabel('displaced_x-axis'); ylabel('displaced_y-axis'); zlabel('displaced_z-axis');
title('Displaced plot of the Workspace for the RightArm');
view(-103,12);                                      %Adjust the view
%--------------------------------------------------------------------------
% GETTING A SLICE OF THE TRAJECTORY

% To get one slice of the trajectory
% Empirically determined that these numbers describe the first complete
% traj

for index = 1:ceil(length(xyz)/3)               % This number is 161 for 481 total samples
x_slice(index)=xyz(index,1,1); %#ok<AGROW>
y_slice(index)=xyz(index,2,1); %#ok<AGROW>
z_slice(index)=xyz(index,3,1); %#ok<AGROW>
end

% Plot it
figure, plot3(x_slice,y_slice,z_slice)
grid on;
xlabel('x_slice'); ylabel('y_slice'); zlabel('z_slice');
title('Plot of the first slice of the Workspace for the RightArm');
view(-103,12);  

%--------------------------------------------------------------------------
% FILL AN OCCUPANCY GRID

% Create a matrix that can capture the entire space + 50 more grids in
% each dimension

    %workspace_matrix = zeros( size(x)+[50,0],size(z)+[50,0]size(z)+[50,0] );

%We must know fill in the our occupancy grid

% (1) Extract the xyz coordinate at each index of the xyz matrix.
% (2) That xyz coordinate must now become the INDEX for the
% workspace_matrix
% (3) We will fill that workspace index with a value of 1 to indicate
% occupied.

%for x_index = 1:size(x)
%   for y_index = 1:size(y)
%        for z_index = 1:size(z)
            
            % Save the values of the x,y,z coordinates in a temp variable
%            temp_x = displaced_x(x_index);
%            temp_y = displaced_y(y_index);
%            temp_z = displaced_z(z_index);
            
            % Fill the workspace matrix indeces corresponding to the
            % cartesian coordiantes with a value of 1
%            workspace_matrix(temp_x,temp_y,temp_z) = 1;
%        end
%    end
%end


% For interpolation

% Create a 2D array (2nd dimension represents a time-series)
% X-Interpolation
x_interp = zeros(length(xyz),2);
x_interp(:,2) = x(:,1);
% Fill the second dimension with a time series, in increments of 0.2 secs
for index = 1:length(xyz)
x_interp(index,1) = 0.2*index;
end

% Y-Interpolation
y_interp = zeros(length(xyz),2);
y_interp(:,2) = y(:,1);
% Fill the second dimension with a time series, in increments of 0.2 secs
for index = 1:length(xyz)
y_interp(index,1) = 0.2*index;
end

% Z-Interpolation
z_interp = zeros(length(xyz),2);
z_interp(:,2) = z(:,1);
% Fill the second dimension with a time series, in increments of 0.2 secs
for index = 1:length(xyz)
z_interp(index,1) = 0.2*index;
end

%--------------------------------------------------------------------------
% SPHERICAL COORDS TO IMPLEMENT GRID PLOT

% This next portion of code has been implemented in the following way to
% assit with 'gridplot'. Due to the nature of the data, the way that the
% points are being interpolated is not working. But it seems that in
% spherical coordinates the nature of the problem is overcome.

% Convert xyz to spherical coords
[th, phi, r] = cart2sph(x,y,z);

% Find the max and min for each of the variables, to get an idea of how
% fine the mesh should be. 

%Select the max and min values for the theta
max_th = max( th );
min_th = min( th );
%Select the max and min values for the r
max_r = max(r);
min_r = min(r);
%Select the max and min values for the phi
max_phi = max(phi);
min_phi = min(phi);

% Create the mesh
[THETA_I,Phi_I] = meshgrid(min_th:(max_th-min_th)/200:max_th);
% Get the 
RI=griddata(th,phi,r,THETA_I,Phi_I);

% Once we have our sampling points, transform back to cartesian coords
% before plotting
[xx,yy,zz]=sph2cart(THETA_I,Phi_I,RI);

% Plot it
figure, surf(xx,yy,zz)
grid on;
xlabel('x_interp'); ylabel('y_interp'); zlabel('z_interp');
title('Plot of the interpolated matrix for the Workspace of the RightArm');
view(49,36);  

%--------------------------------------------------------------------------
% UPPER AND LOWER HEMISPHERES WITH GRIDPLOT AND SURF FUNCS

% Given that the interpolation that is occuring with gridplot and surf is
% not working quite well because of the connection between high z values
% and low z-values, we will partition our original data in an upper and
% lower hemisphere. The data points were selected by inspection of the
% plot, and the the indeces pertaining to divisios were searched.

% Fill the upper and lower hemispheres by sections (each section pertains
% to stages in the overal motion. There are a total of 5 stages in our
% motions).

% 1st stage
xyz_upper(1:83,1,1) = xyz(1:83,1,1)';
xyz_upper(1:83,2,1) = xyz(1:83,2,1)';
xyz_upper(1:83,3,1) = xyz(1:83,3,1)';

xyz_lower(1:78,1,1) = xyz(84:161,1,1)';             %78 entries
xyz_lower(1:78,2,1) = xyz(84:161,2,1)'; 
xyz_lower(1:78,3,1) = xyz(84:161,3,1)';

% 2nd stage
xyz_upper(84:164,1,1) = xyz(162:242,1,1)';
xyz_upper(84:164,2,1) = xyz(162:242,2,1)';
xyz_upper(84:164,3,1) = xyz(162:242,3,1)';

xyz_lower(79:157,1,1) = xyz(243:321,1,1)';          % 78 elements in this section 
xyz_lower(79:157,2,1) = xyz(243:321,2,1)';
xyz_lower(79:157,3,1) = xyz(243:321,3,1)';

% 3rd stage
xyz_upper(165:246,1,1) = xyz(322:403,1,1)';         % 81 elements in array
xyz_upper(165:246,2,1) = xyz(322:403,2,1)';
xyz_upper(165:246,3,1) = xyz(322:403,3,1)';

xyz_lower(158:235,1,1) = xyz(404:481,1,1)';         % 77 elements in this section 
xyz_lower(158:235,2,1) = xyz(404:481,2,1)';
xyz_lower(158:235,3,1) = xyz(404:481,3,1)';

% Check to comment this section out, whether you are using 3 discs or 5

if (five_slices) 

        % 4th stage
        xyz_upper(247:327,1,1) = xyz(482:562,1,1)';         % 80 elements in array
        xyz_upper(247:327,2,1) = xyz(482:562,2,1)';
        xyz_upper(247:327,3,1) = xyz(482:562,3,1)';

        xyz_lower(236:314,1,1) = xyz(563:641,1,1)';         % 78 elements in this section 
        xyz_lower(236:314,2,1) = xyz(563:641,2,1)';
        xyz_lower(236:314,3,1) = xyz(563:641,3,1)';

        % 5th stage
        xyz_upper(328:406,1,1) = xyz(642:720,1,1)';         % 81 elements in array
        xyz_upper(328:406,2,1) = xyz(642:720,2,1)';
        xyz_upper(328:406,3,1) = xyz(642:720,3,1)';

        xyz_lower(315:395,1,1) = xyz(721:801,1,1)';         % 77 elements in this section 
        xyz_lower(315:395,2,1) = xyz(721:801,2,1)';
        xyz_lower(315:395,3,1) = xyz(721:801,3,1)';
        
end

%Plot the data
xu = xyz_upper(:,1,1);
yu = xyz_upper(:,2,1);
zu = xyz_upper(:,3,1);

xl = xyz_lower(:,1,1);
yl = xyz_lower(:,2,1);
zl = xyz_lower(:,3,1);

figure, plot3(xu,yu,zu); hold
plot3(xl,yl,zl), grid on;
xlabel('x-axis'); ylabel('y-axis'); zlabel('z-axis');
title('Upper Slice and Lower Slices super-imposed');
view(-103,12);  

% Try mesh on this

% Estabilsh the granularity of the mesh
[XI,YI] = meshgrid(-1000:2:800);
% Interpolate the data at every XI, YI for upper slice
ZU=griddata(xu,yu,zu,XI,YI);
% Now for lower slice
ZL=griddata(xl,yl,zl,XI,YI);

% MESH****************
% Create the mesh, holding it in the figure, to then add the 3D-plot
figure, surf(XI,YI,ZU)
surf(XI,YI,ZL)
% Add labels
xlabel('x-axis'); ylabel('y-axis'); zlabel('z-axis');
title('Meshgrid plot of the Workspace for the RightArm');
view(-103,12);     

% SPHERICAL COORDS***************
% Convert xyz to spherical coords
[thu, phiu, ru] = cart2sph(xu,yu,zu);
[thl, phil, rl] = cart2sph(xl,yl,zl);

% This next statement might seem redundant, but is necessary to get the
% granularity of the mesh for the upper and lower slices
[th, phi, r] = cart2sph(x,y,z);

% Find the max and min for each of the variables, to get an idea of how
% fine the mesh should be. 

%Select the max and min values for the theta
max_th = max( th );
min_th = min( th );
%Select the max and min values for the r
max_r = max(r);
min_r = min(r);
%Select the max and min values for the phi
max_phi = max(phi);
min_phi = min(phi);

% Create the mesh
[THETA_I,Phi_I] = meshgrid(min_th:(max_th-min_th)/250:max_th);

% Get the interpolation for the upper half
RIU=griddata(thu,phiu,ru,THETA_I,Phi_I);
% Get the interpolation for the lower half
RIL=griddata(thl,phil,rl,THETA_I,Phi_I);

% Once we have our sampling points, transform back to cartesian coords
% before plotting
% Upper half
[xxu,yyu,zzu]=sph2cart(THETA_I,Phi_I,RIU);
% Lower half
[xxl,yyl,zzl]=sph2cart(THETA_I,Phi_I,RIL);

% Plot it
figure, surf(xxu,yyu,zzu), hold
surf(xxl,yyl,zzl);
grid on;
xlabel('x_interp'); ylabel('y_interp'); zlabel('z_interp');
title('Plot of the Meshgrid of superimposed upper- and lower- slices');
view(87,12);  
