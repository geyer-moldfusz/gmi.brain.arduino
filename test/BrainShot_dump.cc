#include <stdint.h>
#include <cstdlib>
#include <cmath>
#include <bmpfile.h>


#define MAP_WIDTH 384
#define MAP_HEIGHT 384
#define MAX_X 500000
#define MAX_Y 500000

class MapStream {
    public:
        MapStream() {
            mapData = NULL;
            count = 0;
        }

        void load(uint32_t* data) {
            mapData = data;
        }

        uint8_t read() {
            if (!mapData) return -1;

            int16_t x = (MAP_WIDTH / -2) + ((count * 8) % MAP_WIDTH);
            int16_t y = (MAP_HEIGHT / 2) - ((count * 8) / MAP_WIDTH);

            uint8_t d = 0x00;

            float n = mapData[2] * (MAP_HEIGHT / 2) / MAX_Y;
            float m = n / (((float)mapData[0] / MAX_X) * (MAP_WIDTH / -2));

            int16_t dist = floor(((y - n) / m) - x);
            if ((dist >= 0) && (dist < 8)) {
                d = ((d | 0x80) >> dist);
            }

            if ((x == 0) && ((y % 10) == 0)) d = 0xff;

            count++;
            return d;
        }

    private:
        int count;
        uint32_t *mapData;
};

int main( int argc, const char* argv[] ) {
    MapStream mapStream;
    uint32_t data[8] = {279573, 184756, 285474, 274864, 295485, 381746, 183742, 294726} ;
    mapStream.load(data);

    bmpfile_t* bmp = bmp_create(MAP_WIDTH, MAP_HEIGHT, 1);
    rgb_pixel_t pixel = {1, 1, 1, 0};


    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j+=8) {
            uint8_t px = mapStream.read();
            for (int k = 0; k < 8; k++) {
                if (((px << k) & 0x80) == 0x80) {
                    bmp_set_pixel(bmp, j+k, i, pixel);
                }
            }
        }
    }
    bmp_save(bmp, "dump.bmp");
}
