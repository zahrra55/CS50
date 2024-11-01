#include <cs50.h>
#include <stdio.h>

bool check_luhn(long card);
void check_type(long card);

int main(void)
{
    long card;

    // Prompt for card number until it's valid (positive number).
    do
    {
        card = get_long("Number: ");
    } while (card < 0);

    // Check validity using Luhn’s Algorithm
    if (check_luhn(card))
    {
        // Check card type based on length and starting digits
        check_type(card);
    }
    else
    {
        printf("INVALID\n");
    }
}

bool check_luhn(long card)
{
    int sum = 0;
    bool alternate = false;

    while (card > 0)
    {
        int digit = card % 10;
        if (alternate)
        {
            digit *= 2;
            sum += (digit / 10) + (digit % 10);
        }
        else
        {
            sum += digit;
        }
        alternate = !alternate;
        card /= 10;
    }

    return (sum % 10) == 0;
}

void check_type(long card)
{
    // Determine the length of the card number
    int length = 0;
    long temp = card;
    while (temp > 0)
    {
        temp /= 10;
        length++;
    }

    // Determine the first two digits for card type checking
    long start_digits = card;
    while (start_digits >= 100)
    {
        start_digits /= 10;
    }

    // Determine card type
    if (length == 15 && (start_digits == 34 || start_digits == 37))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (start_digits >= 51 && start_digits <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && (start_digits / 10 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
