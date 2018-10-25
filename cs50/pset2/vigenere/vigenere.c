// A program that encrypts messages using Vigenere's cypher

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    //More or less than one argument yields error and quits program.
    if (argc != 2)
    {
        printf("Enter one word as the secret key.\n");
        return 1;
    }

    //If characters in keyphrase are not alphabetical, give error.
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]) == false)
        {
            printf("Alphabetic characters only, please.\n");
            return 1;
        }
    }

    //After successful key, prompt user for plaintext entry.
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    //Vigenere's cypher implemented as nested if statements within a for loop
    for (int j = 0, o = strlen(plaintext), k = strlen(argv[1]), alphaCount = 0; j < o; j++)
    {

        //Print non-alphabetic characters directly with no cypher
        if (isalpha(plaintext[j]) == false)
        {
            printf("%c", plaintext[j]);
        }

        //Encypher all alphabetic characters
        else
        {
            //ASCII integer of the character + current keyword position.
            //Subtract one so 'a' yields 0, 'b' yields 1, ... 'z' yields 25
            int newChar = ((int) plaintext[j] + ((int) argv[1][alphaCount % k]) % 32 - 1);

            //Uppercase rules:
            if (isupper(plaintext[j]))
            {
                if (newChar > 90)
                {
                    printf("%c", (char)(newChar - 26));
                }
                else
                {
                    printf("%c", (char) newChar);
                }
                alphaCount++;
            }

            //Lowercase rules:
            else
            {
                if (newChar > 122)
                {
                    printf("%c", (char)(newChar - 26));
                }
                else
                {
                    printf("%c", (char) newChar);
                }
                alphaCount++;
            }
        }
    }
    printf("\n");
}