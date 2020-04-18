#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Mediu";          // fill in here your router or wifi SSID
const char *password = "0000123456"; // fill in here your router or wifi password
IPAddress ip(192, 168, 1, 222);
#define RELAY 0 // relay connected to  GPIO0
WiFiServer server(80);
// test git
int isAutoPowerOff = 1;
unsigned  long timeReayStart = 1L;
unsigned  long timeRelayWorking;
unsigned  long timeToStayOn = 1800000L;


void setup()
{
  Serial.begin(115200); // must be same baudrate with the Serial Monitor

  pinMode(RELAY, OUTPUT);
  // start with relay OFF
  digitalWrite(RELAY, HIGH);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(IPAddress(192, 168, 1, 222), IPAddress(192, 168, 1, 1), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 1));

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
  Serial.print("https://192.168.0.178/");
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
  }



  HTTPClient http;
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

  //  while (!client.available())
  //  {
  //    delay(1);
  //  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  int value = LOW;

  // Match the request
  if (request.indexOf("/RELAY=7731") != -1)
  {
    Serial.println("RELAY=ON");
    digitalWrite(RELAY, LOW);
    value = LOW;
    timeReayStart = millis();
    isAutoPowerOff = 1;
  }


  if (request.indexOf("/RELAY=7730") != -1)
  {
    Serial.println("RELAY=OFF");
    digitalWrite(RELAY, HIGH);
    value = HIGH;
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
  Serial.println("Client disonnected");
  Serial.println("");

}
