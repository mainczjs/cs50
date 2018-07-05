// Helper functions for music
#include <string.h>
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include "helpers.h"
#define A4_FREQ 440
#define A4_BASE 'A'
#define A4_OCTAVE 4

// Converts a fraction formatted as X/Y to eighths
// duration("1/8") -> 1
// duration("1/4") -> 2
// duration("1/2") -> 3
int duration(string fraction)
{
    // error checking: a valid fraction has at least 3 chars
    if ((strlen(fraction) < 3))
    {
        return -1;
    }
    else
    {
        int *num = malloc(sizeof(int));
        int *den = malloc(sizeof(int));
        sscanf(strtok(fraction, "/"), "%i", num);
        sscanf(strtok(NULL, "/"), "%i", den);
        return (int)(((double) * num / *den) * 8);
    }
}

// Calculates frequency (in Hz) of a note
// frequency("A4") = 440
int frequency(string note)
{
    int semitones = 0;
    int *octave = malloc(sizeof(int));
    char base = note[0];
    if (note[1] == '#')
    {
        // note is elevated by a half-step
        semitones = 1;
        sscanf(&note[2], "%i", octave);
    }
    else if (note[1] == 'b')
    {
        // note is lowered by a half-step
        semitones = -1;
        sscanf(&note[2], "%i", octave);
    }
    else
    {
        semitones = 0;
        sscanf(&note[1], "%i", octave);
    }
    semitones += (base - 'A') * 2;
    // between H/B and C is only single half-step!
    if (base >= 'C')
    {
        semitones -= 1;
    }
    // between E and F is only single half-step!
    if (base >= 'F')
    {
        semitones -= 1;
    }
    // freq = 2^(n/12) * 440, n = # of semitones from A4
    // n = (4-octave)*12 + semitones
    int frequency = (int)round(pow(2, ((*octave - A4_OCTAVE) * 12 + semitones) / 12.0) * A4_FREQ);
    // printf("base=%c\tsemitones=%i\toctave=%i\n", base, semitones, *octave);
    return frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strlen(s) == 0)
    {
        return true;
    }
    return false;
}