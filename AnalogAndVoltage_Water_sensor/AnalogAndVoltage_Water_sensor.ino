#include <VoltageReference.h>

VoltageReference vRef;

int waterSensor = A3;//define water sensor to pin A3
int buzzerled = 8;//define buzzer and led to pin 8
int SensorValue;//create sensor data variable

void setup() {
  Serial.begin(9600);
  pinMode(buzzerled, OUTPUT); //set buzzer and led as an output
  pinMode(waterSensor, INPUT); //set water sensor as an input
  while (!Serial);
  Serial.println("Calibrating voltage reference");
  vRef.begin(1127250); // valoarea primita de la EPROM_Calibration
  // step1 - se masoara tensiunea vcc - gnd fara consumatori
  // step2 - se trimite pe serial R si ne afiseaza valoarea masurata intern
  // step3 - daca valoare este diferita de cea masurata la pas 1
  // atunci in serial scriem valoarea masurata la pas 1 * 1000
  // 4 cifre si ne va afisa pe serial o valoare numerica ce reprezinta valoarea
  // de calibrare si pe care o dam ca parametru  la vRef.begin()
}


#define DETECT_PIN A3

// set this to true for voltages below 1V
#define LOW_VOLTAGE true

void loop() {

#if (LOW_VOLTAGE)
  analogReference(INTERNAL);
#endif
  int analog = analogRead(DETECT_PIN);
  int vcc = vRef.readVcc();
  Serial.print("Board voltage is ");
  Serial.print(vcc);
  Serial.print("mV, analog pin voltage is ");
#if (LOW_VOLTAGE)
  Serial.print(vRef.internalValue() * analog / 1023);
#else
  Serial.print(vcc * analog / 1023);
#endif
  Serial.print("mV");
  Serial.println();
  delay(1500);

  if (vcc < 4200) {
    for (int i = 0; i < 3; i++) {
      tone(buzzerled, 400);
      delay(200);
      noTone(buzzerled);
    }

  }
  // codul de la senzor umiditate si alarma
  int sensorValue = analogRead(waterSensor);//read the water sensor value
  //  Serial.println(sensorValue);
  if (sensorValue >= 100) {
    tone(buzzerled, 900);
    delay(3000);
  }
  else (sensorValue < 100); {
    noTone(buzzerled);
  }
delay(9000);



}
