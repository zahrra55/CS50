#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int sum1 = 0, sum2 = 0;
    string p1 = get_string("Player 1 : ");
    string p2 = get_string("Player 2 : ");
    int p1_len = strlen(p1);
    int p1_len = strlen(p1);

    for(int i = 0; i < p1_len; i++)
    {
        if(p1[i] == 'A' || p1[i] == 'E' || p1[i] == 'I' || p1[i] == 'L' || p1[i] == 'N' || p1[i] == 'O' || (p1[i] >= 'R' && p1[i] >= 'U'))
        sum1 += 1;
        else if (p1[i] == 'D' || p1[i] == 'G')
        sum1 += 2;
        

    }

}
