#include <Servo.h>                      // Include servo library

// Declare left and right servos
Servo servoLeft;                        
Servo servoRight;

// Defines TrIg and Echo pins of each Ultrasonic Sensor
const int trigPinF = 2;
const int echoPinF = 3;

const int trigPinR = 4;
const int echoPinR = 5;

const int trigPinL = 6;
const int echoPinL = 7;

// Constant for distance walls are away from sensors
const int DISTANCE = 50;

// Variables for the duration and the distance
long duration;

long frontDistance;
long leftDistance;
long rightDistance;

int iteration;

//#####
//SETUP
void setup(){
  pinMode(trigPinF, OUTPUT);             // Sets the trigPinF as an Output
  pinMode(echoPinF, INPUT);              // Sets the echoPinF as an Input
  pinMode(trigPinL, OUTPUT);             // Sets the trigPinF as an Output
  pinMode(echoPinL, INPUT);              // Sets the echoPinF as an Input
  pinMode(trigPinR, OUTPUT);             // Sets the trigPinF as an Output
  pinMode(echoPinR, INPUT);              // Sets the echoPinF as an Input
  
  Serial.begin(9600);
}


//#########
//MAIN LOOP
void loop()
{
  // If there are no walls around it
  if (calculateFrontDistance() > DISTANCE && calculateRightDistance() > DISTANCE && calculateLeftDistance() > DISTANCE){
    forward();
  }
  // If there are walls all around it (dead-end)
  else if ( calculateFrontDistance() < DISTANCE && calculateRightDistance() < DISTANCE && calculateLeftDistance() < DISTANCE){
    rotateLeft();
    delay(500);

  // Comparing left and right distances from sensors
  if (calculateLeftDistance() > calculateRightDistance())
    rotateLeft();
  else
    rotateRight();
  }
  // If wall in front and on right
  else if (calculateFrontDistance() < DISTANCE && calculateRightDistance() < DISTANCE && calculateLeftDistance() > DISTANCE){
    rotateLeft();
  }
  // If wall in front and on left
  else if (calculateFrontDistance() < DISTANCE && calculateRightDistance() > DISTANCE && calculateLeftDistance() < DISTANCE){
    rotateRight();
  }
  // If wall only in front (T junction)
  else if (calculateFrontDistance() < DISTANCE && calculateRightDistance() > DISTANCE && calculateLeftDistance() > DISTANCE){
    // Need to buy switch to iterate over choices
    // Always going left on the first iteration
    // Always going right on the second iteration
    // Comparing the iterations
  }
  else
  {
    forward();
  }
}


//#############################
//ENABLING AND DISABLING SERVOS
void enableServos(){
  servoLeft.attach(13);                 // Attach left signal to pin 13
  servoRight.attach(12);                // Attach right signal to pin 12
}

void disableServos(){                   // Halt servo signals
  servoLeft.detach();                   // Stop sending servo signals
  servoRight.detach();
}


//#############################
//MOVEMENT FUNCTIONS
void forward()
{
  enableServos();
  servoLeft.writeMicroseconds(1450);    // Left wheel counterclockwise at quater max speed
  servoRight.writeMicroseconds(1550);   // Right wheel clockwise at quater max speed
}

void rotateLeft()
{
  servoLeft.writeMicroseconds(1550);    // Left wheel clockwise at quater max speed
  servoRight.writeMicroseconds(1550);   // Right wheel clockwise at quater max speed
}

void rotateRight()
{
  servoLeft.writeMicroseconds(1450);    // Left wheel counterclockwise at quater max speed
  servoRight.writeMicroseconds(1450);   // Right wheel counterclockwise at quater max speed
}


//########################
//AUTOCORRECTING FUNCTIONS
static bool correctingLeft()
{
  servoLeft.writeMicroseconds(1550);    // Left wheel counterclockwise
  servoRight.writeMicroseconds(1500);   // Right wheel clockwise slower
}
void correctingRight()
{
  servoLeft.writeMicroseconds(1500);    // Left wheel counterclockwise slower
  servoRight.writeMicroseconds(1450);   // Right wheel clockwise
}


//##############################
//DISTANCE CALCULATION FUNCTIONS
int calculateFrontDistance(){            // Function for calculating the distance measured by the Front Ultrasonic sensor
  digitalWrite(trigPinF, LOW); 
  delayMicroseconds(2);
  
  digitalWrite(trigPinF, HIGH);          // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPinF, LOW);
  duration = pulseIn(echoPinF, HIGH);    // Reads the echoPin, returns the sound wave travel time in microseconds
  frontDistance = duration * 0.34 / 2;   // Multiply by speed of sound divided by 2 (distance is there and back)
  return frontDistance;
}

int calculateLeftDistance(){             // Function for calculating the distance measured by the Left Ultrasonic sensor
  digitalWrite(trigPinL, LOW); 
  delayMicroseconds(2);
  
  digitalWrite(trigPinL, HIGH);          // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  duration = pulseIn(echoPinL, HIGH);    // Reads the echoPin, returns the sound wave travel time in microseconds
  leftDistance = duration * 0.34 / 2;    // Multiply by speed of sound divided by 2 (distance is there and back)
  return leftDistance;
}

int calculateRightDistance(){            // Function for calculating the distance measured by the Right Ultrasonic sensor 
  digitalWrite(trigPinR, LOW); 
  delayMicroseconds(2);
  
  digitalWrite(trigPinR, HIGH);          // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  duration = pulseIn(echoPinR, HIGH);    // Reads the echoPin, returns the sound wave travel time in microseconds
  rightDistance = duration * 0.34 / 2;   // Multiply by speed of sound divided by 2 (distance is there and back)
  return rightDistance;
}