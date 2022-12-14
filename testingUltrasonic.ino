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
}
void loop() {   
  distance = calculateDistance();       // Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  Serial.print("\n"); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port

  delay(10);                          // delay between triggering the sensor 
  
  if (distance > 70) {
    forward(50);
  }
}

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.34 / 2;          // Multiply by speed of sound divided by 2 (distance is there and back
  return distance;
}

void forward(int time)                  // Forward function
{
  enableServos();
  servoLeft.writeMicroseconds(1700);    // Left wheel counterclockwise
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

void turnLeft(int time)                 // Left turn function
{
  servoLeft.writeMicroseconds(1300);    // Left wheel clockwise
  servoRight.writeMicroseconds(1300);   // Right wheel clockwise
  delay(time);                          // Maneuver for time ms
}

void turnRight(int time)                // Right turn function
{
  servoLeft.writeMicroseconds(1700);    // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);   // Right wheel counterclockwise
  delay(time);                          // Maneuver for time ms
}

void backward(int time)                 // Backward function
{
  servoLeft.writeMicroseconds(1300);    // Left wheel clockwise
  servoRight.writeMicroseconds(1700);   // Right wheel counterclockwise
  delay(time);                          // Maneuver for time ms
}
