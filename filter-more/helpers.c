#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Average =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = Average;
            image[i][j].rgbtGreen = Average;
            image[i][j].rgbtRed = Average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (width % 2 == 0)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width / 2; j++)
            {
                int temp = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
                image[i][width - 1 - j].rgbtBlue = temp;
                temp = image[i][j].rgbtGreen;
                image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
                image[i][width - 1 - j].rgbtGreen = temp;
                temp = image[i][j].rgbtRed;
                image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
                image[i][width - 1 - j].rgbtRed = temp;
            }
        }
    }
    else
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < (width - 1) / 2; j++)
            {
                int temp = image[i][j].rgbtBlue;
                image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
                image[i][width - 1 - j].rgbtBlue = temp;
                temp = image[i][j].rgbtGreen;
                image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
                image[i][width - 1 - j].rgbtGreen = temp;
                temp = image[i][j].rgbtRed;
                image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
                image[i][width - 1 - j].rgbtRed = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float count = 0;
            int box_sum[3] = {0, 0, 0};
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (i - 1 + k < 0 || i - 1 + k > height - 1)
                    {
                        continue;
                    }
                    if (j - 1 + l < 0 || j - 1 + l > width - 1)
                    {
                        continue;
                    }

                    box_sum[0] = box_sum[0] + image[i - 1 + k][j - 1 + l].rgbtBlue;
                    box_sum[1] = box_sum[1] + image[i - 1 + k][j - 1 + l].rgbtGreen;
                    box_sum[2] = box_sum[2] + image[i - 1 + k][j - 1 + l].rgbtRed;
                    count = count + 1;
                }
            }
            int Average[3];
            for (int k = 0; k < 3; k++)
            {
                Average[k] = round(box_sum[k] / count);
            }
            temp[i][j].rgbtBlue = Average[0];
            temp[i][j].rgbtGreen = Average[1];
            temp[i][j].rgbtRed = Average[2];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int box_sum_gy[3] = {0, 0, 0};
            int box_sum_gx[3] = {0, 0, 0};
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (i + k - 1 < 0 || i + k - 1 > height - 1)
                    {
                        continue;
                    }
                    if (j + l - 1 < 0 || j + l - 1 > width - 1)
                    {
                        continue;
                    }

                    box_sum_gy[0] = box_sum_gy[0] + image[i - 1 + k][j - 1 + l].rgbtBlue * gy[k][l];
                    box_sum_gx[0] = box_sum_gx[0] + image[i - 1 + k][j - 1 + l].rgbtBlue * gx[k][l];

                    box_sum_gy[1] =
                        box_sum_gy[1] + image[i - 1 + k][j - 1 + l].rgbtGreen * gy[k][l];
                    box_sum_gx[1] =
                        box_sum_gx[1] + image[i - 1 + k][j - 1 + l].rgbtGreen * gx[k][l];

                    box_sum_gy[2] = box_sum_gy[2] + image[i - 1 + k][j - 1 + l].rgbtRed * gy[k][l];
                    box_sum_gx[2] = box_sum_gx[2] + image[i - 1 + k][j - 1 + l].rgbtRed * gx[k][l];
                }
            }
            int box_sum[3];
            for (int k = 0; k < 3; k++)
            {
                box_sum[k] =
                    round(sqrt(box_sum_gx[k] * box_sum_gx[k] + box_sum_gy[k] * box_sum_gy[k]));
                if (box_sum[k] > 255)
                {
                    box_sum[k] = 255;
                }
            }

            temp[i][j].rgbtBlue = box_sum[0];
            temp[i][j].rgbtGreen = box_sum[1];
            temp[i][j].rgbtRed = box_sum[2];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
