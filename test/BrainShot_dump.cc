#include <cstdlib>
#include <algorithm>
#include <stdint.h>
#include <stdio.h>
#include <cmath>
#include <bmpfile.h>


#define MAP_WIDTH 384
#define MAP_HEIGHT 384
#define MAX 500000
#define WIDE 5

using namespace std;

class MapStream {
    public:
        MapStream() {
            mapData = NULL;
            count = 0;
        }

        void load(uint32_t* data) {
            mapData = data;
            for (uint8_t i=0; i<8; i++) {
                uint8_t r = data[i] * (MAP_WIDTH / 4) / MAX; // XXX max(data[i], MAX)

                // heads up:
                // to save RAM we store int8, we have to *2 the values when
                // using them later.
                p[i][0] = cos(i * M_PI_4) * r;
                p[i][1] = sin(i * M_PI_4) * r;
            }
        }

        uint8_t read() {
            if (!mapData) return -1;

            int16_t x = (MAP_WIDTH / -2) + ((count * 8) % MAP_WIDTH);
            int16_t y = (MAP_HEIGHT / 2) - ((count * 8) / MAP_WIDTH);

            uint8_t d = 0x00;

            for (uint8_t i=0; i<8; i++) {
                if (y < (min(p[(i+1) % 8][1], p[i][1])) * 2) continue;
                if (y > (max(p[(i+1) % 8][1], p[i][1])) * 2) continue;

                float m = (float)(p[(i+1) % 8][1] - p[i][1]) / (float)(p[(i+1) % 8][0] - p[i][0]);
                int16_t n = (p[i][1] - (p[i][0] * m)) * 2;

                //if (abs(m) > 1) {
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
                //}

                /*
                // y distance
                dist = floor((m * x + n) - y);
                if (abs(dist) < (WIDE + abs(m * 8))) {
                    if (m > 0) {
                    } else {
                        if (dist > (WIDE + m * 8)) {
                            d = (d | 0xff << (int)((WIDE-dist) * (-1 / m)));
                            continue;
                        }
                        if ((dist < 0) && (abs(dist) > WIDE)) {
                            d = (d | 0xff >> (int)((dist-WIDE) * (-1 / m)));
                            d = 0xff;
                            continue;
                        }
                    }
                }
                */
            }

            count++;
            return d;
        }

    private:
        uint32_t count;
        uint32_t *mapData;
        int8_t p[8][2];
        int16_t dist;
};

int main() {
    MapStream mapStream;
    uint32_t data[8] = {379573, 184756, 485474, 174864, 295485, 481746, 183742, 294726} ;
    mapStream.load(data);

    bmpfile_t* bmp = bmp_create(MAP_WIDTH, MAP_HEIGHT, 1);
    rgb_pixel_t pixel = {1, 1, 1, 0};


    for (int a = 0; a < MAP_HEIGHT; a++) {
        for (int b = 0; b < MAP_WIDTH; b+=8) {
            uint8_t px = mapStream.read();
            for (int k = 0; k < 8; k++) {
                if (((px << k) & 0x80) == 0x80) {
                    bmp_set_pixel(bmp, b+k, a, pixel);
                }
            }
        }
    }
    bmp_save(bmp, "dump.bmp");
}
