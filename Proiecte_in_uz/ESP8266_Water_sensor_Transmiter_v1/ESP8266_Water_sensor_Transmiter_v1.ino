
// transmite daca este apa sau nu

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Mediu";          // fill in here your router or wifi SSID
const char *password = "0000123456"; // fill in here your router or wifi password
IPAddress ip(192, 168, 1, 222);
#define SENSOR 0 // relay connected to  GPIO0
WiFiServer server(80);
// test git

String postQuery;
int value;
int haveToSendData = 0;
int valueSent = 0;



void setup()
{
  Serial.begin(115200); // must be same baudrate with the Serial Monitor
  haveToSendData = 0;
  pinMode(SENSOR, INPUT);
  // start with relay OFF


  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(IPAddress(192, 168, 1, 222), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 1));
  //  WiFi.config(IPAddress(192, 168, 1, 223), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 1));
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }  Serial.println("");
  Serial.println("WiFi connected");

}
//*************************************
//******************LOOP
//*************************************

void loop()
{
  value = digitalRead(SENSOR);

  if (value > 0) {
    Serial.println("V1");
    postQuery = "waterDetected=1";
    haveToSendData = (valueSent == 0) ? 1 : 0;
  } else {
    Serial.println("V0");
    postQuery = "waterDetected=0";
    haveToSendData = (valueSent == 1) ? 1 : 0;
  }

  if (haveToSendData == 1) {
    Serial.println("hAVE TO SEND DATA");
    HTTPClient http;
    // nu stie https
    //    http.begin("http://etixbizi.ro/api/env3224_data");
    //    http.begin("http://etixmonitor-ndcristian86536.codeanyapp.com/api/env3224_data");
    http.begin("http://192.168.1.222/");
    //    http.addHeader("Content-Type", "application/json; charset=utf-8");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
    //    http.addHeader("Content-Type", "text/plain");
    int httpCodeTemp = http.POST(postQuery);   //Send the request
    String payloadTemp = http.getString();    //Get the response payload
    Serial.println(httpCodeTemp);
    Serial.println(payloadTemp);
    http.end();
    valueSent = (value > 0) ? 1 : 0;
  }
  delay(5000);

}
