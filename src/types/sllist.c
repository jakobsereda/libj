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

void sllist_delete_node(struct j_sllist *list, void *data, int (*comp)(void *, void *), void (*clear_data)(void *))
{
    if (!list || sllist_is_empty(list) || !comp)
        return;

    struct j_slnode *curr = list->head;

    // handle the case where the data
    // matches the head of the list
    if (comp(data, curr->data)) {
        struct j_slnode *tmp = curr->next;

        if (clear_data)
            clear_data(curr);

        free(curr);
        list->head = tmp;

        // if we deleted the only element in the
        // list, then update the tail pointer
        if (list->size-- == 1)
            list->tail = tmp;

        return;
    }

    while (curr->next) {
        if (comp(data, curr->next->data))
            break;
        curr = curr->next;
    }

    if (!curr->next) return;

    struct j_slnode *tmp = curr->next->next;

    if (clear_data)
        clear_data(curr->next);

    free(curr->next);

    if (curr->next == list->tail)
        list->tail = curr;

    curr->next = tmp;
    list->size--;
}

void sllist_delete_node_idx(struct j_sllist *list, int idx, void (*clear_data)(void *))
{
    if (!list || sllist_is_empty(list) || idx < 0 || idx >= list->size)
        return;

    if (idx == 0)
        sllist_delete_head(list, clear_data);

    if (idx == list->size - 1)
        sllist_delete_tail(list, clear_data);

    // note: 0 < idx < list->size - 1
    struct j_slnode *curr = list->head;
    while (idx-- > 1)
        curr = curr->next;

    struct j_slnode *tmp = curr->next->next;

    if (clear_data)
        clear_data(curr->next);

    free(curr->next);
    curr->next = tmp;
    list->size--;
}

int sllist_is_empty(struct j_sllist *list)
{
    return list->size == 0;
}

struct j_slnode *sllist_find_node(struct j_sllist *list, void *data, int (*comp)(void *, void *))
{
    if (!list || sllist_is_empty(list))
        return NULL;

    struct j_slnode *curr = list->head;
    while (curr) {
        if (comp(data, curr->data))
            return curr;
        curr = curr->next;
    }

    return NULL;
}

struct j_slnode *sllist_find_node_idx(struct j_sllist *list, int idx)
{
    if (!list || sllist_is_empty(list) || idx < 0 || idx >= list->size)
        return NULL;

    // note: 0 < idx < list->size - 1
    struct j_slnode *curr = list->head;
    while (idx-- > 0)
        curr = curr->next;

    return curr;
}

void sllist_reverse(struct j_sllist *list)
{
    if (!list || sllist_is_empty(list))
        return;

    struct j_slnode *prev = NULL;
    struct j_slnode *curr = list->head;
    struct j_slnode *next = NULL;

    list->tail = curr;

    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    list->head = prev;
}

void sllist_concat(struct j_sllist *dest, struct j_sllist *src)
{
    if (!dest || sllist_is_empty(dest) || !src || sllist_is_empty(src))
        return;

    dest->tail->next = src->head;
    dest->tail = src->tail;
    dest->size += src->size;

    src->head = NULL;
    src->tail = NULL;
    src->size = 0;
}

struct j_slnode *sllist_merge(struct j_slnode *l, struct j_slnode *r, int (*comp)(void *, void *))
{
    // credit: https://stackoverflow.com/a/11273262/

    struct j_slnode out;
    struct j_slnode *p = &out;
    out.next = NULL;

    while (l && r) {
        if (comp(l->data, r->data)) {
            p->next = l;
            l = l->next;
        } else {
            p->next = r;
            r = r->next;
        }

        p = p->next;
    }

    if (l)
        p->next = l;
    else
        p->next = r;

    return out.next;
}

void sllist_sort(struct j_sllist *list, int (*comp)(void *, void *))
{
    if (!list || sllist_is_empty(list) || !comp)
        return;

    int mid = list->size / 2;
    struct j_slnode *curr = list->head;
    for (int i = 1; i < mid; i++)
        curr = curr->next;

    struct j_sllist split;
    sllist_init(&split);

    split.head = curr->next;
    split.tail = list->tail;
    split.size = list->size - mid;

    list->tail = curr;
    list->size = mid;

    curr->next = NULL;

    sllist_sort(list, comp);
    sllist_sort(&split, comp);

    list->head = sllist_merge(list->head, split.head, comp);

    curr = list->head;
    while (curr->next)
        curr = curr->next;
    list->tail = curr;

    list->size += split.size;
}

void sllist_for_each(struct j_sllist *list, void (*proc)(void *))
{
    if (!list || sllist_is_empty(list) || !proc)
        return;

    struct j_slnode *curr = list->head;
    while (curr) {
        proc(curr->data);
        curr = curr->next;
    }
}

struct j_sllist *sllist_map(struct j_sllist *list, void *(*proc)(void *))
{
    if (!list) return NULL;

    if (sllist_is_empty(list) || !proc)
        return list;

    struct j_sllist *ret = malloc(sizeof(struct j_sllist));
    sllist_init(ret);

    struct j_slnode *curr = list->head;
    while (curr) {
        void *mapped = proc(curr->data);
        sllist_append(ret, mapped);
        curr = curr->next;
    }

    return ret;
}

struct j_sllist *sllist_filter(struct j_sllist *list, int (*pred)(void *))
{
    if (!list) return NULL;

    if (sllist_is_empty(list) || !pred)
        return list;

    struct j_sllist *ret = malloc(sizeof(struct j_sllist));
    sllist_init(ret);

    struct j_slnode *curr = list->head;
    while (curr) {
        if (pred(curr->data))
            sllist_append(ret, curr->data);
        curr = curr->next;
    }

    return ret;
}

void *sllist_reduce(struct j_sllist *list, void *acc, void *(*proc)(void *, void *))
{
    if (!list || sllist_is_empty(list) || !proc)
        return NULL;

    struct j_slnode *curr = list->head;
    while (curr) {
        acc = proc(acc, curr->data);
        curr = curr->next;
    }

    return acc;
}
