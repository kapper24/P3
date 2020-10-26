#include "CrustCrawlerKinematics.h"

arma::Mat<double> CrustCrawlerKinematics::ForwardKinematics(double t1, double t2, double t3, double t4) {	
	double z = TargetMatrix(2, 3);
	double y = TargetMatrix(1, 3);
	t4 = (90 * PI/180 - t2 - t3) + atan((z - ShoulderHeightFromBase) / (ShoulderDistanceFromBase - y));
	t1 *= PI / 180;
	t2 *= PI / 180;
	t3 *= PI / 180;
	t4 *= PI / 180;


	return {
		{cos(t1 + t2 + t3 + t4) / 2 - cos(t2 - t1 + t3 + t4) / 2, sin(t2 - t1 + t3 + t4) / 2 - sin(t1 + t2 + t3 + t4) / 2, -cos(t1), -(sin(t1) * (290 * sin(t2 + t3) + 437 * sin(t2))) / 2},
		{ sin(t2 - t1 + t3 + t4) / 2 + sin(t1 + t2 + t3 + t4) / 2, cos(t1 + t2 + t3 + t4) / 2 + cos(t2 - t1 + t3 + t4) / 2, -sin(t1), (cos(t1) * (290 * sin(t2 + t3) + 437 * sin(t2))) / 2 },
		{ cos(t2 + t3 + t4), -sin(t2 + t3 + t4), 0, 145 * cos(t2 + t3) + (437 * cos(t2)) / 2 },
		{ 0, 0, 0, 1 } };
	
}
CrustCrawlerKinematics::Angles CrustCrawlerKinematics::InverseKinematics(arma::Mat<double> TargetMatrix)
{
	Angles angles;
	
	double x = TargetMatrix(0, 3);
	double y = TargetMatrix(1, 3);
	double z = TargetMatrix(2, 3);
	double L = sqrt((x * x) + (y * y) + (z * z));
	double phi1 = asin(z / L);
	double phi2 = acos(((218.5 * 218.5) + (L * L) - 145.0 * 145) / (2 * 218.5 * L));
	double phi3 = acos(((218.5 * 218.5) + (145.0 * 145) - L * L) / (2 * 218.5 * 145));
	double EEz = TargetMatrix(2, 3);
	double EEy = TargetMatrix(1, 3);
	angles.theta1 = atan2(-x, y) * 180 / PI;
	angles.theta2 = (90 * PI / 180 - phi1 - phi2) * 180 / PI;
	angles.theta3 = 180 - (phi3) * 180 / PI;
	angles.theta4 = (90 - angles.theta2 - angles.theta3) + atan((EEz - ShoulderHeightFromBase) / (ShoulderDistanceFromBase - EEy)) * 180/PI;
	return angles;
}
