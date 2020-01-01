#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "SSID"
#define STAPSK  "PASSWORD"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;

int UP = 2; // the input to the relay pin
int DOWN = 0; // the input to the relay pin

void setup(void) {
  pinMode(UP, OUTPUT); // initialize pin as OUTPUT
  pinMode(DOWN, OUTPUT); // initialize pin as OUTPUT

  
//  pinMode(13, OUTPUT);          // sets the digital pin 13 as output
//  digitalWrite(13, HIGH);       // switches OFF the relay
//  pinMode(12, OUTPUT);          // sets the digital pin 13 as output
//  digitalWrite(12, HIGH);       // switches OFF the relay
  
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }


  server.on("/up", []() {
    server.send(200, "text/plain", "this works as well");
    digitalWrite(UP, HIGH);        // switches ON the relay
    digitalWrite(DOWN, LOW);        // switches ON the relay
    delay(625);    
    digitalWrite(UP, HIGH);        // switches ON the relay
    digitalWrite(DOWN, HIGH);        // switches ON the relay

  });

  server.on("/down", []() {
    server.send(200, "text/plain", "this works as well");
    digitalWrite(UP, LOW);        // switches ON the relay
    digitalWrite(DOWN, HIGH);        // switches ON the relay
    delay(1000);    
    digitalWrite(UP, HIGH);        // switches ON the relay
    digitalWrite(DOWN, HIGH);        // switches ON the relay
  });



  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
