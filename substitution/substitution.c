#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char List[26];
int j = 0;
int k;

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    else
    {
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.");
            return 1;
        }
        else
        {
            for (int i = 0, l = strlen(argv[1]); i < l; i++)
            {
                if (isalpha(argv[1][i]))
                {

                    for (j = 0, k = strlen(List); j < k; j++)
                    {
                        if (List[j] == '\0')
                        {
                            break;
                        }
                        else if (List[j] == argv[1][i] || List[j] == argv[1][i] - 32 ||
                                 List[j] == argv[1][i] + 32)
                        {
                            printf("repitition not allowed");
                            return 1;
                        }
                    }
                    List[j] = argv[1][i];
                }
                else
                {
                    printf("Key must contain Alphabets.");
                    return 1;
                }
            }

            string ptext = get_string("plaintext: ");
            for (int a = 0, q = strlen(ptext); a < q; a++)
            {
                if (ptext[a] >= 'a' && ptext[a] <= 'z')
                {
                    ptext[a] = argv[1][ptext[a] - 97];
                    if (ptext[a] >= 'a' && ptext[a] <= 'z')
                    {
                        continue;
                    }
                    else
                    {
                        ptext[a] = ptext[a] + 32;
                    }
                }
                if (ptext[a] >= 'A' && ptext[a] <= 'Z')
                {
                    ptext[a] = argv[1][ptext[a] - 65];
                    if (ptext[a] >= 'A' && ptext[a] <= 'Z')
                    {
                        continue;
                    }
                    else
                    {
                        ptext[a] = ptext[a] - 32;
                    }
                }
            }
            printf("ciphertext: %s\n", ptext);
            return 0;
        }
    }
}
