#ifndef Slist_H
#define Slist_H


#include <stddef.h>

typedef void *Pointer;

typedef struct tNode {
    Pointer data;
    struct tNode *next;
} Node;

typedef struct tSlist {
    Node *head;
} Slist;

void slist_create(Slist *list);
void slist_destroy(Slist *list);
size_t slist_length(Slist *list);
Pointer slist_get(Slist *list, int index);
Pointer slist_get_last(Slist *list);
void slist_prepend(Slist *list, Pointer data);
void slist_append(Slist *list, Pointer data);
Pointer slist_remove(Slist *list, int index);
int slist_find(Slist *list, Pointer data);
Pointer slist_remove_first(Slist *list, Pointer data);
void slist_copy(Slist *dst, Slist *src);
void slist_concat(Slist *dst, Slist *src);
void slist_foreach(Slist *list, void (*func)(Pointer data, void *arg), void *arg);
int slist_find_custom(Slist *list, int (*predicate)(Pointer data, void *arg), void *arg, Pointer *out);
void slist_from_array(Slist *list, Pointer *arr, size_t n);
Pointer *slist_to_array(Slist *list, size_t *n);

#endif