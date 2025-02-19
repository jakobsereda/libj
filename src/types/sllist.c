#include "../../libj.h"
#include <stdlib.h>

void sllist_init(struct j_sllist *list)
{
    if (!list) return;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void sllist_clear(struct j_sllist *list, void (*clear_data)(void *))
{
    if (!list || sllist_is_empty(list))
        return;

    struct j_slnode *curr = list->head;
    while (curr) {
        struct j_slnode *tmp = curr->next;

        if (clear_data)
            clear_data(curr->data);

        free(curr);
        curr = tmp;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void sllist_append(struct j_sllist *list, void *data)
{
    if (!list) return;

    struct j_slnode *node = malloc(sizeof(struct j_slnode));
    node->data = data;
    node->next = NULL;

    if (list->head)
        list->tail->next = node;
    else
        list->head = node;

    list->tail = node;
    list->size++;
}

void sllist_prepend(struct j_sllist *list, void *data)
{
    if (!list) return;

    struct j_slnode *node = malloc(sizeof(struct j_slnode));
    node->data = data;
    node->next = list->head;

    if (!list->tail)
        list->tail = node;

    list->head = node;
    list->size++;
}

void sllist_insert(struct j_sllist *list, void *data, int idx)
{
    if (!list || idx < 0 || idx > list->size)
        return;

    if (idx == 0) {
        sllist_prepend(list, data);
        return;
    }

    if (idx == list->size) {
        sllist_append(list, data);
        return;
    }

    // we know 1 < idx < list->size at this
    // point so we can traverse without worrying
    // about going past the end of the list
    struct j_slnode *curr = list->head;
    while (idx-- > 1)
        curr = curr->next;

    struct j_slnode *node = malloc(sizeof(struct j_slnode));
    node->data = data;

    node->next = curr->next;
    curr->next = node;
    list->size++;
}

void sllist_delete_head(struct j_sllist *list, void (*clear_data)(void *))
{
    if (!list || sllist_is_empty(list))
        return;

    struct j_slnode *tmp = list->head;
    list->head = list->head->next;

    if (list->size-- == 1)
        list->tail = NULL;

    if (clear_data)
        clear_data(tmp->data);

    free(tmp);
}

void sllist_delete_tail(struct j_sllist *list, void (*clear_data)(void *))
{
    if (!list || sllist_is_empty(list))
        return;

    if (list->size-- == 1) {
        if (clear_data)
            clear_data(list->head->data);

        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    struct j_slnode *curr = list->head;
    while (curr->next != list->tail)
        curr = curr->next;

    if (clear_data)
        clear_data(curr->next->data);

    free(curr->next);
    curr->next = NULL;
    list->tail = curr;
}

void sllist_delete_node(struct j_sllist *list, void *data, void (*clear_data)(void *))
{
    //
}

void sllist_delete_node_idx(struct j_sllist *list, int idx, void (*clear_data)(void *))
{
    //
}

int sllist_is_empty(struct j_sllist *list)
{
    return list->size == 0;
}

struct j_slnode *sllist_find_node(struct j_sllist *list, void *data, int (*comp)(void *, void *))
{
    if (!list || !list->head)
        return NULL;

    struct j_slnode *curr = list->head;
    while (curr) {
        // comp should return 1 (or some non-zero value)
        // when its inputs are the 'same', and zero when 
        // they are 'different'
        if (comp(curr->data, data))
            return curr;
        curr = curr->next;
    }

    return NULL;
}

struct j_slnode *sllist_find_node_idx(struct j_sllist *list, int idx)
{
    return NULL;
}

void sllist_reverse(struct j_sllist *list)
{
    //
}

void sllist_concat(struct j_sllist *dest, struct j_sllist *src)
{
    //
}

void sllist_sort(struct j_sllist *list, int (*comp)(void *, void *))
{
    //
}

void sllist_for_each(struct j_sllist *list, void (*proc)(void *))
{
    //
}

struct j_sllist *sllist_map(struct j_sllist *list, void *(*proc)(void *))
{
    //
    return NULL;
}

struct j_sllist *sllist_filter(struct j_sllist *list, int (*pred)(void *))
{
    //
    return NULL;
}

void *sllist_reduce(struct j_sllist *list, void *acc, void *(*proc)(void *, void *))
{
    //
    return NULL;
}
