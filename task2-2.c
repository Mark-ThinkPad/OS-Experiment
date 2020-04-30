#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int p1=0, p2=0, i=0;
    while ((p1=fork()) == -1);
    if (p1==0)
        for (i = 0; i < 10; i++)
            printf("daughter %d\n", i);
    else
    {
        while ((p2=fork()) == -1);
        if (p2==0)
            for (i = 0; i < 10; i++)
                printf("son %d\n", i);
        else
            for (i = 0; i < 10; i++)
                printf("parent %d\n", i);
    } 

    return 0;
}
