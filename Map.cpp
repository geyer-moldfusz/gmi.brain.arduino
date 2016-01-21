#include "Map.h"
#include "Logger.h"

Map::Map() {
    mapData = NULL;
}

void Map::load(uint32_t* data) {
    Logger::log(F("load map data"));
    mapData = data;
    for (int i=0; i<EEG_POWER_BANDS; i++) {
        Serial.println(*(mapData+i));
    }
}

