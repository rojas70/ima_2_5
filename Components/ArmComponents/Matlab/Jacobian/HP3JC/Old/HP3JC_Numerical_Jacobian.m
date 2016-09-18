function J = HP3JC_Numerical_Jacobian(Angle)

% HP3JC Force Controller outputs

Angle = (Angle*pi)/180;

J11 = -0.25*(sin(Angle(2))*(1080*cos(Angle(3) + Angle(4)) + 489*cos(Angle(3) + Angle(4) - Angle(6)) + 489*cos(Angle(3) + Angle(4) + Angle(6)) + 2*(520*sin(Angle(3)) + 3*sin(Angle(3) + Angle(4))*(20 - 163*cos(Angle(5))*sin(Angle(6))))));
J12 = -(sin(Angle(2))*(1080*cos(Angle(3) + Angle(4)) + 489*cos(Angle(3) + Angle(4) - Angle(6)) + 489*cos(Angle(3) + Angle(4) + Angle(6)) + 2*(520*sin(Angle(3)) + 3*sin(Angle(3) + Angle(4))*(20 - 163*cos(Angle(5))*sin(Angle(6))))))/4;
J13 = 0.5*(-520*cos(Angle(3)) + 3*(180 + 163*cos(Angle(6)))*sin(Angle(3) + Angle(4)) + cos(Angle(3) + Angle(4))*(-60 + 489*cos(Angle(5))*sin(Angle(6))));

J21 = -0.75*(cos(Angle(2))*(360*cos(Angle(3) + Angle(4)) + 163*cos(Angle(3) + Angle(4) - Angle(6)) + 163*cos(Angle(3) + Angle(4) + Angle(6)) + 2*sin(Angle(3) + Angle(4))*(20 - 163*cos(Angle(5))*sin(Angle(6)))));
J22 = -0.75*(sin(Angle(2))*(360*cos(Angle(3) + Angle(4)) + 163*cos(Angle(3) + Angle(4) - Angle(6)) + 163*cos(Angle(3) + Angle(4) + Angle(6)) + 2*sin(Angle(3) + Angle(4))*(20 - 163*cos(Angle(5))*sin(Angle(6)))));
J23 = 0.5*(3*((180 + 163*cos(Angle(6)))*sin(Angle(3) + Angle(4)) + cos(Angle(3) + Angle(4))*(-20 + 163*cos(Angle(5))*sin(Angle(6)))));

J31 = 0.5*(489*(cos(Angle(5))*sin(Angle(2)) + cos(Angle(2))*cos(Angle(3) + Angle(4))*sin(Angle(5)))*sin(Angle(6)));
J32 = 0.5*(-489*(cos(Angle(2))*cos(Angle(5)) - cos(Angle(3) + Angle(4))*sin(Angle(2))*sin(Angle(5)))*sin(Angle(6)));
J33 = 0.5*(-489*sin(Angle(3) + Angle(4))*sin(Angle(5))*sin(Angle(6)));

J = [J11 J12 J13
     J21 J22 J23
     J31 J32 J33];
end