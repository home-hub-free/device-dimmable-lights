#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <server-handler.h>

ESP8266WebServer server(80);
int PWM = 0;
float frequencyValuePerPercent = 2.55;

void set() {
  String value = server.arg("value");
  int percent = value.toInt();
  int newPWM = frequencyValuePerPercent * percent;
  int multiplier = newPWM > PWM ? 1 : -1;

  while (PWM != newPWM) {
    PWM = PWM + multiplier;
    analogWrite(D0, PWM);
    delay(1);
  }

  if (PWM >= 255) {
    digitalWrite(D0, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (PWM <= 0) {
    digitalWrite(D0, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }

  Serial.println(value);
  server.send(200, "text/plain", "true");
}

void test() {
  server.send(200, "text/plain", "it works brah");
}

void initServer() {
  server.on("/set", set);
  server.on("/test", test);
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
unsigned long interval = 30 * 1000;
void loop() {
  unsigned long currentMills = millis();

  server.handleClient();

  if (currentMills - previousMillis >= interval) {
    previousMillis = currentMills;
    declareDevice();
  }
} 