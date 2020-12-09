TorqueAndVelocity=[0.22495656	-2.39808239
0.22495656	-1.774580968
0.22495656	-1.055156251
0.22495656	-0.263789063
0.22495656	0
0.22495656	0.599520597
0.22495656	1.29496449];

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