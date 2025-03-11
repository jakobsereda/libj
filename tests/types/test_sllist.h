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

void test_sllist_delete_head_empty();
void test_sllist_delete_head_single();
void test_sllist_delete_head_multiple();

void test_sllist_delete_tail_empty();
void test_sllist_delete_tail_single();
void test_sllist_delete_tail_multiple();

void test_sllist_delete_node_empty();
void test_sllist_delete_node_single();
void test_sllist_delete_node_not_found();
void test_sllist_delete_node_callback();

void test_sllist_delete_node_idx_empty();
void test_sllist_delete_node_idx_out_of_bounds();
void test_sllist_delete_node_idx_callback();

void test_sllist_is_empty_true();
void test_sllist_is_empty_false();

void test_sllist_find_node_empty();
void test_sllist_find_node_not_found();
void test_sllist_find_node_multiple();

void test_sllist_find_node_idx_empty();
void test_sllist_find_node_idx_out_of_bounds();
void test_sllist_find_node_idx_multiple();

void test_sllist_reverse_empty();
void test_sllist_reverse_single();
void test_sllist_reverse_multiple();

void test_sllist_concat_empty();
void test_sllist_concat_multiple();

void test_sllist_for_each_empty();
void test_sllist_for_each_multiple();

void test_sllist_map_empty();
void test_sllist_map_multiple();

void test_sllist_filter_empty();
void test_sllist_filter_multiple();

void test_sllist_reduce_empty();
void test_sllist_reduce_multiple();

#endif
