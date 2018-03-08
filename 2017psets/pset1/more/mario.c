#include <stdio.h>
#include <cs50.h>

void print_pyramid(int n);
void print_char(char c, int n);


int main(void)
{
    int n;

    do
    {
        printf("Height: ");
        n = get_int();

    }
    while ( n < 0 || n > 23);

    print_pyramid(n);

}

void print_pyramid(int n)
{
    for (int i = 0; i < n; i++)
    {

        print_char(' ', (n - i - 1));
        print_char('#', (i + 1));
        print_char(' ', 2);
        print_char('#', (i + 1));
        printf("\n");


    }
}

void print_char(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}