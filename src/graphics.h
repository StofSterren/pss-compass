#ifndef GFX_H
#define GFX_H

#include <stdint.h>
#include <stdlib.h>

struct canvas {
    size_t x;
    size_t y;
    uint8_t* values;
};

int canvas_new(struct canvas**);
int canvas_end(struct canvas*);

int pnm_type(size_t length, uint8_t *bytes);

int pbm_read(size_t length, uint8_t* bytes, struct canvas*);
int pgm_read(size_t length, uint8_t* bytes, struct canvas*);
int ppm_read(size_t length, uint8_t* bytes, struct canvas*);
#endif
