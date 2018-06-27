#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool has_n_digits(long num, int digits)
{
    int quotient = num / pow(10, digits-1);
    if ((quotient > 0) && (quotient <= 9))
    {
        return true;
    } else {
        return false;
    }
}

bool is_valid(long num)
{
    //TODO: implement luhns algorithm
}

bool determine_cc_type(long num)
{
    // AMEX starts with 34 or 37
    // MasterCard starts with 51..55
    // VISA starts with a 4
    if (is_valid(num))
    {
        if (has_n_digits(num, 15))  // AMEX
        {
            printf("AMEX\n");
            return true;
        }
        if (has_n_digits(num, 16) || has_n_digits(num, 13)) // VISA or MasterCard
        {
            printf("VISA\n");
            return true;
        }
    }
    else
    {
        printf("INVALID\n")
        return false;
    }
}

int main(void)
{
    printf("Number: ");
    long num = get_long_long();
    // printf("You entered: %li\n", num);

    if (determine_cc_type(num) == false)
    {
        printf("INVALID\n");
    }
    else
    {
        printf("VALID\n");
    }
}