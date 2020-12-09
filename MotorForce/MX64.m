TorqueAndVelocity=[0.22495656	-2.565948157
0.22495656	-1.798561792
0.22495656	-0.98321378
0.22495656	-0.047961648
0.22495656	0.407674006
0.22495656	1.318945314
0.22495656	2.134293327];

PWM=[-300
-200
-100
0
100
200
300];

UpperTorqueConstant = TorqueAndVelocity(1:4,1:2)\PWM(1:4,1)
BottomTorqueConstant = TorqueAndVelocity(5:7,1:2)\PWM(5:7,1)

MiddelTorqueConstant = (UpperTorqueConstant+BottomTorqueConstant)/2
VelocityConstant = TorqueAndVelocity\PWM