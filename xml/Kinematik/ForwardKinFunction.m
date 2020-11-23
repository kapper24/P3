%% Crustecrwler forward kinematics
function [T04] = ForwardKinFunction(t1, t2, t3, t4)
% Denne section udregner Matricen T04, med de vinkler vi selv s?tter ind
% t1, t2, t3 og t4 beskriver theta vinklerne i hver motor
syms t1 t2 t3 t4
%Her kan man s?tte vinkler ind i hver motor:
%Vinklerne inds?ttes i denavit hartenberg parameterne for vores robot:
T01=TDH(0,0,0,t1+90*pi/180)
T12=TDH(-90*pi/180,0,0,t2-90*pi/180)
T23=TDH(0,220,0,t3);
T34=TDH(0,147,0,t4);
%Base to final joint
T04=T01*T12*T23*T34
end 