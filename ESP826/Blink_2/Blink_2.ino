int led = 3;//RX
//int led_2 =1;//TX


void setup() {
  // put your setup code here, to run once:
  // pinMode(led, FUNCTION_3);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led , HIGH);
  delay(1000);
  digitalWrite(led , LOW);
  delay(1000);
}
