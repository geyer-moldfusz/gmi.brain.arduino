#ifndef MAPSTREAM_H
#define MAPSTREAM_H

#define MAP_WIDTH 384
#define MAP_HEIGHT 384
#define WIDE 5

#define MAX 650000

#include <Stream.h>

class MapStream : public Stream {
    public:
        MapStream();
        void load(uint32_t*);
        virtual int read();
        virtual size_t write(uint8_t);
        virtual int available();
        virtual int peek();
        virtual void flush();
    private:
        uint32_t count;
        uint32_t *mapData;
        int8_t p[8][2];
        uint8_t d;
        int16_t x;
        int16_t y;
        float m;
        int16_t n;
        int16_t dist;
};

#endif // MAPSTREAM_H
