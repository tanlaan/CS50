// Credit: take in a number, check whether it is a valid credit card number.
// Say which company the card is from or INVALID

#include <stdio.h>
#include <cs50.h>

int digit_count(long long num);
void longlong_to_array(int array[], long long num, int length);
int get_first_digits(long long num, int length);
bool test_luhn(int array[], int length);

int main(void)
{
    printf("Number: ");
    long long card = get_long_long();

    // Identify how many digits we have
    int digits = digit_count(card);

    // Create an array the "length" of our number in digits
    int digit_array[digits];

    // Insert each digit of the number entered into the array
    longlong_to_array(digit_array, card, digits);

    // Get the first two digits of the number to check against (one in the case of starting with 4)
    int first_digits = get_first_digits(card, digits);

    // filter out the specific values of digits we want
    // Verify number passes luhn test
    if (test_luhn(digit_array, digits))
    {
        // Check lengths
        switch (digits)
        {
            case 13:
            {
                if (first_digits == 4)
                {
                    printf("VISA\n");
                    break;
                }
            }
            case 15:
            {
                if (first_digits == 34 || first_digits == 37)
                {
                    printf("AMEX\n");
                    break;
                }

            }
            case 16:
            {
                switch (first_digits)
                {
                    case 4:
                    {
                        printf("VISA\n");
                        break;
                    }
                    case 51:
                    case 52:
                    case 53:
                    case 54:
                    case 55:
                    {
                        printf("MASTERCARD\n");
                        break;
                    }
                    default:
                        printf("INVALID\n");
                }
                break;
            }
            default:
                printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int digit_count(long long num)
{
    int count = 0;
    while (num > 0)
    {
        num /= 10;  // Slice a digit off the end
        count += 1; // Increase our digit count
    }

    if (num < 0)
    {
        count = -1; // Just in case a negative number is passed for some reasone we can check for it at a later date
    }

    return count;
}

void longlong_to_array(int array[], long long num, int length)
{
    for (int i = length - 1; i >= 0; i--)   // Start from the end of the array and move towards the 0th digit
    {
        array[i] = num % 10;                // Insert last number of the current num
        num /= 10;                          // Strip one digit off the end
    }
    return;
}

int get_first_digits(long long num, int length)
{
    int digits = 0;
    long long temp = 1;
    for (int i = 0; i < length - 2; i++)
    {
        temp *= 10;
    }
    digits = (int)(num / temp);

    if (digits / 10 == 4)
    {
        digits = 4; // case for VISA
    }

    return digits;
}

bool test_luhn(int array[], int length)
{
    int prod_counter, sum_counter, sum = 0; // Counter offset by one for each set we will need to add together later

    if (length % 2 == 0)    // If the number is an even number of digits, the products start at the first digit
    {
        prod_counter = 0;
        sum_counter = 1;
    }
    else                    // Else they start at the second digit
    {
        prod_counter = 1;
        sum_counter = 0;
    }

    // Loop to add products of digit * 2
    for (; prod_counter < length; prod_counter += 2)
    {
        if (array[prod_counter] > 4) // exception for when the product is greater than 9, we add the tens and ones digit together.
        {
            sum += 1 + ((array[prod_counter] * 2) % 10);
        }
        else
        {
            sum += array[prod_counter] * 2;
        }
    }

    // Loop to add the other digits to the sum
    for (; sum_counter < length; sum_counter += 2)
    {
        sum += array[sum_counter];
    }

    if (sum % 10 == 0)  // If sum evenly divisible by 10 we have a valid card
    {
        return true;
    }
    else                // Otherwise we don't
    {
        return false;
    }
}