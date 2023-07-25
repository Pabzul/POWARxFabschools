#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2); // could also be 0x27 instead of 0x3F

#define MUX_A D5
#define MUX_B D4
#define MUX_C D3
#define ANALOG_INPUT A0
#define Light 10

const char* Cond = "";
float  LDR;
float  LDRval;


void setup() {
  
  Serial.begin(9600);

  lcd.init();
  lcd.display();

  pinMode(Light, OUTPUT);

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
  
    Serial.println(LDR);
    analogWrite(14, (LDR / 4));;
    if (LDRval < 50) {
      const char* Cond = "DARK";

    } else if (LDRval >= 50) {
      const char* Cond = "LIGHT";
    }
    lcd.setCursor(0, 0);
    lcd.print(" LIGHT   /   COND");
    lcd.setCursor(0, 1);
    lcd.print(LDRval);
    lcd.print(" %");
    lcd.setCursor(8, 1);
    lcd.print(Cond);


  delay(1000);

}
