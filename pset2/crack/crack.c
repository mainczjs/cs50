#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypt.h>
#include <time.h>
#define _XOPEN_SOURCE
#define MAX_PW_LENGTH 5


string crack(string);
string crackn(string, int);
int check(string, string);
void crack_list();

const string hashes[10] = {"50xcIMJ0y.RXo", "50mjprEcqC/ts", "50GApilQSG3E2",
                           "50n0AAUD.pL8g", "50CcfIk1QrPr6", "509nVI8B9VfuA",
                           "50JIIyhDORqMU", "50JGnXUgaafgc", "51u8F0dkeDSbY",
                           "50cI2vYkF0YU2"
                          };

const char alpha[] = "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const int ALPHABET_SIZE = sizeof(alpha) - 1;

int main(int argc, string argv[])
{
    // DEBUG: Take time it takes to crack password
    // clock_t clk_start = clock();

    // Parse args, print usage message on invalid argument(s)
    if (argc != 2)
    {
        // DEBUG: Crack single hash
        // argv[1] = "50JGnXUgaafgc"; // 4-letter password ("ROFL")
        // argv[1] = "50GApilQSG3E2"; // 5-letter password (???)

        // DEBUG: Crack list of hashes
        // crack_list();

        // Production Code
        printf("Usage: %s [hash]\n", argv[0]);
        return 1;
    }


    // printf("Input: %s\n", argv[1]);

    string pw = crack(argv[1]);
    if (strcmp(pw, "") != 0)
    {
        // clock_t clk_end = clock();
        // double runtime = (clk_end - clk_start) / 1000000.0;
        // printf("%s found in %2.2fs\n", pw, runtime);
        printf("%s\n", pw);
        return 0;
    }
    // printf("No password found in %2.2fs\n", ((clock_t) clock() - clk_start) / 1000000.0);
    return 1;
}

// Try all possible passwords with length up to MAX_PW_LENGTH.
// Return password as string if found.
// Return empty string otherwise.
string crack(string hash)
{
    for (int n = 1; n <= MAX_PW_LENGTH; n++)
    {
        // Debugging Output
        // printf("Trying %i-letter passwords!\n", n);

        // put var on heap instead of stack to be able to use it as return val
        // per https://stackoverflow.com/questions/34227581/
        char *pw = malloc((MAX_PW_LENGTH + 1));
        pw = crackn(hash, n);
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
string crackn(string hash, int num)
{
    // put var on heap instead of stack to be able to use it as return val
    // per https://stackoverflow.com/questions/34227581/
    char *pw = malloc((MAX_PW_LENGTH + 1) * sizeof(char *));
    // Generate all possible 1-letter words
    if (num == 1)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            // create 1-letter password from chars
            pw[0] = alpha[i];
            pw[1] = '\0';
            if (check(pw, hash))
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
                // create 2-letter password from chars
                pw[0] = alpha[i];
                pw[1] = alpha[j];
                pw[2] = '\0';
                if (check(pw, hash))
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
                    // create 3-letter password from chars
                    pw[0] = alpha[i];
                    pw[1] = alpha[j];
                    pw[2] = alpha[k];
                    pw[3] = '\0';
                    if (check(pw, hash))
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
                        // create 4-letter password from chars
                        pw[0] = alpha[i];
                        pw[1] = alpha[j];
                        pw[2] = alpha[k];
                        pw[3] = alpha[l];
                        pw[4] = '\0';
                        if (check(pw, hash))
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
                            // create 5-letter password from chars
                            pw[0] = alpha[i];
                            pw[1] = alpha[j];
                            pw[2] = alpha[k];
                            pw[3] = alpha[l];
                            pw[4] = alpha[m];
                            pw[5] = '\0';
                            if (check(pw, hash))
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
int check(string pw, string hash)
{
    char salt[3] = {hash[0], hash[1], '\0'};
    if (strcmp(crypt(pw, salt), hash) == 0)
    {
        // Debugging output
        // printf("%s (salt: %s) -> %s\n", hash, salt, pw);
        return 1;
    }
    return 0;
}

void crack_list()
{
    for (int i = 0; i < sizeof(hashes); i++)
    {
        clock_t clk_start = clock();
        string pw = crack(hashes[i]);
        if (strcmp(pw, "") != 0)
        {
            clock_t clk_end = clock();
            double runtime = (clk_end - clk_start) / 1000000.0;
            int minutes = (int)(runtime / 60);
            printf("%s -> %s (in %dm %2.2fs)\n", hashes[i], pw, minutes, runtime - (minutes * 60));
            continue;
        }
        else
        {
            printf("%s could not be found!\n", hashes[i]);
        }
    }
}