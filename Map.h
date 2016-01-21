#ifndef MAP_H
#define MAP_H

#include <Brain.h>

class Map {
    public:
        Map();
        void load(uint32_t*);
    private:
        uint32_t *mapData;
};

#endif // MAP_H
