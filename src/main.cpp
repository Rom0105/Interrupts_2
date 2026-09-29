#include <Arduino.h>
#define BUTTON_PIN 4

volatile bool interruptFlag = false;
volatile unsigned long lastInterruptTime = 0;
volatile unsigned long counter = 0;

void IRAM_ATTR handLeInterrupt() {
  interruptFlag = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handLeInterrupt, FALLING);
  Serial.println("Ready. Press the button!");
  
}

void loop() {
  if (interruptFlag) {
    interruptFlag = false;

    unsigned long currentTime = millis();
    if(currentTime - lastInterruptTime > 50) {
      counter++;
      Serial.print("Interrupt count: ");
      Serial.println(counter);
      lastInterruptTime = currentTime;
    }
  }
}

