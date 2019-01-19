#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char* longestPalindrome(const char* s) {
    int len;
    int max_len = 1;
    const char *end;
    const char *max_pos;
    char *ret = NULL;

    assert(s != NULL);
    len = strlen(s);
    if (len == 0)
        return NULL;

    ret = (char *)malloc(len + 1);
    if (ret == NULL)
        return NULL;

    end = s + len;
    for (const char *p = s; p < end; p++)
    {
        /* find the end point */
        for (const char *p1 = end; p < p1; p1--)
        {
            const char *s1 = p;
            const char *e1 = p1;
            int cur_len = e1 - s1 + 1;
            if (max_len >= cur_len)
                break;
            /* check is a palindrome */
            do {
                /* reset */
                if (*s1 != *e1)
                {
                    cur_len = 0;
                    break;
                }
                s1++;
                e1--;
            } while (s1 < e1);

            if (cur_len > max_len)
            {
                max_len = cur_len;
                max_pos = p;
            }
        }
    }

    if (max_len > 1)
    {
        memcpy(ret, max_pos, max_len);
        ret[max_len] = 0;
    }
    else
    {
        ret[0] = *s;
        ret[1] = 0;
    }
    return ret;
}

int main(int argc, char **argv)
{
    char *p;

    if (argc != 2)
    {
        printf("usage: %s <possiable string>\r\n", argv[0]);
        return 0;
    }

    p = longestPalindrome(argv[1]);
    if (p != NULL)
    {
        printf("The longest palinkdrome string is %s\r\n", p);
        free(p);
    }

    return 0;
}
