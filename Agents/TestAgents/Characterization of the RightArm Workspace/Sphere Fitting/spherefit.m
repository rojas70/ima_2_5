function out = spherefit(x)

% Function that computes the distance betweeen the radius of a shpere and
% its center. This function will normally be called by lsqnonlin, which
% will pass an x vector composed of a Cx,Cy,Cz, and r, typical of a
% spherical equation: (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 - r = 0

% Segment the vector into Cx,Cy,Cz, and R
cx = x(1);
cy = x(2);
cz = x(3);
r  = x(4);

% This variable will be established before calling this function. It will
% represent the cartesian coordinates of the sphere used to find a center
% point and radius. I.e. coords[XI,YI,ZI].
global coords

% Find the length of coords
n = size(coords,1);

% Run a loop to find the distance for each of the points of the surface of
% the sphere

out = zeros(n,1);
for i=1:n
    out(i) = sqrt( (coords(i,1)-cx)^2 + (coords(i,2)-cy)^2 + (coords(i,3)-cz)^2)-r;
end