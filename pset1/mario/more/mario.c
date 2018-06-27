#include <stdio.h>

int main(void)
{
    // Define and declare initial value for height
    int height = -1;
    while (height < 0 || height > 23)
    {
        // Prompt user for input
        printf("Height: ");

        // Safely reading input and casting to int
        // per https://stackoverflow.com/questions/9278226/
        char line[256];
        int i;
        if (fgets(line, sizeof(line), stdin))
        {
            if (1 == sscanf(line, "%d", &i))
            {
                height = i;
            }
        }
    }

    // Print pyramide
    for (int i = 1; i <= height; i++)
    {
        // Padding for left half of pyramide
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
        // Left half of pyramide
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("  ");

        // Right half of pyramide
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
