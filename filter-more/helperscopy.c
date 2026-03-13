#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[1][1];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[0][0] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp[0][0];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // copy over to have original values
    RGBTRIPLE ori[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ori[i][j] = image[i][j];
        }
    }
    // // deal w corners
    // // assume its at least 3 by 3
    // image[0][0].rgbtBlue = (ori[0][0].rgbtBlue + ori[0][1].rgbtBlue + ori[1][0].rgbtBlue +
    // ori[1][1].rgbtBlue)/4; image[0][width - 1].rgbtBlue = (ori[0][width - 1].rgbtBlue +
    // ori[0][width - 2].rgbtBlue + ori[1][width - 1].rgbtBlue + ori[1][width - 2].rgbtBlue)/4;
    // image[height - 1][0].rgbtBlue = (ori[height - 1][0].rgbtBlue + ori[height - 2][0].rgbtBlue +
    // ori[height - 2][1].rgbtBlue + ori[height - 1][1].rgbtBlue)/4; image[height - 1][width -
    // 1].rgbtBlue = (ori[height - 1][width - 1].rgbtBlue + ori[height - 2][width - 2].rgbtBlue +
    // ori[height - 1][width - 2].rgbtBlue + ori[height - 2][width - 1].rgbtBlue)/4;

    // retry

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;
            int count = 0;

            for (int m = i - 1; m <= i + 1; m++)
            {
                for (int n = j - 1; n <= j + 1; n++)
                {
                    if (m >= 0 && m < height && n >= 0 && n < width)
                    {
                        sumBlue += ori[m][n].rgbtBlue;
                        sumGreen += ori[m][n].rgbtGreen;
                        sumRed += ori[m][n].rgbtRed;
                        count += 1;
                    }
                }
            }

            image[i][j].rgbtBlue = round((float) sumBlue / count);
            image[i][j].rgbtGreen = round((float) sumGreen / count);
            image[i][j].rgbtRed = round((float) sumRed / count);

            // image[i][j].rgbtBlue = (ori[i - 1][j - 1].rgbtBlue + ori[i - 1][j].rgbtBlue + ori[i -
            // 1][j + 1].rgbtBlue + ori[i][j - 1].rgbtBlue + ori[i][j].rgbtBlue + ori[i][j +
            // 1].rgbtBlue + ori[i + 1][j - 1].rgbtBlue + ori[i + 1][j].rgbtBlue + ori[i + 1][j +
            // 1].rgbtBlue)/9;
        }
    }

    // // deal w edges (6)
    // for (int i = 1; i < width - 1; i++)
    // {
    //     image[0][i].rgbtBlue = (ori[0][i - 1].rgbtBlue + ori[0][i + 1].rgbtBlue +
    //     ori[0][i].rgbtBlue + ori[1][i].rgbtBlue + ori[1][i - 1].rgbtBlue + ori[1][i +
    //     1].rgbtBlue)/6;
    // }
    // for (int i = 1; i < width - 1; i++)
    // {
    //     image[height - 1][i].rgbtBlue = (ori[height - 1][i].rgbtBlue + ori[height - 1][i +
    //     1].rgbtBlue + ori[height - 1][i - 1].rgbtBlue + ori[height - 2][i].rgbtBlue + ori[height
    //     - 2][i + 1].rgbtBlue + ori[height - 2][i - 1].rgbtBlue)/6;
    // }
    // for (int i = 1; i < height - 1; i++)
    // {
    //     image[i][0].rgbtBlue = (ori[i][0].rgbtBlue + ori[i + 1][0].rgbtBlue + ori[i -
    //     1][0].rgbtBlue + ori[i][1].rgbtBlue + ori[i + 1][1].rgbtBlue + ori[i - 1][1].rgbtBlue)/6;
    // }
    // for (int i = 1; i < height - 1; i++)
    // {
    //     image[i][width - 1].rgbtBlue = (ori[i][width - 1].rgbtBlue + ori[i + 1][width -
    //     1].rgbtBlue + ori[i - 1][width - 1].rgbtBlue + ori[i][width - 2].rgbtBlue + ori[i +
    //     1][width - 2].rgbtBlue + ori[i - 1][width - 2].rgbtBlue)/6;
    // }

    // // deal w middle that has (9)

    // for (int i = 1; i < height - 1; i++)
    // {
    //     for (int j = 1; j < width - 1; j++)
    //     {
    //         image[i][j].rgbtBlue = (ori[i - 1][j - 1].rgbtBlue + ori[i - 1][j].rgbtBlue + ori[i -
    //         1][j + 1].rgbtBlue + ori[i][j - 1].rgbtBlue + ori[i][j].rgbtBlue + ori[i][j +
    //         1].rgbtBlue + ori[i + 1][j - 1].rgbtBlue + ori[i + 1][j].rgbtBlue + ori[i + 1][j +
    //         1].rgbtBlue)/9;
    //     }
    // }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /*
    gx
    -1   0   1
    -2   0   2
    -1   0   1

    gy
    -1  -2  -1
     0   0   0
     1   2   1
    */

    // copy over to have original values
    RGBTRIPLE ori[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ori[i][j] = image[i][j];
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int redsumgx, greensumgx, bluesumgx;
    int redsumgy, greensumgy, bluesumgy;
    int count1, count2, redfinal, greenfinal, bluefinal;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // for each pixel
            count1 = 0;
            redsumgx = greensumgx = bluesumgx = redsumgy = greensumgy = bluesumgy = 0;

            for (int m = i - 1; m < i + 2; m++)
            {
                count2 = 0;

                for (int n = j - 1; n < j + 2; n++)
                {
                    if ((m >= 0 && m < height && n >= 0 && n < width))
                    {
                        redsumgx += (ori[m][n].rgbtRed * gx[count1][count2]);
                        greensumgx += (ori[m][n].rgbtGreen * gx[count1][count2]);
                        bluesumgx += (ori[m][n].rgbtBlue * gx[count1][count2]);
                        redsumgy += (ori[m][n].rgbtRed * gy[count1][count2]);
                        greensumgy += (ori[m][n].rgbtGreen * gy[count1][count2]);
                        bluesumgy += (ori[m][n].rgbtBlue * gy[count1][count2]);
                    }
                    count2 += 1;
                }
                count1 += 1;
            }
            // final = sqrt(redsumgx);
            redfinal = round(sqrt(redsumgx * redsumgx + redsumgy * redsumgy));
            if (redfinal > 255)
                redfinal = 255;
            greenfinal = round(sqrt(greensumgx * greensumgx + greensumgy * greensumgy));
            if (greenfinal > 255)
                greenfinal = 255;
            bluefinal = round(sqrt(bluesumgx * bluesumgx + bluesumgy * bluesumgy));
            if (bluefinal > 255)
                bluefinal = 255;

            image[i][j].rgbtRed = redfinal;
            image[i][j].rgbtGreen = greenfinal;
            image[i][j].rgbtBlue = bluefinal;
        }
    }

    return;
}
