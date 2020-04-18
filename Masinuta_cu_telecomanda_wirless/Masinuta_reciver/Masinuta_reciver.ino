//https://www.youtube.com/watch?v=Da4HY7HZ6h0
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

const int IN1 = 2;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;

//const int X_pin = 2;//analog
//const int Y_pin = 3;//analog

const int ENA = 10;
const int ENB = 3;

int motorPower = 50;
int turnPower = 50;
int turn ; 
int forward ;
int text[2] ;

void setup() {
  Serial.begin(9600);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  // put your setup code here, to run once:

}

void loop() {
  if (radio.available()) {
    //int text[2] ;
    radio.read(&text, sizeof(text));
    Serial.print("Mesaj1: ");
    Serial.println(text[0]);

        Serial.print("Mesaj2: ");
        Serial.println(text[1]);
  }

  analogWrite(ENA, motorPower);//mers viteza
  analogWrite(ENB, turnPower); //viraj putere

  //  digitalWrite(IN1, LOW); //mers fata
  //  digitalWrite(IN2, LOW); //mers spate
  //  digitalWrite(IN3, LOW); //viraj dreapta
  //  digitalWrite(IN4, LOW); //viraj stanga

//  Serial.print("X-axis: ");
//  Serial.print(analogRead(X_pin));
//  Serial.print("\n");
//  Serial.print("Y-axis: ");
//  Serial.print(analogRead(Y_pin));
//  Serial.print("\n\n");

  turn = text[0];
  forward = text[1];


  motorPower = 50 + round(abs(forward - 513) / 5) * 2;
  turnPower = 50 + round(abs(turn - 511) / 5) * 2;
  Serial.print("motorPower: ");
  Serial.print(motorPower);
  Serial.print("\n");
  Serial.print("turnPower: ");
  Serial.print(turnPower);
  Serial.print("\n\n");
  //delay(150);

  if (forward < 400 ) {
    digitalWrite(IN1, HIGH); //mers fata
  } else {
    digitalWrite(IN1, LOW); //mers fata
  }

  if (forward > 700 ) {
    digitalWrite(IN2, HIGH); //mers spate
  } else {
    digitalWrite(IN2, LOW); //mers spate
  }

  if (turn < 400 ) {
    digitalWrite(IN3, HIGH); //viraj dreapta
  } else {
    digitalWrite(IN3, LOW); //viraj dreapta
  }

  if (turn > 700 ) {
    digitalWrite(IN4, HIGH); //viraj stanga
  } else {
    digitalWrite(IN4, LOW); //viraj stanga
  }
  //delay(155);

  // put your main code here, to run repeatedly:

}
