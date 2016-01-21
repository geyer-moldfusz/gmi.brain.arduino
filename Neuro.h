#ifndef NEURO_H
#define NEURO_H

#define NR_RX_PIN 7
#define NR_TX_PIN 8

#include <Brain.h>

class Neuro {
    public:
        Neuro();
        void enable();
        void disable();
        uint32_t* read();

    private:
        Brain *neuro;
};

#endif // NEURO_H
