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
