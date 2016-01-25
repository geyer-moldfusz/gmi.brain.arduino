#include <Arduino.h>
#include "MapStream.h"

MapStream::MapStream() {
    mapData = NULL;
    flush();
}

void MapStream::load(uint32_t* data) {
    mapData = data;
    for (uint8_t i=0; i<8; i++) {
        uint8_t r = map(
            constrain(data[i], 0, MAX), 0, MAX, 0, MAP_WIDTH / 4);

        // heads up:
        // to save RAM we store int8, we have to *2 the values when
        // using them later.
        p[i][0] = cos(i * M_PI_4) * r;
        p[i][1] = sin(i * M_PI_4) * r;
        Serial.print(p[i][0]);
        Serial.print(F(":"));
        Serial.println(p[i][1]);

    }
}

int MapStream::read() {
    if (!mapData) return -1;

    x = (MAP_WIDTH / -2) + ((count * 8) % MAP_WIDTH);
    y = (MAP_HEIGHT / 2) - ((count * 8) / MAP_WIDTH);

    d = 0x00;

    for (uint8_t i=0; i<8; i++) {
        if (y < (min(p[(i+1) % 8][1], p[i][1])) * 2) continue;
        if (y > (max(p[(i+1) % 8][1], p[i][1])) * 2) continue;

        m = (float)(p[(i+1) % 8][1] - p[i][1]) / (float)(p[(i+1) % 8][0] - p[i][0]);
        n = (p[i][1] - (p[i][0] * m)) * 2;

        // x distance
        dist = floor(((y - n) / m) - x);
        if ((dist >= 0) && (dist < (8 + WIDE))) {
            if (dist > WIDE) {
                d = (d | ((0x01 << (8 + WIDE - dist)) - 1));
                continue;
            }
            if ((8 - dist) < WIDE) {
                d = 0xff;
                break;
            }
        }
        if (abs(dist) <= WIDE) {
            d = (d | (0xff << (8 - (WIDE + dist))));
        }
        continue;
    }

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
