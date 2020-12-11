#include <Dynamixel_Serial.h>

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

////////////////////////////////////////////////////////////////////////////////////////////

#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define LED13 0x0D
#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode
#define MOTOR1_ID 0x01
#define MOTOR2_ID 0x02
#define MOTOR3_ID 0x03
#define MOTOR4_ID 0x04
double PWM[4];
String pwmString[4];
bool donereading[4] = {false,false,false,false};
int angle[4];
int anglevelocity[4];
SoftwareSerial mySerial(10, 11);    // RX, TX

int *data;

int var = 4;

void setup() {

  Serial.flush();                                       // Clear the serial buffer of garbage data before running the code.
  mySerial.begin(SERVO_SET_Baudrate);                   // We now need to set Ardiuno to the new Baudrate speed 115200
  Serial.begin(115200);                                  // Start serial communication on baudrate 57600
  Dynamixel.begin(mySerial);                            // Calling mySerial function which sets 10 pin as the 2nd RX serial pin, and sets pin 11 as the 2nd TX serial pin
  Dynamixel.setDirectionPin(SERVO_ControlPin);          // Optional. Set direction control pin which control if the program writes or reads to and from the robot
  Dynamixel.setOperatingMode(MOTOR1_ID, 16);
  Dynamixel.setOperatingMode(MOTOR2_ID, 16);
  Dynamixel.setOperatingMode(MOTOR3_ID, 16);
  Dynamixel.setOperatingMode(MOTOR4_ID, 16);
  // Turn on hold on the servos:
  Dynamixel.setHoldingTorque(MOTOR1_ID, true);               //Turn on hold torque on servo 1
  Dynamixel.setHoldingTorque(MOTOR2_ID, true);               //Turn on hold torque on servo 2
  Dynamixel.setHoldingTorque(MOTOR3_ID, true);               //Turn on hold torque on servo 3
  Dynamixel.setHoldingTorque(MOTOR4_ID, true);               //Turn on hold torque on servo 4

  delay(3000);


}


void loop() {
  angle[0] = Dynamixel.getPositionD(MOTOR1_ID);
  anglevelocity[0] = Dynamixel.getVelocity(MOTOR1_ID);
  angle[1] = Dynamixel.getPositionD(MOTOR2_ID);
  anglevelocity[1] = Dynamixel.getVelocity(MOTOR2_ID);
  angle[2] = Dynamixel.getPositionD(MOTOR3_ID);
  anglevelocity[2] = Dynamixel.getVelocity(MOTOR3_ID);
  angle[3] = Dynamixel.getPositionD(MOTOR4_ID);
  anglevelocity[3] = Dynamixel.getVelocity(MOTOR4_ID);

  String message;
  message = "M";
  for(int i = 0; i < 4; i++){
  message += "A";
  message += i;
  message+= angle[i]; 
  message += "V";
  message += i;
  message += anglevelocity[i];
  message += 'M';
  }
  
  String received = "";
  while(Serial.available() > 0){
    char rx = Serial.read();
    if (rx == 'a'){
      Serial.println(message);
      }
    received += rx;
  }

  if(received != ""){
  for(int i = 2; i < 6; i++){
    char x = received.charAt(received.indexOf("P0",0)+i);
    if(x >= '0' && x <='9' || x == '-' && donereading[0] == false){
      pwmString[0] += x;
      }
      else{donereading[0] = true;}
      
      
       x = received.charAt(received.indexOf("P1",0)+i);
     if(x >= '0' && x <='9' || x == '-'&& donereading[0] == false){
      pwmString[1] += x;
      } else{donereading[1] = true;}
       x = received.charAt(received.indexOf("P2",0)+i);
     if(x >= '0' && x <='9' || x == '-'&& donereading[0] == false){
      pwmString[2] += x;
      } else{donereading[2] = true;}
       x = received.charAt(received.indexOf("P3",0)+i);
     if(x >= '0' && x <='9' || x == '-'&& donereading[0] == false){
      pwmString[3] += x;
      } else{donereading[3] = true;}
    }
    /*
    Serial.print(pwmString[0]);
    Serial.print(" ");
    Serial.print(pwmString[1]);
    Serial.print(" ");
    Serial.print(pwmString[2]);
    Serial.print(" ");
    Serial.println(pwmString[3]);
    */
    Dynamixel.setGoalPWM(MOTOR1_ID, pwmString[0].toInt());
    Dynamixel.setGoalPWM(MOTOR2_ID, pwmString[1].toInt());
    Dynamixel.setGoalPWM(MOTOR3_ID, pwmString[2].toInt());
    Dynamixel.setGoalPWM(MOTOR4_ID, pwmString[3].toInt());
    pwmString[0] = "";
    pwmString[1] = "";
    pwmString[2] = "";
    pwmString[3] = "";
    donereading[0] = false;
    donereading[1] = false;
    donereading[2] = false;
    donereading[3] = false;
    Serial.println(message);
    
    }

}
