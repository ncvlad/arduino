/*
  Arduino Wireless Communication Tutorial
      Example 1 - Transmitter Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https:// github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

const int X_pin = 1;
const int Y_pin = 3;
const int SV_pin1 = 10;//digital
const int SV_pin2 = 9;//digital
int forward ;
int turn;
int ledRosu;
int ledAlb;
int data[2];
int sendCondition;
int sendZeroPosition;

void setup() {
  Serial.begin(115200);
  pinMode(SV_pin1, INPUT);
  digitalWrite(SV_pin1, HIGH);
  pinMode(SV_pin2, INPUT);
  digitalWrite(SV_pin2, HIGH);
  radio.begin();
  sendZeroPosition = 0;
  sendCondition = 0;
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}
void loop() {

  forward = analogRead(X_pin);
  turn = analogRead(Y_pin);
  ledRosu = digitalRead(SV_pin1);
  ledAlb = digitalRead(SV_pin2);

  data[0] = forward;
  data[1] = turn;
  data[2] = ledRosu;
  data[3] = ledAlb;

  //const char text[] = "Hello World";
  //radio.write(&text, sizeof(text));


  if ((turn > 530 || turn < 500) || (forward > 525 || forward < 500) ) {
    sendCondition = 1;
    sendZeroPosition = 1;
  };
  // trimite date doar daca se misca butoanele joysticl-ului
  if (sendCondition == 1)  {

    Serial.println("Forward");
    Serial.println(data[0]);
    Serial.println("turn");
    Serial.println(data[1]);

    radio.write(&data, sizeof(data));

  };
  // daca nu se misca joistick-urile trebuie sa trimita datele de repaus pentru ca masina sa se opreasca
  // din miscare sau virare
  if (sendZeroPosition == 1 && sendCondition == 0) {
    Serial.println("Send stop semnal");
    Serial.println("Forward");
    Serial.println(data[0]);
    Serial.println("turn");
    Serial.println(data[1]);

    radio.write(&data, sizeof(data));
    sendZeroPosition = 0;
  }
  sendCondition = 0;

  //delay(1000);
}
