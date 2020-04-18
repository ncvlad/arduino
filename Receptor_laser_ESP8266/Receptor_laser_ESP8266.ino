/*
   Laser Sensor module for Arduino
   Turns ON a buzzer or you can control a motor or servo or any other action,

   Watch the video https://youtu.be/h_y1y6eUvIY

 *  *
  Laser Sensor module for Arduino
  Written by Ahmad Nejrabi for Robojax.com
  on Feb 02, 2018 at 18:24 in Ajax, Ontario, Canada
   Permission granted to share this code given that this
   note is kept with the code.
   Disclaimer: this code is "AS IS" and for educational purpose only.

  /*
  /*




*/
// Saser Sensor code for Robojax.com
int DETECT = D7;// pin 2 for  sensor
//#define ACTION 8 // pin 8 for action to do someting


void setup() {
  Serial.begin(9600);
  Serial.println("Robojax.com Laser Module Test");
  pinMode(DETECT, INPUT);//define detect input pin
  // pinMode(ACTION, OUTPUT);//define ACTION output pin

  // Laser sensor code for Robojax.com

}

void loop() {
  // Laser Sensor code for Robojax.com

  int detected = digitalRead(DETECT);// read Laser sensor

  if ( detected == HIGH)
  {
    // noTone(8);// set the buzzer ON
    Serial.println("Detected!");

  } else {
    // tone(8,800); // Set the buzzer OFF
    Serial.println("No laser");
    // Laser Sensor code for Robojax.com

  }
  delay(200);
} void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
