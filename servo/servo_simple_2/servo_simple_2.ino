#include <Servo.h>
Servo servo;


void setup() {
  servo.attach(9);
  servo.write(0);
}
void loop()
{
  servo.write(80);//110 viraj drept, 140 viraj stanga, 80 viraj dreapta
//  delay(1000);
//  servo.write();
//  delay(1000);
}
