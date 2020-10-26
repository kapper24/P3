#pragma once
#include <armadillo>
class CrustCrawlerKinematics
{
public:
	double ShoulderDistanceFromBase = 400;
	double ShoulderHeightFromBase = 100;
	struct Angles {
		double theta1;
		double theta2;
		double theta3;
		double theta4;
	};
	arma::Mat<double> TargetMatrix = arma::zeros(4, 4);
	arma::Mat<double>  ForwardKinematics(double t1, double t2, double t3, double t4);
	Angles InverseKinematics(arma::Mat<double> TargetMatrix);
	
protected:
	double PI = arma::datum::pi;
private:
	
	

	//arma::mat T04; 

};

