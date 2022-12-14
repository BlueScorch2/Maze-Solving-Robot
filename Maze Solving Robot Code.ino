#include <Servo.h>                      // Include servo library

// Declare left and right servos
Servo servoLeft;                        
Servo servoRight;


// Defines TrIg and Echo pins of each Ultrasonic Sensor
const int trigPinF = 2;
const int echoPinF = 3;

const int trigPinL = 4;
const int echoPinL = 5;

const int trigPinR = 6;
const int echoPinR = 7;


// Variables for the duration and the distance
long duration;

long frontDistance;
long leftDistance;
long rightDistance;

//###########
void setup(){
  pinMode(trigPinF, OUTPUT);             // Sets the trigPinF as an Output
  pinMode(echoPinF, INPUT);              // Sets the echoPinF as an Input
  pinMode(trigPinL, OUTPUT);             // Sets the trigPinF as an Output
  pinMode(echoPinL, INPUT);              // Sets the echoPinF as an Input
  pinMode(trigPinR, OUTPUT);             // Sets the trigPinF as an Output
  pinMode(echoPinR, INPUT);              // Sets the echoPinF as an Input
  
  Serial.begin(9600);
}

//##########
void loop(){   
  frontDistance = calculateFrontDistance();       // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
  if  (frontDistance > 70){
    leftDistance = calculateLeftDistance();         // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
    rightDistance = calculateRightDistance();       // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
    forward();
    }
  else{
    disableServos();
    }
  Serial.print("F: ");                            // Sends the distance value into the Serial Port
  Serial.println(frontDistance);                    // Sends the distance value into the Serial Port
  Serial.print("L: ");                            // Sends the distance value into the Serial Port
  Serial.println(leftDistance);                     // Sends the distance value into the Serial Port
  //delay(15);                                      // delay between triggering the sensor 
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


//##################
//MOVEMENT FUNCTIONS
void forward()                          // Forward function
{
  enableServos();
  //disableServos();

  if (leftDistance < 40 and leftDistance > 5){
    correctingLeft();
    //delay(5);
    Serial.println("C: ");                            // Sends the distance value into the Serial Port
  }
  //else if (rightDistance = 15){
    //correctingRight();
    //Serial.println("R: ");                            // Sends the distance value into the Serial Port
    //delay(20);
  //}
  else{
    servoLeft.writeMicroseconds(1700);    // Left wheel counterclockwise
    servoRight.writeMicroseconds(1300);   // Right wheel clockwise
    //delay(20);
    Serial.println("G: ");                            // Sends the distance value into the Serial Port
  }
}

//void backward()//int time)              // Backward function
//{
//  servoLeft.writeMicroseconds(1300);    // Left wheel clockwise
//  servoRight.writeMicroseconds(1700);   // Right wheel counterclockwise
//  //delay(time);                        // Maneuver for time ms
//}

void turnLeft()                         // Left turn function
{
  servoLeft.writeMicroseconds(1400);    // Left wheel clockwise at half speed
  servoRight.writeMicroseconds(1400);   // Right wheel clockwise at half speed
  delay(50);
  
  if (leftDistance != rightDistance){
    servoLeft.writeMicroseconds(1400);    // Left wheel clockwise at half speed
    servoRight.writeMicroseconds(1400);   // Right wheel clockwise at half speed
    turnLeft();
  }
}

void turnRight()                        // Left turn function
{
  servoLeft.writeMicroseconds(1600);    // Left wheel counterclockwise at half speed
  servoRight.writeMicroseconds(1600);   // Right wheel counterclockwise at half speed
  delay(50);
  
  if (leftDistance != rightDistance){
    servoLeft.writeMicroseconds(1600);    // Left wheel clockwise at half speed
    servoRight.writeMicroseconds(1600);   // Right wheel clockwise at half speed
    turnRight();
  }
}


//########################
//AUTOCORRECTING FUNCTIONS
void correctingLeft()
{
  servoLeft.writeMicroseconds(1700);    // Left wheel counterclockwise
  servoRight.writeMicroseconds(1500);   // Right wheel clockwise slower
}
void correctingRight()
{
  servoLeft.writeMicroseconds(1500);    // Left wheel counterclockwise slower
  servoRight.writeMicroseconds(1300);   // Right wheel clockwise
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
