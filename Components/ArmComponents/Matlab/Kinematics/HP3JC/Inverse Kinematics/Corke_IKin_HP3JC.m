% Computation of IKinematics using Corke's toolking.
% 1) Create the links
% 2) Create the robot
% 3) Call Ikine

function Q = Corke_IKin_HP3JC(XYZRPY, ToolType)

    % DH Parameters
    % Link lengths
    a0 =   0.0;
    a1 =   0.0;
    a2 = 260.0;       % Length of link 2
    a3 =  30.0;       % Originally not considered, now considered
    a4 =   0.0;
    a5 =   0.0;

    % Link offsets
    d1 =    0.0;
    d2 =    0.0; 
    d3 =    0.0;
    d4 = -270.0;      % Revised. Changed the sign of the d4 and d6 from positive to negative. This provides the right sign for the x-direction of the end-effector.
    d5 =    0.0;
    % Depending on the kind of tool type this d6 will change.
    if ToolType == 0        % Empty. Just the length of the wrist
        d6 = -90;   
    elseif ToolType == 1    % Barret. The lenght of the barret hand is added.
        d6 = -244.5;     
    elseif ToolType == 2    % Assembly structure, lenght of wrist, barret and truss.
        d6 = -244.5 - 7112;     
    end
       
    % Alpha angles
    alpha0 =    0.0;     
    alpha1 =  -pi/2;
    alpha2 =     pi;
    alpha3 =  -pi/2;  
    alpha4 =   pi/2;
    alpha5 =  -pi/2;
    
    % Theta angles
    theta1 =   0.0;
    theta2 = -pi/2;   
    theta3 =   0.0;   
    theta4 =   0.0;  
    theta5 =   0.0;  
    theta6 =   0.0; 

    % Create the HP3JC robot object. First create each of the links.
    %  link([alpha   A theta   d revolute(0)], convention)
    L1=link([alpha0 a0 theta1 d1 0], 'modified');
    L2=link([alpha1 a1 theta2 d2 0], 'modified');
    L3=link([alpha2 a2 theta3 d3 0], 'modified');
    L4=link([alpha3 a3 theta4 d4 0], 'modified');
    L5=link([alpha4 a4 theta5 d5 0], 'modified');
    L6=link([alpha5 a5 theta6 d6 0], 'modified');
    
    % Create the robot object
    HP3JC = robot({L1 L2 L3 L4 L5 L6});
  
    % Define the goal trajectory point - use input argument from fnctn    
     R06 = RPY_2_R06(XYZRPY); 
     
     % ********** NOTE **********
     % If your computer says that it could not solve the IKin's, it is due
     % to an insufficiency of computer power. If so, use the code below.     
%      Test fkin
%     qz = [0, -pi/2, 0, 0, 0, 0];
%     T06 = fkine(HP3JC, qz);  
%     T06(13) = XYZRPY(1);
%     T06(14) = XYZRPY(2);
%     T06(15) = XYZRPY(3);    

    % Call the inverse kinematics call
    Q = ikine(HP3JC, R06);
    % Q = ikine(HP3JC, R06); % Ikine won't take the values of R06 even
    % though they are the same as T06. The difference is that "0" values
    % for T06 exist to 3 decimal places. Have not been able to do that with
    % R06. Hence, the workaround seen above. 

    % Convert to degrees
    Q = Q * 180/pi;
    
    % The adjustments before are a result of observed data. In some
    % experiments the HP3JC robot was asked to move to different cartesian
    % locations. From there, the angles were recorded. The file can be
    % found at: 
    % Adjust q4
    if Q(4) < 0
        Q(4) = 180 + Q(4);
    end
    
    % Adjust q5
    if Q(5) > 0
        Q(5) = -Q(5) - 90;
    else
        Q(5) = Q(5) - 90;
    end
    
    % Adjust q6
    Q(6) = 180 - Q(4);
    if Q(6) > 90
        Q(6) = Q(6) - 180;
        Q(4) = Q(4) + 180;
    end    

end