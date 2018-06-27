#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // initialization of coin values
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;

    // Getting user input
    double total = -1.0;
    while (total < 0)
    {
        printf("Change owed: ");
        total = get_float();
    }
    int itotal = round(total / 0.01);

    // Calculating numbers of coins needed
    int n_quarter = itotal / quarter;
    itotal = itotal - quarter * n_quarter;
    // printf("subtotal after quarter: %i (n_quarter=%i, %i in quarter)\n", itotal, n_quarter, n_quarter * quarter);
    int n_dime = itotal / dime;
    itotal = itotal - dime * n_dime;
    // printf("subtotal after dime: %i (n_dime=%i, %i in dimes)\n", itotal, n_dime, n_dime * dime);
    int n_nickel = itotal / nickel;
    itotal = itotal - nickel * n_nickel;
    // printf("subtotal after nickel: %i (n_nickel=%i, %i in nickel)\n", itotal, n_nickel, n_nickel * nickel);
    int n_penny = itotal / penny;
    itotal -= penny * n_penny;
    // printf("subtotal after penny: %i (n_penny=%i, %i in pennies)\n", itotal, n_penny, n_penny * penny);

    // printf("%f = %i quarters, %i dimes, %i nickels, %i pennies\n", total, n_quarter, n_dime, n_nickel, n_penny);
    printf("%i\n", n_quarter + n_dime + n_nickel + n_penny);
}