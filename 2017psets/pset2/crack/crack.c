#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

string crack(string hash);


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("./crack hash\n");
        return 1;
    }
    else
    {
        printf("%s\n", crack(argv[1]));
        return 0;
    }

}

string crack(string hash)
{
    static char plaintext[5];
    // Setting salt to "aa"
    char salt[3] = {'5', '0', '\0'};
    char alpha[52];
    string guess;

    // Initialize alpha array with lower and upper.
    for (int i = 0; i < 26; i++)
    {
        alpha[i] = 97 + i;
        alpha[i + 26] = 65 + i;
    }

    // Run through with only a single character string
    for (int i = 0; i < 52; i++)
    {
        // Set plaintext's first character to the ith value of alpha's set
        plaintext[0] = alpha[i];

        guess = crypt(plaintext, salt);

        if (!strcmp(hash, guess))
        {
            return plaintext;
        }
    }
    // Run through with two character strings
    for (int i = 0; i < 52; i++)
    {

        plaintext[0] = alpha[i];

        for (int j = 0; j < 52; j++)
        {
            plaintext[1] = alpha[j];

            guess = crypt(plaintext, salt);

            // Use strcmp to tell whether the hash and guess are the same (returns 0 for true, so have to use !)
            if (!strcmp(hash, guess))
            {
                return plaintext;
            }
        }
    }

    //Three character strings
    for (int i = 0; i < 52; i++)
    {
        plaintext[0] = alpha[i];

        for (int j = 0; j < 52; j++)
        {

            plaintext[1] = alpha[j];

            for (int k = 0; k < 52; k++)
            {
                plaintext[2] = alpha[k];

                guess = crypt(plaintext, salt);

                // Use strcmp to tell whether the hash and guess are the same (returns 0 for true, so have to use !)
                if (!strcmp(hash, guess))
                {
                    return plaintext;
                }
            }
        }
    }

    // Four character strings - really wish I could remember how to do recursion here...
    for (int i = 0; i < 52; i++)
    {
        plaintext[0] = alpha[i];

        for (int j = 0; j < 52; j++)
        {
            plaintext[1] = alpha[j];

            for (int k = 0; k < 52; k++)
            {

                plaintext[2] = alpha[k];

                for (int l = 0; l < 52; l++)
                {
                    plaintext[3] = alpha[l];

                    guess = crypt(plaintext, salt);

                    // Use strcmp to tell whether the hash and guess are the same (returns 0 for true, so have to use !)
                    if (!strcmp(hash, guess))
                    {
                        return plaintext;
                    }
                }
            }
        }
    }


    return "Failed.\n";

}