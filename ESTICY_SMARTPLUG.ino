#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
const char* ssid = "ESTICY";        //WIFI Name
const char* password = "esticyesp"; //WIFI Password

IPAddress staticIP(192,168,43,100);

IPAddress gateway(192,168,43,1);

IPAddress subnet(255,255,255,0);

int ledPin1 = 13; 
int ledPin2 = 12; 
int ledPin3 = 14;
WiFiServer server(80);

String html ="<DOCTYPE html> <html> <head> <title> ESTICY Remote-Controller </title> <hr size='10px'color=#BCAAA4 width= \"50%\" height=\"50%\"> <body> <body bgcolor=\"teal\"> <center> <font color =#EEEEEE <font size =\"24\" <font face=\"ALGERIAN\"> ESTICY Smart-Plug </font> </center> <b> <center> Copyright : Des 2018 </b></center> <style> .submit {background-color :#E0E0E0; color:black; font-weight: bold; border:2px solid #000000; padding:15px 15px; margin-right:10px ;margin-left:10px; } </style> <blink> <hr size = \"10px\" color=#BCAAA4 width = \"50%\" height=\"50%\"> </blink> <b> <center> Electric Plug 1 </b> </center> <form1> <center> <a href=\"LED1=ON\" ><input class=\"submit\" type=\"submit\" value=\"ON\"/> </a> <a href=\"LED1=OFF\" ><input class=\"submit\" type =\"submit\" value=\"OFF\"/> </form1> </center></a> <br> </br> <b><center> Electric Plug 2 </b> </center> <b><right> <form2> <center> <a href=\"LED2=ON\"> <input class=\"submit\" type=\"submit\" value=\"ON\" /> <a href=\"LED2=OFF\"><input class=\"submit\" type =\"submit\" value=\"OFF\"/> </form2> </center> <br></br> </a> <b><center> Electric Plug 3 </b> </center> <form3> <center> <a href=\"LED3=ON\"> <input class=\"submit\" type=\"submit\" value=\"ON\"/> </a> <a href=\"LED3=OFF\"><input class=\"submit\" type =\"submit\" value=\"OFF\"/> </form3> </center></a> </body> </body> </head> </html>";
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");

  while(!WiFi.config(staticIP, gateway, subnet)) {
  Serial.println("STA Failed to configure");
}
 
  server.begin();
  Serial.println("Server started");
 
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(ledPin1, HIGH);
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(ledPin1, LOW);
  }
  if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(ledPin2, HIGH);
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(ledPin2, LOW);
  }  
   if (request.indexOf("/LED3=ON") != -1)  {
    digitalWrite(ledPin3, HIGH);
  }
  if (request.indexOf("/LED3=OFF") != -1)  {
    digitalWrite(ledPin3, LOW);
  }
 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println(html);
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
