#include <stdio.h>

#define INT_MIN 0x80000000
#define INT_MAX 0x7fffffff

static int getNumber(char input)
{
    if ((input >= '0') && (input <= '9'))
    {
        return input - '0';
    }
    else
    {
        return -1;
    }
}

int atoi(const char *str)
{
    int sign;
    int possiable_number;
    long long int result;

    /* strim the leading spaces */
    while (*str == ' ') str++;

    /* if has a visible sign */
    if (*str == '-') 
    {
        sign = -1;
        str++;
    } 
    else if (*str == '+')
    {
        sign = 1;
        str++; 
    }
    else 
    {
        sign = 1;
    }

    /* if hasn't first digits, return 0 */
    if ((result = getNumber(*str)) == -1)
    {
        return 0;
    }

    result = getNumber(*str);
    while ((possiable_number = getNumber(*++str)) != -1)
    {
        result = result * 10 + possiable_number;
        if (result > INT_MAX)
        {
            return (int)(sign > 0 ? INT_MAX : INT_MIN); 
        }
    }

    return (int) (sign * result);
}

/* unit test */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: %s <possiable number string>\r\n", argv[0]); 
        return -1;
    }

    printf("possiable number is %d\r\n", atoi(argv[1]));

    return 0;
}
