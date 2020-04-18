int waterSensor = A3;//define water sensor to pin A3
int buzzerled = 8;//define buzzer and led to pin 8
int SensorValue;//create sensor data variable

void setup() {
  Serial.begin(9600);
  pinMode(buzzerled, OUTPUT); //set buzzer and led as an output
  pinMode(waterSensor, INPUT); //set water sensor as an input

}

void loop() {

  int sensorValue = analogRead(waterSensor);//read the water sensor value
  Serial.println(sensorValue);
  if (sensorValue >= 100) {
    tone(buzzerled, 900);
    delay(3000);
  }
  else (sensorValue < 100); {
    noTone(buzzerled);
  }
}
