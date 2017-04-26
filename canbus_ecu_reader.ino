/* CAN Bus ECU Reader
 * www.skpang.co.uk
 * V1.0 Jan 2017
 *   
 * Uses Teensy CAN-Bus breakout board:
 * http://skpang.co.uk/catalog/teensy-canbus-breakout-board-include-teensy-32-p-1507.html
 * 
 * and 128x64 OLED display:
 * http://skpang.co.uk/catalog/oled-128x64-display-for-teensy-breakout-board-p-1508.html
 * 
 * Also requres new FlexCAN libarary
 * https://github.com/collin80/FlexCAN_Library
 * 
 * 
 */
#include "ecu_reader.h"
#include <FlexCAN.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#define OLED_DC     6
#define OLED_CS     10
#define OLED_RESET  5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

ecu_t old_ecu;

void setup() {
 
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(0);
  display.setTextColor(WHITE);
  display.setCursor(0,15);
  display.println(" Teensy ECU Reader");
  display.println(" ");
  display.println(" skpang.co.uk");
  display.println(" ");
  display.println(" 01/17");
  display.display();
  ecu_reader.init(500000);
  delay(1000);
  Serial.println(F("ECU Reader v1.0 SK Pang 12/16"));
  display.clearDisplay();
  
  display.setCursor(0,55);
  display.println("      kph         rpm");  
  display.display(); 
  old_ecu.engine_rpm = -1;
  old_ecu.coolant_temp = 0;
  old_ecu.vehicle_speed = -1;
  old_ecu.throttle_position = -1;
}

void loop() {

  int engine_data;

  if(ecu_reader.request(ENGINE_RPM,&engine_data) == 1)   // Get engine rpm and display on LCD
  {
          if(engine_data != old_ecu.engine_rpm)
          {
              display.setFont(&FreeSansBold12pt7b);
              Serial.println(engine_data);
              display.fillRect(70,30,55,22,BLACK);
              if(engine_data < 10)                // Make it right justified
              {
                  display.setCursor(111,50);
              }else if(engine_data < 100)
              {
                
                display.setCursor(98,50);
              }else if(engine_data < 1000)
              {
                 display.setCursor(83,50);
                
              }else display.setCursor(70,50);
                
              display.println(engine_data);
              display.display();
              old_ecu.engine_rpm = engine_data;
              
          }
  }   
  delay(10);   
  
  if(ecu_reader.request(ENGINE_COOLANT_TEMP,&engine_data) == 1)
  {
     if(engine_data != old_ecu.coolant_temp)
     {
        Serial.println(engine_data);;
        display.setFont();
        display.fillRect(0,0,40,10,BLACK);
        display.setCursor(0,0);
        display.print(engine_data);
        display.print((char) 247);  // display degress symbol
        display.print("C ");
        display.display();
        old_ecu.coolant_temp = engine_data;
     }
  }
  delay(10);    
  
  if(ecu_reader.request(VEHICLE_SPEED,&engine_data) == 1)
  {
    if(engine_data != old_ecu.vehicle_speed)
     {  
        display.setFont(&FreeSansBold12pt7b);
        Serial.println(engine_data);;
        display.fillRect(13,30,55,22,BLACK);
        if(engine_data < 10)                // Make it right justified
        {
              display.setCursor(40,50);
        }else if(engine_data < 100)
        {
              display.setCursor(28,50);
                
        }else display.setCursor(13,50);
                
        display.println(engine_data);
        display.display();
        old_ecu.vehicle_speed = engine_data;
     }
  }
  delay(10);
  
  if(ecu_reader.request(THROTTLE,&engine_data) ==1 )
  {
      if(engine_data != old_ecu.throttle_position)
     {  
        Serial.println(engine_data);   
        display.setFont();
        display.fillRect(100,0,20,10,BLACK);
        display.setCursor(100,0);
        display.print(engine_data);
        display.display();
        
        old_ecu.throttle_position = engine_data;
     } 
  }   
  delay(10);
  
}
