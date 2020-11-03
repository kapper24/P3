#include <Dynamixel_Serial.h>
#include "Group363Converter.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// How to run it: upload to arduino with the dynamixel_serial library installed in your arduino libraries folder.             //
//                After upload, disconnect usb from arduino and add power to CrustCrawler and the arduino board.              //
//                The program should start by it self. :)                                                                     //
//                                                                                                                            //
//                PIN Setup:  Green wire to PIN 10,                                                                           //
//                            Yellow wire to PIN 11,                                                                          //
//                            Black wire to ground,                                                                           //
//                            Red wire to 5v,                                                                                 //
//                            Blue wire to PIN2                                                                               //
//                                                                                                                            //
//                This code was developed in collaboration with several groups, to enable all the groups a good               //
//                base code to start programming the CrustCrawler from. ;)                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <SoftwareSerial.h>

int count = 0;

#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define LED13 0x0D
#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode
#define MOTOR1_ID 0x01
#define MOTOR2_ID 0x02
#define MOTOR3_ID 0x03
#define MOTOR4_ID 0x04
SoftwareSerial mySerial(10, 11);    // RX, TX

int *data;

int var = 4;

void setup(){

  Serial.flush();                                       // Clear the serial buffer of garbage data before running the code.
  mySerial.begin(SERVO_SET_Baudrate);                   // We now need to set Ardiuno to the new Baudrate speed 115200
  Serial.begin(9600);                                  // Start serial communication on baudrate 57600
  Dynamixel.begin(mySerial);                            // Calling mySerial function which sets 10 pin as the 2nd RX serial pin, and sets pin 11 as the 2nd TX serial pin
  Dynamixel.setDirectionPin(SERVO_ControlPin);          // Optional. Set direction control pin which control if the program writes or reads to and from the robot
  
  // Turn on hold on the servos:
  Dynamixel.setHoldingTorque(MOTOR1_ID, true);               //Turn on hold torque on servo 1
  Dynamixel.setHoldingTorque(MOTOR2_ID, true);               //Turn on hold torque on servo 2
  Dynamixel.setHoldingTorque(MOTOR3_ID, true);               //Turn on hold torque on servo 3
  Dynamixel.setHoldingTorque(MOTOR4_ID, true);               //Turn on hold torque on servo 4

  //

  // Set the Profile acceleration.
  Dynamixel.setProfileAcceleration(MOTOR1_ID, 3);  //Set the Profile Acceleration for each servo. (max. is 32767)
  Dynamixel.setProfileAcceleration(MOTOR2_ID, 1);  //Set the Profile Acceleration for each servo. (max. is 32767)
  Dynamixel.setProfileAcceleration(MOTOR3_ID, 1);  //Set the Profile Acceleration for each servo. (max. is 32767)
  Dynamixel.setProfileAcceleration(MOTOR4_ID, 1);  //Set the Profile Acceleration for each servo. (max. is 32767)
  
  
  // Set the Profile velocity.
  Dynamixel.setProfileVelocity(MOTOR1_ID, 200);  //Set the Profile Velocity for each servo. (max. is 1023)
  Dynamixel.setProfileVelocity(MOTOR2_ID, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
  Dynamixel.setProfileVelocity(MOTOR3_ID, 120);  //Set the Profile Velocity for each servo. (max. is 1023)
  Dynamixel.setProfileVelocity(MOTOR4_ID, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
 

  //Get position for servos in steps
  Dynamixel.getPosition(MOTOR1_ID); 
  Dynamixel.getPosition(MOTOR2_ID);
  Dynamixel.getPosition(MOTOR3_ID);
  Dynamixel.getPosition(MOTOR4_ID);
  
    
  //Get position for servos in degrees
  Dynamixel.getPositionD(MOTOR1_ID);
  Dynamixel.getPositionD(MOTOR2_ID);
  Dynamixel.getPositionD(MOTOR3_ID);
  Dynamixel.getPositionD(MOTOR4_ID);

  
  Dynamixel.setNGoalPositions(Converter.degreesToBits(
    90),
      Converter.degreesToBits(180),
      Converter.degreesToBits(180),
      Converter.degreesToBits(180),
      0);
  delay(3000);

 
}


char rx_byte = 0;
char joint = 0;
int jointfound = 0;
String number = "";
void loop() {
   
    if (Serial.available() > 0) {    // is a character available?
        rx_byte = Serial.read();       // get the character

        // check if a number was received
     if ((rx_byte >= '0') && (rx_byte <= '9') && jointfound != 1) {
        joint = rx_byte;
        jointfound = 1;
        }
        else if ((rx_byte >= '0') && (rx_byte <= '9') && jointfound == 1) {
            number += rx_byte;
        }
        else if ((rx_byte == '-') && jointfound == 1) {
         number += rx_byte;
     }
        else if (rx_byte == ':') {
            switch (joint)
            {
            case '1':
                Dynamixel.setGoalPosition(MOTOR1_ID, Converter.degreesToBits(number.toInt()));
                jointfound = 0;
            break;
            case '2':
                Dynamixel.setGoalPosition(MOTOR2_ID, Converter.degreesToBits(number.toInt()));
                jointfound = 0;
            break;
            case '3':
                Dynamixel.setGoalPosition(MOTOR3_ID, Converter.degreesToBits(number.toInt()));
                jointfound = 0;
            break;
            case '4':
                Dynamixel.setGoalPosition(MOTOR4_ID, Converter.degreesToBits(number.toInt()));
                jointfound = 0;
            break;

            default:
                break;
            }
            
            number = "";
        }
       
    }
    
}
