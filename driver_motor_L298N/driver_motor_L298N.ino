//https://www.youtube.com/watch?v=Da4HY7HZ6h0
const int IN1 = 7;
const int IN2 = 6;
const int IN3 = 5;
const int IN4 = 4;

const int ENA = 9;
const int ENB = 3;


void setup() {

  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {

  analogWrite(ENA, 100);//mers viteza
  analogWrite(ENB, 255); //viraj putere

  digitalWrite(IN1, HIGH); //mers inapoi
  digitalWrite(IN2, LOW); //mers fata
  digitalWrite(IN3, HIGH); //viraj dreapta
  digitalWrite(IN4, LOW); //viraj stanga

  // put your main code here, to run repeatedly:

}
