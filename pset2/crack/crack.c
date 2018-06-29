#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

string crack(string, string);
string crackn(string, string, int);
int check(string, string, string);

string hashes[10] = {"50xcIMJ0y.RXo", "50mjprEcqC/ts", "50GApilQSG3E2", "50n0AAUD.pL8g", "50CcfIk1QrPr6",
                     "509nVI8B9VfuA", "50JIIyhDORqMU", "50JGnXUgaafgc", "51u8F0dkeDSbY", "50cI2vYkF0YU2"
                    };

char alpha[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                  't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                  'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
                 };

const int ALPHABET_SIZE = sizeof(alpha);
const int MAX_PW_LENGTH = 5;

int main(int argc, string argv[])
{
    // Parse args, print usage message on invalid argument(s)
    if (argc != 2)
    {
        // Debugging: crack list of hashes
        for (int i = 0; i < sizeof(hashes); i++)
        {
            char salt[3] = {hashes[i][0], hashes[i][1], '\0'};
            string pw = crack(hashes[i], salt);
            if (strcmp(pw, "") != 0)
            {
                printf("%s (salt: %s) -> %s\n", hashes[i], salt, pw);
                continue;
            }
            else
            {
                printf("%s could not be found!\n", hashes[i]);
            }
        }

        // Regular: Print usage and return with error.
        // printf("Usage: %s [hash]\n", argv[0]);
        // return 1;
    }


    // printf("Input: %s\n", argv[1]);
    char salt[3] = {argv[1][0], argv[1][1], '\0'};
    string pw = crack(argv[1], salt);
    if (strcmp(pw, "") != 0)
    {
        printf("%s\n", pw);
        return 0;
    }
    return 1;
}

// Try all possible passwords with length up to MAX_PW_LENGTH.
// Return password as string if found.
// Return empty string otherwise.
string crack(string hash, string salt)
{
    for (int n = 1; n <= MAX_PW_LENGTH; n++)
    {
        // Debugging Output
        // printf("Trying %i-letter passwords!\n", n);

        // put var on heap instead of stack to be able to use it as return val
        // per https://stackoverflow.com/questions/34227581/
        char *pw = malloc(5 * sizeof(char *));
        pw = crackn(hash, salt, n);
        if (strcmp(pw, "") != 0)
        {
            return pw;
        }
    }
    return "";
}

// Try all possible passwords of length n for hash, encrypted with salt.
// Returns password as string if found.
// Returns empty string otherwise.
string crackn(string hash, string salt, int num)
{
    // put var on heap instead of stack to be able to use it as return val
    // per https://stackoverflow.com/questions/34227581/
    char *pw = malloc((MAX_PW_LENGTH+1) * sizeof(char *));
    // Generate all possible 1-letter words
    if (num == 1)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            pw[0] = alpha[i];
            pw[1] = '\0';
            if (check(pw, hash, salt))
            {
                return pw;
            }
        }
    }
    // Generate all possible 2-letter words
    else if (num == 2)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            for (int j = 0; j < ALPHABET_SIZE; j++)
            {
                pw[0] = alpha[i];
                pw[1] = alpha[j];
                pw[2] = '\0';
                if (check(pw, hash, salt))
                {
                    return pw;
                }
            }
        }
    }
    // Generate all possible 3-letter words
    else if (num == 3)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            for (int j = 0; j < ALPHABET_SIZE; j++)
            {
                for (int k = 0; k < ALPHABET_SIZE; k++)
                {
                    // create password from chars
                    pw[0] = alpha[i];
                    pw[1] = alpha[j];
                    pw[2] = alpha[k];
                    pw[3] = '\0';
                    if (check(pw, hash, salt))
                    {
                        return pw;
                    }
                }
            }
        }
    }
    // Generate all possible 4-letter words
    else if (num == 4)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            for (int j = 0; j < ALPHABET_SIZE; j++)
            {
                for (int k = 0; k < ALPHABET_SIZE; k++)
                {
                    for (int l = 0; l < ALPHABET_SIZE; l++)
                    {
                        // create password from chars
                        pw[0] = alpha[i];
                        pw[1] = alpha[j];
                        pw[2] = alpha[k];
                        pw[3] = alpha[l];
                        pw[4] = '\0';
                        if (check(pw, hash, salt))
                        {
                            return pw;
                        }
                    }
                }
            }
        }
    }
    // Generate all possible 5-letter words
    else if (num == 5)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            for (int j = 0; j < ALPHABET_SIZE; j++)
            {
                for (int k = 0; k < ALPHABET_SIZE; k++)
                {
                    for (int l = 0; l < ALPHABET_SIZE; l++)
                    {
                        for (int m = 0; m < ALPHABET_SIZE; m++)
                        {
                            // create password from chars
                            pw[0] = alpha[i];
                            pw[1] = alpha[j];
                            pw[2] = alpha[k];
                            pw[3] = alpha[l];
                            pw[4] = alpha[m];
                            pw[5] = '\0';
                            if (check(pw, hash, salt))
                            {
                                return pw;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        eprintf("Maximum supported length is 5!\n");
    }
    return "";
}

// Encrypt password with salt and compare to hash
// If hashes match, return true. Otherwise, false.
int check(string pw, string hash, string salt)
{
    if (strcmp(crypt(pw, salt), hash) == 0)
    {
        // Debugging output
        // printf("%s (salt: %s) -> %s\n", hash, salt, pw);
        return 1;
    }
    return 0;
}