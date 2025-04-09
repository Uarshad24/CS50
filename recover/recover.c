#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Usage: ./recover card.raw");
        printf("File could not be opened");
        return 1;
    }
    char filename[20];
    int i = 0;
    sprintf(filename, "%03i.jpg", i);
    FILE *img = fopen(filename, "w");
    BYTE a[512];
    bool found = false;

    while (fread(&a, 512, 1, f) != 0)
    {
        if (found == false)
        {
            if (a[0] == 0xff && a[1] == 0xd8 && a[2] == 0xff && (a[3] & 0xf0) == 0xe0)
            {
                found = true;
                fwrite(&a, 512, 1, img);
            }
        }
        else
        {
            if (a[0] == 0xff && a[1] == 0xd8 && a[2] == 0xff && (a[3] & 0xf0) == 0xe0)
            {
                fclose(img);
                i += 1;
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                fwrite(&a, 512, 1, img);
            }
            else
            {
                fwrite(&a, 512, 1, img);
            }
        }
    }
    fclose(img);
    fclose(f);
}
