int detected = D8;
int i=0; //save



void setup() {
  Serial.begin(9600);
  pinMode(detected, OUTPUT);//define ACTION output pin

}

void loop() {
  //  tone(detected,5000);
  //  delay(50);
  //  tone(detected,4000);
  //  delay(50);
  //  tone(detected,3000);
  //  delay(50);
  //  tone(detected,2000);
  //  delay(50);
  //  tone(detected,1000);
  //  delay(50);
  //  tone(detected,900);
  //  delay(50);
  //  tone(detected,800);
  //  delay(50);

  for (i = 800; i < 900; i++) {
    tone(detected, i);
    delay(15);
  }
  for (i = 900; i > 800; i--) {
    tone(detected, i);
    delay(15);
  }

}
