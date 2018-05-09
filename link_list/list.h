#ifndef __LIST_H_
#define __LIST_H_

typedef struct List {
    int data;
    struct List *next;
} list_t;

extern list_t* list_delete(int data);
extern list_t* list_init(int data);
extern list_t* list_insert(list_t *head, int data);
extern void list_show(list_t *head);
extern void list_free(list_t *head);
extern list_t* list_merge(list_t *a, list_t *b);

#endif
