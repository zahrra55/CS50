#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = get_int("Howmany blocks do you want? ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < i + 1; j++)
            printf("#");
        printf("\n");
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < i + 1; j++)
            printf("#");
        printf("\n");
    }
}
