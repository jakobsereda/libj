#include "test_include.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    assert(test_sllist_init());
    assert(test_sllist_clear_empty());
    assert(test_sllist_clear_nonempty());
    // assert(test_sllist_append_empty());
    // assert(test_sllist_append_nonempty());

    printf("All tests passed!\n");

    return 0;
}
