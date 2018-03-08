#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void caesar(long int n, string s);
void print_rotated(int n, char s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error: This program only takes a single number.\n");
        return 1;
    }
    else
    {
        printf("plaintext:  ");
        string s = get_string();
        printf("ciphertext: ");
        char *ptr; // Pointer required for strtol() to work
        // Convert our argv number from a string to a long int so we can use it with our other functions and pass it along
        caesar(strtol(argv[1], &ptr, 10), s);
        return 0;
    }
}

void caesar(long int n, string s)
{
    // Loop through the characters in the plaintext
    for(int i = 0, len = strlen(s); i < len; i++)
    {
        print_rotated(n, s[i]);
    }
    printf("\n");
}

void print_rotated(int n, char c)
{

    if(islower(c))
    {
        // Convert to base 26, modulo with 26, convert back to ascii
        printf("%c", ((((c - 97) + n) % 26) + 97));
    }
    else if (isupper(c))
    {
        // Convert to base 26, modulo with 26, convert back to ascii
        printf("%c", ((((c - 65) + n) % 26) + 65 ));
    }
    else
    {
        // All non alphanumeric characters don't get rotated
        printf("%c", c);
    }
}
