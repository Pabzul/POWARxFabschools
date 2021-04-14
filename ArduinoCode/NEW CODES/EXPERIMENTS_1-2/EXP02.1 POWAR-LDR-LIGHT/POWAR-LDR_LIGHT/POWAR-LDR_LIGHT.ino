#define LDR A0
#define Light 10

float LDRval = 0;
float sunny = 0; // calibrate sensor value WHEN LIGHT
float dark = 1024; // calibrate sensor value WHEN DARK
float treshold = 50; // define treshold to turn lights ON or OFF

void setup() {
  
  Serial.begin(9600);
  
  pinMode(Light, OUTPUT);
  digitalWrite(Light,LOW);
}

void loop() {

  LDRval = map(analogRead(LDR),sunny,dark,0,100);
  
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

}
