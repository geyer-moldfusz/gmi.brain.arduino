#ifndef LOGGER_H
#define LOGGER_H

class Logger {
     public:
        static void setup();
        static void idle();
        static void read();
        static void process();
        static void print();
        static void error();
};

#endif // LOGGER_H
