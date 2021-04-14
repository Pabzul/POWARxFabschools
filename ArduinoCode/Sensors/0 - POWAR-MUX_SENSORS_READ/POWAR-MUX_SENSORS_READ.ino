#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

#define MUX_A D5
#define MUX_B D4
#define MUX_C D3

#define ANALOG_INPUT A0

float LDRval;
float LDR;
float MOISTval;
float Moist;
float MOISTdry = 0; // Calibrate with reading when DRY
float MOISTwet = 1024; // Calibrate with reading when TOTALLY WET
float Tank;
float TANKval;
float TANKdry = 0; // Calibrate with reading when DRY
float TANKwet = 1024; // Calibrate with reading when TOTALLY WET

DHT dht(DHTPIN, DHTTYPE);

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

  // LDR READ - MuxPin2
  changeMux(LOW, HIGH, LOW);
  LDR = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 2 pin of Mux
  LDRval = map(LDR,0,1024,0,100);
  delay(300);

  // MOIST READ - MuxPin1
  changeMux(LOW, LOW, HIGH);
  Moist = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 1 pin of Mux
  MOISTval = map(Moist,MOISTdry,MOISTwet,0,100);
  delay(300);
  
  // TANK READ - MuxPin0
  changeMux(LOW, LOW, LOW);
  Tank = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 0 pin of Mux
  TANKval = map(Tank,TANKdry,TANKwet,0,100);
  delay(300);

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
  
  Serial.print(F("Light Percent: "));
  Serial.print(LDRval);
  Serial.println(" %");

  Serial.print(" Water Percent: ");
  Serial.print(TANKval);
  Serial.println(" %");

  Serial.print(" Moist Percent: ");
  Serial.print(MOISTval);
  Serial.println(" %");

}
