// Include Libraries //

#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>



// Internet Settings //

#define NETWORK "DOCTORS"
#define PASSWORD "z2NVoCvA"



// Define Inputs and Outputs //

#define MUX_A D5
#define MUX_B D4
#define MUX_C D3
#define ANALOG_INPUT A0
#define Pump 9
#define LEDstrip 10
#define Cold 8 //This is a ventilator, but could be a peltier
//#define Hot 35 //This Option would need something to heat...



// Set String variables names //

String  TOP = "";
String  BoxTempC = "";
String  BoxHum = "";
String  City = "";
String  Country = "";
String  Weather = "";
String  Description = "";
String  TempC = "";
String  MinTempC = "";
String  MaxTempC = "";
String  Time = "";
String  Sunrise = "";
String  Sunset = "";
String  Humidity = "";
String  Clouds = "";
String  Light = "";



// Set Float variables names //

float LDR;
float LDRval;
float Moist;
float MOISTval;
float MOISTdry = 0; // Calibrate with reading when DRY
float MOISTwet = 1024; // Calibrate with reading when TOTALLY WET
float Tank;
float TANKval;
float TANKdry = 0; // Calibrate with reading when DRY
float TANKwet = 1024; // Calibrate with reading when TOTALLY WET



// Components Settings //

DHT dht(2,DHT11);
LiquidCrystal_I2C lcd(0x27,16,2); // If screen doesn't works change 0x27 for 0x3F
WiFiClient espClient;
PubSubClient client(espClient);



// MQTT Topic Subscription //

void reconnectmqttserver() {
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
String clientId = "ESP32Client-";
 clientId += String(random(0xffff), HEX);
if (client.connect(clientId.c_str())) {
Serial.println("connected");
  client.subscribe("POWAR/City");
  client.subscribe("POWAR/Country");
  client.subscribe("POWAR/Weather");
  client.subscribe("POWAR/Description");
  client.subscribe("POWAR/TempC");
  client.subscribe("POWAR/MinTempC");
  client.subscribe("POWAR/MaxTempC");
  client.subscribe("POWAR/Time");
  client.subscribe("POWAR/Sunrire");
  client.subscribe("POWAR/Sunset");
  client.subscribe("POWAR/Humidity");
  client.subscribe("POWAR/Clouds");
  client.subscribe("POWAR/Light");
} else {
Serial.print("failed, rc=");
Serial.print(client.state());
Serial.println(" try again in 5 seconds");
delay(5000);
}
}
}



// Get messages from topics and Serial Print them //

char msgmqtt[50];
void callback(char* topic, byte* payload, unsigned int length) {
  String MQTT_DATA = "";
  for (int i=0;i<length;i++) {
   MQTT_DATA += (char)payload[i];}
  TOP = topic;
  if (TOP == "POWAR/City") {
    Serial.print("City: ");
    Serial.print(MQTT_DATA);
    Serial.println("");
    City = MQTT_DATA;

  }
  if (TOP == "POWAR/Country") {
    Serial.print("Country: ");
    Serial.print(MQTT_DATA);
    Serial.println("");
    Country = MQTT_DATA;

  }
  if (TOP == "POWAR/Weather") {
    Serial.print("Weather: ");
    Serial.print(MQTT_DATA);
    Serial.println("");
    Weather = MQTT_DATA;

  }
  if (TOP == "POWAR/Description") {
    Serial.print("Description: ");
    Serial.print(MQTT_DATA);
    Serial.println("");
    Description = MQTT_DATA;

  }
  if (TOP == "POWAR/TempC") {
    Serial.print("TempC: ");
    Serial.print(MQTT_DATA.toFloat());
    Serial.println("");
    TempC = MQTT_DATA;

  }
  if (TOP == "POWAR/MinTempC") {
    Serial.print("Min TempC: ");
    Serial.print(MQTT_DATA.toFloat());
    Serial.println("");
    MinTempC = MQTT_DATA;

  }
  if (TOP == "POWAR/MaxTempC") {
    Serial.print("Max TempC: ");
    Serial.print(MQTT_DATA.toFloat());
    Serial.println("");
    MaxTempC = MQTT_DATA.toFloat();

  }
  if (TOP == "POWAR/Time") {
    Serial.print("Time: ");
    Serial.print(MQTT_DATA.toInt());
    Serial.println("");
    Time = MQTT_DATA;

  }
  if (TOP == "POWAR/Sunrise") {
    Serial.print("Sunrise: ");
    Serial.print(MQTT_DATA.toInt());
    Serial.println("");
    Sunrise = MQTT_DATA;

  }
  if (TOP == "POWAR/Sunset") {
    Serial.print("Sunset: ");
    Serial.print(MQTT_DATA.toInt());
    Serial.println("");
    Sunset = MQTT_DATA;

  }
  if (TOP == "POWAR/Humidity") {
    Serial.print("Humidity: ");
    Serial.print(MQTT_DATA.toInt());
    Serial.println("");
    Humidity = MQTT_DATA;

  }
  if (TOP == "POWAR/Clouds") {
    Serial.print("Clouds: ");
    Serial.print(MQTT_DATA.toInt());
    Serial.println("");
    Clouds = MQTT_DATA;

  }
  if (TOP == "POWAR/Light") {
    Serial.print("Light: ");
    Serial.print(MQTT_DATA.toInt());
    Serial.println("");
    Light = MQTT_DATA;

  }
  TOP = "";

}




