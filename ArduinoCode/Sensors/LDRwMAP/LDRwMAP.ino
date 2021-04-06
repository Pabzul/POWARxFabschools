
#define LDR A0

float LDRvalue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  LDRvalue = map(analogRead(LDR),0,1024,0,100);
  Serial.print(LDRvalue);
  Serial.println(" %");
  delay(300);

}
