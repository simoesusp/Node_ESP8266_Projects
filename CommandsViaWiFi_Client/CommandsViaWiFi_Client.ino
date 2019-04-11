#include <ESP8266WiFi.h>


const char *ssid = "your-ssid";
const char *password = "your-passward";

int sensorValue = 25;        // value read from the potentiometer
int outputValue = 0;        // value sent to server

void setup() {
  Serial.begin(115200);
  delay(10);

  // Explicitly set the ESP8266 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  // read the analog in value:
  sensorValue++;
  // map to range. The pot goes from about 3 to 1023. This makes the sent value be between 0 and 999 to fit on the OLED
  outputValue = map(sensorValue, 3, 1023, 0, 999);

  char intToPrint[5];
  itoa(outputValue, intToPrint, 10); //integer to string conversion for OLED library


  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const char * host = "192.168.4.1";
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request. Something like /data/?sensor_reading=123
  String url = "/data/";
  url += "?sensor_reading=";
  url += intToPrint;

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  delay(1000);
}
