#include "helpers.h"
#include "math.h"
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterates over image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            double avg = (double)(red + green + blue) / 3;

            image[i][j].rgbtRed = (int)round(avg);
            image[i][j].rgbtGreen = (int)round(avg);
            image[i][j].rgbtBlue = (int)round(avg);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // iterates over image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round((.393 * originalRed) + (.769 * originalGreen) + (.189 * originalBlue));
            int sepiaGreen = round((.349 * originalRed) + (.686 * originalGreen) + (.168 * originalBlue));
            int sepiaBlue = round((.272 * originalRed) + (.534 * originalGreen) + (.131 * originalBlue));

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int last;
    // iterates over image array
    for (int i = 0; i < height; i++)
    {
        last = width-1;
        for (int j = 0; j < round(width/2); j++)
        {
            RGBTRIPLE aux = image[i][j];
            image[i][j] = image[i][last];
            image[i][last] = aux;
            last--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of original image[][]
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // iterate over rgb values and check the position of the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // top left corner pixel
            if (i == 0 && j == 0)
            {
                int red = copy[i][j].rgbtRed +
                          copy[i][j+1].rgbtRed +
                          copy[i+1][j].rgbtRed +
                          copy[i+1][j+1].rgbtRed;

                int green = copy[i][j].rgbtGreen +
                            copy[i][j+1].rgbtGreen +
                            copy[i+1][j].rgbtGreen +
                            copy[i+1][j+1].rgbtGreen;

                int blue = copy[i][j].rgbtBlue +
                           copy[i][j+1].rgbtBlue +
                           copy[i+1][j].rgbtBlue +
                           copy[i+1][j+1].rgbtBlue;

                double avgRed = (double)red / 4;
                double avgGreen = (double)green / 4;
                double avgBlue = (double)blue / 4;

                image[i][j].rgbtRed = (int)avgRed;
                image[i][j].rgbtGreen = (int)avgGreen;
                image[i][j].rgbtBlue = (int)avgBlue;
            }
            // top right corner pixel
            if (i == 0 && j == width-1)
            {
                int red = copy[i][j].rgbtRed +
                          copy[i][j-1].rgbtRed +
                          copy[i+1][j].rgbtRed +
                          copy[i+1][j-1].rgbtRed;

                int green = copy[i][j].rgbtGreen +
                            copy[i][j-1].rgbtGreen +
                            copy[i+1][j].rgbtGreen +
                            copy[i+1][j-1].rgbtGreen;

                int blue = copy[i][j].rgbtBlue +
                           copy[i][j-1].rgbtBlue +
                           copy[i+1][j].rgbtBlue +
                           copy[i+1][j-1].rgbtBlue;

                double avgRed = (double)red / 4;
                double avgGreen = (double)green / 4;
                double avgBlue = (double)blue / 4;

                image[i][j].rgbtRed = (int)avgRed;
                image[i][j].rgbtGreen = (int)avgGreen;
                image[i][j].rgbtBlue = (int)avgBlue;
            }
            // bottom left corner pixel
            if (i == height-1 && j == 0)
            {
                int red = copy[i][j].rgbtRed +
                          copy[i-1][j].rgbtRed +
                          copy[i][j+1].rgbtRed +
                          copy[i-1][j+1].rgbtRed;

                int green = copy[i][j].rgbtGreen +
                            copy[i-1][j].rgbtGreen +
                            copy[i][j+1].rgbtGreen +
                            copy[i-1][j+1].rgbtGreen;

                int blue = copy[i][j].rgbtBlue +
                           copy[i-1][j].rgbtBlue +
                           copy[i][j+1].rgbtBlue +
                           copy[i-1][j+1].rgbtBlue;

                double avgRed = (double)red / 4;
                double avgGreen = (double)green / 4;
                double avgBlue = (double)blue / 4;

                image[i][j].rgbtRed = (int)round(avgRed);
                image[i][j].rgbtGreen = (int)round(avgGreen);
                image[i][j].rgbtBlue = (int)round(avgBlue);
            }
            // bottom right corner pixel
            if (i == height-1 && j == width-1)
            {
                int red = copy[i][j].rgbtRed +
                          copy[i-1][j].rgbtRed +
                          copy[i][j-1].rgbtRed +
                          copy[i-1][j-1].rgbtRed;

                int green = copy[i][j].rgbtGreen +
                            copy[i-1][j].rgbtGreen +
                            copy[i][j-1].rgbtGreen +
                            copy[i-1][j-1].rgbtGreen;

                int blue = copy[i][j].rgbtBlue +
                           copy[i-1][j].rgbtBlue +
                           copy[i][j-1].rgbtBlue +
                           copy[i-1][j-1].rgbtBlue;

                double avgRed = (double)red / 4;
                double avgGreen = (double)green / 4;
                double avgBlue = (double)blue / 4;

                image[i][j].rgbtRed = (int)round(avgRed);
                image[i][j].rgbtGreen = (int)round(avgGreen);
                image[i][j].rgbtBlue = (int)round(avgBlue);
            }
            // top pixels
            if (i == 0 && (j > 0 && j < width-1))
            {
                int red = copy[i][j].rgbtRed +
                          copy[i+1][j].rgbtRed +
                          copy[i][j-1].rgbtRed +
                          copy[i][j+1].rgbtRed +
                          copy[i+1][j-1].rgbtRed +
                          copy[i+1][j+1].rgbtRed;

                int green = copy[i][j].rgbtGreen +
                            copy[i+1][j].rgbtGreen +
                            copy[i][j-1].rgbtGreen +
                            copy[i][j+1].rgbtGreen +
                            copy[i+1][j-1].rgbtGreen +
                            copy[i+1][j+1].rgbtGreen;

                int blue = copy[i][j].rgbtBlue +
                           copy[i+1][j].rgbtBlue +
                           copy[i][j-1].rgbtBlue +
                           copy[i][j+1].rgbtBlue +
                           copy[i+1][j-1].rgbtBlue +
                           copy[i+1][j+1].rgbtBlue;

                double avgRed = (double)red / 6;
                double avgGreen = (double)green / 6;
                double avgBlue = (double)blue / 6;

                image[i][j].rgbtRed = (int)round(avgRed);
                image[i][j].rgbtGreen = (int)round(avgGreen);
                image[i][j].rgbtBlue = (int)round(avgBlue);
            }
            // bottom pixels
            if (i == height-1 && (j > 0 && j < width-1))
            {
                int red = copy[i][j].rgbtRed +
                          copy[i-1][j].rgbtRed +
                          copy[i][j-1].rgbtRed +
                          copy[i][j+1].rgbtRed +
                          copy[i-1][j-1].rgbtRed +
                          copy[i-1][j+1].rgbtRed;

                int green = copy[i][j].rgbtGreen +
                            copy[i-1][j].rgbtGreen +
                            copy[i][j-1].rgbtGreen +
                            copy[i][j+1].rgbtGreen +
                            copy[i-1][j-1].rgbtGreen +
                            copy[i-1][j+1].rgbtGreen;

                int blue = copy[i][j].rgbtBlue +
                           copy[i-1][j].rgbtBlue +
                           copy[i][j-1].rgbtBlue +
                           copy[i][j+1].rgbtBlue +
                           copy[i-1][j-1].rgbtBlue +
                           copy[i-1][j+1].rgbtBlue;

                double avgRed = (double)red / 6;
                double avgGreen = (double)green / 6;
                double avgBlue = (double)blue / 6;

                image[i][j].rgbtRed = (int)round(avgRed);
                image[i][j].rgbtGreen = (int)round(avgGreen);
                image[i][j].rgbtBlue = (int)round(avgBlue);
            }
            // left pixels
            if ((j == 0) && (i > 0 && i < height-1))
            {
                int red = copy[i][j].rgbtRed +
                          copy[i+1][j].rgbtRed +
                          copy[i][j+1].rgbtRed +
                          copy[i+1][j+1].rgbtRed +
                          copy[i-1][j+1].rgbtRed +
                          copy[i-1][j].rgbtRed;

                int green = copy[i][j].rgbtGreen +
                            copy[i+1][j].rgbtGreen +
                            copy[i][j+1].rgbtGreen +
                            copy[i+1][j+1].rgbtGreen +
                            copy[i-1][j+1].rgbtGreen +
                            copy[i-1][j].rgbtGreen;

                int blue = copy[i][j].rgbtBlue +
                           copy[i+1][j].rgbtBlue +
                           copy[i][j+1].rgbtBlue +
                           copy[i+1][j+1].rgbtBlue +
                           copy[i-1][j+1].rgbtBlue +
                           copy[i-1][j].rgbtBlue;

                double avgRed = (double)red / 6;
                double avgGreen = (double)green / 6;
                double avgBlue = (double)blue / 6;

                image[i][j].rgbtRed = (int)round(avgRed);
                image[i][j].rgbtGreen = (int)round(avgGreen);
                image[i][j].rgbtBlue = (int)round(avgBlue);
            }
            // right pixels
            if (j == height-1 && (i > 0 && i < height-1))
            {
                int red = copy[i][j].rgbtRed +
                          copy[i][j-1].rgbtRed +
                          copy[i-1][j].rgbtRed +
                          copy[i+1][j].rgbtRed +
                          copy[i-1][j-1].rgbtRed +
                          copy[i+1][j-1].rgbtRed;

                int green = copy[i][j].rgbtGreen +
                            copy[i][j-1].rgbtGreen +
                            copy[i-1][j].rgbtGreen +
                            copy[i+1][j].rgbtGreen +
                            copy[i-1][j-1].rgbtGreen +
                            copy[i+1][j-1].rgbtGreen;

                int blue = copy[i][j].rgbtBlue +
                           copy[i][j-1].rgbtBlue +
                           copy[i-1][j].rgbtBlue +
                           copy[i+1][j].rgbtBlue +
                           copy[i-1][j-1].rgbtBlue +
                           copy[i+1][j-1].rgbtBlue;

                double avgRed = (double)red / 6;
                double avgGreen = (double)green / 6;
                double avgBlue = (double)blue / 6;

                image[i][j].rgbtRed = (int)round(avgRed);
                image[i][j].rgbtGreen = (int)round(avgGreen);
                image[i][j].rgbtBlue = (int)round(avgBlue);
            }
            // middle pixels
            if ((i > 0 && j > 0) && (i < height-1 && j < width-1))
            {
                int red = copy[i][j].rgbtRed +
                          copy[i][j-1].rgbtRed +
                          copy[i][j+1].rgbtRed +
                          copy[i-1][j].rgbtRed +
                          copy[i-1][j-1].rgbtRed +
                          copy[i-1][j+1].rgbtRed +
                          copy[i+1][j].rgbtRed +
                          copy[i+1][j-1].rgbtRed +
                          copy[i+1][j+1].rgbtRed;

                int green = copy[i][j].rgbtGreen +
                            copy[i][j-1].rgbtGreen +
                            copy[i][j+1].rgbtGreen +
                            copy[i-1][j].rgbtGreen +
                            copy[i-1][j-1].rgbtGreen +
                            copy[i-1][j+1].rgbtGreen +
                            copy[i+1][j].rgbtGreen +
                            copy[i+1][j-1].rgbtGreen +
                            copy[i+1][j+1].rgbtGreen;

                int blue = copy[i][j].rgbtBlue +
                           copy[i][j-1].rgbtBlue +
                           copy[i][j+1].rgbtBlue +
                           copy[i-1][j].rgbtBlue +
                           copy[i-1][j-1].rgbtBlue +
                           copy[i-1][j+1].rgbtBlue +
                           copy[i+1][j].rgbtBlue +
                           copy[i+1][j-1].rgbtBlue +
                           copy[i+1][j+1].rgbtBlue;

                double avgRed = (double)red / 9;
                double avgGreen = (double)green / 9;
                double avgBlue = (double)blue / 9;

                image[i][j].rgbtRed = (int)round(avgRed);
                image[i][j].rgbtGreen = (int)round(avgGreen);
                image[i][j].rgbtBlue = (int)round(avgBlue);
            }
        }
    }
    return;
}
