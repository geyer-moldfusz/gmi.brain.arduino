#include <Arduino.h>
#include "FSM.h"
#include "Logger.h"

FSM::FSM() : myState(&FSM::initial) {
    Logger::setup();
    map = new Map();
    neuro = new Neuro();
    printer = new Printer();
}

void FSM::init() {
    dispatch(0);
}

void FSM::dispatch(unsigned const sig) {
    (this->*myState)(sig);
}

void FSM::tran(FSM::State target) {
    myState = target;
}

void FSM::initial(unsigned int) {
    TRAN(&FSM::idle);
    dispatch(0);
}

void FSM::idle(unsigned int) {
    Logger::idle();
    TRAN(&FSM::reading);
}

void FSM::reading(unsigned int) {
    Logger::read();
    neuro->enable();
    map->load(neuro->read());
    neuro->disable();
    TRAN(&FSM::processing);
    dispatch(0);
}

void FSM::processing(unsigned int) {
    Logger::process();
    TRAN(&FSM::printing);
    delay(5000);
    dispatch(0);
}

void FSM::printing(unsigned int) {
    printer->enable();
    delay(500);
    printer->prnt();
    delay(500);
    printer->disable();
    delay(500);
    TRAN(&FSM::idle);
    dispatch(0);
}
