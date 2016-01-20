#include <Arduino.h>
#include "FSM.h"

FSM *fsm = NULL;

void intr() {
    fsm->dispatch(0);
}

void setup() {
    Serial.begin(9600);
    fsm = new FSM();
    pinMode(3, INPUT_PULLUP);
    attachInterrupt(1, intr, FALLING);
}

void loop() {
}
