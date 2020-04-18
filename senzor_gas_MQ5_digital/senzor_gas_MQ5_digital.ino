//#define gasSens A1 // Setting the Output of MQ5 to Analog 1 pin of ARDUINO board
int gas = 0 ;// A variable required for storing the values from the sensor
int buzzer = 10;

void setup() {

  Serial.begin(9600);// Starting serial communication

  pinMode(6, INPUT); // Setup the gas sensor as an input
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.println("Active gas sensor!");//Printing this message on the serial monitor
  delay(1500);// 1,5 seconds delay in between the readings

}

void loop() {

  int gas = digitalRead(6);// Reading the data received from the MQ-5 and storing it in a variable

  //Setting up the limits for gas detection

  if (gas == 1) //Printing a message if there is a gas leak
  {

    Serial.print("Value: ");
    Serial.print(gas);//Printing the value obtained from the gas sensor
    Serial.println(" no gas");//Message
    digitalWrite(7, HIGH);
    digitalWrite(9, LOW);
    noTone(buzzer);
    delay(500); //0,5 seconds delay until the next message will show up

  }
  else if (gas == 0 )
  {

    Serial.print("Value: ");
    Serial.print(gas);//Value recieved from the gas sensor
    Serial.println(" gas");
    digitalWrite(9, HIGH);
    digitalWrite(7, LOW);
    tone(buzzer, 900);
    delay(1000);
  }

}
