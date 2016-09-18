%% Null-space Projections
% The purpose of this program is to test whether or not the gradient of Y
% is actually being projected unto the null-space of X. That is, the
% gradient of X is not affected when the gradient of Y is projected unto
% it. This is a 2D program.

clc
clear

%% Create a 3D plot
x = -3:.2:3;
y = -3:.2:3;
clf
[xx,yy] = meshgrid(x,y);
zz = peaks(xx,yy);

%% Color and label the plot
hold on
pcolor(x,y,zz);
axis([-3 3 -3 3]);
colormap((jet+white)/2);
shading interp

%% Compute the fx and fy gradients
[px,py] = gradient(zz,.2,.2);

% Include a display of the direction of the gradient
quiver(x,y,px,py,2,'k');
axis off
hold off

%% Create an eye matrix
I=eye(2,2);

%% Generate the null-space projection operator wrt X

% Basically, if we multiply a vector that is in the null-space of X with
% this matrix operator, the result will be zero. If we multiply a regular
% vector with this operator, it will project that vector such that it is in
% the null-space of X. We could test the result by re-multiplying it again
% by the matrix operator and expecting a result = 0. 

% gradient_vector=[px(i), py(j)];
% null_space_proj=I-px*inv(px'*px)*px';
%% Test

% (A) to test to see if whether or not the projected py onto px is in the
% null space.

% Right now we are using values of i and j for ease, but really need to
% create a trajectory.

% Could also use for this specific map floor( 31*randn(1) )  
zero = 1;
while zero == 1
    
        i= floor( 30*rand + 1)
        j= floor( 30*rand + 1)
        
        % Create gradient vector as a function of px and py
        traj=[px(i,j);py(i,j)]              % selecting the gradient at a point in the map.
        
        % Create a structure for the null-space matrix operator
         null_space_proj=I-(traj*inv(traj'*traj)*traj')

        result = null_space_proj * traj    % random selection of elements
        zero = null_space_proj*result < 1e-12
    
end
