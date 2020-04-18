/*
   HTTP Client POST Request
   Copyright (c) 2018, circuits4you.com
   All rights reserved.
   https://circuits4you.com
   Connects to WiFi HotSpot. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
//------------------------------------
// new added from DHT
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2
DHT dht(DHTPIN, DHTTYPE, 11);
float humidity, temp_C;  // Values read from sensor
String webString = "";   // String to display
// Generally, you should use "unsigned long" for variables that hold time
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor
//------------------------------------

/* Set these to your desired credentials. */
const char *ssid = "mediu3g";  //ENTER YOUR WIFI SETTINGS
const char *password = "0000123456";

//Web/Server address to read/write from
//const char *host = "192.168.2.104";   //https://circuits4you.com website or IP address of server
const char *host = "https://www.etixbizi.ro";

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(115200);

  // new added from DHT
  dht.begin();           // initialize temperature sensor
  //-------------------
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot

  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  HTTPClient http;    //Declare object of class HTTPClient

  //String ADCData, station, postData;
  String temp_val, humidity_val, station, postData, postTemp, postHumidity;
  //int adcvalue = analogRead(A0); //Read Analog value of LDR
  //ADCData = String(adcvalue);   //String to interger conversion
  gettemperature();
  temp_val = String(temp_C);
  humidity_val = String(humidity);

  //ADCData = "WWWWWWWWWWWWWWWWWWWW";
  station = "HomeS";

  //Post Data
  //postData = "temp=" + temp_val + "&humidity=" + humidity_val +  "&station=" + station;
  //  postTemp = "?measure=humidity&value=" + humidity_val + "&station=" + station;
  //  postHumidity = "?measure=temperature&value=" "&humidity=" + humidity_val +  "&station=" + station;
  postTemp = "value=1212";
  postHumidity = "value=1212";
  //http.begin("http://192.168.2.104:3000");              //Specify request destination
  http.begin("https://www.etixbizi.ro/api/env3224_data");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  //http.addHeader("Content-Type", "text/plain");
  int httpCodeTemp = http.POST(postTemp);   //Send the request
  String payloadTemp = http.getString();    //Get the response payload

  Serial.println(postTemp);
  Serial.println(postHumidity);
  Serial.println(httpCodeTemp);   //Print HTTP return code
  Serial.println(payloadTemp);

  int httpCodeHumidity = http.POST(postHumidity);   //Send the request
  String payloadHumidity = http.getString();

  Serial.println(httpCodeHumidity);   //Print HTTP return code
  Serial.println(payloadHumidity);    //Print request response payload

  http.end();  //Close connection

  delay(50000);  //Post Data at every 5 seconds
}
//=======================================================================


void gettemperature() {
  // Wait at least 2 seconds seconds between measurements.
  // if the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor
  // Works better than delay for things happening elsewhere also
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you read the sensor
    previousMillis = currentMillis;

    // Reading temperature for humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    humidity = dht.readHumidity();          // Read humidity (percent)
    //temp_C = dht.readTemperature(true);     // Read temperature as Fahrenheit
    temp_C = ((dht.readTemperature(true) - 32) / 1.8);
    Serial.println(temp_C);
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temp_C)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}
