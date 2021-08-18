#include <stdio.h>
#include <string.h>

int main(void)
{
    while(1)
    {
        char input[100];

        fgets(input, 100, stdin);

        char reject[5] = {'$', '#', '^', '%'};

        printf("%ld\n", strcspn(input, reject));
    }
}
