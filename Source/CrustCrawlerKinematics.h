#pragma once
#include <armadillo>
class CrustCrawlerKinematics
{
public:
	double ShoulderDistanceFromBase = -200;
	double ShoulderHeightFromBase = -1000;
	struct Angles {
		double theta1;
		double theta2;
		double theta3;
		double theta4;
	};
	struct Pos {
		double x, y, z;
	};
	arma::Mat<double> TargetMatrix = arma::zeros(4, 4);
	Pos  ForwardKinematics(double t1, double t2, double t3, double t4);
	Angles InverseKinematics(double x, double y, double z);
	
protected:
	double PI = arma::datum::pi;
private:
	
	

	//arma::mat T04; 

};

