#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "error.h"
#include "graphics.h"

/* Allocate a new canvas. */
int canvas_new(struct canvas** canvas) {
    assert(canvas != NULL);

   * canvas = malloc(sizeof(struct canvas));

    if(*canvas == NULL) {
        return E_MALLOC_FAILED;
    }

    memset(*canvas, '\0', sizeof(struct canvas));

    return OK;
}

/* Free a canvas. */
int canvas_end(struct canvas* canvas) {
    assert(canvas != NULL);

    if(canvas->values != NULL) {
        free(canvas->values);
    }

    free(canvas);

    return OK;
}

/* Read a Portable Anymap Format header, the PNM formats include PBM, PGM,
 * and PPM. */
int pnm_type(size_t length, uint8_t* bytes) {
    if(length < 2) {
        return E_NOT_PNM;
    }

    if(bytes[0] != 'P') {
        return E_NOT_PNM;
    }

    if(bytes[1] != '4' && bytes[1] != '5' && bytes[1] != '6') {
        return E_NOT_PNM_SUPPORTED;
    }

    return 0;
}

int pnm_size(size_t length, uint8_t* bytes, struct canvas* canvas) {
    int err;

    if((err = pnm_type(length, bytes))) {
        return err;
    }

    return OK;
}

/* Read a PBM file into a canvas. */
int pbm_read(size_t length, uint8_t* bytes, struct canvas* canvas) {
    assert(bytes != NULL);
    assert(canvas != NULL);
    return OK;
}

/* Read a PGM file into a canvas. */
int pgm_read(size_t length, uint8_t* bytes, struct canvas* canvas) {
    assert(bytes != NULL);
    assert(canvas != NULL);

    return OK;
}

/* Read a PPM file into a canvas. */
int ppm_read(size_t length, uint8_t* bytes, struct canvas* canvas) {
    assert(bytes != NULL);
    assert(canvas != NULL);

    return OK;
}
