#ifndef TEST_SLLIST_H
#define TEST_SLLIST_H

void test_sllist_init();

void test_sllist_clear_empty();
void test_sllist_clear_nonempty();
void test_sllist_clear_callback();

void test_sllist_append_empty();
void test_sllist_append_multiple();

void test_sllist_prepend_empty();
void test_sllist_prepend_multiple();

void test_sllist_insert_empty();
void test_sllist_insert_negidx();
void test_sllist_insert_badidx();
void test_sllist_insert_multiple();

#endif
