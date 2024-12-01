#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            int avarage = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
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

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumRed, sumGreen, sumBlue, count;
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumRed = sumGreen = sumBlue = count = 0; // Reset sums for each pixel

            for (int ni = -1; ni < 2; ni++)
            {
                for (int nj = -1; nj < 2; nj++)
                {
                    int nei = i + ni;
                    int nej = j + nj;

                    // Check if neighbor pixel is valid
                    if (nei >= 0 && nei < height && nej >= 0 && nej < width)
                    {
                        sumRed += image[nei][nej].rgbtRed;
                        sumGreen += image[nei][nej].rgbtGreen;
                        sumBlue += image[nei][nej].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average and assign to temp
            temp[i][j].rgbtRed = round((float)sumRed / count);
            temp[i][j].rgbtGreen = round((float)sumGreen / count);
            temp[i][j].rgbtBlue = round((float)sumBlue / count);
        }
    }

    // Copy the blurred image back to the original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int sumRedx, sumGreenx, sumBluex;
    int sumRedy, sumGreeny, sumBluey;

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumRedx = sumGreenx = sumBluex = 0; // Reset X's sums for each pixel
            sumRedy = sumGreeny = sumBluey = 0; // Reset Y's sums for each pixel

            for (int ni = -1; ni < 2; ni++)
            {
                for (int nj = -1; nj < 2; nj++)
                {
                    int nei = i + ni;
                    int nej = j + nj;

                    // Check if neighbor pixel is valid
                    if (nei >= 0 && nei < height && nej >= 0 && nej < width)
                    {
                        int WX = Gx[ni + 1][nj + 1];
                        int WY = Gy[ni + 1][nj + 1];

                        sumRedx += image[nei][nej].rgbtRed * WX;
                        sumGreenx += image[nei][nej].rgbtGreen * WX;
                        sumBluex += image[nei][nej].rgbtBlue * WX;

                        sumRedy += image[nei][nej].rgbtRed * WY;
                        sumGreeny += image[nei][nej].rgbtGreen * WY;
                        sumBluey += image[nei][nej].rgbtBlue * WY;

                    }
                }
            }

            int Red = round(sqrt(sumRedx * sumRedx + sumRedy * sumRedy));
            int Green = round(sqrt(sumGreenx * sumGreenx + sumGreeny * sumGreeny));
            int Blue = round(sqrt(sumBluex * sumBluex + sumBluey * sumBluey));


            if (Red > 255) temp[i][j].rgbtRed = 255;
            else temp[i][j].rgbtRed = Red;

            if (Green > 255) temp[i][j].rgbtGreen = 255;
            else temp[i][j].rgbtGreen = Green;

            if (Blue > 255) temp[i][j].rgbtBlue = 255;
            else temp[i][j].rgbtBlue = Blue;

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

}
