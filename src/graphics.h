#ifndef GFX_H
#define GFX_H

#include <stdint.h>
#include <stdlib.h>

struct pnm {
    size_t length;
    size_t position;
    uint8_t *bytes;
};

typedef struct pnm PNM;

struct canvas {
    size_t x;
    size_t y;
    uint8_t* values;
};

typedef struct canvas Canvas;

int canvas_new(struct canvas**);
int canvas_end(struct canvas*);

int pnm_new(struct pnm**);
int pnm_end(struct pnm*);

int pnm_read_byte(struct pnm*, uint8_t*);
int pnm_ascii_read_character(struct pnm*, uint8_t*);
int pnm_ascii_read_number(struct pnm*, uint16_t*);

int pnm_type(size_t length, uint8_t *bytes);
int pnm_size(size_t length, uint8_t *bytes, struct canvas*);

int pbm_read(size_t length, uint8_t* bytes, struct canvas*);
int pgm_read(size_t length, uint8_t* bytes, struct canvas*);
int ppm_read(size_t length, uint8_t* bytes, struct canvas*);
#endif
