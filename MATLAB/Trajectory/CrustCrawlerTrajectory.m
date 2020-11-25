%% CrustCrawler trajectory (from moving to still)
syms t a b c d e f g h i j k l
theta0 = [a;b;c;d];        % insert start angle
thetaf = [e;f;g;h];        % insert end angle
dtheta = [i;j;k;l];        % insert start speed
syms tf % = 1;             % insert time duration

a0_1 = theta0(1);                             % outputs the value of a0
a1_1 = dtheta(1);
a2_1 = 3/(tf^2)*(thetaf(1)-theta0(1));       % outputs the value of a2
a3_1 = -2/(tf^3)*(thetaf(1)-theta0(1));      % outputs the value of a3
pos1 = a0_1+(a1_1*t)+(a2_1*t^2)+(a3_1*t^3);
vel1 = diff(pos1,t);
acc1 = diff(vel1,t);

a0_2 = theta0(2);                             % outputs the value of a0
a1_2 = dtheta(2);
a2_2 = 3/(tf^2)*(thetaf(2)-theta0(2));       % outputs the value of a2
a3_2 = -2/(tf^3)*(thetaf(2)-theta0(2));      % outputs the value of a3
pos2 = a0_2+(a1_2*t)+(a2_2*t^2)+(a3_2*t^3);
vel2 = diff(pos2,t);
acc2 = diff(vel2,t);

a0_3 = theta0(3);                             % outputs the value of a0
a1_3 = dtheta(3);
a2_3 = 3/(tf^2)*(thetaf(3)-theta0(3));       % outputs the value of a2
a3_3 = -2/(tf^3)*(thetaf(3)-theta0(3));      % outputs the value of a3
pos3 = a0_3+(a1_3*t)+(a2_3*t^2)+(a3_3*t^3);
vel3 = diff(pos3,t);
acc3 = diff(vel3,t);

a0_4 = theta0(4);                             % outputs the value of a0
a1_4 = dtheta(4);
a2_4 = 3/(tf^2)*(thetaf(4)-theta0(4));       % outputs the value of a2
a3_4 = -2/(tf^3)*(thetaf(4)-theta0(4));      % outputs the value of a3
pos4 = a0_4+(a1_4*t)+(a2_4*t^2)+(a3_4*t^3);
vel4 = diff(pos4,t);
acc4 = diff(vel4,t);

pos = [pos1;pos2;pos3;pos4]
vel = [vel1;vel2;vel3;vel4]
acc = [acc1;acc2;acc3;acc4]