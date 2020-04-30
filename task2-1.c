#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int p1 = 0, p2 = 0;
    while ((p1=fork()) == -1);
    if (p1==0) printf("b\n");
    else
    {
        while ((p2=fork()) == -1);
        if (p2==0) printf("c\n");
        else printf("a\n");
    }
    
    return 0;
}
