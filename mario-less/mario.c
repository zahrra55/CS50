#include <cs50.h>
#include <stdio.h>
// this is less-mario
void print_rwo(int s,int b);
int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while(n < 1);

    for(int i = 0; i < n; i++)
    {
        // Print the row.
        print_rwo(i+1);
    }
}

void print_rwo(int s,int b)
{
    for(int j = 0; j < s; j++)
    for(int i = 0; i < b; i++)
    {
        printf("#");
    }
    printf("\n");
}
