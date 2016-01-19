#ifndef BRAIN_H
#define BRAIN_H

#include <gmock/gmock.h>
#include <arduino-mock/Serial.h>

/*
class BrainMock {
    public:
        MOCK_METHOD1(brain, q
  
        */

class Brain {
    public:
        Brain(Serial_);
        bool update();
        char* readCSV();
};


#endif // BRAIN_H
