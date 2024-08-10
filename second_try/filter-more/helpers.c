#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtGreen = image[i][j].rgbtBlue = image[i][j].rgbtRed = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp;
            temp.rgbtBlue = image[i][j].rgbtBlue;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            temp.rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtBlue = temp.rgbtBlue;
            image[i][width - j - 1].rgbtGreen = temp.rgbtGreen;
            image[i][width - j - 1].rgbtRed = temp.rgbtRed;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int a,b,c;
            a = b = c = 0;
            int counter = 0;
            for(int m = -1; m < 2; m++)
            {
                if(i + m < 0 || i+m >= height)
                {
                    continue;
                }
                        for(int n = -1; n < 2; n++)
                        {
                            if(j + n < 0 || j+n >= width)
                            {
                                continue;
                            }
                            a += image[i+m][j+n].rgbtRed;
                            b +=  image[i+m][j+n].rgbtGreen;
                            c += image[i+m][j+n].rgbtBlue;
                            counter++;
                        }
            }
            temp[i][j].rgbtRed = round((float)a / counter);
            temp[i][j].rgbtGreen = round((float)b / counter);
            temp[i][j].rgbtBlue = round((float)c / counter);
        }
    }
for(int i = 0; i < height; i++)
{
    for(int j = 0; j < width; j++)
    {
        image[i][j] = temp[i][j];
    }
}
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int hor[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int ver[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int a1 = 0, b1 = 0, c1 = 0, a2 = 0, b2 = 0, c2 = 0;

            for (int m = -1; m < 2; m++)
            {
                if (i + m < 0 || i + m >= height)
                {
                    continue;
                }

                for (int n = -1; n < 2; n++)
                {
                    if (j + n < 0 || j + n >= width)
                    {
                        continue;
                    }

                    a1 += image[i + m][j + n].rgbtRed * hor[m + 1][n + 1];
                    b1 += image[i + m][j + n].rgbtGreen * hor[m + 1][n + 1];
                    c1 += image[i + m][j + n].rgbtBlue * hor[m + 1][n + 1];
                    a2 += image[i + m][j + n].rgbtRed * ver[m + 1][n + 1];
                    b2 += image[i + m][j + n].rgbtGreen * ver[m + 1][n + 1];
                    c2 += image[i + m][j + n].rgbtBlue * ver[m + 1][n + 1];
                }
            }

            if (a1 > 255) a1 = 255;
            if (b1 > 255) b1 = 255;
            if (c1 > 255) c1 = 255;
            if (a2 > 255) a2 = 255;
            if (b2 > 255) b2 = 255;
            if (c2 > 255) c2 = 255;

            temp[i][j].rgbtRed = round(sqrt(pow(a1, 2) + pow(a2, 2)));
            temp[i][j].rgbtGreen = round(sqrt(pow(b1, 2) + pow(b2, 2)));
            temp[i][j].rgbtBlue = round(sqrt(pow(c1, 2) + pow(c2, 2)));
        }
    }
for(int i = 0; i < height; i++)
{
    for(int j = 0; j < width; j++)
    {
        image[i][j] = temp[i][j];
    }
}
}
