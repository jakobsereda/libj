#ifndef LIBJ_H
#define LIBJ_H

// Singly Linked List
// ==================
// src/types/sllist.c

typedef struct slnode {
    void          *data;
    struct slnode *next;
} j_slnode;

typedef struct sllist {
    j_slnode *head;
    j_slnode *tail;
    int       size;
} j_sllist;

void sllist_init(j_sllist *list);

void sllist_clear(j_sllist *list);

void sllist_append(j_sllist *list, void *data);

void sllist_prepend(j_sllist *list, void *data);

void sllist_insert(j_sllist *list, void *data, int idx);

void sllist_delete_node(j_sllist *list, void *data);

void sllist_delete_head(j_sllist *list);

void sllist_delete_tail(j_sllist *list);

j_slnode *sllist_find_node(j_sllist *list, void *data);

j_slnode *sllist_find_node_idx(j_sllist *list, int idx);

void sllist_reverse(j_sllist *list);

// Doubly Linked List
// ==================
// src/types/dllist.c

typedef struct dlnode {
    void          *data;
    struct dlnode *next;
    struct dlnode *prev;
} j_dlnode;

typedef struct dllist {
    j_dlnode *head;
    j_dlnode *tail;
    int       size;
} j_dllist;

#endif
