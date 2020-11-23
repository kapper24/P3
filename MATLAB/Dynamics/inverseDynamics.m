clear
%Symbolic definition 
syms tau1 tau2 tau3 tau4 real
syms theta1 theta2 theta3 theta4 real
syms d_theta1 d_theta2 d_theta3 d_theta4 real 
syms dd_theta1 dd_theta2 dd_theta3 dd_theta4 real
%Definition of the zero vector, unit-vector, z & and gravitational vector
h1 = [0; 0; 0];
z = [0; 0; 1];
g = [0; 0; -9.82];

%Mass for links 
m1 = 264.61/1000; 
m2 = 263.10/1000; 
m3 = 142.00/1000; 
m4 = 161.00/1000; 

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
i1 = ([180746.81,   4.25,       -9.07
       4.25,        163815.97,  2751.51
       -9.07,       2751.51,    125650.60])/1000000000;
i2 = ([65785.55,    10428.75,   -4474.81
       10428.75,    1226411.48, -51.74
       -4474.81,    -51.74,     119407])/1000000000;
i3 = ([40062.95,    -4676.13,   -225.49
       -4676.13,    387451.92,  -1.45
       -225.49,     -1.45,      366295.38])/1000000000;
i4 = ([202964.37,   -61712.92,  -0.07
       -61712.92,   134276.04,  0.00
       -0.07,       0.00,       302429.25])/1000000000;

%Global Inertia tensor - By multiplying with the rotaionen the global
%inertia tensors can be found 
I1 = R_01*i1*transpose(R_01);
I2 = R_02*i2*transpose(R_02); 
I3 = R_03*i3*transpose(R_03);
I4 = R_04*i4*transpose(R_04);

%Lenght of joints - local frame - we only need the lenght of joint 2 and 3
s1 = [0;     0; 0];
s2 = [0.220; 0; 0]; 
s3 = [0.147; 0; 0]; 

%Lenght of joints - global frame - by multiplying with the rotation matrix,
%S can be used to find Vi
S1 = R_01*s1;
S2 = R_02*s2;
S3 = R_03*s3;

%Lenght to Center of Mass - local frame - Found with solid works 
sc2 = [0.15479; -0.00089; -0.00026];
sc3 = [0.09747; -0.00189; 0.00002];
sc4 = [0.07014; -0.02734; 0.0];

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
T1 = 1/2*transpose(omega1)*(I1*omega1);
%Potentiel 
U1 = -m1*transpose(g)*h1;


%/Body 2
omega2 = omega1+d_theta2*R_02*z;
V2 = V1+cross(omega1, S1);
Vc2 = V2+cross(omega2, Sc2);
%General motion 
%Kinetisk
T2 = 1/2*m2*(transpose(Vc2)*Vc2)+1/2*transpose(omega2)*(I2*omega2);
%Potentiel 
U2 = -m2*transpose(Rc2)*g;


%/Body 3 
omega3 = omega2+d_theta3*R_03*z; 
V3 = V2+cross(omega2, S2); %find equation
Vc3 = V3+cross(omega3, Sc3); %find equation
%General motion 
%Kinetisk
T3 = 1/2*m3*(transpose(Vc3)*Vc3)+1/2*transpose(omega3)*(I3*omega3);
%Potentiel 
U3 = -m3*transpose(Rc3)*g;


%/Body 4
omega4 = omega3+d_theta4*R_04*z;
V4 = V3+cross(omega3, S3);
Vc4 = V4+cross(omega4, Sc4);
%General motion 
%Kinetisk
T4 = 1/2*m4*(transpose(Vc4)*Vc4)+1/2*transpose(omega4)*(I2*omega4);
%Potentiel 
U4 = -m4*transpose(Rc4)*g;
%First the lagragiant has to be calculated
L = T1+T2+T3+T4-U1-U2-U3-U4;

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
simpleTau1 = simplify(expand(tau1));
vpaSimpleTau1 = vpa(simpleTau1);
a_vpaSimpleTau1 = diff(vpaSimpleTau1, dd_theta1);
b_vpaSimpleTau1 = diff(vpaSimpleTau1, dd_theta2);
c_vpaSimpleTau1 = diff(vpaSimpleTau1, dd_theta3);
d_vpaSimpleTau1 = diff(vpaSimpleTau1, dd_theta4);

simpleTau2 = simplify(expand(tau2));
vpaSimpleTau2 = vpa(simpleTau2);
a_vpaSimpleTau2 = diff(vpaSimpleTau2, dd_theta1);
b_vpaSimpleTau2 = diff(vpaSimpleTau2, dd_theta2);
c_vpaSimpleTau2 = diff(vpaSimpleTau2, dd_theta3);
d_vpaSimpleTau2 = diff(vpaSimpleTau2, dd_theta4);

simpleTau3 = simplify(expand(tau3));
vpaSimpleTau3 = vpa(simpleTau3);
a_vpaSimpleTau3 = diff(vpaSimpleTau3, dd_theta1);
b_vpaSimpleTau3 = diff(vpaSimpleTau3, dd_theta2);
c_vpaSimpleTau3 = diff(vpaSimpleTau3, dd_theta3);
d_vpaSimpleTau3 = diff(vpaSimpleTau3, dd_theta4);

simpleTau4 = simplify(expand(tau4));
vpaSimpleTau4 = vpa(simpleTau4);
a_vpaSimpleTau4 = diff(vpaSimpleTau4, dd_theta1);
b_vpaSimpleTau4 = diff(vpaSimpleTau4, dd_theta2);
c_vpaSimpleTau4 = diff(vpaSimpleTau4, dd_theta3);
d_vpaSimpleTau4 = diff(vpaSimpleTau4, dd_theta4);

M = [a_vpaSimpleTau1, b_vpaSimpleTau1, c_vpaSimpleTau1, d_vpaSimpleTau1;
     a_vpaSimpleTau2, b_vpaSimpleTau2, c_vpaSimpleTau2, d_vpaSimpleTau2;
     a_vpaSimpleTau3, b_vpaSimpleTau3, c_vpaSimpleTau3, d_vpaSimpleTau3;
     a_vpaSimpleTau4, b_vpaSimpleTau4, c_vpaSimpleTau4, d_vpaSimpleTau4];
simpleM = simplify(expand(M));
 
dd_vector = [dd_theta1; dd_theta2; dd_theta3; dd_theta4];
d_vector = [d_theta1; d_theta2; d_theta3; d_theta4];
zero = [0; 0; 0; 0];

G = [subs(vpaSimpleTau1, [(d_vector);(dd_vector)], [zero;zero]);
     subs(vpaSimpleTau2, [(d_vector);(dd_vector)], [zero;zero]);
     subs(vpaSimpleTau3, [(d_vector);(dd_vector)], [zero;zero]);
     subs(vpaSimpleTau4, [(d_vector);(dd_vector)], [zero;zero])];
simpleG = simplify(expand(G));

EOM = [vpaSimpleTau1; vpaSimpleTau2; vpaSimpleTau3; vpaSimpleTau4];
C = EOM - (simpleM*dd_vector) - simpleG;
simpleC = simplify(expand(C));

EOMFinal = simpleM*dd_vector + simpleC + simpleG