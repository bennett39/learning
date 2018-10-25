// Program to read jpgs from a memory card

#include <stdint.h>
#include <stdio.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check command line args
    if (argc != 2)
    {
        fprintf(stderr, "Usage: $ ./recover input");
        return 1;
    }

    // remember file name
    char *infile = argv[1];

    // open & check infile
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // read 512 bytes
    BYTE buffer[512];
    fread(&buffer, 512, 1, inptr); // 512, 1 or 1, 512

    // declare img
    FILE *img = NULL;

    // how many jpgs we've found
    int counter = 0;

    do {
        // check first 4 bytes if jpg
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // if out file is open, close it
            if (counter > 0)
            {
                fclose(img);
            }

            // create & fopen new ###.jpg
            char filename[8];
            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");

            // fwrite 512 bytes to out img file
            fwrite(&buffer, 512, 1, img);

            // increment counter
            counter++;
        }
        else if (counter > 0)
        {
            // fwrite 512 bytes to current img file
            fwrite(&buffer, 512, 1, img);
        }
    }
    // while more than 512 bytes remain
    while (fread(&buffer, 512, 1, inptr) > 0);

    fclose(img);
}