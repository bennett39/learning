//A program to crack simple passwords that use crypt.
//I know there has to be some type of recursive function to make this work better, but I'm happy just to have a working program.

#define _XOPEN_SOURCE

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int checkCrypt(string hash, string shadow);

int main(int argc, string argv[])
{
    //More or less than one argument yields error and quits program.
    if (argc != 2)
    {
        printf("Enter one string as the encrypted password.\n");
        return 1;
    }

    //Salt is first two digits of argv[1]
    char salt[3];
    salt[0] = (char) argv[1][0];
    salt[1] = (char) argv[1][1];
    salt[2] = '\0';

    char key[6];
    string alphabet = "etaoinsrhldcuETAOINSRHLDCUmfpgwybvkxjqzMFPGWYBVKXJQZ";

    //Crack a password of a single alpha character [a-zA-Z]
    for (int i = 0; i < 52; i++)
    {
        key[0] = alphabet[i];
        key[1] = '\0';

        if ((checkCrypt(crypt(key, salt), argv[1])) == 0)
        {
            goto end_nested_loop;
        }
    }

    //Two character passwords:
    for (int i = 0; i < 52; i++)
    {
        key[0] = alphabet[i];

        for (int j = 0; j < 52; j++)
        {

            key[1] = alphabet[j];
            key[2] = '\0';

            if ((checkCrypt(crypt(key, salt), argv[1])) == 0)
            {
                goto end_nested_loop;
            }
        }
    }

    //Three character passwords:
    for (int i = 0; i < 52; i++)
    {
        key[0] = alphabet[i];

        for (int j = 0; j < 52; j++)
        {
            key[1] = alphabet[j];

            for (int k = 0; k < 52; k++)
            {
                key[2] = alphabet[k];
                key[3] = '\0';

                if ((checkCrypt(crypt(key, salt), argv[1])) == 0)
                {
                    goto end_nested_loop;
                }
            }
        }
    }

    //Four character passwords:
    for (int i = 0; i < 52; i++)
    {
        key[0] = alphabet[i];

        for (int j = 0; j < 52; j++)
        {
            key[1] = alphabet[j];

            for (int k = 0; k < 52; k++)
            {
                key[2] = alphabet[k];
                for (int l = 0; l < 52; l++)
                {
                    key[3] = alphabet[l];
                    key[4] = '\0';

                    if ((checkCrypt(crypt(key, salt), argv[1])) == 0)
                    {
                        goto end_nested_loop;
                    }
                }
            }
        }
    }

    //Five character passwords:
    for (int i = 0; i < 52; i++)
    {
        key[0] = alphabet[i];

        for (int j = 0; j < 52; j++)
        {
            key[1] = alphabet[j];

            for (int k = 0; k < 52; k++)
            {
                key[2] = alphabet[k];
                for (int l = 0; l < 52; l++)
                {
                    key[3] = alphabet[l];

                    for (int m = 0; m < 52; m++)
                    {
                        key[4] = alphabet[m];
                        key[5] = '\0';

                        if ((checkCrypt(crypt(key, salt), argv[1])) == 0)
                        {
                            goto end_nested_loop;
                        }
                    }
                }
            }
        }
    }

end_nested_loop:
    printf("%s\n", key);
}

//Check if hash matches input, character by character
int checkCrypt(string hash, string shadow)
{
    int x = 0;

    do
    {
        if (hash[x] == shadow[x])
        {
            x++;
        }
        else
        {
            return 1;
        }
    }
    while (x < strlen(shadow));

    return 0;
}