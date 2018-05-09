/*
 * merge two sorted single link lists to one sorted.
 */
#include "list.h"

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
        (void)list_insert(a, na[i]);
    }
    list_show(a);

    for (i = 0; i < sizeof(nb)/sizeof(int); i++)
    {
        (void)list_insert(b, nb[i]);     
    }
    list_show(b);

    head = list_merge(a, b);
    list_show(head);

    list_free(head);

    return 0;
}
