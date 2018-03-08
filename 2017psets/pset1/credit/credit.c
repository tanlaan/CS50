#include <stdio.h>
#include <cs50.h>

bool checksum(long long card);
void check_company(long long card);
int starts_with(long long card);
int digit_length(long long card);

int main(void)
{
    printf("Number: ");
    long long card = get_long_long();

    if (checksum(card))
    {
        check_company(card);
    }
    else
    {
        printf("INVALID\n");
    }

}

bool checksum(long long card)
{
    // 0. Multiply every other digit by 2, starting with the number's
    // second to last digit. Add those together
    // 1. Add the sum to the sum of the digits that weren't multiplied
    int i = 1;
    int d = 0;
    int even = 0;
    int odd = 0;
    int total = 0;
    for (long long temp = card; temp > 0; temp = temp / 10)
    {
        d = temp % 10;

        if (i % 2 == 0)
        {
            // even
            if ( (d * 2) > 9)
            {
                int dd = d * 2;
                even += (dd) % 10;
                dd = dd / 10;
                even += (dd) % 10;
            }
            else
            {
                even += d * 2;
            }
        }
        else
        {
            // odd
            odd += d;

        }
        i++;
    }
    total = even + odd;

    // 2. If the total's last digit is 0, the number is valid
    if (total % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

void check_company(long long card)
{

    switch (starts_with(card))
    {
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49://Visa
            if (digit_length(card) == 13 || digit_length(card) == 16)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
            break;
        case 34:
        case 37: //American Express
            if (digit_length(card) == 15)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
            break;
        case 51:
        case 52:
        case 53:
        case 54:
        case 55: //Master Card
            if (digit_length(card) == 16)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
            break;
        default:
            printf("INVALID\n");
    }

}

int starts_with(long long card)
{
    while (card > 100)
    {
        card = card / 10;
    }
    int start = (int) card;
    return start;
}

int digit_length(long long card)
{
    int length = 0;
    while (card > 0)
    {
        card = card / 10;
        length = length + 1;
    }

    return length;
}