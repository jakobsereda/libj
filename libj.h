#ifndef LIBJ_H
#define LIBJ_H

// Singly Linked List
// ==================
// src/types/sllist.c

struct j_slnode {
    void            *data;
    struct j_slnode *next;
};

struct j_sllist {
    struct j_slnode *head;
    struct j_slnode *tail;
    int              size;
};

void sllist_init(struct j_sllist *list);

void sllist_clear(struct j_sllist *list, void (*clear_data)(void *));

void sllist_append(struct j_sllist *list, void *data);

void sllist_prepend(struct j_sllist *list, void *data);

void sllist_insert(struct j_sllist *list, void *data, int idx);

void sllist_delete_node(struct j_sllist *list, void *data);

void sllist_delete_head(struct j_sllist *list);

void sllist_delete_tail(struct j_sllist *list);

struct j_slnode *sllist_find_node(struct j_sllist *list, void *data);

struct j_slnode *sllist_find_node_idx(struct j_sllist *list, int idx);

void sllist_reverse(struct j_sllist *list);

// Doubly Linked List
// ==================
// src/types/dllist.c

struct j_dlnode {
    void            *data;
    struct j_dlnode *next;
    struct j_dlnode *prev;
};

struct j_dllist {
    struct j_dlnode *head;
    struct j_dlnode *tail;
    int              size;
};

#endif
