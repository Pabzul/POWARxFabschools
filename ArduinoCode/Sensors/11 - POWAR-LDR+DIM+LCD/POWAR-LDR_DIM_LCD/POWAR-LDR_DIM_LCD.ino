#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const char* Cond = "";

float  LDR;
float  LDRval;

LiquidCrystal_I2C lcd(0x3F,16,2); // could also be 0x27 instead of 0x3F

void setup()
{

lcd.init();
lcd.display();

Serial.begin(9600);

}


void loop()
{

    LDR = analogRead(A0);
    LDRval = (map(LDR, 0, 1023, 0, 100));
    Serial.println(analogRead(A0));
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

}
