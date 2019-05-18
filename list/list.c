#include <stdio.h>
#include <stdlib.h>
#include "list.h"

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

list_t* list_insert(list_t *head, int data)
{
    list_t *new_node;

    new_node = (list_t *)malloc(sizeof(list_t));
    if (new_node != NULL)
    {
        new_node->data = data;      
        new_node->next = head->next;
        head->next = new_node;
        return new_node;
    }

    return NULL;
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


list_t* list_merge(list_t *a, list_t *b)
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

list_t* list_delete(list_t *head, int data)
{
    list_t **cur;

    for (cur = &head; *cur != NULL; )
    {
        list_t *entry = *cur;
	if (entry->data == data)
	{
            *cur = entry->next;
            free(entry);
	}
	else
	{
            cur = &entry->next;
	}
    }
    return head;
}
