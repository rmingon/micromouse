#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

Adafruit_SH1106 display(0); 

const int pulsePin = A3; // Input signal connected to Pin 12 of Arduino

int pulseHigh; // Integer variable to capture High time of the incoming pulse

int pulseLow; // Integer variable to capture Low time of the incoming pulse

float pulseTotal; // Float variable to capture Total time of the incoming pulse

float frequency; // Calculated Frequency

void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 38004.750593824225 Hz (16000000/((420+1)*1))
  OCR1A = 420;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 1
  TCCR1B |= (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  Serial.begin(115200);

  pinMode(pulsePin, INPUT);
  pinMode(2, OUTPUT);

  digitalWrite(2, LOW);
  display.begin();  // initialisation de l'afficheur
  display.clearDisplay();   // ça efface à la fois le buffer et l'écran

  setupTimer1();
}

void loop() {
  display.clearDisplay();   // ça efface à la fois le buffer et l'écran

pulseHigh = pulseIn(pulsePin, HIGH);

pulseLow = pulseIn(pulsePin, LOW);

pulseTotal = pulseHigh + pulseLow; // Time period of the pulse in microseconds

frequency = 1000000 / pulseTotal; // Frequency in Hertz (Hz)
    
      display.setCursor(30, 15);  // coordonnées du point de départ du texte
      display.setTextColor(WHITE);
      display.setTextSize(1);  // taille par défaut
      display.println(analogRead(pulsePin));

      display.display();  // affichage à l'écran
  
}


ISR(TIMER1_COMPA_vect) {
  PORTD ^= (1 << PD2);
}