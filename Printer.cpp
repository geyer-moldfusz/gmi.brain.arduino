#include "Printer.h"
#include "Logger.h"

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

void Printer::prnt(int width, int height, Stream* data) {
    Logger::log(F("printer print"));
    printer->feed(2);
    printer->justify('C');
    printer->println(F("---START---"));
    printer->justify('L');
    printer->printBitmap(width, height, data);
    printer->justify('C');
    printer->println(F("---END---"));
    printer->feed(2);
}
