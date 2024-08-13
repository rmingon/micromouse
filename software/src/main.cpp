#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(0); 

const int ir1 = PINC3;
const int ir2 = PINC2;
const int ir3 = PINC1;
const int ir4 = PINC0;
const int ir5 = PIN_A7;
const int ir6 = PIN_A6;

void setup() {
  Serial.begin(115200);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
  pinMode(ir6, INPUT);
  
  display.begin();
  display.clearDisplay(); 

}

void loop() {
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setTextSize(1); 
  
  display.setCursor(0, 50);
  display.println(analogRead(ir1));
  
  display.setCursor(0, 30);
  display.println(analogRead(ir2));
  
  display.setCursor(30, 10);
  display.println(analogRead(ir3));

  display.setCursor(80, 10);
  display.println(analogRead(ir4));
  
  display.setCursor(100, 30);
  display.println(analogRead(ir5));
  
  display.setCursor(100, 50);
  display.println(analogRead(ir6));

  display.display();

  delay(200);
  
}