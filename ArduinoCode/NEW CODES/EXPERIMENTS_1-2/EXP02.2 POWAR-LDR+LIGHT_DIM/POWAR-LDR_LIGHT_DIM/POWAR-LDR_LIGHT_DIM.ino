#define LDR A0
#define Light 10

int LDRval = 0;

void setup() {
  
  Serial.begin(9600);
  pinMode(Light, OUTPUT);
}

void loop() {

  LDRval = analogRead(LDR);
  analogWrite(Light, (LDRval/4));

}
