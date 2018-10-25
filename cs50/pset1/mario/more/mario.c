//A program to create a pyramid (a la Super Mario), with a base & height specified by the user. [Max height = 23]

#include <stdio.h>
#include <cs50.h>

//char* hashMaker(int row); - I attempted to create a function to reduce redundancy but quickly found myself confused by how C handles strings/characters

int main(void)
{
    int height = get_int("Height: ");
    if (height > 0 && height <= 23)
    {
        for (int i = 0; i < height; i++)
        {
            for (int k = height - i - 1; k > 0; k--)
            {
                printf(" ");
            }
            //printf("%s", hashMaker(i)); - function would replace the following 4 lines of code, repeated again in lines 26-29
            for (int j = 0; j <= i; j++)
            {
                printf("#");
            }
            printf("  ");
            //printf("%s", hashMaker(i));
            for (int j = 0; j <= i; j++)
            {
                printf("#");
            }
            printf("\n");
        }
    }
    else if (height < 0 || height > 23)
    {
        printf("Invalid entry. Try again:\n");
        main();
    }
}

/*char* hashMaker(int row)
{
    {
        return("#");
    }
    return("");
}*/