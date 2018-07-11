#include <stdio.h>
#include <cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>

char *crypt(const char *key, const char *salt);
void crack(string hash, char clear[]);

int main(int argc, string argv[])
{
    if (argc != 2)              // Failed to give correct amount of arguments
    {
        printf("Either too many or too few arguments. Example: ./crack 12345\n");
        return 1;
    }
    else
    {
        string hash = argv[1];  // Get hash string from command line argument
        char clear[6];          // Cleartext variable
        crack(hash, clear);     // Brute force cleartext
        printf("%s\n", clear);  // Print it to screen
        return 0;
    }

}

void crack(string hash, char clear[])
{
    char alpha_chars[52];                   // Array for all alphanumeric characters
    int i, a;                               // Counter vars
    for (i = 0, a = 65; i < 26; i++, a++)   // First loop through of capital leters
    {
        alpha_chars[i] = a;
    }
    for (i = 26, a = 97; i < 52; i++, a++)  // Second loop through for lowercase letters
    {
        alpha_chars[i] = a;
    }

    int depth = 0;                          // Set depth to zero to only start inner for loop
    for (i = 0; i < 52; i++)
    {
        if (depth < 4)  // Used to make sure that the "first run" that counts is the following run. i will equal 0 twice
        {
            i = -1;
        }
        else            // Once we've passed through all the inner loops once we continue normally
        {
            clear[depth - 4] = alpha_chars[i];
        }

        for (int j = 0; j < 52; j++)
        {
            if (depth < 3)
            {
                j = -1;
            }
            else
            {
                clear[depth - 3] = alpha_chars[j];
            }
            for (int k = 0; k < 52; k++)
            {
                if (depth < 2)
                {
                    k = -1;
                }
                else
                {
                    clear[depth - 2] = alpha_chars[k];
                }
                for (int l = 0; l < 52; l++)
                {
                    if (depth < 1)
                    {
                        l = -1;
                    }
                    else
                    {
                        clear[depth - 1] = alpha_chars[l];
                    }
                    for (int m = 0; m < 52; m++)                    // Inner most loop
                    {
                        clear[depth] = alpha_chars[m];              // First run depth = 0 and m = 0
                        clear[depth + 1] = '\0';                    // End character in array is set to EOL
                        if (strcmp(crypt(clear, "50"), hash) == 0)  // Compare strings of encrypted clear and original hash
                        {
                            return;                                 // Success
                        }

                    }
                    if (depth == 0)                                 // We must increase depth after our first run through to
                    {
                        depth++;                                    // go from 1 character to 2
                    }
                }
                if (depth == 1)
                {
                    depth++;
                }
            }
            if (depth == 2)
            {
                depth++;
            }
        }
        if (depth == 3)
        {
            depth++;
        }
    }
    clear = "FAIL";
    return;
}