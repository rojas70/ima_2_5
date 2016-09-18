%% Author: epokh
%% Website: www.epokh.org/drupy
%% This software is under GPL
%% Modified by Juan Rojas to work symbolically

function [Mdh]=DHmatrix_sym(theta,d,a,alpha, version)
% output:   DH matrix
% input:    DH parameters:
% theta:    rotation along x(n) axis
% d:        traslation along z(n) axis
% a:        translation along x(n+1) axis
% alpha:    rotation along x(n+1) axis
% All angles expressed in degrees

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

%% Classical Version
    if version == 0
    
        Mdh=[cos(theta)    -sin(theta)*cosd(alpha)    sin(theta)*sin(alpha)     a*cos(theta);
             sin(theta)    cos(theta)*cosd(alpha)     -cos(theta)*sin(alpha)    a*sin(theta);
             0,            sin(alpha),                cosd(alpha),              d;
             0,            0,                         0,                        1];


%% Craig's Version
    elseif version == 1
    
        Mdh=[cos(theta)                 -sin(theta)                0                             a;
             sin(theta)*cosd(alpha)     cos(theta)*cosd(alpha)     -sind(alpha)     -sind(alpha)*d;
             sin(theta)*sind(alpha),    cos(theta)*sind(alpha),    cosd(alpha),      cosd(alpha)*d;
             0,                         0,                         0,                            1];

    else
    
        Mdh=[cos(theta)                 -sin(theta)                0                             a;
             sin(theta)*cosd(alpha)     cos(theta)*cosd(alpha)     -sind(alpha)     -sind(alpha)*d;
             sin(theta)*sind(alpha),    cos(theta)*sind(alpha),    cosd(alpha),      cosd(alpha)*d;
             0,                         0,                         0,                            1];       
     
    end

end
     