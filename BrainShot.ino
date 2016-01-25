#include "FSM.h"

#define WAIT 20

FSM *fsm = NULL;
volatile bool intr = false;

void disable_intr() {
    detachInterrupt(1);
}

void intr_handler() {
    disable_intr();
    Serial.println(F("INTR"));
    intr = true;
}

void enable_intr() {
    EIFR = (1 << INTF1); // clear interrupts
    attachInterrupt(1, intr_handler, FALLING);
}

void setup() {
    Serial.begin(9600);
    fsm = new FSM();
    fsm->init();

    pinMode(3, INPUT_PULLUP);
    enable_intr();
}

void loop() {
    if (intr) {
        intr = false;
        fsm->dispatch(0);
        enable_intr();
    }
    delay(100);
}
