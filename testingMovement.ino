#include <Servo.h>                      // Include servo library

Servo servoLeft;                        // Declare left and right servos
Servo servoRight;

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 2;
const int echoPin = 3;
// Variables for the duration and the distance
long duration;
long distance;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  turnLeft(5000);
} 

void loop() {
}

void forward(int time)                  // Forward function
{
  enableServos();
  servoLeft.writeMicroseconds(1700);    // Left wheel counterclockwise
  servoRight.writeMicroseconds(1300);   // Right wheel clockwise
  delay(time);                          // Maneuver for time ms
  disableServos();
}

void turnLeft(int time)                  // Forward function
{
  enableServos();
  servoLeft.writeMicroseconds(1300);    // Left wheel counterclockwise
  servoRight.writeMicroseconds(1300);   // Right wheel clockwise
  delay(time);                          // Maneuver for time ms
  disableServos();
}

void enableServos()  {
  servoLeft.attach(13);                 // Attach left signal to pin 13
  servoRight.attach(12);                // Attach right signal to pin 12
}

void disableServos()                    // Halt servo signals
{
  servoLeft.detach();                   // Stop sending servo signals
  servoRight.detach();
}
