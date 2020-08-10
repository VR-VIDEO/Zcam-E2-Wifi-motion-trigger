#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266HTTPClient.h>
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
//Your Domain name with URL path or IP address with path
String serverName = "http://10.98.33.1";
int sensor = 14;
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(sensor, INPUT); // declare sensor as input
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("ZCAM WiFi Manager");
    Serial.println("connected :)");
  }     

void loop() { 
  if (WiFi.status() == WL_CONNECTED)
        {
           long state = digitalRead(sensor);
  delay(1000);
    if(state == HIGH){
     
      Serial.println("Motion detected!");
       zcamGET();
    }
    else {
     
      Serial.println("Motion absent!");
      }
        
         delay(5000); 
          }
     
     
}
void zcamGET(){
     HTTPClient http;

      String serverPath = serverName + "/ctrl/rec?action=start";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    
    
          } 
                       
        
     
  
