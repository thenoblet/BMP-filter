#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            //int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            //Calculating the average of the 3 colors.
            float average = ((blue + green + red) / 3.0);

            int pixel = round(average);

            image[i][j].rgbtBlue = pixel;
            image[i][j].rgbtGreen = pixel;
            image[i][j].rgbtRed = pixel;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through rows
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //calculating new sepia color values based on the original color values.
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //Capping the sepia colour values to 255.
            if (sepiaRed >= 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }

            //Assign new sepia color values to pixels.
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //int index;
    RGBTRIPLE temp; //Declare viariable 'temp' to hold values temporarily
    for (int i = 0; i < height; i++) // loop through the rows
    {
        //index = i;
        for (int j = 0; j < width / 2; j++) // loops through only half of the columns with 'width/2'
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1]; //'width-j-1 accesses the arrays from the other half of the column
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width]; //declare variable copy to save copies of original pixels.
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
            //declare variables to store the sum of colour values in the pixel
            int Red = 0;
            int Blue = 0;
            int Green = 0;

            int count = 0; //keeps track of the number of neighbouring pixels.

            for (int row = -1; row <= 1; row++) //
            {
                for (int column = -1; column <= 1; column++)
                {
                    int x = i + row;
                    int y = j + column;

                    if (x >= 0 && x < height && y >= 0 && y < width) //check if the surrounding pixels is within the bounds of the image
                    {
                        Red = Red + image[x][y].rgbtRed;
                        Blue = Blue + image[x][y].rgbtBlue;
                        Green = Green + image[x][y].rgbtGreen;
                        count++;
                    }
                }
            }
            /*int averageRed = round(Red / (float)count);
            int averageBlue = round(Blue / (float)count);
            int averageGreen = round(Green / (float)count);
            */

            copy[i][j].rgbtRed = round(Red / (float)count);
            copy[i][j].rgbtBlue = round(Blue / (float)count);
            copy[i][j].rgbtGreen = round(Green / (float)count);
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
