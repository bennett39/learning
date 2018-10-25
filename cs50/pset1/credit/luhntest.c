//Testing a function that calculates Luhn's algorithm on a long long, returning an int of 0 (yes) or non-zero (no).

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long n = get_long_long("Enter card number: ");
    int arr[16] = {0, 0, 0, 0, 0};
    int luhnTotal = 0;

    //Create array of digits from long long "n"
    for (int i = 0; i < 16; i++)
    {
        arr[15 - i] = n % 10;
        n /= 10;
    }

    /*
    //Print the array so I can see what's going on.
    int j = 0;
    while (j < 16)
    {
        printf("%d, ", arr[j]);
        j++;
    }
    printf("\n");
    */

    //Start at end. Add last digit, multiply second to last by two then add, repeat.
    for (int k = 0; k < 16; k++)
    {
        if (k % 2 == 0)
        {
            luhnTotal += arr[15 - k];
            //printf("%d\n", luhnTotal); - Print to check each step of addition in the terminal
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
            //printf("%d\n", luhnTotal); - Print to check each step of addition in the terminal
        }
    }
    printf("\nluhnTotal = %d\nluhnTotal mod 10 = %d\n", luhnTotal, (luhnTotal % 10));
}