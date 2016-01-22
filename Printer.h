#ifndef PRINTER_H
#define PRINTER_H

#define RX_PIN 5
#define TX_PIN 6

#include <Stream.h>
#include <Adafruit_Thermal.h>
#include <SoftwareSerial.h>

class Printer {
    public:
        Printer();
        void enable();
        void disable();
        void prnt(int, int, Stream*);

    private:
        Adafruit_Thermal *printer;
        SoftwareSerial *printerSerial;
};

#endif // PRINTER_H
