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
    // if list->head == NULL, the list is
    // empty and we don't need to clear
    if (!list || !list->head)
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
