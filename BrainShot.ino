
#include "FSM.h"

FSM *fsm = NULL;
volatile bool intr = false;

void intr_handler() {
    detachInterrupt(1);
    intr = true;
}

void setup() {
    Serial.begin(9600);
    fsm = new FSM();
    fsm->init();

    pinMode(3, INPUT_PULLUP);
    attachInterrupt(1, intr_handler, FALLING);
}

void loop() {
    if (intr) {
        intr = false;
        fsm->dispatch(0);
        attachInterrupt(1, intr_handler, FALLING);    
    }
}
