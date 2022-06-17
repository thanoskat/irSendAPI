#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "irDevices.h"

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
const uint16_t kIrLed = 14;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
uint8_t deviceCount = sizeof(devices)/sizeof(devices[0]);
ESP8266WebServer server(80);

void sendIR() {
  String message = "";
  String device = "";
  String command = "";
  for(uint8_t i = 0; i < server.args(); i++){
    if(server.argName(i) == "device"){
      device += server.arg(i);
    }
    else if (server.argName(i) == "command"){
      command += server.arg(i);
    }
    message += server.argName(i) + ": " + server.arg(i) + "\n";
  }
  message += "\n";
  bool deviceFound = false;
  bool commandFound = false;
  //Iterate through devices in irDevices.h
  for(uint8_t i=0; i<deviceCount; i++){
    if(device == devices[i].deviceName){
      deviceFound = true;
      //Iterate through commands in device
      for(uint8_t j=0; j<50; j++){
        if(command == devices[i].irCommand[j].commandName){
          commandFound = true;
          if(irsend.send(devices[i].protocol, devices[i].irCommand[j].irCode, devices[i].nbits, 2)){
            message +="IR code sent successfully";
            Serial.println("OK " + command + " " + device);
          }
          else{
            message +="Error while sending IR code";
          }
          break;
        }
      }
    }
  }
  if(!deviceFound){
    message +="Device " + device + " not found\n";
  }
  else if(!commandFound){
    message +="Command " + command + " not found\n";
  }
  server.send(200, "text/plain", message);
}

// Define routing
void restServerRouting() {
    server.on("/", HTTP_GET, []() {
        server.send(200, F("text/html"), F("Welcome to the REST Web Server"));
    });
    server.on(F("/sendIR"), HTTP_GET, sendIR);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
  irsend.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.printf("Connected to %s\n", ssid);
  Serial.println("IP address: " + WiFi.localIP().toString());

//  if (MDNS.begin("esp8266")) { // Activate mDNS to connect with hostmane esp8266.local
//    Serial.println("MDNS responder started");
//  }

//  Add service to MDNS-SD
//  MDNS.addService("http", "tcp", 80);

  restServerRouting();
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
//  MDNS.update();
  server.handleClient();
}
