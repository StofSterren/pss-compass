#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "error.h"
#include "graphics.h"

int canvas_new(struct canvas** canvas) {
    assert(canvas != NULL);

    *canvas = malloc(sizeof(struct canvas));

    if(*canvas == NULL) {
        return E_MALLOC_FAILED;
    }

    memset(*canvas, '\0', sizeof(struct canvas));

    return OK;
}

int canvas_end(struct canvas* canvas) {
    assert(canvas != NULL);

    if(canvas->values != NULL) {
        free(canvas->values);
    }

    free(canvas);

    return OK;
}

int pbm_read(size_t length, uint8_t *bytes, struct canvas *canvas) {
    assert(bytes != NULL);
    assert(canvas != NULL);

    return OK;
}

int pgm_read(size_t length, uint8_t *bytes, struct canvas *canvas) {
    assert(bytes != NULL);
    assert(canvas != NULL);

    return OK;
}

int ppm_read(size_t length, uint8_t *bytes, struct canvas *canvas) {
    assert(bytes != NULL);
    assert(canvas != NULL);

    return OK;
}
