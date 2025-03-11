#include "test_include.h"
#include <stdio.h>

int main()
{
    printf("\n====<   RUNNING TESTS   >====\n");

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
    test_sllist_delete_head_empty();
    test_sllist_delete_head_single();
    test_sllist_delete_head_multiple();
    test_sllist_delete_tail_empty();
    test_sllist_delete_tail_single();
    test_sllist_delete_tail_multiple();
    test_sllist_delete_node_empty();
    test_sllist_delete_node_single();
    test_sllist_delete_node_not_found();
    test_sllist_delete_node_callback();
    test_sllist_delete_node_idx_empty();
    test_sllist_delete_node_idx_out_of_bounds();
    test_sllist_delete_node_idx_callback();
    test_sllist_is_empty_true();
    test_sllist_is_empty_false();
    test_sllist_find_node_empty();
    test_sllist_find_node_not_found();
    test_sllist_find_node_multiple();
    test_sllist_find_node_idx_empty();
    test_sllist_find_node_idx_out_of_bounds();
    test_sllist_find_node_idx_multiple();
    test_sllist_reverse_empty();
    test_sllist_reverse_single();
    test_sllist_reverse_multiple();
    test_sllist_concat_empty();
    test_sllist_concat_multiple();
    test_sllist_for_each_empty();
    test_sllist_for_each_multiple();
    test_sllist_map_empty();
    test_sllist_map_multiple();
    test_sllist_filter_empty();
    test_sllist_filter_multiple();
    test_sllist_reduce_empty();
    test_sllist_reduce_multiple();

    printf("\n====< ALL TESTS PASSED! >====\n");

    return 0;
}
