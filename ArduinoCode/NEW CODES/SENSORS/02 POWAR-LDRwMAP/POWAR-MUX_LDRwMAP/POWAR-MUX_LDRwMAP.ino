#define MUX_A D5
#define MUX_B D4
#define MUX_C D3

#define ANALOG_INPUT A0

float LDRval;
float LDR;

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

  // LDR READ - MuxPin2
  changeMux(LOW, HIGH, LOW);
  LDR = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 2 pin of Mux
  LDRval = map(LDR,0,1024,100,0);
  
  Serial.print(LDRval);
  Serial.println(" %");

}
