#include "FSM.h"
#include "Logger.h"

FSM::FSM() : myState(&FSM::initial) {
    Logger::setup();
}

void FSM::init() {
    dispatch(0);
}

void FSM::dispatch(unsigned const sig) {
    (this ->*myState)(sig);
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
    TRAN(&FSM::processing);
}

void FSM::processing(unsigned int) {
    Logger::process();
    TRAN(&FSM::printing);
}

void FSM::printing(unsigned int) {
    Logger::print();
    TRAN(&FSM::idle);
}
