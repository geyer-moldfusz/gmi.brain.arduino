#include <Arduino.h>
#include "MapStream.h"

MapStream::MapStream() {
    mapData = NULL;
    flush();
}

void MapStream::load(uint32_t* data) {
    mapData = data;
}

int MapStream::read() {
    if (!mapData) return -1;

    int16_t x = (MAP_WIDTH / -2) + ((count * 8) % MAP_WIDTH);
    int16_t y = (MAP_HEIGHT / 2) - ((count * 8) / MAP_WIDTH);

    uint8_t d = 0x00;

    float n = mapData[2] * (MAP_HEIGHT / 2) / MAX_Y;
    float m = n / (((float)mapData[0] / MAX_X) * (MAP_WIDTH / -2));

    int16_t dist = floor(((y - n) / m) - x);
    if ((dist >= 0) && (dist < 8)) {
        d = ((d | 0xe0) >> dist);
        Serial.println(n);
        Serial.println(m);
        Serial.print(dist);
        Serial.print(F(":"));
        Serial.print(x);
        Serial.print(F(":"));
        Serial.print(y);
        Serial.print(F(":  "));
        Serial.println(d, BIN);
    }

    if ((x == 0) && ((y % 10) == 0)) d = 0xff;

    count++;
    return d;
}

size_t MapStream::write(uint8_t) {
    setWriteError();
    return 0;
}

int MapStream::available() {
    if (!mapData) return 0;
    return sizeof(uint8_t);
}

int MapStream::peek() {
    // XXX
    return read();
}

void MapStream::flush() {
    count = 0;
}
