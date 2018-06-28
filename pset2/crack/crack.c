#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

string crack(string hash, string salt);

string passwords[10] = {"50xcIMJ0y.RXo", "50mjprEcqC/ts", "50GApilQSG3E2", "50n0AAUD.pL8g", "50CcfIk1QrPr6",
                        "509nVI8B9VfuA", "50JIIyhDORqMU", "50JGnXUgaafgc", "51u8F0dkeDSbY", "50cI2vYkF0YU2"};
char chars[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                  't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                  'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main(int argc, string argv[])
{
    // Parse args, print usage message on invalid argument(s)
    if (argc != 2)
    {
        argv[1] = passwords[0];
        // printf("Usage: %s [hash]\n", argv[0]);
        // return 1;
    }

    string hash = argv[1];
    string salt = "50";
    string pw;

    printf("'pass' -> '%s'\n", crypt("pass", "50"));

    printf("Input: %s\n", argv[1]);
    pw = crack(hash, salt);
    printf("Output: %s\n", pw);

}

string crack(string hash, string salt)
{
    printf("Hash: %s, Salt: %s\n", hash, salt);
    string test_hash;
    // Check passwords of length 1

    // Outer loop switches lowercase and uppercase, inner loop switches characters
    // char start[2] = {'a', 'A'};
    for (int i = 0; i < sizeof(chars); i++)
    {
        printf("%c", i);
        test_hash = crypt(strcat(&chars[i], &chars[i]), salt);
        printf("%s\n", test_hash);
    }

    return test_hash;
}