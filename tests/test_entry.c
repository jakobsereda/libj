#include "test_include.h"
#include <stdio.h>

int main()
{
    test_sllist_init();
    test_sllist_clear_empty();
    test_sllist_clear_nonempty();
    test_sllist_clear_callback();
    test_sllist_append_empty();
    test_sllist_append_multiple();
    test_sllist_insert_empty();
    test_sllist_insert_negidx();
    test_sllist_insert_badidx();
    test_sllist_insert_multiple();

    printf("ALL TESTS PASSED!\n");

    return 0;
}
