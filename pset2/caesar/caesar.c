#include <stdio.h>
#include <cs50.h>

string caesar(string plain, int key);
char alpha_offset(char c, int n);

int main(int argc, char *argv[])
{
    if (argc == 2)                              // If and only if we have one argument following our call to run do we procede
    {
        printf("plaintext:  ");                 // Print so user recognises what to type
        string plain = get_string();            // Get plaintext to convert

        int key = atoi(argv[1]);                // Take key from command line argument
        string cipher = caesar(plain, key);     // Convert plaintext to cipher text

        printf("ciphertext: %s\n", cipher);     // Print to screen
        return 0;
    }
    else
    {
        return 1;                               // Error
    }
}

string caesar(string plain, int key)
{
    string cipher = plain;                                      // Initialize key
    int counter = 0;                                            // Set counter to zero
    while (plain[counter] != '\0')                              // While not EOL
    {
        cipher[counter] = alpha_offset(plain[counter], key);    // Cipher = offset plaintext char
        counter++;                                              // Increase counter to go to next char
    }
    return cipher;                                              // Return the new cipher string
}

char alpha_offset(char c, int n)
{
    if (c >= 'a' && c <= 'z')                   // If lowercase offset within bounds
    {
        c = (((c - 96) + n) % 26) + 96;
        return c;
    }
    else if (c >= 'A' && c <= 'Z')              // Else if uppercase offset within bounds
    {
        c = (((c - 64) + n) % 26) + 64;
        return c;
    }
    else                                        // Else non alphabetic character, return original character
    {
        return c;
    }
}