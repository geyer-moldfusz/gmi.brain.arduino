#ifndef MAP_H
#define MAP_H

#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT / 8)

#include "MapStream.h"

class Map {
    public:
        void load(uint32_t*);
        Stream*  process();
    private:
        MapStream mapStream;
};

#endif // MAP_H
