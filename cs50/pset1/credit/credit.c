//A program to check if a credit card number is valid.

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int luhn(long long n);

int main(void)
{
    long long cardNum = get_long_long("Enter card number: ");

    int digits = log10(cardNum) + 1;
    int firstDigit = cardNum / pow(10, (digits - 1));
    int secondDigit = cardNum / pow(10, (digits - 2));
    secondDigit %= 10;

    //Amex cards begin with 34 or 37 and have 15 digits
    if (firstDigit == 3 && (secondDigit == 4 || secondDigit == 7) && digits == 15)
    {
        if (luhn(cardNum) == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    //Mastercards begin with 51 through 55 and have 16 digits
    else if (firstDigit == 5 && secondDigit > 0 && secondDigit <= 5 && digits == 16)
    {
        if (luhn(cardNum) == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    //Visa cards begin with 4 and have 13 or 16 digits
    else if (firstDigit == 4 && (digits == 13 || digits == 16))
    {
        if (luhn(cardNum) == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}

//Function uses Luhn's algorithm to check number validity.
//If returns zero, card is valid. Non-zero, invalid.
int luhn(long long n)
{
    int arr[16] = {0, 0, 0, 0, 0};
    int luhnTotal = 0;

    //Create array of digits from long long "n"
    for (int i = 0; i < 16; i++)
    {
        arr[15 - i] = n % 10;
        n /= 10;
    }

    //Start at end. Add last digit, multiply second to last by two then add, repeat.
    for (int k = 0; k < 16; k++)
    {
        if (k % 2 == 0)
        {
            luhnTotal += arr[15 - k];
        }
        else
        {
            if ((arr[15 - k] * 2) > 9)
            {
                luhnTotal += (arr[15 - k] * 2) - 9; //If product is > 9, Luhn's Algorithm says to subtract 9
            }
            else
            {
                luhnTotal += (arr[15 - k] * 2);
            }
        }
    }
    return (luhnTotal % 10);
}