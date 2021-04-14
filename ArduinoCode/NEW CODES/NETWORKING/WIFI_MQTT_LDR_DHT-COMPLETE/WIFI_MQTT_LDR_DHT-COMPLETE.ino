#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>
 
const char* ssid = "";
const char* password = "";
const char* mqtt_server = "46.101.82.150";
 
int brightness;
 
WiFiClient espClient;
PubSubClient client(espClient);
 
#include <DHT.h>
#define DHTPIN 2
#define ledPin 0
#define LDRpin A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
 
int LDRread = 0;
 
long now = millis();
long lastMeasure = 0;
 
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  
  dht.begin();
 
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
 
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("POWARfull Connection");
 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 
}
 
void loop() {
 
  if (!client.connected()) reconnect();
  client.loop();
 
  if (millis() % 500 == 0) {
 
 
//---------- TEAM MESSAGE ---------//
 
    // SET THE TOPIC TO PUBLISH HERE
    client.publish("POWAR/TEAM", "Colombia");
 
 
 
//---------- LDR Read ---------//
 
    LDRread = analogRead(LDRpin);
    float LDRmap = map(LDRread, 0, 1023, 100, 0); //map the values of the sensor between 0 and 100
 
 
 
//---------- LDR Publish ---------//
 
    // Send value as characters
    char LDRmsg[50];
    snprintf (LDRmsg, 50, "%f", LDRmap);
    Serial.print("Publish message: ");
    Serial.println(LDRmsg);
 
    // SET THE TOPIC TO PUBLISH HERE
    client.publish("POWAR/LDR", LDRmsg);
 
 
 
//---------- DHT Read ---------//
 
   now = millis();
 
  if (now - lastMeasure > 500) {
    lastMeasure = now;
 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
 
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
 
 
 
 
//---------- DHT Publish ---------//
 
    // Send value as characters
    char DHTmsg[5];
    snprintf (DHTmsg, 5, "%f", t);
    Serial.print("Publish message: ");
    Serial.println(DHTmsg);
 
    // SET THE TOPIC TO PUBLISH HERE
    client.publish("POWAR/DHT", DHTmsg);
 
    }
  }
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  String topicStr = topic;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[0]);
  }
  Serial.println();
 
  // Switch on the LED if an 1 was received as first character
  if (payload[0] == '1') {
    digitalWrite(ledPin, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    Serial.println("LIGHT ON");
  } else {
    digitalWrite(ledPin, LOW);  // Turn the LED off by making the voltage HIGH
    Serial.println("LIGHT OFF");
  }
 
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
