#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "Mediu"; // fill in here your router or wifi SSID
const char* password = "0000123456"; // fill in here your router or wifi password
IPAddress ip(192, 168, 1, 222);
 #define RELAY 0 // relay connected to  GPIO0
WiFiServer server(80);

void setup() 
{
  Serial.begin(115200); // must be same baudrate with the Serial Monitor
 
  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY, HIGH);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  
  WiFi.config(IPAddress(192,168,1,222), IPAddress(192,168,1,1), IPAddress(255,255,255,0),IPAddress(192,168,1,1));
 
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
 
void loop() 
{
  HTTPClient http; 
String ADCData, station, getData, relayStatus;
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) 
  {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
//  while(!client.available())
//  {
//    delay(1);
//  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
  int value = LOW;
  if (request.indexOf("/RELAY=7731") != -1)  
  {
    Serial.println("RELAY=ON");
    digitalWrite(RELAY,LOW);
    value = LOW;
  }
  if (request.indexOf("/RELAY=7730") != -1)  
  {
    Serial.println("RELAY=OFF");
    digitalWrite(RELAY,HIGH);
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
 
  if(value == HIGH) 
  {
    client.print("OFF");
    relayStatus = "solarWatering=OFF";
  } 
  else 
  {
    client.print("ON");
    relayStatus = "solarWatering=ON";
  }
  client.println("<br><br>");
  //client.println("Turn <a href=\"/RELAY=OFF\">OFF</a> RELAY<br>");
  //client.println("Turn <a href=\"/RELAY=ON\">ON</a> RELAY<br>");
    client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");


  getData = "http://www.etixsmart.ro/api/solar_watering/?" + relayStatus;
//getData = "solarWatering=" + relayStatus;
  
  //http.begin("http://www.etixsmart.ro/too=foo");     //Specify request destination
  http.begin(getData);
  
  int httpCode = http.GET();            //Send the request
  String payload = http.getString();    //Get the response payload
 
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
 
  http.end();  //Close connection
  
//  delay(5000);  //GET Data at every 5 seconds/
  
}
