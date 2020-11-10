#include<iostream>

using namespace std;

double * dynaPower (double t1, double w1, double t2, double w2, double t3, double w3, double t4, double w4) //Wanted torques for motor 1-4 and angular velocity
{
double const c28 [2] {558.1313, 146.4923};  //Motor constants for the MX-28
double const c64 [2] {190.7093, 123.7781};  //Motor constants for the MX-64
double const c106 [2] {107.0786, 166.3125}; //Motor constants for the MX-106

double PWM1 = t1 * c64[0] + w1 * c64[1];    //Needed PWM to run first motor with determined torque
double PWM2 = t2 * c106[0] + w2 * c106[1];  //Needed PWM to run second motor with determined torque
double PWM3 = t3 * c64[0] + w3 * c64[1];    //Needed PWM to run third motor with determined torque
double PWM4 = t4 * c28[0] + w4 * c28[1];    //Needed PWM to run fourth motor with determined torque

double allPWM [4] {PWM1, PWM2, PWM3, PWM4}; //Array of the four PWM's

return allPWM;
}

int main()
{
    cout<<"Nodvendig PWM for at na torque 0.07 når vinkelhastighed er 2 rad/s" << endl;
    
    for (int i = 0; i < 4; i++)
    {
        cout<<"PWM for motor " << i+1 << " er: " << dynaPower(0.07, 2, 0.07, 2, 0.07, 2, 0.07, 2)[i] << endl;
    }
    
}
    
