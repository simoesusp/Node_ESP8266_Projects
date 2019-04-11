/* Create a server in the ESP that keep listening to 192.168.43.160
 * Port 80 by default
 * 
 * To send commands to Node via Browser, just type:
 * 192.168.43.160/ligaled   and wait for the reply
 * 192.168.43.160/motor?speed=25     sends number 25
 * 
 * To send commands to Nede via Terminal, just type:
 * curl 192.168.43.160/ligaled   and wait for the reply
 * curl 192.168.43.160/motor?speed=25     sends number 25
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
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

void motor() {
  if(server.hasArg("speed")) {
    int speed = server.arg("speed").toInt();

    Serial.println(speed);

    server.send(200, "text/html", "OK! velocidade recebida");
  }
}

void setup() {
  //LED
  pinMode(LED_BUILTIN, OUTPUT);
  
  // OTA SETUP
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(500);
    ESP.restart();
  }

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { 
      type = "filesystem";
    }

    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // END OF OTA SETUP

  //HTTP SERVER?
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/motor", HTTP_GET, motor);

  server.on("/ligaled", []() {
    server.send(200, "text/plain", "ligou");
    digitalWrite(LED_BUILTIN, LOW);
  });

  server.on("/desligaled", []() {
    server.send(200, "text/plain", "apagou");
    digitalWrite(LED_BUILTIN, HIGH);
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  //END OF HTTP SERVER
}

void loop() {
  ArduinoOTA.handle();

  server.handleClient();
  MDNS.update();
}
