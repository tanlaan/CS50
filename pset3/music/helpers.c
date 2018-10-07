// Helper functions for music

#include <cs50.h>

#include "helpers.h"

#include "math.h"

#include <string.h>


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int x, y;
    // tokenizes the passed in string to extract everything up to the "/" then convert from alphanumeric to integer
    x = atoi(strtok(fraction, "/"));
    y = atoi(strtok(NULL, "/"));            // continues to tokenize the same string from the last point it found.

    while (y % 2 == 0)
    {
        if (y == 8)
        {
            return x;                       // The fraction is already in 1/8ths
        }
        else if (y < 8)                     // The fraction is larger than 1/8th, such as 1/4 or 1/2
        {
            x *= 2;
            y *= 2;
        }
        else
        {
            return 0;                       // In this case, we have a fraction smaller than 1/8th such as 1/16th or 1/32nd
        }
    }

    return -1;                              // We should never get here if we are given a fraction divisible by two
}
int semitones_from_a4(string note)
{
    int semitones = 0;
    char letter, octave, adjacent = ' ';
    int l, o;
    letter = note[0];

    if (strlen(note) == 2)
    {
        octave = note[1];
    }
    else                                    // Our note contains an adjacent
    {
        adjacent = note[1];
        octave = note[2];
    }

    switch (letter)                         // Compare the letter of our note to numeric values associated
    {
        case 'C':
            l = 1;
            break;
        case 'D':
            l = 3;
            break;
        case 'E':
            l = 5;
            break;
        case 'F':
            l = 6;
            break;
        case 'G':
            l = 8;
            break;
        case 'A':
            l = 10;
            break;
        case 'B':
            l = 12;
            break;
    }

    if (adjacent == '#')                    // If our note is a sharp we adjust our number up
    {
        l += 1;
    }

    if (adjacent == 'b')                    // If our note is a flat we adjust our number down
    {
        l -= 1;
    }

    o = atoi(&octave);

    semitones = (l - 10) + ((o - 4) * 12);  // A is equivelant to "10" and each octave up or down from 4 is worth 12 notes

    return semitones;
}

// Calculates frequency (in Hz) of a note
// 2**(n/12) * 44 (rounded to whole frequency)
int frequency(string note)
{
    return (int)round(pow(2, (semitones_from_a4(note) / 12.0)) * 440);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (!strcmp(s, ""))                     // Compare passed string to "" (not NULL) to see if rest
    {
        return true;
    }

    else
    {
        return false;
    }
}
