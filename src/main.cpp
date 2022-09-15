#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <server-handler.h>

ESP8266WebServer server(80);
int PWM = 0;

void set() {
  String value = server.arg("value");
  if (value == "true") {
    while (PWM <= 255) {
      PWM++;
      analogWrite(D0, PWM);
      delay(1);
    }
    digitalWrite(D0, HIGH);
  }
  if (value == "false") {
    while (PWM >= 0) {
      PWM--;
      analogWrite(D0, PWM);
      delay(1);
    }
    digitalWrite(D0, LOW);
  }

  Serial.println(value);
  server.send(200, "text/plain", "true");
}

void initServer() {
  // server.on("/", void handleRoot() {});
  server.on("/set", set);
  // server.on("/set-pwm", setPwm);
  server.begin();
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);

  // server-handler.h
  wifi_connect();
  declareDevice();

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
}