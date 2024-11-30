#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            int avarage = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avarage;
        }

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;

    for (int ni = -1; ni < 2; ni++)
        for(int nj = -1; nj < 2; nj++)
        {
            int nei = i + ni;
            int nej = j + nj;
        if(nei >= 0 && nei < height && nej >= 0 && nei < width)
            {
                sumRed += image[nei][nej].rgbtRed;
                sumGreen += image[nei][nej].rgbtGreen;
                sumBlue += image[nei][nej].rgbtBlue;
                count++;
            }
        }

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][j];
            image[i][j] = temp;
            //
            //int avarage = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            //image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avarage;
        }

}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
