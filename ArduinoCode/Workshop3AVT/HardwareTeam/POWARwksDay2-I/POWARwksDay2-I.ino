#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
#define LDR A0


DHT dht(DHTPIN, DHTTYPE);
float LDRvalue = 0;


void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(1000);
  LDRvalue = map(analogRead(LDR),0,1024,0,100);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(F("Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(F("Light %: "));
  Serial.print(LDRvalue);
  Serial.println(" %");

}
