// Helper functions for music synthesizing

#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to X eighths
int duration(string fraction)
{
    int x = atoi(&fraction[0]);
    int y = atoi(&fraction[2]);

    x = (8 / y) * x;

    return x;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char whiteKey = 'A';
    whiteKey = note[0];

    char accidental[2] = "";
    if (strlen(note) == 3)
    {
        accidental[0] = note[1];
    }

    int octave = atoi(&note[strlen(note) - 1]);
    long double freq = 440.00;
    const char keys[] = "C#D#EF#G#A#B";

    int index = strchr(keys, whiteKey) - keys - 9; //Subtract 9 b/c C-G are lower than A & A is at 9th index in array
    long double n = (double) index / 12.00;

    //Change white key:
    freq *= pow(2.00, n);

    //Change octaves:
    if (octave - 4 > 0)
    {
        for (int i = octave - 4; i > 0; i--)
        {
            freq *= 2;
        }
    }
    else if (octave - 4 < 0)
    {
        for (int i = octave - 4; i < 0; i++)
        {
            freq /= 2;
        }
    }

    //Change accidentals
    if (accidental[0] == '#')
    {
        freq *= pow(2.00, .08333);
    }
    else if (accidental[0] == 'b')
    {
        freq /= pow(2.00, .08333);
    }

    return round(freq);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strncmp(s, "", 1) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
