#ifndef MAPSTREAM_H
#define MAPSTREAM_H

#define MAP_WIDTH 384
#define MAP_HEIGHT 384

#define MAX_X 500000
#define MAX_Y 500000

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
        int count;
        uint32_t *mapData;
};

#endif // MAPSTREAM_H
