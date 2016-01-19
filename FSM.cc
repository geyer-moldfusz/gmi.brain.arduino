#include <iostream>
#include "FSM.h"

FSM::FSM() : myState(&FSM::initial) {}

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
    std::cout << "initial called";
    TRAN(&FSM::idle);
}

void FSM::idle(unsigned int) {
    std::cout << "idle called";
}
