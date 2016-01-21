#include <Arduino.h>
#include "Logger.h"

void Logger::setup() {
    pinMode(13, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
}

void Logger::log(const __FlashStringHelper *msg) {
    Serial.println(msg);
}

void Logger::idle() {
    Serial.println(F("idle"));
    digitalWrite(13, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
}

void Logger::read() {
    Serial.println(F("read"));
    digitalWrite(13, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
}

void Logger::process() {
    Serial.println(F("process"));
    digitalWrite(13, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
}

void Logger::print() {
    Serial.println(F("print"));
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
}

void Logger::error() {
    Serial.println(F("error"));
    digitalWrite(13, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
}
