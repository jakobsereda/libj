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
    assert(list->size == 0);

    free(list);
}

void test_sllist_clear_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    sllist_clear(list, NULL);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);

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
    assert(list->size == 0);

    free(list);
}

static int callback_count = 0;

void clear_data(void *data) {
    callback_count++;
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

    sllist_clear(list, clear_data);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);
    assert(callback_count == 2);

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

    assert(list->size == 1);
    assert((*(int *) list->head->data) == 1);
    assert((*(int *) list->tail->data) == 1);

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

    assert(list->size == 2);
    assert((*(int *) list->head->data) == 1);
    assert((*(char *) list->tail->data) == 'j');

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_prepend_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    sllist_append(list, &a);

    assert(list->size == 1);
    assert((*(int *) list->head->data) == 1);
    assert((*(int *) list->tail->data) == 1);

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

    assert(list->size == 2);
    assert((*(char *) list->head->data) == 'j');
    assert((*(int *) list->tail->data) == 1);

    sllist_clear(list, NULL);
    free(list);
}

void test_sllist_insert_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    free(list);
}

void test_sllist_insert_negidx()
{
    //
}

void test_sllist_insert_badidx()
{
    //
}

void test_sllist_insert_multiple()
{
    //
}
