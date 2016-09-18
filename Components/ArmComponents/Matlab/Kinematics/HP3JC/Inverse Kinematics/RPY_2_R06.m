function R06 = RPY_2_R06(XYZRPY)

%% Global variable
    R06 = zeros(4,4);

    % Precompute Trig Functions in radians to save on evaluations according
    % to euler-angles (also known as roll-pitch-yaw angles)
	ca = cos(XYZRPY(6)); sa = sin(XYZRPY(6));   % Yaw
	cb = cos(XYZRPY(5)); sb = sin(XYZRPY(5));   % Pitch
    % Help computation of cos (pi/2)
    if abs(XYZRPY(5)) == 1.57
        cb = 0;
    end
	cg = cos(XYZRPY(4)); sg = sin(XYZRPY(4));   % Roll
    
    % Inverse solution for roll-pitch-yaw angle set
    % R = Rz(alpha)Ry(Beta)Rx(gamma). Where,
    % Rz_alpha = [ca -sa   0;
    %             sa  ca   0;
    %              0   0   1;];
    % 
    % Ry_beta  = [cb   0  sb;
    %              0   1   0;
    %            -sb   0  cb;];   
    % 
    % Rx_gamma = [ 1   0   0;
    %              0  cg -sg;
    %              0  sg  cb;];     
    % R = | ca -sa 0 || cb  0 sb || 1  0 0  |		 | r11 r12 r13  Px|
    % 	  | sa ca  0 || 0   1  0 || 0 cg -sg| = oM = | r21 r22 r23  Py|	// See Robot Simulation by Dr. Cook page A-12
    % 	  | 0   0  1 ||-sb  0 cb || 0 sg cg |		 | r31 r32 r33  Pz|
    %                                                |   0   0   0   1|   
         
%% R06 matrix computations                                             
             
	% First Column
	R06(1,1) = ca*cb;				% r11
	R06(2,1) = sa*cb;				% r21
	R06(3,1) = -sb;					% r31
	R06(4,1) = 0.0;					% r41

	% Second Column
	R06(1,2) = ca*sb*sg - sa*cg;	% r12
	R06(2,2) = sa*sb*sg + ca*cg;	% r22
	R06(3,2) = cb*sg;				% r32
	R06(4,2) = 0.0;					% r42
	
	% Third Column
	R06(1,3) = ca*sb*cg + sa*sg;	% r13
	R06(2,3) = sa*sb*cg - ca*sg;	% r23
	R06(3,3) = cb*cg;				% r33
	R06(4,3) = 0.0;					% r43

	% Fourth Column -  position vector.
	R06(1,4) = XYZRPY(1);			% X	
	R06(2,4) = XYZRPY(2);			% Y
	R06(3,4) = XYZRPY(3);			% Z
	R06(4,4) = 1.0;
    
end