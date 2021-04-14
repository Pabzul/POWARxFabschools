#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "46.101.82.150";

int brightness;

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);

  // Creamos una instancia de la clase WiFiManager
  WiFiManager wifiManager;

  // Descomentar para resetear configuración
  wifiManager.resetSettings();

  // Cremos AP y portal cautivo
  wifiManager.autoConnect("«--POWAR--»", "12345678");

  Serial.println("YOU ARE CONNECTED");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
}

void loop() {

  if (!client.connected()) reconnect();
  client.loop();

  // Publish every 1000 milliseconds
  if (millis() % 1000 == 0) {

    // READ YOUR SENSOR DATA HERE
    float value = (analogRead(A0))/10;

    // Send value as characters
    char msg[50];
    snprintf (msg, 50, "%f", value);
    Serial.print("Publish message: ");
    Serial.println(msg);

    // SET THE TOPIC TO PUBLISH HERE
    client.publish("POWAR/LIGHT", msg);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  String strPayload = String((char*)payload);

  // Serial.println(strPayload.toFloat());
  // Serial.println(strPayload.toInt());

  // USE RECEIVED DATA HERE
  if (strPayload.toInt() > 5) digitalWrite(D2, LOW);
  else digitalWrite(D2, HIGH);

  //y = map(strPayload, 0, 2000, 0, 255)
  //analogWrite(D2, y)

  brightness = map(strPayload.toInt(), 0, 2000, 0, 255);
  analogWrite(D2, brightness);

}

void reconnect() {

  // Loop until we're reconnected
  while (!client.connected()) {

    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");

      // SET THE TOPIC TO SUBSCRIBE HERE
      client.subscribe("POWAR/LED");

    } else {

      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);

    }
  }
}
