# POWARxFabschools
POWAR at Fabschools

## BOM
*ESP-12 version at Fablab Benfica*

- Node-MCU ESP12 dev board;
- 3 sets of Jumper Wires - MM, MF, FF;
- 1 breadboard Power Adaptor;
- 1 Breadboard;
- 1 mini-breadboard;
- [1 Water-Pump + Tubing](https://www.amazon.es/-/pt/gp/product/B08BZBN29C/ref=ppx_od_dt_b_asin_title_s00?ie=UTF8&psc=1);
- [1 Fan]()
- [1 Temp and Humid Sensor](https://www.amazon.es/-/pt/gp/product/B07TSF94KD/ref=ppx_od_dt_b_asin_title_s00?ie=UTF8&psc=1)
- [1 LCD]()
- [1 LCD breakout]()
- [1 Mosfet Module]()
- [1 Light Sensor]()
- [1 2x relay module]()
- [1 water sensor]()
- [1 Moisture Sensor](https://www.amazon.es/-/pt/gp/product/B07V6M5C4H/ref=ppx_od_dt_b_asin_title_s00?ie=UTF8&psc=1)
- [1 grow Led Strip]()
- [1 Powar Source]() - *unavailable*



## Code

-  Arduino Code for each sensor:
  - [LED Blink](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/SENSORS/01%20POWAR-LED_Blink/POWAR-LED_Blink)
  - [LDR Light Sensor](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/SENSORS/02%20POWAR-LDRwMAP)
  - [DHT Humidy and Temperature](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/SENSORS/03%20POWAR-DHT/POWAR-DHT)
  - [Plant Moisture Sensor](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/SENSORS/04%20POWAR-MOISTURE)
  - [Tank water Level](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/SENSORS/05%20POWAR-TANKLEVELwMAP/POWAR-TANKLEVELwMAP)


- Arduino Code that adds all sensors together and prints their values on Serial Port:
  - [Sensors Multiplexer](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/MULTIPLEXER%20FULL%20SENSORS%20READ/POWAR-MUX_UNIFIED_SENSORS_READ)


- Arduino Code for Lesson 1;
  - [Thirsty Plant](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/MULTIPLEXER%20FULL%20SENSORS%20READ/POWAR-MUX_UNIFIED_SENSORS_READ)


- Arduino Code for Lesson 2;
  - [Automatic Light](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/EXPERIMENTS_1-2/EXP02.3%20POWAR-LDR%2BDIM%2BLCD)


- Arduino Code for Lesson 3;
  - [Automatic Light](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/EXPERIMENTS_1-2/EXP02.3%20POWAR-LDR%2BDIM%2BLCD)



- Arduino Code that connects prev version through MQTT to a Node-RED server through a wifi connection.
  - [LDR+DHT+LED PUBLISH MQTT + WEBSERVER](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/NETWORKING/WIFI_MQTT_LDR_DHT-COMPLETE)



- Arduino Final Code with al sensors sending data to MQTT and subscription to weather API data;
  - [FULL CODE](https://github.com/Fablab-Benfica/POWARxFabschools/tree/main/ArduinoCode/NEW%20CODES/FINAL%20CODE/POWAR_FINAL_CODE_ESP8266)


## Schematics

#### Lesson 1 - Thirsty Plant:

Make a water pump to automatically water your plants when they are thirsty.

Connect a Capacitive Moisture Sensor and a water pump to your ESP and automatize the watering process.


![thristy plant connections](Schematics/EXPERIMENTS/EXP1-POWAR-MOIST-PUMP.png)

//



#### Lesson 2 - Automatic lights:

Make your LED lights react according to the light sensor.

Create a project in which lights will be activated when it is too dark, and it will also show in the LCD screen te percentage of luminosity in the room.

![LDR connection](Schematics/EXPERIMENTS/EXP2-POWAR-LDR-LIGHT-LCD.png)

//


#### Lesson 3 - Global weather vs global communication:

Connect to the internet and get weather information from elsewhere in your POWAR box.

![Go Full POWAR](Schematics/POWAR-FULL.png)


## Node-RED POWAR server guide

... write the instructions to configure your own node-red sensor
