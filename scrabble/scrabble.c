#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int cal_score(string word);

int main(void)
{
    string word1 = get_string("Player1:");
    string word2 = get_string("Player2:");

    int score1 = cal_score(word1);
    int score2 = cal_score(word2);
    printf("%d\n", score1);
    printf("%d\n", score2);
    if (score1 > score2)
    {
        printf("Player 1 wins\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins\n");
    }
    else
    {
        printf("Tie\n");
    }
}

int cal_score(string word)
{
    int score = 0;
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        if (isupper(word[i]))
        {
            score = score + points[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score = score + points[word[i] - 'a'];
        }
    }
    return score;
}
