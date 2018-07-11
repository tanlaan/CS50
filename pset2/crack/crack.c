#include <stdio.h>
#include <cs50.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>

char *crypt(const char *key, const char *salt);
void crack(string hash, char clear[]);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Either too many or too few arguments. Example: ./crack 12345\n");
        return 1;
    }
    else
    {
        string hash = argv[1];
        char clear[6];
        crack(hash, clear);
        printf("%s\n", clear);
        return 0;
    }

}

void crack(string hash, char clear[])
{
    char alpha_chars[52];
    int i, a;
    for (i = 0, a = 65; i < 26; i++, a++)
    {
        alpha_chars[i] = a;
    }
    for (i = 26, a = 97; i < 52; i++, a++)
    {
        alpha_chars[i] = a;
    }

    int depth = 0;
    for (i = 0; i < 52; i++)
    {
        if (depth < 4)
        {
            i = -1;
        }
        else
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
                    for (int m = 0; m < 52; m++)
                    {
                        clear[depth] = alpha_chars[m];
                        clear[depth + 1] = '\0';
                        if (strcmp(crypt(clear, "50"), hash) == 0)
                        {
                            return;
                        }

                    }
                    if (depth == 0)
                    {
                        depth++;
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