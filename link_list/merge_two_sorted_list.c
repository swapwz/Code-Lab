/*
 * merge two sorted single link lists to one sorted.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct List {
    int data;    
    struct List *next;
} list_t;

list_t* merge_sort(list_t *a, list_t *b)
{
    list_t *head;
    list_t *prev;

    if (a == NULL)
    {
        return b;     
    }

    if (b == NULL)
    {
        return a;    
    }

    if (a->data >= b->data)
    {
        prev = b;
        head = b;     
    }
    else
    {
        prev = a;     
        head = a;
    }

    while ((a != NULL) && (b != NULL))
    {
        if (a->data < b->data)     
        {
            if (prev != a)
            {
                prev->next = a;
                prev = a;
            }
            a = a->next;
        }
        else
        {
            if (prev != b)
            {
                prev->next = b;
                prev = b;
            }
            b = b->next;     
        }
    }

    if (a != NULL)
    {
        prev->next = a;      
    }
    else
    {
        prev->next = b; 
    }

    return head;   
}

list_t* list_init(int data)
{
    list_t *head;

    head = (list_t *) malloc(sizeof(list_t)); 
    if (head != NULL)
    {
        head->data = data;     
        head->next = NULL;
    }

    return head;
}

int list_insert(list_t *head, int data)
{
    list_t *new_node;

    new_node = (list_t *)malloc(sizeof(list_t));
    if (new_node != NULL)
    {
        new_node->data = data;      
        new_node->next = head->next;
        head->next = new_node;
        return 0;
    }

    return -1;
}

void list_show(list_t *head)
{
    while (head != NULL)
    {
        printf("%d->", head->data);    
        head = head->next;
    }

    printf("NULL\r\n");
}

void list_free(list_t *head)
{
    list_t *tmp;

    while (head != NULL)    
    {
        tmp = head->next;     
        free(head);
        head = tmp;
    }
}

int main(int argc, char **argv)
{
    int na[] = {20, 14, 10, 9, 8, 7, 6, 2};
    int nb[] = {20, 14, 10, 9, 8, 7, 6, 2};
    int i;
    list_t *a, *b;
    list_t *head;

    a = list_init(1);
    b = list_init(1);

    for (i = 0; i < sizeof(na)/sizeof(int); i++)
    {
        list_insert(a, na[i]);
    }
    list_show(a);

    for (i = 0; i < sizeof(nb)/sizeof(int); i++)
    {
        list_insert(b, nb[i]);     
    }
    list_show(b);

    head = merge_sort(a, b);
    list_show(head);

    list_free(head);

    return 0;
}
