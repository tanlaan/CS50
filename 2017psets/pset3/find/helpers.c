/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include "helpers.h"
// Size of array based on MAX + 1
const int COUNTMAX = 65537;

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm

    // Create high and low variables
    int low = 0, mid = 0, high = n - 1;
    int temp = 0;

    while (high >= low)
    {

        mid = (high + low) / 2; // Mid is the average of high and low
        temp = values[mid]; // Reduce calls to check array value

        // If we found it, return true
        if (value == temp)
        {
            return true;
        }
        // Value is less than our number, so reduce high's value
        else if (value < temp)
        {
            high = mid - 1;
        }
        // Else we need to adjust our low value
        else
        {
            low = mid + 1;
        }
    }
    // We ran out of options and fell out of the while loop
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    if ( n == 1)
    {
        return;
    }
    int output[n];
    int count[COUNTMAX];

    // Initialize array to 0's
    for (int i = 0; i <= COUNTMAX; i++)
    {
        count[i] = 0;
    }

    // Run through values and increment their respective value pair in ints
    for (int i = 0; i < n; i++)
    {
        count[values[i]] += 1;
    }

    // Initialized running total
    int total = 0;
    int oldCount = 0;
    // Set total to running total of matches
    for (int i = 0; i <= COUNTMAX; i++)
    {
        oldCount = count[i];
        count[i] = total;
        total += oldCount;
    }

    // Go through values[] and for each number, set output's ith value and reduce count's ith to reflect next position when found
    // Referenced Wikipedia  page to understand the algorithm more
    for (int i = 0; i < n; i++)
    {
        output[count[values[i]]] = values[i];
        count[values[i]]++;
    }

    // Transfer sorted values back to values[] due to void return
    for (int i = 0; i < n; i++)
    {
        values[i] = output[i];
    }
    return;
}
