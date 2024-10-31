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
        //s = get_int("Spaces: ");
    }
    while(n < 2 || n > 7);

    //for(int j = 0; j < d; j++)
    for(int i = 0; i < n; i++)
    {
        // Print the row.
        print_rwo(n,i+1);
    }
}

void print_rwo(int s,int b)
{
    for(int j = b-1; j < s; j++)
    printf(" ");

    for(int i = 0; i < b; i++)
    {
        printf("#");
    }
    printf("\n");
}
