#include <servo.h>

servo EscFL;
servo EscFR;
servo EscBL;
servo EscBR;
//all motors are CW 
//all motors are facing forward (nose tip forward)
void setup() {
  Serial.begin(9600);
  //PWM port from mega (2 to 13 , 44 to 46)
  EscFL.attach(3);
  EscFR.attach(4);
  EscBL.attach(5);
  EscBR.attach(6);
}

void loop() {
  int direc;
  value = analogRead(A1); //Value entry -> how do we kno we want to go fast or not
  value=map(value,0,1023,0,180)
  //ESC specification
  //Normal mode : PWM value must be between 90 to 180
  //Reverse mode : PWM value must be between 0 to 90
  //ATTENTION !! The way motors are facing is important
  //Please refer to the Motors diagram
  if (direc == 1){
  //Forward
  //To go forward all motor need to have a value between 90 to 180)
  EscFL.write(value);
  EscFR.write(value);
  EscBL.write(value);
  EscBR.write(value);
  }
  if (direc == 2){
  //Right
  //To go right FL -> Normal / FR -> Reverse / BL -> Reverse / BR -> Normal
  EscFL.write(value);
  EscFR.write(value-90);
  EscBL.write(value-90);
  EscBR.write(value);
  }
  if (direc == 3){
  //Backward
  //To go Backward FL -> Reverse / FR -> Reverse / BL -> reverse / BR -> Reverse
  EscFL.write(value-90);
  EscFR.write(value-90);
  EscBL.write(value-90);
  EscBR.write(value-90);
  }
  if (direc == 4){
  //Left
  //To go Left FL -> Reverse / FR -> Normal / BL -> Normal / BR -> Reverse
  EscFL.write(value-90);
  EscFR.write(value);
  EscBL.write(value);
  EscBR.write(value-90);
  }
  

}
