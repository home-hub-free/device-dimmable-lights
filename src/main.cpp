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
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (value == "false") {
    while (PWM >= 0) {
      PWM--;
      analogWrite(D0, PWM);
      delay(1);
    }
    digitalWrite(D0, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }

  Serial.println(value);
  server.send(200, "text/plain", "true");
}

void initServer() {
  server.on("/set", set);
  server.begin();
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, LOW);

  wifiConnect();
  declareDevice();

  initServer();
  digitalWrite(LED_BUILTIN, HIGH);
}

unsigned long previousMillis = 0;
unsigned long interval = 10 * 1000;
void loop() {
  unsigned long currentMills = millis();

  server.handleClient();

  if (currentMills - previousMillis >= interval) {
    previousMillis = currentMills;
    declareDevice();
  }
} 