
/*----------------------------------------------------------
 * This is a modified version of the Vinerobot code provided 
 * on the vinerobot website.
 * This code has been adapted to allow motor control with an
 * L293D module.
 * 
 * Original authors: May 24, 2018, Javier A. Reyna Zepeda
 * Editor: Kiran Ravi, 31/01/22
 */



/*---------------Includes-----------------------------------*/
#include <math.h>
#include <ctype.h>

/*---------------Module Defines-----------------------------*/
#define OFF               0
#define FORWARD           HIGH
#define REVERSE           LOW
#define GROWTH            HIGH
#define RETRACT           LOW

/*---------------Pin Declares-------------------------------*/
int motorPin1    = 9;  // First PWM output pin, connects to negative of the motor
int motorPin2    = 10; // Second PWM output pin, connects to the positive of the motor 
int motorSpeedPin = 11;  // Speed output pin for motor

/*---------------Motor Dependent Parameters-----------------*/
int minGrowthSpeed  = 0; // Minimum speed required to allow growth
int minGrowthStop   = 0; // Minimum speed required to stop growth
int minRetractSpeed = 0; // Minimum speed required to start retraction

/*---------------Control Variables--------------------------*/
int motorSpeed   = 0;      // Controls the motor's speed from 0-255
int speedDelta   = 5;      // Controls the change in speed

bool vineState  = GROWTH; // Is the motor growing or retracting?
 
unsigned char theKey = ' ';

/*---------------Module Function Prototypes--------------*/
unsigned char TestForKey(void);
void RespToKey(void);
void grow(int);
void retract(int);
void halt();
void deflate();
void inflate();

/*---------------Pre-formed Vine Robot Setup ----------------------*/
void setup() {                 // setup() function required for Arduino
  Serial.begin(9600);

  // Output pins
  pinMode(motorPin1, OUTPUT);     // PWM pin for motor -
  pinMode(motorPin2, OUTPUT);     // PWM pin for motor +
  pinMode(motorSpeedPin, OUTPUT);  // Speed pin for motor 1

  // Initialize motor
  analogWrite(motorSpeedPin, OFF);            // set to not be spinning (0/255)
  digitalWrite(motorPin1, HIGH);              // set motor direction to anti-clockwise by setting negative high
  digitalWrite(motorPin2, LOW);               //... and positive low
}

/*---------------Pre-formed Vine Robot Main Loop-------------------*/
void loop() {        // loop() function required for Arduino
  theKey = Serial.read();
   
  
  if (theKey == 'W'){               //GROW, MOVE FORWARD  
    motorSpeed = minGrowthSpeed;
    grow(motorSpeed);
    vineState = GROWTH;
     Serial.println("Growing");
  }

  if (theKey == 'S'){               //RETRACT, MOVE BACK  
    motorSpeed = minRetractSpeed;
    retract(motorSpeed);
    vineState = RETRACT;
     Serial.println("Retracting");
  }

   if (theKey == 'D'){               //INCREASE SPEED      
    motorSpeed += speedDelta;
    speedChange(motorSpeed);         // Input speed change into new speedChange function
    Serial.println(motorSpeed);
  }
  
  if (theKey == 'A'){               //DECREASE SPEED     
    motorSpeed -= speedDelta;
    speedChange(motorSpeed);        // Input speed change to new speedChange function
    Serial.println(motorSpeed);
  }

  if (theKey == ' '){               //STOP              
    halt();
    Serial.println("Stopping");
  }

    if (theKey == 'X'){               //FULL SPEED AHEAD GROWTH
    motorSpeed = 255;
    grow(motorSpeed);
    vineState = GROWTH;
    Serial.println(motorSpeed);
  }

    if (theKey == 'C'){               //FULL SPEED AHEAD RETRACTION
    motorSpeed = 255;
    retract(motorSpeed);
    vineState = RETRACT;
    Serial.println(motorSpeed);
  }
}



/*----------------------Module Functions--------------------------*/
unsigned char TestForKey(void) {
  unsigned char KeyEventOccurred;
  
  KeyEventOccurred = Serial.available();
  return KeyEventOccurred;
}

// Tells the vine robot to grow at a particular motor speed
void grow(int motorSpeed){
    analogWrite(motorSpeedPin,motorSpeed); 
    digitalWrite(motorPin1, HIGH); 
    digitalWrite(motorPin2, LOW);
}

// Tells the vine robot to retract at a particular motor speed
void retract(int motorSpeed){
    analogWrite(motorSpeedPin,motorSpeed); 
    digitalWrite(motorPin1, LOW); 
    digitalWrite(motorPin2, HIGH);
}

// Tells the motor what speed to go at
void speedChange(int motorSpeed){
  if(motorSpeed > 255){
    Serial.println("Already at max speed");
  }
  
  else if(motorSpeed < 0){
    Serial.println("Already at min speed");
  }
  else{  
  analogWrite(motorSpeedPin,motorSpeed);
  }
}

// Stops the vine robot's growth and remains pressurized
void halt(){
    analogWrite(motorSpeedPin,minGrowthStop); 
}

// Pressurizes the chamber
void deflate(){
}

// Deflates the vine robot
void inflate(){
}
