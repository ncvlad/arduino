#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Mediu";          // fill in here your router or wifi SSID
const char *password = "0000123456"; // fill in here your router or wifi password
IPAddress ip(192, 168, 1, 222);
#define RELAY 0 // relay connected to  GPIO0
WiFiServer server(80);
// test git
int isAutoPowerOff = 1;
int haveToSendData;
int isWaterPresent = 0;

String measureValue = "0";
unsigned  long timeReayStart = 1L;
unsigned  long timeRelayWorking;
unsigned  long timeToStayOn = 1800000L;
unsigned  long checkWaterInterval = 60000L;
int countReceivedMessages = 0;
int lastCounterMessagesComparation = 0;

String postQuery;
int value = LOW;


void setup()
{
  Serial.begin(115200); // must be same baudrate with the Serial Monitor
  haveToSendData = 0;
  pinMode(RELAY, OUTPUT);
  // start with relay OFF
  digitalWrite(RELAY, HIGH);

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
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("https://192.168.1.222/");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
//*************************************
//******************LOOP
//*************************************

void loop()
{
  //Serial.println("LOOP first line");
  // Set relay off after 20 min

  timeRelayWorking = millis() - timeReayStart;

  if (timeRelayWorking > timeToStayOn && isAutoPowerOff == 1) {
    digitalWrite(RELAY, HIGH);
    Serial.println("Relay off after set time");
    isAutoPowerOff = 0;
    haveToSendData = 1;
  }

  if (haveToSendData == 1) {
    //?value=223344&station=pompa&measure=OnOff
    HTTPClient http;
    if (value == HIGH) {
      measureValue = "0";
    } else {
      measureValue = "1";
    }
    // nu stie https
    http.begin("http://etixbizi.ro/api/env3224_data");
    //    http.begin("http://etixmonitor-ndcristian86536.codeanyapp.com/api/env3224_data");
    //    http.addHeader("Content-Type", "application/json; charset=utf-8");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
    //    http.addHeader("Content-Type", "text/plain");
    //    postQuery = "value=" + measureValue + "&station=pompa&measure=OnOff";
    postQuery = "station=pompa&measure=OnOff";
    int httpCodeTemp = http.POST(postQuery);   //Send the request
    String payloadTemp = http.getString();    //Get the response payload
    Serial.println(httpCodeTemp);
    Serial.println(payloadTemp);
    haveToSendData = 0;
    http.end();
  }


  String ADCData, station, getData, relayStatus;

  // Check if a client has connected
  WiFiClient client = server.available();
  // this line end the code here
  if (!client)
  {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  String request2 = client.readString();
  Serial.println("Request is:");
  Serial.println(request);
  Serial.println(request2);

  client.flush();

  if (request2.indexOf("waterDetected=0") != -1) {
    Serial.println("Whater is still prezent");
    isWaterPresent = 1;
    countReceivedMessages ++;

  }

  if (request2.indexOf("waterDetected=1") != -1) {
    Serial.println("Whater is not present. Relay should be OFF");
    digitalWrite(RELAY, HIGH);
  }

  // verificam daca dupa un min de la pornire este apa pe furtun
  if (value = LOW && (millis() - timeReayStart) > checkWaterInterval )  {
    if (isWaterPresent == 0) {
      Serial.println("Whater is not present after set time. Relay should be OFF");
      digitalWrite(RELAY, HIGH);
    }
    checkWaterInterval += 120000L;
    // ne intreseaza doar daca detectorul de apa mai fuctioneaza si trimite mesaje
    // de asta folosim counter si nu mai folosim millis()
    if (countReceivedMessages <= lastCounterMessagesComparation ) {
      // nu se mai primeste mesaj de la detectorul de apa. Problema cu detectorul de apa
      // pompa trebuie oprita
      Serial.println("No signal from water detector after 2 minutes.  Relay should be OFF");
      digitalWrite(RELAY, HIGH); //
    }
    lastCounterMessagesComparation = countReceivedMessages;
  }

  // Match the request
  if (request.indexOf("/RELAY=7731") != -1)
  {
    Serial.println("RELAY=ON");
    digitalWrite(RELAY, LOW);
    value = LOW;
    timeReayStart = millis();
    isAutoPowerOff = 1;
    haveToSendData = 1;
    checkWaterInterval = 60000L;
  }


  if (request.indexOf("/RELAY=7730") != -1)
  {
    Serial.println("RELAY=OFF");
    digitalWrite(RELAY, HIGH);
    value = HIGH;
    haveToSendData = 1;
  }
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  this is a must
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head><title>ESP8266 RELAY Control</title></head>");
  client.print("Relay is now: ");

  if (value == HIGH)
  {
    client.print("OFF");
  }
  else
  {
    client.print("ON");
  }
  client.println("<br><br>");
  client.println("Turn <a>OFF</a> RELAY WORKING<br>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");

}
