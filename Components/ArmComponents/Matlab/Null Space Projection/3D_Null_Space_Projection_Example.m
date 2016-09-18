%% Null-space Projections
% The purpose of this program is to test whether or not the gradient of Y
% is actually being projected unto the null-space of X. That is, the
% gradient of X is not affected when the gradient of Y is projected unto
% it. This is a 2D program.

clc
clear

%% Designate the function for the trajectory

%% (A) Create a liner trajectory
% T0=[1 0 0 410; 0 1 0 -415; 0 0 1 -605; 0 0 0 1];
% T1 = [1 0 0 500; 0 1 0 -350; 0 0 1 -500; 0 0 0 1];
% step = 20;
% ct=ctraj(T0,T1,step);           % Part of Peter Corke's matlab robotic toolbox.
% 
% x=zeros(step,1);
% y=zeros(step,1);
% z=zeros(step,1);
% 
% for i=1:step
%     x(i)=ct(1,4,i);
%     y(i)=ct(2,4,i);
%     z(i)=ct(3,4,i);
% end

%% (B) Create a trigonometric trajectory
t = 0:pi/50:10*pi;
x = sin(t); y = cos(t); z = t;

%% Plot in 3D
plot3(x,y,z)
grid on
axis square

% Cold play in trying to do it in matrix format
% [xx,yy]=meshgrid(sin(t),cos(t));
% zz = sin(xx)+cos(yy);
% figure,surface(xx,yy,zz);
% figure,contour(zz)  

%% Compute the gradients
diff_x = diff(x);
diff_y = diff(y);
diff_z = diff(z);

[row cols] = size(diff_x');
% Create a 3 by cols matrix
grad = [diff_x' diff_y' diff_z'];

% Include a display of the direction of the gradient (2D works better when
% plots are in matrix form).
figure,quiver(diff_x,diff_y);

%% Construction of projection matrix:

% Basically, if we multiply a vector that is in the null-space of X with
% this matrix operator, the result will be zero. If we multiply a regular
% vector with this operator, it will project that vector such that it is in
% the null-space of X. We could test the result by re-multiplying it again
% by the matrix operator and expecting a result = 0.

% Create a 3D eye matrix
I=eye(3,3);

% Generate the null-space projection operator wrt X and test it to see if 
% whether or not the projected py onto px is in the null space.

% To do so, we need to extract a gradient element from the trajectory. A
% way to do so is to use 3 for loops to traverse all x, y, and z elements.
% The values could also be selected by hand.

for i=1:row
    for j=1:row
        for k=1:row
            
        % Extract a single gradient from the matrix 'gradient'.
        grad_element=[grad(i,1); grad(j,2); grad(k,3)];

        % Create a structure for the null-space matrix operator
            % Composed of an outer product and a normalizing inner product
            % element.
        null_space_proj=I-(grad_element*inv(grad_element'*grad_element)*grad_element');

        % Test
        result = null_space_proj * grad_element    % The 'result' is in the null-space.
        zero   = (null_space_proj*result < 1e-12)'    % Re-multiply. The product should be zero. This at least verifies that the results are consisten.
        
        end
    end
end
