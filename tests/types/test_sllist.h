#ifndef TEST_SLLIST_H
#define TEST_SLLIST_H

#include "../../libj.h"

int test_sllist_init();

int test_sllist_clear_empty();
int test_sllist_clear_nonempty();

int test_sllist_append_empty();
int test_sllist_append_nonempty();

int test_sllist_prepend_empty();
int test_sllist_prepend_nonempty();

int test_sllist_insert_empty();
int test_sllist_insert_negidx();
int test_sllist_insert_nonempty();

#endif
