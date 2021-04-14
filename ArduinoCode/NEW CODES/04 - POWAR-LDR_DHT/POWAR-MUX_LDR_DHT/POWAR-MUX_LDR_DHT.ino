#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

#define MUX_A D5
#define MUX_B D4
#define MUX_C D3

#define ANALOG_INPUT A0


DHT dht(DHTPIN, DHTTYPE);
float LDRvalue = 0;


void setup() {
  Serial.begin(9600);
  dht.begin();
  
  //Deifne output pins for Mux
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);     
  pinMode(MUX_C, OUTPUT);     
}

void changeMux(int c, int b, int a) {
  digitalWrite(MUX_A, a);
  digitalWrite(MUX_B, b);
  digitalWrite(MUX_C, c);
}

void loop() {
  delay(1000);

  float LDRvalue;
  float LDR;

  // LDR READ - MuxPin2
  changeMux(LOW, HIGH, LOW);
  LDR = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 2 pin of Mux

  LDRvalue = map(LDR,0,1024,0,100);
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
  Serial.println(F("°C "));
  Serial.print(F("Light Percentage: "));
  Serial.print(LDRvalue);
  Serial.println(" %");

}
