% convert left and right camera angles 
% to pan and verge angles. 
% (angles are in radians)
%
% function [P,V] = LR2PV([L R])

function [P,V] = LR2PV(LR)

L = LR(1,1);
R = LR(1,2);

CL = cos(L);
SL = sin(L);
TL = tan(L);
CR = cos(R);
SR = sin(R);
TR = tan(R);

SRL = sin(R-L);
CRL = cos(R-L);

P = atan((TL+TR)/2);
V = atan(SRL/(sqrt((CR^2)+(2*CR*CL*CRL)+(CL^2))));

return;

