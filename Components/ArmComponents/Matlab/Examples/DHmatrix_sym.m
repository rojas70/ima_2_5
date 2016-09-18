%% Author: epokh
%% Website: www.epokh.org/drupy
%% This software is under GPL
%% Modified by Juan Rojas to work symbolically

function [Mdh]=DHmatrix_sym(theta,d,a,alpha, version)
% output:   DH matrix
% input:    DH parameters:
% theta:    rotation along x(n).
% d:        traslation along z(n) axis
% a:        translation along x(n+1) axis
% alpha:    rotation along x(n+1). 
% All angles come in as degrees except the theta's in the symbolic derivation.
% Radians were considered at one point in time, but they produced
% problematic infinitesimally small floating point numbers as part of the
% computations.

% version:  refers to whether we are using the classical version of DH
% parameters or the one used by craig. "0" -> classical, "1" -> craig's.
% Note that the assignment of link lengths and twists needs to be the
% appropriate one.

% The "d" part of cosd or sind, has been dropped from the functions that
% have theta as an argument. This is necessary to produce a symbolic
% output. Symbolic math will not work with sind and cosd. 
% 
% Also we are interested in reducing the terms with 'alpha' so these terms do keep the
% 'd' part. Also 'a' and 'd' will have numerical values passed to them to
% reducing products associated with them.

%% Convert Angles


%% Classical Version (numerical computation - use degrees).
    if version == 0
    
        Mdh=[cosd(theta)    -sind(theta)*cosd(alpha)    sind(theta)*sind(alpha)     a*cosd(theta);
             sind(theta)     cosd(theta)*cosd(alpha)   -cosd(theta)*sind(alpha)     a*sind(theta);
                       0                 sind(alpha)                cosd(alpha)                 d;
                       0                           0                          0                1];


%% Craig's Version
    elseif version == 1
    
        Mdh=[            cosd(theta)                 -sind(theta)               0                   a;
             sind(theta)*cosd(alpha)      cosd(theta)*cosd(alpha)     -sind(alpha)     -sind(alpha)*d;
             sind(theta)*sind(alpha)      cosd(theta)*sind(alpha)      cosd(alpha)      cosd(alpha)*d;
                                   0                            0                0                 1];

    % This is for the symbolic derivation. 
    % Alphas are computed as degrees, theta's since they are symbolic use
    % the standard cos() and sin() functions. 
    else
    
        Mdh=[            cos(theta)                -sin(theta)                0                  a;
             sin(theta)*cosd(alpha)     cos(theta)*cosd(alpha)     -sind(alpha)     -sind(alpha)*d;
             sin(theta)*sind(alpha)     cos(theta)*sind(alpha)      cosd(alpha)      cosd(alpha)*d;
                                  0                          0                0                 1];            
    end

end
     