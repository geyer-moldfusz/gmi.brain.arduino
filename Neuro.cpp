#include "Logger.h"
#include "Neuro.h"

Neuro::Neuro() {
    neuro = new Brain(Serial);
}

void Neuro::enable() {
    Logger::log(F("neuro enable"));
}

void Neuro::disable() {
    Logger::log(F("neuro disable"));
}

uint32_t* Neuro::read() {
    Logger::log(F("neuro read"));
    for (int i=2; i>0; i--) {
        while (!neuro->update()) {}
    }
    Serial.println(neuro->readCSV());
    return neuro->readPowerArray();
}
