AxisSet = zeros(4,4,2);
AxisSet(4,4,1) = 1';
AxisSet(:,:,2) = diag([25 25 25 1]);

% generate a 3D plot of the geometry
fig = figure;
hold on

% plot the axes
% X
line([0 425],[-225 -225],[0 0],'color','b')
text(450, -225, 25, 'X','color','b')
% Y
line([0 0],[-225 225],[0 0],'color','g')
text(25, 250, 25, 'Y','color','g')
% Z
line([0 0],[-225 -225],[0 425],'color','r')
text(25, -225, 450, 'Z','color','r')

% plot the links
line([  0   0],[0 0], [  0 110],'Color',[1,0.7,0],'LineWidth',1); % 0 to 1 (d1)
line([  0 100],[0 0], [110 110],'Color','y','LineWidth',1); % 1 to 2 (a1)
line([100 100],[0 0], [110 400],'Color','y','LineWidth',1); % 2 to 3 (a2)
line([100 100],[0 0], [400 485],'Color','y','LineWidth',1); % 3 to 4 (a3)
line([100 400],[0 0], [485 485],'Color',[1,0.7,0],'LineWidth',1); % 4 to 5 (d4)
line([400 490],[0 0], [485 485],'Color',[1,0.7,0],'LineWidth',1); % 5 to 6 (d5)


% Plot the world frame @ Joint 1 (actual location)
Pose0 = eye(4);
PlotAxisSet(AxisSet,Pose0,'k');

% Plot Frame 1 (virtual location)
Pose1 = eye(4);
Pose1(1:3,4) = [0 0 110]';
PlotAxisSet(AxisSet,Pose1,[0.75 0.75 0.75]);

% Plot Frame 2 (Joint 2)
Pose2 = eye(4);
Pose2(1:4,1:4) = rotX(-pi/2);
Pose2(1:3,4) = [100 0 110]';
PlotAxisSet(AxisSet,Pose2,'b');

% config consistent with TP controls

title('HP3 home configuration consistent with TP controls');

% Plot Frame 3 (Joint 3)
Pose3 = eye(4);
Pose3(1:4,1:4) = RotY(-pi/2)*RotX(pi/2);
Pose3(1:3,4) = [100 0 110+290]';
PlotAxisSet(AxisSet,Pose3,'g');

% Plot Joint 4 (actual location)
Pose4 = eye(4);
Pose4(1:4,1:4) = RotX(pi)*RotY(-pi/2);
Pose4(1:3,4) = [100+101 0 110+290+85]';
PlotAxisSet(AxisSet,Pose4,'r');

% Plot Frame 4 (virtual location)
Pose4 = eye(4);
Pose4(1:4,1:4) = RotX(pi)*RotY(-pi/2);
Pose4(1:3,4) = [100 0 110+290+85]';
PlotAxisSet(AxisSet,Pose4,[1.0 0.75 0.75]);

% Plot Frame 6
Pose6 = eye(4);
Pose6(1:4,1:4) = RotX(pi)*RotY(-pi/2);
Pose6(1:3,4) = [100+101+199+90 0 110+290+85]';
PlotAxisSet(AxisSet,Pose6,'m');

% Plot Frame 5
Pose5 = eye(4);
Pose5(1:4,1:4) = RotX(pi/2)*RotZ(-pi/2);
Pose5(1:3,4) = [100+101+199 0 110+290+85]';
PlotAxisSet(AxisSet,Pose5,'c');


% % config consistent with DH parameter document
% 
% title('HP3 home configuration based on DH parameter document');
% 
% % Plot Frame 3 (Joint 3)
% Pose3 = eye(4);
% Pose3(1:3,1:3) = RotY(-pi/2)*RotX(-pi/2);
% Pose3(1:3,4) = [100 0 110+290]';
% PlotAxisSet(AxisSet,Pose3,'g');
% 
% % Plot Joint 4 (actual location)
% Pose4 = eye(4);
% Pose4(1:3,1:3) = RotY(-pi/2);
% Pose4(1:3,4) = [100+101 0 110+290+85]';
% PlotAxisSet(AxisSet,Pose4,'r');
% 
% % Plot Frame 4 (virtual location)
% Pose4 = eye(4);
% Pose4(1:3,1:3) = RotY(-pi/2);
% Pose4(1:3,4) = [100 0 110+290+85]';
% PlotAxisSet(AxisSet,Pose4,[1.0 0.50 0.50]);
% 
% % Plot Joint 6 (virtual location)
% Pose6 = eye(4);
% Pose6(1:3,1:3) = RotY(-pi/2);
% Pose6(1:3,4) = [100+300 0 110+290+85]';
% PlotAxisSet(AxisSet,Pose6,[1.0 0.75 1.0]);
% 
% % Plot Frame 5 (Joint 5)
% Pose5 = eye(4);
% Pose5(1:3,1:3) = RotY(-pi/2)*RotX(-pi/2);
% Pose5(1:3,4) = [100+300 0 110+290+85]';
% PlotAxisSet(AxisSet,Pose5,'c');
% 
% % Plot Joint 6 (actual location)
% Pose6 = eye(4);
% Pose6(1:3,1:3) = RotY(-pi/2);
% Pose6(1:3,4) = [100+300+90 0 110+290+85]';
% PlotAxisSet(AxisSet,Pose6,'m');
% 

% EE flange center
plot3(100+101+199+90, 0, 110+290+85,'marker','.','markersize',15,'color','k');


axis equal
axis([0 550 -250 250 0 500])
hold off

