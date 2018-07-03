#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cs50.h>
#include <crypt.h>
#include <time.h>
#define _XOPEN_SOURCE
#include <unistd.h>

static const char alphabet[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const string HASH = "50JGnXUgaafgc";

static const int alphabet_size = sizeof(alphabet) - 1;

int check(string pw, string hash)
{
    char salt[3] = {hash[0], hash[1], '\0'};
    if (strcmp(crypt(pw, salt), "50JGnXUgaafgc") == 0)
    {
        printf("%s (salt: %s) -> %s\n", hash, salt, pw);
        return 1;
    }
    return 0;
}

int brute_impl(char * str, int index, int max_depth)
{
    int i;
    for (i = 0; i < alphabet_size; ++i)
    {
        str[index] = alphabet[i];

        if (index == max_depth - 1)
        {
            if (check(str, HASH))
            {
                return 1;
            }
        }
        else
        {
            if (brute_impl(str, index + 1, max_depth))
            {
                return 1;
            }
        }
    }
    return 0;
}

void brute_sequential(int max_len)
{
    char * buf = malloc(max_len + 1);
    int i;

    for (i = 1; i <= max_len; ++i)
    {
        memset(buf, 0, max_len + 1);
        if (brute_impl(buf, 0, i))
        {
            return;
        }
    }
    free(buf);
}

int main()
{
    clock_t clk_start = clock();
    brute_sequential(4);
    clock_t clk_end = clock();
    printf("crackso() returned in %2.2fs\n", (clk_end - clk_start) / 1000000.0);
    return 0;
}