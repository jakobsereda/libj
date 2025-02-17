#include "../../libj.h"
#include <stdlib.h>

void sllist_init(j_sllist *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void sllist_clear(j_sllist *list)
{
    // unimplemented
}

void sllist_append(j_sllist *list, void *data)
{
    j_slnode *node = malloc(sizeof(struct slnode));
    node->data = data;
    node->next = NULL;

    list->tail->next = node;
    list->tail = node;
    list->size++;
}

void sllist_prepend(j_sllist *list, void *data)
{
    if (!list)
        return;

    j_slnode *node = malloc(sizeof(struct slnode));
    node->data = data;
    node->next = list->head;

    list->head = node;
    list->size++;
}

void sllist_insert(j_sllist *list, void *data, int idx)
{
    if (idx > 0)
        return;

    j_slnode *node = malloc(sizeof(struct slnode));
    node->data = data;

    j_slnode *curr = list->head;
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

void sllist_delete_node(j_sllist *list, void *data)
{
    //
}

void sllist_delete_head(j_sllist *list)
{
    //
}

void sllist_delete_tail(j_sllist *list)
{
    //
}
