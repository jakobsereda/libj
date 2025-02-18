#include "../../libj.h"
#include <stdlib.h>

void sllist_init(struct j_sllist *list)
{
    if (!list) return;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void sllist_clear(struct j_sllist *list)
{
    if (!list || !list->head)
        return;

    struct j_slnode *curr = list->head;
    while (curr) {
        struct j_slnode *tmp = curr->next;
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

    list->head = node;
    list->size++;
}

void sllist_insert(struct j_sllist *list, void *data, int idx)
{
    if (!list || idx < 0) 
        return;

    struct j_slnode *node = malloc(sizeof(struct j_slnode));
    node->data = data;

    struct j_slnode *curr = list->head;
    while (idx > 0) {
        if (!curr->next)
            return;
        curr = curr->next;
        idx--;
    }

    node->next = curr->next;
    curr->next = node;
    list->size++;
}
