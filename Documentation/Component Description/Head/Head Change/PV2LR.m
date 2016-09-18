% convert pan and verge angles 
% to left and right angles
% (angles are in radians)
%
% function [L,R] = PV2LR([P V])

function [L,R] = PV2LR(PV)

P = PV(1,1);
V = PV(1,2);

CP = cos(P);
SP = sin(P);
CV = cos(V);
SV = sin(V);

R = atan2(CV*SP+SV,CV*CP);
L = atan2(CV*SP-SV,CV*CP);

return;

