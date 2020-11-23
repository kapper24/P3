%% Crustcrawler inverse kinematics:
function [t1, t2, t3, t4] = InverseKinFunction(x, y, z, z_patient, y_patient)
% Formler til inverse kinematics:
syms x y z z_patient y_patient
L = sqrt((x^2)+(y^2)+(z^2))
phi1 = asin(z/L)
phi2 = acos(((220^2)+(L^2)-147^2)/(2*220*L))
phi3 = acos(((220^2)+(147^2)-L^2)/(2*220*147))

% Endelige formler hvor x, y og z indsættes:
t1 = atan2(-x,y)*180/pi
t2 = (90*pi/180-phi1-phi2)*180/pi
t3 = 180-(phi3)*180/pi
t4 = (90-t2-t3)+atan(abs(z-z_patient)/abs(y_patient-y))*180/pi
end 