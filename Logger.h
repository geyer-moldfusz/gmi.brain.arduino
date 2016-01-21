#ifndef LOGGER_H
#define LOGGER_H

#include <WString.h>

class Logger {
     public:
        static void setup();
        static void log(const __FlashStringHelper *);

        static void idle();
        static void read();
        static void process();
        static void print();
        static void error();
};

#endif // LOGGER_H
