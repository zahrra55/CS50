#include <cs50.h>
#include <stdio.h>

bool Luhn_s_Algorithm(long n);

int main(void)
{
    long Cnumber;
    int len = 0;
    do
    {
        Cnumber = get_long("Number: ");
    }
    while (Cnumber < 0);

    if (Luhn_s_Algorithm(Cnumber))
    { // if lohn algorithm is right
        // check the card type
        long s = Cnumber;
        while (s > 0)
        {
            s /= 10;
            len++;
        }
        long fir_sec_dgts = Cnumber;
        while (fir_sec_dgts >= 100)
        {
            fir_sec_dgts /= 10;
        }
        if (len == 15 && (fir_sec_dgts == 34 || fir_sec_dgts == 37))
            printf("AMEX\n");

        else if (len == 16 && (fir_sec_dgts >= 51 && fir_sec_dgts <= 55))
            printf("MASTERCARD\n");

        else if ((len == 13 || len == 16) && (fir_sec_dgts / 10 == 4))
            printf("VISA\n");
        else
            printf("INVALID\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

bool Luhn_s_Algorithm(long n)
{
    int sum = 0, pos = 0;
    while (n > 0)
    {
        int digit = n % 10; // finding the last digit
        if (pos % 2 == 1)
        {
            digit *= 2;                         // multiplying every other digit by 2
            sum += (digit / 10) + (digit % 10); // if more than 10, make 2 digits of it
        }
        else
        {
            sum += digit; // adding the rest of the digits
        }
        n /= 10; // complete the process
        pos++;   // increse the pos value
    }
    return (sum % 10) == 0;
}
