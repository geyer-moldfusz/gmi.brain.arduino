#include <Arduino.h>

#include "FSM.h"
#include "Logger.h"

FSM::FSM() : myState(&FSM::idle) {
    Logger::setup();
    mapStream = new MapStream();
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

void FSM::idle(unsigned int) {
    Logger::idle();
    TRAN(&FSM::reading);
}

void FSM::reading(unsigned int) {
    Logger::read();
    neuro->enable();
    mapStream->load(neuro->read());
    neuro->disable();
    TRAN(&FSM::printing);
    dispatch(0);
}

void FSM::printing(unsigned int) {
    printer->enable();
    printer->prnt(MAP_WIDTH, MAP_HEIGHT, mapStream);
    printer->disable();
    TRAN(&FSM::idle);
    dispatch(0);
}
