#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    float word = 1;
    float letter = 0;
    float sentence = 0;
    string Text = get_string("Text:");
    for (int i = 0, l = strlen(Text); i < l; i++)
    {
        if (Text[i] == ' ')
        {
            word = word + 1;
        }
        else if (Text[i] == '.' || Text[i] == '!' || Text[i] == '?')
        {
            sentence = sentence + 1;
        }
        else if (isalpha(Text[i]))
        {
            letter = letter + 1;
        }
    }
    float L = (letter / word) * 100;
    float S = (sentence / word) * 100;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    printf("Grade %f %f %f %f %f", sentence, word, letter, L, S);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 0 && index <= 16)
    {
        printf("Grade %d\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}
