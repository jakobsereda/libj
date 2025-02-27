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

int sort_comp(void *a, void *b)
{
    if (!a || !b) return 0;
    return (*(int *) a) < (*(int *) b);
}

void test_sllist_sort_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    sllist_sort(list, sort_comp);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_sort_sorted()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    int b = 2;
    int c = 4;
    sllist_append(list, &a);
    sllist_append(list, &b);
    sllist_append(list, &c);

    sllist_sort(list, sort_comp);

    assert((*(int *) list->head->data) == 1);
    assert((*(int *) list->head->next->data) == 2);
    assert((*(int *) list->tail->data) == 4);
    assert(list->size == 3);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_sort_odd_length()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 8;
    int b = 2;
    int c = 4;
    sllist_append(list, &a);
    sllist_append(list, &b);
    sllist_append(list, &c);

    sllist_sort(list, sort_comp);

    assert((*(int *) list->head->data) == 2);
    assert((*(int *) list->head->next->data) == 4);
    assert((*(int *) list->tail->data) == 8);
    assert(list->size == 3);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_sort_even_length()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 8;
    int b = 2;
    int c = 13;
    int d = 4;
    sllist_append(list, &a);
    sllist_append(list, &b);
    sllist_append(list, &c);
    sllist_append(list, &d);

    sllist_sort(list, sort_comp);

    assert((*(int *) list->head->data) == 2);
    assert((*(int *) list->head->next->data) == 4);
    assert((*(int *) list->head->next->next->data) == 8);
    assert((*(int *) list->tail->data) == 13);
    assert(list->size == 4);

    sllist_clear(list, NULL);
    free(list);
}
