// Helper functions for music

#include <cs50.h>

// Converts a fraction to eighths
int duration(string fraction);

// Converts a string to semitones from the note A4
// in the form of a two character or three character string
// e.g. A5 or Bb2
int semitones_from_a4(string note);

// Calculates frequency (in Hz) of a note formatted as XY,
// where X is any of A through G and Y is any of 0 through 8,
// or formatted as XYZ, where X is any of A through G, Y is # or b,
// and Z is any of 0 through 8
int frequency(string note);

// Determines whether a string represents a rest
bool is_rest(string s);
