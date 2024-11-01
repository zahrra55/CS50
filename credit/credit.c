#include <cs50.h>
#include <stdio.h>


int main(void)
{
    long Number;
    do
    {
        Number = get_long("Number: ");
    }
    while(Number < 0);

    if(){//if lohn algorithm is right
        //check the card type
    }
    else{
        printf("INVALID\n");
    }
}

bool Luhn_s_Algorithm(long n)
{
    int sum = 0, pos = 0;
    while(n > 0)
    {
        int digit = n % 10; //finding the last digit
        if(pos % 2 == 1)
        {
            digit *= 2; // multiplying every other digit by 2
            sum += (digit / 10) + (digit % 10); // if more than 2 make 
        }
    }
}
