#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "error.h"
#include "graphics.h"

/* Allocate a new canvas. */
int canvas_new(Canvas** canvas) {
    assert(canvas != NULL);

   * canvas = malloc(sizeof(Canvas));

    if(*canvas == NULL) {
        return E_MALLOC_FAILED;
    }

    memset(*canvas, '\0', sizeof(Canvas));

    return OK;
}

/* Free a canvas. */
int canvas_end(Canvas* canvas) {
    assert(canvas != NULL);

    if(canvas->values != NULL) {
        free(canvas->values);
    }

    free(canvas);

    return OK;
}

/* Allocate a new pnm. */
int pnm_new(PNM** pnm) {
    assert(pnm != NULL);

    *pnm = malloc(sizeof(PNM));

    if(*pnm == NULL) {
        return E_MALLOC_FAILED;
    }

    memset(*pnm, '\0', sizeof(PNM));

    return OK;
}

/* Free a pnm. */
int pnm_end(PNM* pnm) {
    assert(pnm != NULL);

    if(pnm->bytes != NULL) {
        free(pnm->bytes);
    }

    free(pnm);

    return OK;
}

int pnm_parse(PNM* pnm, size_t size, uint8_t* bytes) {
    pnm->bytes = malloc(size);

    if(pnm->bytes == NULL) {
        return E_MALLOC_FAILED;
    }

    memcpy(pnm->bytes, bytes, size);

    char type[16] = { 0 };
    pnm_ascii_read_line(pnm, sizeof(type), (uint8_t*) type);

    if(strncmp(type, "P1", sizeof(type)) == 0) {
        pnm->type = PNM_TYPE_1;
    } else if(strncmp(type, "P2", sizeof(type)) == 0) {
        pnm->type = PNM_TYPE_2;
    } else if(strncmp(type, "P3", sizeof(type)) == 0) {
        pnm->type = PNM_TYPE_3;
    } else if(strncmp(type, "P4", sizeof(type)) == 0) {
        pnm->type = PNM_TYPE_4;
    } else if(strncmp(type, "P5", sizeof(type)) == 0) {
        pnm->type = PNM_TYPE_5;
    } else if(strncmp(type, "P6", sizeof(type)) == 0) {
        pnm->type = PNM_TYPE_6;
    } else {
        return E_NOT_PNM;
    }

    uint16_t x;
    pnm_ascii_read_number(pnm, &x);

    uint16_t y;
    pnm_ascii_read_number(pnm, &y);

    return OK;
}

int pnm_read_byte(PNM* pnm, uint8_t* byte) {
    if(pnm->position == pnm->length) {
        return E_END;
    }

    *byte = pnm->bytes[pnm->position++];

    return 0;
}

int pnm_ascii_read_character(PNM* pnm, uint8_t* byte) {
    // XXX check value!
    return pnm_read_byte(pnm, byte);
}

int pnm_ascii_skip_whitespace(PNM* pnm) {
    uint8_t byte;
 
    while(!pnm_ascii_read_character(pnm, &byte)) {
        if(byte != ' ' && byte != '\t' && byte != '\n' && byte != '\r') {
            break;
        }
    }

    return 0;
}

int pnm_ascii_read_number(PNM* pnm, uint16_t* number) {
    uint8_t byte;
    int result = 0;

    *number = 0;

    while(!(result = pnm_ascii_read_character(pnm, &byte))) {
        if(byte < '0' || byte > '9') {
            break;
        }

        if(*number > UINT16_MAX * 10) {
            return E_BOUNDS;
        }

        *number *= 10;

        if(*number > UINT16_MAX - byte) {
            return E_BOUNDS;
        }

        *number += byte - '0';
    }

    return result;
}

int pnm_ascii_read_line(PNM* pnm, size_t length, uint8_t* line) {
    return 0;
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

int pnm_size(size_t length, uint8_t* bytes, Canvas* canvas) {
    int err;

    if((err = pnm_type(length, bytes))) {
        return err;
    }

    return OK;
}

/* Read a PBM file into a canvas. */
int pbm_read(size_t length, uint8_t* bytes, Canvas* canvas) {
    assert(bytes != NULL);
    assert(canvas != NULL);
    return OK;
}

/* Read a PGM file into a canvas. */
int pgm_read(size_t length, uint8_t* bytes, Canvas* canvas) {
    assert(bytes != NULL);
    assert(canvas != NULL);

    return OK;
}

/* Read a PPM file into a canvas. */
int ppm_read(size_t length, uint8_t* bytes, Canvas* canvas) {
    assert(bytes != NULL);
    assert(canvas != NULL);

    return OK;
}
