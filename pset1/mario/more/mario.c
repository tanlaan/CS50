#include <stdio.h>
#include <cs50.h>

void print_pyramid(int h);
void print_multi_char(char c, int n);

int main(void)
{
    int height; // Outside the while loop so we don't try and initialize several times
    while (true)
    {
        printf("Height:");
        height = get_int();
        if (height < 0 || height > 23)
        {
            // Do nothing and ask for input again
        }
        else
        {
            print_pyramid(height);
            break;
        }
    }
    return 0;
}

void print_pyramid(int h)
{
    // Define the count of each piece of our printed line
    int gap = 2;
    int spaces = h - 1;
    int hashes = 1;
    // Loop through the height of our pyramid, which is also our final width
    for (int i = 0; i < h; i++)
    {
        print_multi_char(' ', spaces);
        print_multi_char('#', hashes);
        print_multi_char(' ', gap);
        print_multi_char('#', hashes);
        putchar('\n');

        spaces--;
        hashes++;
    }
}

void print_multi_char(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        putchar(c);
    }
}