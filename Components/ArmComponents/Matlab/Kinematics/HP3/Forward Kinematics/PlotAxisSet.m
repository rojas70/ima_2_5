function PlotAxisSet(AxisSet,Pose,color)

xO = Pose(1,4);
yO = Pose(2,4);
zO = Pose(3,4);

NewAxes = AxisSet(:,:,2)*Pose;
xAxis = NewAxes(1:3,1)+Pose(1:3,4);
yAxis = NewAxes(1:3,2)+Pose(1:3,4);
zAxis = NewAxes(1:3,3)+Pose(1:3,4);

% plot the world frame w/ x, y, & z axes 
line([xO xAxis(1)],[yO xAxis(2)], [zO xAxis(3)],'Color',color,'LineWidth',2,'marker','.','markersize',15);  % x-axis
line([xO yAxis(1)],[yO yAxis(2)], [zO yAxis(3)],'Color',color,'LineWidth',2,'marker','o','markersize',5);   % y-axis
line([xO zAxis(1)],[yO zAxis(2)], [zO zAxis(3)],'Color',color,'LineWidth',2);                               % z-axis

