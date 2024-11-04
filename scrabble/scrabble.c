#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int sum1 = 0, sum2 = 0;
    string p1,p2;
    string play1 = get_string("Player 1 : ");
    string play2 = get_string("Player 2 : ");
    int p1_len = strlen(play1);
    int p2_len = strlen(play2);

    for(int j = 0; j < p1_len; j++)
    {
        p1 = toupper(play1[j]);
    }

    for(int j = 0; j < p2_len; j++)
    {
        p2 = toupper(play2[j]);
    }

    for(int i = 0; i < p1_len; i++)
    {
        if (p1[i] == 'A' || p1[i] == 'E' || p1[i] == 'I' || p1[i] == 'L' || p1[i] == 'N' || p1[i] == 'O' || (p1[i] >= 'R' && p1[i] >= 'U'))
        sum1 += 1;
        else if (p1[i] == 'D' || p1[i] == 'G')
        sum1 += 2;
        else if (p1[i] == 'B' || p1[i] == 'C' || p1[i] == 'M' || p1[i] == 'P')
        sum1 += 3;
        else if (p1[i] == 'F' || p1[i] == 'H' || p1[i] == 'V' || p1[i] == 'W' || p1[i] == 'Y')
        sum1 += 4;
        else if (p1[i] == 'K')
        sum1 += 5;
        else if (p1[i] == 'J' || p1[i] == 'X')
        sum1 += 8;
        else if (p1[i] == 'Q' || p1[i] == 'Z')
        sum1 += 10;
    }

    for(int i = 0; i < p2_len; i++)
    {
        if (p2[i] == 'A' || p2[i] == 'E' || p2[i] == 'I' || p2[i] == 'L' || p2[i] == 'N' || p2[i] == 'O' || (p2[i] >= 'R' && p2[i] >= 'U'))
        sum2 += 1;
        else if (p2[i] == 'D' || p2[i] == 'G')
        sum2 += 2;
        else if (p2[i] == 'B' || p2[i] == 'C' || p2[i] == 'M' || p2[i] == 'P')
        sum2 += 3;
        else if (p2[i] == 'F' || p2[i] == 'H' || p2[i] == 'V' || p2[i] == 'W' || p2[i] == 'Y')
        sum2 += 4;
        else if (p2[i] == 'K')
        sum2 += 5;
        else if (p2[i] == 'J' || p2[i] == 'X')
        sum2 += 8;
        else if (p2[i] == 'Q' || p2[i] == 'Z')
        sum2 += 10;
    }

    if(sum1 > sum2)
    printf("Player 1 wins!\n");
    else if(sum2 > sum1)
    printf("Player 2 wins!\n");
    else
    printf("Tie!\n");

}
