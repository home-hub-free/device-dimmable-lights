#ifndef WIFI_INFO_H_
#define WIFI_INFO_H_

#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiManager.h>
#elif defined(ESP32)
#endif

HTTPClient http;
WiFiClient wifiClient;
WiFiManager wifiManager;

String home_server = "http://192.168.1.199:8080";

const uint32 id = ESP.getChipId();

void wifiConnect() {
  // Attemp to auto-connect for 30 seconds
  wifiManager.setConnectTimeout(10);
  wifiManager.setConfigPortalTimeout(300);
  wifiManager.autoConnect("HHF - Dimmable Lights");

}

void declareDevice() {
  http.begin(wifiClient, home_server + "/device-declare");
  http.addHeader("Content-Type", "application/json");
  String jsonString = "{ \"id\": \"" + String(id) + "\", \"name\": \"dimmable-light\" }";
  int httpCode = http.POST(jsonString);

  if (httpCode > 0) {
    String result = http.getString();
    Serial.print("Ping sent to server: ");
    Serial.println(result);
  } else {
    Serial.print("Oops: ");
    Serial.println(httpCode);
  }
  http.end();
}

#endif /* WIFI_INFO_H_ */