void setup()
{

// Serial Port Begin //

Serial.begin(9600);



// LCD Begin and initial texts //

  lcd.init();
  lcd.backlight();
  Serial.println("===== POWAR BEGIN =====");
  WiFi.disconnect();
  lcd.setCursor(0, 0);
  lcd.print("    Welcome to   ");
  lcd.setCursor(0, 1);
  lcd.print("   =  POWAR  =   ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LOADING WIFI .................................");
  lcd.scrollDisplayLeft();



// WIFI connect + LCD and Serial Print //

  WiFi.begin(NETWORK,PASSWORD);
  while ((!(WiFi.status() == WL_CONNECTED))){
    Serial.print(" ... ");
    delay(300);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("===== POWAR =====");
  lcd.setCursor(0, 1);
  lcd.print("  Is Connected!  ");
  delay(1000);
  Serial.println("");
  Serial.println("===== POWAR is Connected =====");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));



// MQTT Connect //
  Serial.println("Connecting MQTT");
  client.setServer("46.101.82.150", 1883);
  client.setCallback(callback);



// Temperature and Humidity sensor begin //

  dht.begin();



// Set Outputs fir Pump, Light and temperature regulator //

  pinMode(Cold, OUTPUT);
  //  pinMode(Hot, OUTPUT);
  pinMode(Pump, OUTPUT);
  pinMode(LEDstrip, OUTPUT);


  
// Deifne output pins for Multiplexer //

  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);     
  pinMode(MUX_C, OUTPUT);     

}



// Create changeMux function //

void changeMux(int c, int b, int a) {
  digitalWrite(MUX_A, a);
  digitalWrite(MUX_B, b);
  digitalWrite(MUX_C, c);
}




void loop()
{

// MQTT Loop //

    if (!client.connected()) {
    reconnectmqttserver();
    }
    client.loop();


    
// LDR READ - MuxPin 2 //
  long now = millis();
  if (now - lastMsg > 60000) {
    wmm.lastMsg = now;
    changeMux(LOW, HIGH, LOW);
    LDR = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 2 pin of Mux
    LDRval = map(LDR,0,1024,0,100);
    delay(300);


  
// MOIST READ - MuxPin 1 //

    changeMux(LOW, LOW, HIGH);
    Moist = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 1 pin of Mux
    MOISTval = map(Moist,MOISTdry,MOISTwet,0,100);
    delay(300);



// TANK READ - MuxPin0 //

    changeMux(LOW, LOW, LOW);
    Tank = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 0 pin of Mux
    TANKval = map(Tank,TANKdry,TANKwet,0,100);
    delay(300);



// DHT READ //

    float h = dht.readHumidity();
    float t = dht.readTemperature();
  
    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
  
    float hic = dht.computeHeatIndex(t, h, false);



// Serial Print Values //

    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("°C "));
    Serial.print(F("Heat index: "));
    Serial.print(hic);
    Serial.println(F("°C "));
    
    Serial.print(F("Light Percent: "));
    Serial.print(LDRval);
    Serial.println(" %");
  
    Serial.print(" Water Percent: ");
    Serial.print(TANKval);
    Serial.println(" %");
  
    Serial.print(" Moist Percent: ");
    Serial.print(MOISTval);
    Serial.println(" %");
    
    BoxHum = h;
    BoxTempC = t;



// LCD print relative humidity and temperature //

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(BoxTempC.toInt());
    lcd.print(" C");
    lcd.setCursor(0, 1);
    lcd.print("Hum:  ");
    lcd.print(BoxHum.toInt());
    lcd.print(" %");
    delay(1000);



// MQTT publish sensor values to topics //

    snprintf (msgmqtt, 50, "%f",t);
    client.publish("BOX/TempC", msgmqtt);
    snprintf (msgmqtt, 50, "%f",h);
    client.publish("BOX/Hum", msgmqtt);
    snprintf (msgmqtt, 50, "%f",LDRval);
    client.publish("BOX/LDR", msgmqtt);
    snprintf (msgmqtt, 50, "%f",TANKval);
    client.publish("BOX/Tank", msgmqtt);
    snprintf (msgmqtt, 50, "%f",MOISTval);
    client.publish("BOX/Moist", msgmqtt);



// Conditionals for TEMPERATURE regulation //

    if (BoxTempC >= MinTempC && BoxTempC <= MaxTempC) {
      digitalWrite(Cold,LOW);
      // digitalWrite(Hot,LOW);
    } else if (BoxTempC > MaxTempC) {
      digitalWrite(Cold,HIGH);
      // digitalWrite(Hot,LOW);
    } else if (BoxTempC < MinTempC) {
      digitalWrite(Cold,LOW);
      // digitalWrite(Hot,HIGH);
    }


    
// Conditional for RAIN regulation //
    
    if (Weather == "Rain") {
      digitalWrite(Pump,HIGH);
    } else {
      digitalWrite(Pump,LOW);
    }



// Conditional for SUNLIGHT regulation //

    if (Time >= Sunrise && Time <= Sunset) {
      digitalWrite(LEDstrip,HIGH);
    } else if (Time < Sunrise || Time > Sunset) {
      digitalWrite(LEDstrip,LOW);
    }



// LCD print information from Weather APP topics in MQTT //

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("City: ");
    lcd.print(City);
    lcd.setCursor(0, 1);
    lcd.print("Country: ");
    lcd.print(Country);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Weather: ");
    lcd.print(Weather);
    lcd.setCursor(0, 1);
    lcd.print(Description);
    delay(2000);

}
