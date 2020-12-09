TorqueAndVelocity=[0.90840892	-2.062350855
0.90840892	-1.462830258
0.90840892	-0.86330966
0.90840892	-0.143884943
0.90840892	0
0.90840892	0.575539773
0.90840892	1.199041195];

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