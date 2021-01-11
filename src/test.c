#include "minunit.h"

#include "error.h"
#include "graphics.h"

MU_TEST(test_main) {
    mu_assert_int_eq(1, 1);
}

MU_TEST_SUITE(test_command) {
    MU_RUN_TEST(test_main); 
}

MU_TEST(test_canvas_new) {
    struct canvas *canvas;

    mu_assert_int_eq(canvas_new(&canvas), OK);
}

MU_TEST(test_canvas_end) {
    struct canvas *canvas;

    mu_assert_int_eq(canvas_new(&canvas), OK);
    mu_assert_int_eq(canvas_end(canvas), OK);
}

MU_TEST(test_pnm_new) {
    struct pnm *pnm;

    mu_assert_int_eq(pnm_new(&pnm), OK);
}

MU_TEST(test_pnm_end) {
    struct pnm *pnm;

    mu_assert_int_eq(pnm_new(&pnm), OK);
    mu_assert_int_eq(pnm_end(pnm), OK);
}

MU_TEST(test_pnm_read_byte) {
    struct pnm *pnm;
    uint8_t byte;
    uint8_t buffer[] = { 'A', 'B', 'C' };

    mu_assert_int_eq(pnm_new(&pnm), OK);

    // XXX make this better
    pnm->length = 3;
    pnm->bytes = malloc(3);
    memcpy(pnm->bytes, buffer, 3);

    mu_assert_int_eq(pnm_read_byte(pnm, &byte), OK);
    mu_assert_int_eq(byte, 'A');

    mu_assert_int_eq(pnm_read_byte(pnm, &byte), OK);
    mu_assert_int_eq(byte, 'B');

    mu_assert_int_eq(pnm_read_byte(pnm, &byte), OK);
    mu_assert_int_eq(byte, 'C');

    mu_assert_int_eq(pnm_read_byte(pnm, &byte), E_END);
    mu_assert_int_eq(pnm_end(pnm), OK);
}

MU_TEST(test_pnm_ascii_read_number) {
    struct pnm *pnm;
    uint16_t number;
    uint8_t buffer[] = { '1', '2', '3', ' ', '4', '2'};

    mu_assert_int_eq(pnm_new(&pnm), OK);

    // XXX make this better
    pnm->length = 6;
    pnm->bytes = malloc(6);
    memcpy(pnm->bytes, buffer, 6);

    mu_assert_int_eq(pnm_ascii_read_number(pnm, &number), OK);
    mu_assert_int_eq(number, 123);

    mu_assert_int_eq(pnm_ascii_read_number(pnm, &number), E_END);
    mu_assert_int_eq(number, 42);

    // TODO should number be reset to 0 in this case?
    mu_assert_int_eq(pnm_ascii_read_number(pnm, &number), E_END);
    mu_assert_int_eq(number, 0);

    mu_assert_int_eq(pnm_end(pnm), OK);
}

MU_TEST(test_pnm_type) {
    char *bytes = "foo";

    mu_assert_int_eq(pnm_type(0, (uint8_t*) bytes), E_NOT_PNM);
    mu_assert_int_eq(pnm_type(1, (uint8_t*) bytes), E_NOT_PNM);
    mu_assert_int_eq(pnm_type(2, (uint8_t*) bytes), E_NOT_PNM);
    mu_assert_int_eq(pnm_type(3, (uint8_t*) bytes), E_NOT_PNM);

    bytes = "P1";
    mu_assert_int_eq(pnm_type(2, (uint8_t*) bytes), E_NOT_PNM_SUPPORTED);

    bytes = "P2";
    mu_assert_int_eq(pnm_type(2, (uint8_t*) bytes), E_NOT_PNM_SUPPORTED);

    bytes = "P3";
    mu_assert_int_eq(pnm_type(2, (uint8_t*) bytes), E_NOT_PNM_SUPPORTED);

    bytes = "P4";
    mu_assert_int_eq(pnm_type(2, (uint8_t*) bytes), OK);

    bytes = "P5";
    mu_assert_int_eq(pnm_type(2, (uint8_t*) bytes), OK);

    bytes = "P6";
    mu_assert_int_eq(pnm_type(2, (uint8_t*) bytes), OK);
}

MU_TEST(test_pnm_size) {
    char *bytes = "foo";
    struct canvas canvas;

    mu_assert_int_eq(pnm_size(0, (uint8_t*) bytes, &canvas), E_NOT_PNM);
    mu_assert_int_eq(pnm_size(1, (uint8_t*) bytes, &canvas), E_NOT_PNM);
    mu_assert_int_eq(pnm_size(2, (uint8_t*) bytes, &canvas), E_NOT_PNM);
    mu_assert_int_eq(pnm_size(3, (uint8_t*) bytes, &canvas), E_NOT_PNM);

    bytes = "P1";
    mu_assert_int_eq(pnm_size(2, (uint8_t*) bytes, &canvas), E_NOT_PNM_SUPPORTED);

    bytes = "P2";
    mu_assert_int_eq(pnm_size(2, (uint8_t*) bytes, &canvas), E_NOT_PNM_SUPPORTED);

    bytes = "P3";
    mu_assert_int_eq(pnm_size(2, (uint8_t*) bytes, &canvas), E_NOT_PNM_SUPPORTED);

    bytes = "P4";
    mu_assert_int_eq(pnm_size(2, (uint8_t*) bytes, &canvas), OK);

    bytes = "P5";
    mu_assert_int_eq(pnm_size(2, (uint8_t*) bytes, &canvas), OK);

    bytes = "P6";
    mu_assert_int_eq(pnm_size(2, (uint8_t*) bytes, &canvas), OK);
}

MU_TEST(test_pbm_read) {
    struct canvas canvas;
    char *bytes = "foo";

    mu_assert_int_eq(pbm_read(0, (uint8_t*) bytes, &canvas), OK);
}

MU_TEST(test_pgm_read) {
    struct canvas canvas;
    char *bytes = "foo";

    mu_assert_int_eq(pgm_read(0, (uint8_t*) bytes, &canvas), OK);
}

MU_TEST(test_ppm_read) {
    struct canvas canvas;
    char *bytes = "foo";

    mu_assert_int_eq(ppm_read(0, (uint8_t*) bytes, &canvas), OK);
}

MU_TEST_SUITE(test_graphics) {
    MU_RUN_TEST(test_canvas_new); 
    MU_RUN_TEST(test_canvas_end); 

    MU_RUN_TEST(test_pnm_new); 
    MU_RUN_TEST(test_pnm_end); 

    MU_RUN_TEST(test_pnm_read_byte); 

    MU_RUN_TEST(test_pnm_ascii_read_number);

    MU_RUN_TEST(test_pnm_type); 
    MU_RUN_TEST(test_pnm_size); 

    MU_RUN_TEST(test_pbm_read); 
    MU_RUN_TEST(test_pgm_read); 
    MU_RUN_TEST(test_ppm_read); 
}

int main(void) {
    MU_RUN_SUITE(test_command);
    MU_RUN_SUITE(test_graphics);
    MU_REPORT();

    return 0;
}
