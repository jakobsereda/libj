#include "test_sllist.h"
#include <stdlib.h>

int test_sllist_init()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));

    sllist_init(list);

    if (list->head || list->tail || list->size) {
        free(list);
        return 0;
    }

    free(list);
    return 1;
}

int test_sllist_clear_empty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    sllist_clear(list);

    if (list->head || list->tail || list->size) {
        free(list);
        return 0;
    }

    free(list);
    return 1;
}

int test_sllist_clear_nonempty()
{
    struct j_sllist *list = malloc(sizeof(struct j_sllist));
    sllist_init(list);

    int a = 1;
    int b = 2;
    sllist_append(list, &a);
    sllist_append(list, &b);

    sllist_clear(list);

    if (list->head || list->tail || list->size) {
        free(list);
        return 0;
    }

    free(list);
    return 1;
}
