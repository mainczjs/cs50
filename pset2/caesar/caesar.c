#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int strtoint(string s);

int main(int argc, string argv[])
{
    // Print usage, when number of args is not as expected
    if (argc != 2)
    {
        printf("Usage: caesar [distance]\n");
        return 1;
    }
    int distance = strtoint(argv[1]);

    // Get user input
    printf("plaintext: ");
    string inp = get_string();

    for (int i = 0; i < strlen(inp); i++)
    {
        // Handle lowercase input
        if (islower(inp[i]))
        {
            inp[i] -= 'a';
            inp[i] = (inp[i] + distance) % 26;
            inp[i] += 'a';
        }
        // Handle uppercase input
        if (isupper(inp[i]))
        {
            inp[i] -= 'A';
            inp[i] = (inp[i] + distance) % 26;
            inp[i] += 'A';
        }
        // Leave other chars alone
    }
    printf("ciphertext: %s\n", inp);
}

int strtoint(string s)
{
    return (int) strtol(s, (char **)NULL, 10);
}