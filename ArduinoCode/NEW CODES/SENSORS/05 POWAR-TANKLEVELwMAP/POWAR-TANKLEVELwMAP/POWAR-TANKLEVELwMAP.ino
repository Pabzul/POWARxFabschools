#define MUX_A D5
#define MUX_B D4
#define MUX_C D3

#define ANALOG_INPUT A0

float Tank;
float TANKval;
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

  // TANK READ - MuxPin0
  changeMux(LOW, LOW, LOW);
  Tank = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 0 pin of Mux


  TANKval = map(Tank,dry,wet,0,100);
  Serial.print("Tank Read: ");
  Serial.print(Tank);
  Serial.print(" Water Percent: ");
  Serial.print(TANKval);
  Serial.println(" %");
  delay(1000);
}
