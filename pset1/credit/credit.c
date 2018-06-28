#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool has_n_digits(long num, int digits);
long starts_with(long num, long start);
bool luhn(long num);
bool validity_check(long num);

int main(void)
{
    // Ask user for credit card number
    printf("Number: ");
    long num = get_long_long();

    // Run validity check
    validity_check(num);
}

// Check, whether num has n digits. Return true if it has, otherwise return false!
bool has_n_digits(long num, int digits)
{
    // cut off assumed number of digits
    int quotient = num / pow(10, digits - 1);
    // check, whether remainder is in [1;9]
    return ((quotient > 0) && (quotient <= 9));
}

// Check, whether num starts with start. Return true if it does, otherwise return false!
long starts_with(long num, long start)
{
    while (num)
    {
        if (num == start)
        {
            return true;
        }
        // num too big, cut off last digit!
        num /= 10;
    }
    // num did not match start!
    return false;
}

bool luhn(long num)
{
    long cur_digit;
    long sum_mult = 0;
    long sum_not_mult = 0;
    int i = 0;

    while (num)
    {
        cur_digit = num % 10;
        if (i % 2 == 0)
        {
            // printf("%li is uneven digit! Will add it to sum!\n", cur_digit);
            sum_not_mult += cur_digit;
        }
        else
        {
            long mult_by_two = 2 * cur_digit;
            // printf("%li is even digit! Adding up digits of %li equals ", cur_digit, mult_by_two);
            while (mult_by_two)
            {
                sum_mult += mult_by_two % 10;
                mult_by_two /= 10;
            }
            // printf("%li\n", sum_mult);
        }
        num /= 10;
        i++;
    }
    // printf("CC: %li+%li=%li\n", sum_mult, sum_not_mult, sum_mult + sum_not_mult);
    if ((sum_mult + sum_not_mult) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool validity_check(long num)
{
    if (luhn(num))
    {
        // printf("%li passes Luhn's Algorithm! Will check for institute now!\n", num);

        // AMEX has 15 digits and starts with 34 or 37
        if (has_n_digits(num, 15) && (starts_with(num, 34) == 3 || starts_with(num, 37)))
        {
            printf("AMEX\n");
            return true;
        }

        // VISA has 13 or 16 digits and starts with a 4
        if ((has_n_digits(num, 16) || has_n_digits(num, 13)) && starts_with(num, 4))
        {
            printf("VISA\n");
            return true;
        }

        // MasterCard has 16 digits and starts with one of 51, 52, ..., 55
        if (has_n_digits(num, 16) && (starts_with(num, 51) || starts_with(num, 52) ||
                                      starts_with(num, 53) || starts_with(num, 54) ||
                                      starts_with(num, 55)))
        {
            printf("MASTERCARD\n");
            return true;
        }
    }
    printf("INVALID\n");
    return false;
}