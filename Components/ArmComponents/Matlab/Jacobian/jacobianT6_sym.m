%% Author: Juan Rojas
function [J]=jacobianT6_sym(T0n, Tuh)

% Description:
% Input: - T0n is the full base-to-wrist transform.
%        - Tuh is the contiguous list of matrices: T01,T12...Tn-1,n
%        - JType is a vector of size n, that has as elements characters that
%          have an 'R' for revolute joints, or a 'P' for prismatic joints.
%
% Note:   If the DOF of the manipulator are less than 6 complete the
%         transformation matrices with identity matrices
% Output: the geometric Jacobian by cross-product generalized method.
%
% Theory:
% The upper section of the jacobian represents the linear velocity
% computations and the lower section of the jacobian represents the angular
% computations.
%
% J(theta_1-6) = [ z_01 X (0_P_6 - 0_P_0 ... z_06 X (0_P_6 - 0_P_5 ]
%                        z_01                      z_06
%
% Functionality: 
% 1) The full transform is available from the calling function.
% 2) The position for the ith column is computed by multipliying the homogeneous
%    transforms and extracting the position from the last column.
% 3) The subtraction is computed.
% 4) The angular velocity for the ith joint is computed by multiplying: 
%    R0i (which is the product R01*R02...available from before) x z ( which is [0 0 1]).
% 5) By analyzing the end-result of the cross product, place results in the
%    Jacobian in a row-wise manner.

%% Compuation 

    % Local variables    
	J=zeros(6,6);   % Create buffer vector for the Jacobian.
    count = 1;      % Have a local counter to tell us how many transforms to multiply
    Ti6 = eye(4,4); % Buffer to store temporary results of transform products.
    
    
    % Determine the size of the base-to-wrist transform, in this way we know
    % how many columns we will be computing (ie # of joints). 
    [rows cols] = size(Tuh);
    % Determine the total # of transformations/joints.
    cols = cols/4;
    
    % Compute the Jacobian matrix one column at at time. 
    for c = 1:cols

       % 2) Compute ith transform
       % ie. if count=1, go through rows 1:4 and cols 1:4 => T01
       %     if count=2, go through rows 1:4 and cols 5:8 => T12 (*T01 = T02).
       %     if count=3, go through rows 1:4 and cols 9:12=> T23 (*T02 = T03).
       % So, when The final product for c = 1 is: T06
       %                       c = 2 is: T16
        if count < cols
            Ti6=Ti6*Tuh(1:4,(4*count)-3:4*count)  
        
        
            % Increase count
            count = count+1;

            % Simplify this matrix
            Ti6 = simple(Ti6)

            % 3) Compute position difference
            P = T0n(1:3,4) - Ti6(1:3,4);

            % 4) Compute the ith joint angular velocity           
            %    Ti6*[001] => the ath column [r13; r23; r33];
            a = Ti6(1:3,3);     % r13, r23, r33 = a(z)

           % 5) Place results in the Jacobian
            % Column 1
            if c == 1                             
                J11 = a(2)*P(3) - a(3)*P(2);    
                J21 = a(3)*P(1) - a(1)*P(3);
                J31 = a(1)*P(2) - a(2)*P(1);    
                J41 = a(1);                     
                J51 = a(2);                    
                J61 = a(3);    
                
                % Fill in the Jacobian
                J = [J11; J21; J31; J41; J51; J61];

            elseif c == 2
                J12 = a(2)*P(3) - a(3)*P(2);    
                J22 = a(3)*P(1) - a(1)*P(3);
                J32 = a(1)*P(2) - a(2)*P(1);  
                J42 = a(1);                     
                J52 = a(2);                     
                J62 = a(3);
                
                % Fill in the Jacobian
                J = [J11 J12; J21 J22; J31 J32; J41 J42; J51 J52; J61 J62];              

            elseif c == 3
                J13 = a(2)*P(3) - a(3)*P(2);    
                J23 = a(3)*P(1) - a(1)*P(3);
                J33 = a(1)*P(2) - a(2)*P(1);  
                J43 = a(1);
                J53 = a(2);
                J63 = a(3);

                % Fill in the Jacobian
                J = [J11 J12 J13; J21 J22 J23; J31 J32 J33; J41 J42 J43; J51 J52 J53; J61 J62 J63];              
                
            elseif c == 4
                J14 = a(2)*P(3) - a(3)*P(2);    
                J24 = a(3)*P(1) - a(1)*P(3);
                J34 = a(1)*P(2) - a(2)*P(1);  
                J44 = a(1);
                J54 = a(2);
                J64 = a(3);
                
                % Fill in the Jacobian
                J = [J11 J12 J13 J14; J21 J22 J23 J24; J31 J32 J33 J34; J41 J42 J43 J44; J51 J52 J53 J54; J61 J62 J63 J64];                              

            elseif c == 5
                J15 = a(2)*P(3) - a(3)*P(2);    
                J25 = a(3)*P(1) - a(1)*P(3);
                J35 = a(1)*P(2) - a(2)*P(1);  
                J45 = a(1);
                J55 = a(2);
                J65 = a(3);
                
                % Fill in the Jacobian
                J = [J11 J12 J13 J14 J15; J21 J22 J23 J24 J25; J31 J32 J33 J34 J35; J41 J42 J43 J44 J45; J51 J52 J53 J54 J55; J61 J62 J63 J64 J65];                                             

            elseif c == 6
                J16 = a(2)*P(3) - a(3)*P(2);    
                J26 = a(3)*P(1) - a(1)*P(3);
                J36 = a(1)*P(2) - a(2)*P(1);  
                J46 = a(1);
                J56 = a(2);
                J66 = a(3);    
                
                % Fill in the Jacobian
                J = [J11 J12 J13 J14 J15 J16;
                     J21 J22 J23 J24 J25 J26
                     J31 J32 J33 J34 J35 J36
                     J41 J42 J43 J44 J45 J46
                     J51 J52 J53 J54 J55 J56
                     J61 J62 J63 J64 J65 J66];                 
            end
        
        end % End count
        
    end % End for c:1:1:6        
     
    % Now we want to simplify this expression as much as possible.
    J = simplify(J);   
    J = simple(J);
    
end % End function