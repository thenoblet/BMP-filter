#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Red = 0, Blue = 0, Green = 0;

            int count = 0;

            for (int row = -1; row <= 1; row++)
            {
                for (int column = -1; column <= 1; column++)
                {
                    int x = i + row;
                    int y = j + column;

                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        Red += image[x][y].rgbtRed;
                        Blue += image[x][y].rgbtBlue;
                        Green += image[x][y].rgbtGreen;
                        count++;
                    }
                }
            }
            copy[i][j].rgbtRed = round(Red / (float) count);
            copy[i][j].rgbtBlue = round(Blue / (float) count);
            copy[i][j].rgbtGreen = round(Green / (float) count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}

// implementation of the Sobel Operator to detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of original image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // sobel operator for x direction
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    // sobel operator for y direction
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Red, Green, Blue;
            int GxRed = 0, GxGreen = 0, GxBlue = 0;
            int GyRed = 0, GyGreen = 0, GyBlue = 0;

            // iterate through 3x3 grid
            for (int row = -1; row <= 1; row++)
            {
                for (int column = -1; column <= 1; column++)
                {
                    int x = i + row;
                    int y = j + column;

                    // check if the current neigbouring pixel is within the bounds of the image
                    if (x >= 0 && x < height && y >= 0 && y < width)
                    {
                        // x direction
                        GxRed += image[x][y].rgbtRed * Gx[row + 1][column + 1];
                        GxGreen += image[x][y].rgbtGreen * Gx[row + 1][column + 1];
                        GxBlue += image[x][y].rgbtBlue * Gx[row + 1][column + 1];

                        // y direction
                        GyRed += image[x][y].rgbtRed * Gy[row + 1][column + 1];
                        GyGreen += image[x][y].rgbtGreen * Gy[row + 1][column + 1];
                        GyBlue += image[x][y].rgbtBlue * Gy[row + 1][column + 1];
                    }
                }
            }

            // calculate the new pixel values
            Red = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
            Green = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));
            Blue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));

            // Cap values at 255
            if (Red > 255)
            {
                Red = 255;
            }
            if (Green > 255)
            {
                Green = 255;
            }
            if (Blue > 255)
            {
                Blue = 255;
            }

            // assign calculated new pixel values to copied image
            copy[i][j].rgbtRed = Red;
            copy[i][j].rgbtGreen = Green;
            copy[i][j].rgbtBlue = Blue;
        }
    }

    // iterate through pixels to assign copied pixels back to original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}
