#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    while(1)
    {
        char * input = malloc(sizeof(char) * 100);

        fgets(input, 100, stdin);

        char * reject = "$%^' '&";

        while(*input != '\0')
        {
            int itr = strcspn(input, reject);

            if(itr == 0)
            {
                printf(" %c ", *input);
                input++;
            }

            for(int i = 0; i < itr; i++)
            {
                printf("%c", *input);

                input++;
            }
        }
    }
}
