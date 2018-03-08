#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // Get name from user
    string name = get_string();
    char prev = ' ';
    char cur = ' ';
    for(int i = 0, n = strlen(name); i < n; i++)
    {
        cur = name[i];
        // Only if our last character was a space and our current is not
        if (prev == ' ' && cur != ' ')
        {
            printf("%c", toupper(cur));
        }

        prev = cur;

    }
    printf("\n");


}