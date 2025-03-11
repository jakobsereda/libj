#include "test_sllist.h"
#include "../../libj.h"
#include <stdlib.h>
#include <assert.h>

void test_sllist_init()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));

    sllist_init(list);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(sllist_is_empty(list));

    free(list);
}

void test_sllist_clear_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    sllist_clear(list, NULL);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(sllist_is_empty(list));

    free(list);
}

void test_sllist_clear_nonempty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    int b = 2;
    sllist_append(list, &a);
    sllist_append(list, &b);

    sllist_clear(list, NULL);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(sllist_is_empty(list));

    free(list);
}

static int clear_callback_count = 0;

void clear_clear_data(void *data)
{
    clear_callback_count++;
    free(data);
}

void test_sllist_clear_callback()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int *a = malloc(sizeof(int));
    *a = 1;
    int *b = malloc(sizeof(int));
    *b = 2;
    sllist_append(list, a);
    sllist_append(list, b);

    sllist_clear(list, clear_clear_data);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(sllist_is_empty(list));
    assert(clear_callback_count == 2);

    // we cannot assert a and b are freed,
    // but its worthwhile to check for memory
    // leaks to verify the callback is working

    free(list);
}

void test_sllist_append_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    sllist_append(list, &a);

    assert((*(int *) list->head->data) == 1);
    assert((*(int *) list->tail->data) == 1);
    assert(list->size == 1);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_append_multiple()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    char b = 'j';
    sllist_append(list, &a);
    sllist_append(list, &b);

    assert((*(int *) list->head->data) == 1);
    assert((*(char *) list->tail->data) == 'j');
    assert(list->size == 2);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_prepend_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    sllist_append(list, &a);

    assert((*(int *) list->head->data) == 1);
    assert((*(int *) list->tail->data) == 1);
    assert(list->size == 1);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_prepend_multiple()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    char b = 'j';
    sllist_prepend(list, &a);
    sllist_prepend(list, &b);

    assert((*(char *) list->head->data) == 'j');
    assert((*(int *) list->tail->data) == 1);
    assert(list->size == 2);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_insert_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    sllist_insert(list, &a, 0);

    assert((*(int *) list->head->data) == 1);
    assert((*(int *) list->tail->data) == 1);
    assert(list->size == 1);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_insert_negidx()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    sllist_insert(list, &a, -1);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(sllist_is_empty(list));

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_insert_badidx()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    sllist_insert(list, &a, 1);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(sllist_is_empty(list));

    sllist_append(list, &a);

    int b = 2;
    sllist_insert(list, &b, 2);

    assert((*(int *) list->head->data) == 1);
    assert((*(int *) list->tail->data) == 1);
    assert(list->size == 1);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_insert_multiple()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    char b = 'j';
    long c = 42;
    sllist_append(list, &a);
    sllist_append(list, &b);

    sllist_insert(list, &c, 1);

    assert((*(int *) list->head->data) == 1);
    assert((*(long *) list->head->next->data) == 42);
    assert((*(char *) list->tail->data) == 'j');
    assert(list->size == 3);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_delete_head_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    sllist_delete_head(list, NULL);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_delete_head_single()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    sllist_append(list, &a);

    sllist_delete_head(list, NULL);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);

    sllist_clear(list, NULL);
    free(list);
}

static int delete_head_callback_count = 0;

void delete_head_clear_data(void *data)
{
    delete_head_callback_count++;
    free(data);
}

void test_sllist_delete_head_multiple()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int *a = malloc(sizeof(int));
    *a = 1;
    int b = 2;
    sllist_append(list, a);
    sllist_append(list, &b);

    sllist_delete_head(list, delete_head_clear_data);

    assert(*((int *)list->head->data) == 2);
    assert(list->size == 1);
    assert(delete_head_callback_count == 1);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_delete_tail_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    sllist_delete_tail(list, NULL);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_delete_tail_single()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    sllist_append(list, &a);

    sllist_delete_tail(list, NULL);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);

    sllist_clear(list, NULL);
    free(list);
}

static int delete_tail_callback_count = 0;

void delete_tail_clear_data(void *data)
{
    delete_tail_callback_count++;
    free(data);
}

void test_sllist_delete_tail_multiple()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    int *b = malloc(sizeof(int));
    *b = 2;
    sllist_append(list, &a);
    sllist_append(list, b);

    sllist_delete_tail(list, delete_head_clear_data);

    assert(*((int *)list->head->data) == 2);
    assert(list->size == 1);
    assert(delete_head_callback_count == 1);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_delete_node_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_delete_node_single()
{

}

void test_sllist_delete_node_not_found()
{

}

void test_sllist_delete_node_callback()
{

}

void test_sllist_delete_node_idx_empty()
{

}

void test_sllist_delete_node_idx_out_of_bounds()
{

}

void test_sllist_delete_node_idx_callback()
{

}

void test_sllist_is_empty_true()
{

}

void test_sllist_is_empty_false()
{

}

void test_sllist_find_node_empty()
{

}

void test_sllist_find_node_not_found()
{

}

void test_sllist_find_node_multiple()
{

}

void test_sllist_find_node_idx_empty()
{

}

void test_sllist_find_node_idx_out_of_bounds()
{

}

void test_sllist_find_node_idx_multiple()
{

}

void test_sllist_reverse_empty()
{

}

void test_sllist_reverse_single()
{

}

void test_sllist_reverse_multiple()
{

}

void test_sllist_concat_empty()
{

}

void test_sllist_concat_multiple()
{

}

void test_sllist_for_each_empty()
{

}

void test_sllist_for_each_multiple()
{

}

void test_sllist_map_empty()
{

}

void test_sllist_map_multiple()
{

}

void test_sllist_filter_empty()
{

}

void test_sllist_filter_multiple()
{

}

void test_sllist_reduce_empty()
{

}

void test_sllist_reduce_multiple()
{

}
