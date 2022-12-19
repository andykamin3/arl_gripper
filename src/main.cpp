/*
  * main.cpp
  * Stepper motor control over Serial monitor
  * Created on: 19-12-2022
  * Author: @kaminker
*/
#include <Arduino.h>
#include <Stepper.h>
#define BAUD_RATE 9600
#define LED_PIN 13

// Stepper motor settings
#define STEPS 200

// States
#define IDLE 0 
#define OPENING 1
#define CLOSING 2
#define TIMEOUT 3

// Serial commands
#define OPEN 'o'
#define CLOSE 'c'

int8_t state = IDLE;
Stepper myStepper(STEPS, 8, 9, 10, 11);



void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Initialized");
  myStepper.setSpeed(60);
}

void loop() {
  switch (state)
  {
  case IDLE:
    if (Serial.available() > 0) {
      char command = Serial.read();
      if (command == OPEN) {
        state = OPENING;
      } else if (command == CLOSE) {
        state = CLOSING;
      }
    }
    break;
  case OPENING:
    digitalWrite(LED_PIN, HIGH);
    myStepper.step(STEPS);
    digitalWrite(LED_PIN, LOW);
    state = IDLE;
    break;
  case CLOSING:
    digitalWrite(LED_PIN, HIGH);
    myStepper.step(-STEPS);
    digitalWrite(LED_PIN, LOW);
    state = IDLE;
    break;
  case TIMEOUT:
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
    break;
  default:
    break;
  }
}

// TODO: Remove blocking instructions & use AccelStepper library
