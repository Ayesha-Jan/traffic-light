#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>
#include <detail/mimetable.h>

#ifndef STASSID
#define STASSID "Ayesha"
#define STAPSK "ayesha123"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;
ESP8266WebServer server(80);

const int redLed = 13;
const int yellowLed = 12;
const int greenLed = 14;

void handleNotFound() {
    digitalWrite(redLed, 1);
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
    server.send(404, "text/plain", message);
    digitalWrite(redLed, 0);
  }

void handleRedLedOn() {
    digitalWrite(redLed, HIGH);
    server.send(200, "text/plain", "Red LED is ON");
  }
void handleYellowLedOn() {
    digitalWrite(yellowLed, HIGH);
    server.send(200, "text/plain", "Yellow LED is ON");
  }
 void handleGreenLedOn() {
    digitalWrite(greenLed, HIGH);
    server.send(200, "text/plain", "Green LED is ON");
  }
   
void handleRedLedOff() {
    digitalWrite(redLed, LOW);
    server.send(200, "text/plain", "Red LED is OFF");
  }
void handleYellowLedOff() {
    digitalWrite(yellowLed, LOW);
    server.send(200, "text/plain", "Yellow LED is OFF");
  }
void handleGreenLedOff() {
    digitalWrite(greenLed, LOW);
    server.send(200, "text/plain", "Green LED is OFF");
  }

void setup() {
    Serial.begin(115200);

    pinMode(redLed, OUTPUT);
    pinMode(yellowLed, OUTPUT);
    pinMode(greenLed, OUTPUT);

    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    if (!LittleFS.begin()) {
        Serial.println("LittleFS mount failed!");
        return;
    }

    server.on("/", HTTP_GET, []() {
        File file = LittleFS.open("/index.html", "r");
        if (!file) {
            server.send(404, "text/plain", "File not found");
            return;
        }
        server.streamFile(file, "text/html");
        file.close();
    });

    server.on("/style.css", HTTP_GET, []() {
      File file = LittleFS.open("/style.css", "r");
      if (!file) {
          server.send(404, "text/plain", "File not found");
          return;
      }
      server.streamFile(file, "text/css");
      file.close();
    });
  
    server.on("/script.js", HTTP_GET, []() {
      File file = LittleFS.open("/script.js", "r");
      if (!file) {
          server.send(404, "text/plain", "File not found");
          return;
      }
      server.streamFile(file, "application/javascript");
      file.close();
    });

    server.on("/car.png", HTTP_GET, []() {
        File file = LittleFS.open("/car.png", "r");
        if (!file) {
            server.send(404, "text/plain", "File not found");
            return;
        }
        server.streamFile(file, "image/png");
        file.close();
    });

    server.on("/red/led/on", HTTP_GET, handleRedLedOn);
    server.on("/red/led/off", HTTP_GET, handleRedLedOff);
    server.on("/yellow/led/on", HTTP_GET, handleYellowLedOn);
    server.on("/yellow/led/off", HTTP_GET, handleYellowLedOff);
    server.on("/green/led/on", HTTP_GET, handleGreenLedOn);
    server.on("/green/led/off", HTTP_GET, handleGreenLedOff);

    server.onNotFound(handleNotFound);

    server.begin();
}

void loop() {
    server.handleClient();
}