#define MUX_A D5
#define MUX_B D4
#define MUX_C D3

#define ANALOG_INPUT A0

#define Light 10

float LDRval;
float LDR;
float sunny = 0; // calibrate sensor value WHEN LIGHT
float dark = 1024; // calibrate sensor value WHEN DARK
float treshold = 50; // define treshold to turn lights ON or OFF

void setup() {
  
  Serial.begin(9600);
  
  pinMode(Light, OUTPUT);
  digitalWrite(Light,LOW);

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
  
  Serial.print("LDR Read: ");
  Serial.print(LDR);
  Serial.print(" Light Percent: ");
  Serial.print(LDRval);
  Serial.println(" %");

  if (LDRval < treshold) {
    digitalWrite(Light,HIGH);

  } else {
    digitalWrite(Light,LOW);

  }

  delay(1000);

}
