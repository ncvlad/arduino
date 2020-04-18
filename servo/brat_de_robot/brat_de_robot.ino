//add the aervo library
#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//define our servos
Servo servo1;
Servo servo2;

//define joystick pin (Analog)
int joyX = 0;
int joyY = 1;

//variable to read the values from the analog pins
int joyVal1;
int joyVal2;

void setup()
{ //attaches our servos on pins PWM 3-5
  servo1.attach(9);
  servo2.attach(10);
  lcd.begin(16, 2);
}

void loop()
{
  lcd.clear();
  //read the value of joystick (between 0-1023)
  joyVal1 = analogRead(joyX);
  joyVal1 = map (joyVal1, 0, 1023, 0, 180); //servo value between 0-180
  servo1.write(joyVal1); //set the servo position according to the joystick value

  
  joyVal2 = analogRead(joyY);
  joyVal2 = map (joyVal2, 0, 1023, 0, 180);
  servo2.write(joyVal2);
  //delay(55);
  lcd.setCursor(0, 0);
  lcd.print("joyVal2:");
  lcd.print(joyVal2);
  //lcd.clear();
  // delay(55);
  lcd.setCursor(0, 1);
  lcd.print("joyVal1:");
  lcd.print(joyVal1);
  delay(55);

  //  lcd.setCursor(0, 1);
  //  lcd.print("fortnite");
}
