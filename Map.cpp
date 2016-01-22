#include <Brain.h>

#include "Map.h"
#include "Logger.h"

void Map::load(uint32_t* data) {
    Logger::log(F("load map data"));
    mapStream.flush();
    mapStream.load(data);
    for (int i=0; i<EEG_POWER_BANDS; i++) {
        Serial.println(*(data+i));
    }
}

Stream* Map::process() {
    return &mapStream;
}
