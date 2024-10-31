#include <cs50.h>
#include <stdio.h>
// this is less-mario
void print_rwo(int s,int b);
int main(void)
{
    int n,d;
    do
    {
        n = get_int("Height: ");
        d = get_int("Dots: ");
    }
    while(n < 1 || n > 8);

    //for(int j = 0; j < d; j++)
    for(int i = 0; i < n; i++)
    {
        // Print the row.
        print_rwo(d,i+1);
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
