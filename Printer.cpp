#include "Logger.h"
#include "Printer.h"

Printer::Printer() {
    printerSerial = new SoftwareSerial(RX_PIN, TX_PIN);
    printer = new Adafruit_Thermal(printerSerial);
}

void Printer::enable() {
    Logger::log(F("printer enable"));
    printerSerial->begin(19200);
    printer->begin();
    printer->wake();
    printer->setDefault();
}

void Printer::disable() {
    Logger::log(F("printer disable"));
    printer->sleep();
    printerSerial->end();
}

void Printer::prnt() {
    Logger::log(F("printer print"));
    printer->feed(2);
    printer->underlineOn();
    printer->println(F("PRINTING STUFF\n"));
    printer->feed(2);
}
