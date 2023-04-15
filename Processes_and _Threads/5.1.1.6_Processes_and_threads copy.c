#include <stdio.h>
#include <stdlib.h>

int 
main(void)
{
    char *nam = "USERNAME";
    char *val = getenv(nam);

    if (val == NULL)
    {
        printf("%s undefined\n",nam);
        return 1;
    }
    printf("%s = %s\n", nam, val);
    return 0;
}