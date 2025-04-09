#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Enter the Card Number:");
    int t = 1;
    int T1 = 0;
    int T2 = 0;
    int digits = 0;
    int A1;
    int A_s_n;
    int M_s_n;
    while (number != 0)
    {
        A1 = number % 10;
        number /= 10;
        if (t == 0)
        {
            int A2 = 2 * A1;
            if (A2 / 10 != 0)
            {
                int Ten = A2 / 10;
                int Unit = A2 % 10;
                A2 = Unit + Ten;
            }
            T1 = T1 + A2;
            t = 1;
        }
        else
        {
            T2 = T2 + A1;
            t = 0;
        }
        digits = digits + 1;
        if (digits == 14)
        {
            A_s_n = A1;
        }
        if (digits == 15)
        {
            M_s_n = A1;
        }
    }
    int Sum = T1 + T2;
    if (Sum % 10 == 0)
    {
        if (digits == 15)
        {
            if (A1 == 3 && (A_s_n == 4 || A_s_n == 7))
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (digits == 13)
        {
            printf("VISA\n");
        }
        else if (digits == 16)
        {
            if (A1 == 4)
            {
                printf("VISA\n");
            }
            else if (A1 == 5 &&
                     (M_s_n == 1 || M_s_n == 2 || M_s_n == 3 || M_s_n == 4 || M_s_n == 5))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
