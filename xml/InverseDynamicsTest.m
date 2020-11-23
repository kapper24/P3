clear
%Symbolic definition 
syms tau1 tau2 tau3 tau4 
syms theta1 theta2 theta3 theta4 
syms d_theta1 d_theta2 d_theta3 d_theta4
syms dd_theta1 dd_theta2 dd_theta3 dd_theta4

%Definition of the zero vector, unit-vector, z & and gravitational vector
h1 = [0; 0; 0];
z = [0; 0; 1];
g = [0; 0; -9.82];

%Mass for links 
m1 = 264.61; 
m2 = 263.10; 
m3 = 142.00; 
m4 = 161.00; 

%Rationmatrices for each joint taken from DH-parameters
R_01 = [cos(theta1 + pi/2), -sin(theta1 + pi/2), 0
        sin(theta1 + pi/2),  cos(theta1 + pi/2), 0
                     0,               0, 1];
R_02 = R_01*[cos(theta2 - pi/2), -sin(theta2 - pi/2), 0
                          0,               0, 1
            -sin(theta2 - pi/2), -cos(theta2 - pi/2), 0];
R_03 = R_02*[cos(theta3), -sin(theta3), 0
             sin(theta3),  cos(theta3), 0
                   0,        0, 1];
R_04 = R_03*[cos(theta4), -sin(theta4), 0
             sin(theta4),  cos(theta4), 0
                   0,        0, 1];

%Local Inertia tensor - from solid works
i1 = [212334.27, 5.14, -10.62;
	  5.14, 192034.63, 3280.22;
	 -10.62, 3280.22, 146773.77];
i2 = [73984.05, 12163.56, -5231.59;
      12163.56, 1291198.05, -58.34
     -5231.59, -58.34, 1257216.65];
i3 = [35591.58, -3562.36, -234.81;
      -3562.36, 340324.49, -1.17;
       -234.81, -1.17, 322597.64];
i4 = [193479.06, -51646.20, -0.06;
      51646.20, 114126.84, 0.00;
	 -0.06, 0.00, 278336.63];

%Global Inertia tensor - By multiplying with the rotaionen the global
%inertia tensors can be found 
I1 = R_01*i1*transpose(R_01);
I2 = R_02*i2*transpose(R_02); 
I3 = R_03*i3*transpose(R_03);
I4 = R_04*i4*transpose(R_04);

%Lenght of joints - local frame - we only need the lenght of joint 2 and 3 
s2 = [220; 0; 0]; 
s3 = [147; 0; 0]; 

%Lenght of joints - global frame - by multiplying with the rotation matrix,
%S can be used to find Vi
S2 = R_02*s2;
S3 = R_03*s3;

%Lenght to Center of Mass - local frame - Found with solid works 
sc2 = [163.48; -0.76; -0.29];
sc3 = [101.38; -2.01; 0.02];
sc4 = [72.32; -28.70; 0];

%Lenght to Center of Mass - global frame - by multiplying with the rotation
%matrix Sc can be used to find Vci
Sc2 = R_02*sc2;
Sc3 = R_03*sc3;
Sc4 = R_04*sc4; 

%Rc is used to find potentiel energy - this can be called the height 
Rc2 = Sc2; 
Rc3 = S2 + Sc3;
Rc4 = S2 + S3 + Sc4;



%/Body 1 
%Our first link is a fixed rotation, therefor the V1 and Vc1 is 0. 
%omega1 is the rotational velocity and is equal to d_theta1
omega1 = [0; 0; d_theta1];
V1 = [0; 0; 0];
Vc1 = [0; 0; 0];
 
%Fixed rotation
%Kinetisk
T1 = 1/2*dot(omega1, (I1*omega1));
%Potentiel 
U1 = -m1*dot(g, h1);
%/Body 2
omega2 = omega1+d_theta2*R_02*z;
Vc2 = V1+cross(omega1, Sc2);
V2 = V1+cross(omega1, S2);

%General motion 
%Kinetisk
T2 = 1/2*m2*dot(Vc2, Vc2)+1/2*dot(omega2, (I2*omega2));
%Potentiel 
U2 = -m2*dot(g, Rc2);
%/Body 3 
omega3 = omega2+d_theta3*R_03*z; 
Vc3 = V2+cross(omega2, Sc3); %find equation
V3 = V2+cross(omega2, S3); %find equation

%General motion 
%Kinetisk
T3 = 1/2*m3*dot(Vc3, Vc3)+1/2*dot(omega3, (I3*omega3));
%Potentiel 
U3 = -m2*dot(g, Rc3);
%/Body 4
omega4 = omega3+d_theta4*R_04*z;
Vc4 = V3+cross(omega3, Sc4);
%V4 = R_04*(V3+Cross(omega3, S4)) 

%General motion 
%Kinetisk
T4 = 1/2*m4*dot(Vc4, Vc4)+1/2*dot(omega3, (I3*omega3));
%Potentiel 
U4 = -m4*dot(g, Rc4);
%First the lagragiant has to be calculated
L = T1-U1+T2+T3+T4-U2-U3-U4;

pd_T1 = diff(L, d_theta1);
d_pd_T1 = diff(pd_T1,theta1)*d_theta1+diff(pd_T1,d_theta1)*dd_theta1+diff(pd_T1,theta2)*d_theta2+diff(pd_T1,d_theta2)*dd_theta2+diff(pd_T1,theta3)*d_theta3+diff(pd_T1,d_theta3)*dd_theta3+diff(pd_T1,theta4)*d_theta4+diff(pd_T1,d_theta4)*dd_theta4;
pd_V1 = diff(L,theta1);

pd_T2 = diff(L, d_theta2);
d_pd_T2 = diff(pd_T2,theta1)*d_theta1+diff(pd_T2,d_theta1)*dd_theta1+diff(pd_T2,theta2)*d_theta2+diff(pd_T2,d_theta2)*dd_theta2+diff(pd_T2,theta3)*d_theta3+diff(pd_T2,d_theta3)*dd_theta3+diff(pd_T2,theta4)*d_theta4+diff(pd_T2,d_theta4)*dd_theta4;
pd_V2 = diff(L,theta2);

pd_T3 = diff(L, d_theta3);
d_pd_T3 = diff(pd_T3,theta1)*d_theta1+diff(pd_T3,d_theta1)*dd_theta1+diff(pd_T3,theta2)*d_theta2+diff(pd_T3,d_theta2)*dd_theta2+diff(pd_T3,theta3)*d_theta3+diff(pd_T3,d_theta3)*dd_theta3+diff(pd_T3,theta4)*d_theta4+diff(pd_T3,d_theta4)*dd_theta4;
pd_V3 = diff(L,theta3);

pd_T4 = diff(L, d_theta4);
d_pd_T4 = diff(pd_T4,theta1)*d_theta1+diff(pd_T4,d_theta1)*dd_theta1+diff(pd_T4,theta2)*d_theta2+diff(pd_T4,d_theta2)*dd_theta2+diff(pd_T4,theta3)*d_theta3+diff(pd_T4,d_theta3)*dd_theta3+diff(pd_T4,theta4)*d_theta4+diff(pd_T4,d_theta4)*dd_theta4;
pd_V4 = diff(L,theta4);

%Partial diverativ with matlab
tau1 = d_pd_T1-pd_V1;
tau2 = d_pd_T2-pd_V2;
tau3 = d_pd_T3-pd_V3;
tau4 = d_pd_T4-pd_V4;

%simpleTau1 = simplify(tau1)
%simpleTau2 = simplify(tau2)
%simpleTau3 = simplify(tau3)
%simpleTau4 = simplify(tau4)