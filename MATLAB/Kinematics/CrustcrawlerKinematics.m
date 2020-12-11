%% Crustecrwler forward kinematics
% Denne section udregner Matricen T04, med de vinkler vi selv s?tter ind
% t1, t2, t3 og t4 beskriver theta vinklerne i hver motor
syms t1 t2 t3 t4
PI=sym(pi);
%Her kan man s?tte vinkler ind i hver motor:
%t1=10*pi/180;
%t1 = 10
%t2=20*pi/180;
%t2 = 20
%t3=30*pi/180;
%t3 = 30
%t4=40*pi/180;
%t4=40
%Vinklerne inds?ttes i denavit hartenberg parameterne for vores robot:

%The TDH is a function for calculating transformation matrices using
%Denavit Hartenberg Parameters (The TDH.m file can be found under the 
%kinematics folder in the Matlab folder in the appendix).
T01=TDH(0,0,0,t1+90*PI/180);
T12=TDH(-90*PI/180,0,0,t2-90*PI/180);
T23=TDH(0,220,0,t3);
T34=TDH(0,147,0,t4);
%Base to final link
T04=T01*T12*T23*T34
simplify(T04);
%% Final transformation matrix, joint 4 in relation to joint 1
T04 =   [cos(t4)*(cos(t3)*cos(t1 + pi/2)*cos(t2 - pi/2) - cos(t1 + pi/2)*sin(t3)*sin(t2 - pi/2)) - sin(t4)*(cos(t3)*cos(t1 + pi/2)*sin(t2 - pi/2) + cos(t1 + pi/2)*cos(t2 - pi/2)*sin(t3)), - cos(t4)*(cos(t3)*cos(t1 + pi/2)*sin(t2 - pi/2) + cos(t1 + pi/2)*cos(t2 - pi/2)*sin(t3)) - sin(t4)*(cos(t3)*cos(t1 + pi/2)*cos(t2 - pi/2) - cos(t1 + pi/2)*sin(t3)*sin(t2 - pi/2)), -sin(t1 + pi/2), 220*cos(t1 + pi/2)*cos(t2 - pi/2) + 147*cos(t3)*cos(t1 + pi/2)*cos(t2 - pi/2) - 147*cos(t1 + pi/2)*sin(t3)*sin(t2 - pi/2);
         cos(t4)*(cos(t3)*cos(t2 - pi/2)*sin(t1 + pi/2) - sin(t3)*sin(t1 + pi/2)*sin(t2 - pi/2)) - sin(t4)*(cos(t3)*sin(t1 + pi/2)*sin(t2 - pi/2) + cos(t2 - pi/2)*sin(t3)*sin(t1 + pi/2)), - cos(t4)*(cos(t3)*sin(t1 + pi/2)*sin(t2 - pi/2) + cos(t2 - pi/2)*sin(t3)*sin(t1 + pi/2)) - sin(t4)*(cos(t3)*cos(t2 - pi/2)*sin(t1 + pi/2) - sin(t3)*sin(t1 + pi/2)*sin(t2 - pi/2)),  cos(t1 + pi/2), 220*cos(t2 - pi/2)*sin(t1 + pi/2) + 147*cos(t3)*cos(t2 - pi/2)*sin(t1 + pi/2) - 147*sin(t3)*sin(t1 + pi/2)*sin(t2 - pi/2);
                                                                   - sin(t4)*(cos(t3)*cos(t2 - pi/2) - sin(t3)*sin(t2 - pi/2)) - cos(t4)*(cos(t3)*sin(t2 - pi/2) + cos(t2 - pi/2)*sin(t3)),                                                               sin(t4)*(cos(t3)*sin(t2 - pi/2) + cos(t2 - pi/2)*sin(t3)) - cos(t4)*(cos(t3)*cos(t2 - pi/2) - sin(t3)*sin(t2 - pi/2)),               0,                                            - 220*sin(t2 - pi/2) - 147*cos(t3)*sin(t2 - pi/2) - 147*cos(t2 - pi/2)*sin(t3);
                                                                                                                                                                                         0,                                                                                                                                                                                   0,               0,                                                                                                                         1];
 
%% Crustcrawler inverse kinematics:
syms x y z
%x = -50;
%y = 173.5986;
%z = 200;

y_patient = 500;
z_patient = 0;

%Formler til inverse kinematics:
L = sqrt((x^2)+(y^2)+(z^2))
phi1 = asin(z/L)
phi2 = acos(((220^2)+(L^2)-147^2)/(2*220*L))
phi3 = acos(((220^2)+(147^2)-L^2)/(2*220*147))

% Endelige formler hvor x, y og z indsættes:
t1 = atan2(-x,y)*180/pi
t2 = (90*pi/180-phi1-phi2)*180/pi
t3 = 180-(phi3)*180/pi
t4 = (90-t2-t3)+(atan((z-z_patient)/(y_patient-y))*180/pi)