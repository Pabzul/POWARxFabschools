#define MUX_A D5
#define MUX_B D4
#define MUX_C D3

#define ANALOG_INPUT A0

float MOISTval;
float Moist;
float dry = 0; // Calibrate with reading when DRY
float wet = 1024; // Calibrate with reading when TOTALLY WET

void setup() {
  Serial.begin(9600);
    
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

  // MOIST READ - MuxPin1
  changeMux(LOW, LOW, HIGH);
  Moist = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 1 pin of Mux
  MOISTval = map(Moist,dry,wet,0,100);
  
  Serial.print("Moist Read: ");
  Serial.print(Moist);
  Serial.print(" Moist Percent: ");
  Serial.print(MOISTval);
  Serial.println(" %");
  delay(1000);

}
