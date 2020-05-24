int RELAY = 10;
int sensor = 7;
unsigned  long timeToStayOff = 300000L;
//unsigned  long timeToStayOff = 5000L;
unsigned  long lastTimeAlarm ;
unsigned  long pause;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  pinMode(sensor, INPUT);
  lastTimeAlarm = millis();
   digitalWrite(RELAY, HIGH);
}

void loop() {
  int lumina = digitalRead(sensor);
  Serial.println(lumina);
 
  pause = millis() - lastTimeAlarm;
  Serial.println(pause);
  Serial.println(timeToStayOff);

  if (lumina == 0 && pause > timeToStayOff ) {
    //    for (int i = 3000; i < 3020; i++) {
    //      tone(buzzer, i);
    //      delay(40);
    //      noTone(buzzer);
    //      delay(40);
    //
    //    }
    //    delay (5000);
    //
    //    for (int i = 250; i < 275; i++) {
    //      tone(buzzer, i);
    //      delay(40);
    //      noTone(buzzer);
    //      delay(40);
    //    }
    Serial.println("Lumina:");
    Serial.println(lumina);
    digitalWrite(RELAY, LOW);
    delay (5000);
    digitalWrite(RELAY, HIGH);


    lastTimeAlarm = millis();

  }

  delay (1000);

}
