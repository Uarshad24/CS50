#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int Height;
    int m = 1;
    do
    {
        Height = get_int("Height of the Pyramid?");
    }
    while (Height < 1 || Height > 8);
    int n = Height;
    for (int t = 1; t <= Height; t++)
    {
        for (int i = 1; i <= Height; i++)
        {
            if (i < n)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        for (int j = 1; j <= Height; j++)
        {
            if (j <= m)
            {
                printf("#");
            }
            else
            {
                continue;
            }
        }

        printf("\n");
        m = m + 1;
        n = n - 1;
    }
}
