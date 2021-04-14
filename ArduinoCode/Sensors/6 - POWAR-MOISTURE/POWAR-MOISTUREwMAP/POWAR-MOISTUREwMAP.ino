#define Moist A0

float MOISTval;
float dry = 0; // Calibrate with reading when DRY
float wet = 1024; // Calibrate with reading when TOTALLY WET

void setup() {
  Serial.begin(9600);

}

void loop() {

  MOISTval = map(analogRead(Moist),dry,wet,0,100);
  Serial.print("Moist Read: ");
  Serial.print(Moist);
  Serial.print(" Moist Percent: ");
  Serial.print(MOISTval);
  Serial.println(" %");

}
