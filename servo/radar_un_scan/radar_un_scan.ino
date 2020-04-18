/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int trigPin = 11;
int echoPin = 10;
int scanNr = 0;

void setup() {
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if(scanNr==0){
    for (pos = 0; pos <= 180; pos += 30) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    Serial.print("servo position: ");
    Serial.println(pos);
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    getDistance();
    
    delay(900);                       // waits 15ms for the servo to reach the positio
  }
  scanNr=4;
    }
    
  myservo.write(90);
}



long getDistance(){
  long duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print(distance);
  Serial.println("CM");

  }
