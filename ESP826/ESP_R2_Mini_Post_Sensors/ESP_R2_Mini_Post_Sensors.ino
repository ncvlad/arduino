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

String webString = "";   // String to display
// Generally, you should use "unsigned long" for variables that hold time
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor
//------------------------------------

/* Set these to your desired credentials. */
const char *ssid = "Edimax";  //ENTER YOUR WIFI SETTINGS
const char *password = "0000123456";

//Web/Server address to read/write from
//const char *host = "192.168.2.104";   //https://circuits4you.com website or IP address of server
const char *host = "http://www.etixsmart.ro";

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(115200);


  // initialize temperature sensor
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
  String moving, light , temp_val, humidity_val, station, postData;
  //int adcvalue = analogRead(A0); //Read Analog value of LDR
  //ADCData = String(adcvalue);   //String to interger conversion

 // temp_val = String(temp_C);
 // humidity_val = String(humidity);
 light =

 
  station = "Living";

  //Post Data
  postData = "temp=" + temp_val + "&humidity=" + humidity_val +  "&station=" + station + "&moving=" + moving + "&light=" + light;

  //http.begin("http://192.168.2.104:3000");              //Specify request destination
  http.begin("http://www.etixsmart.ro/api/home");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  //http.addHeader("Content-Type", "text/plain");
  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection

  delay(50000);  //Post Data at every 5 seconds
}
//=======================================================================
