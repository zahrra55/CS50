#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("couldn't open the file..\n");
        return 1;
    }
    printf("the file is opened!\n");

    // Create a buffer for a block of data
    uint8_t buffer[BUFFER_SIZE];
    char fname[8];
    FILE *img = NULL;
    int c = 0;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, BUFFER_SIZE, card) == BUFFER_SIZE)
    {
        // Create JPEGs from the data
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            if (img != NULL)
            {
                fclose(img);
            }

            // Open a new JPEG file
            sprintf(fname, "%03i.jpg", c++);

            img = fopen(fname, "w");

            if (img == NULL)
            {
                fprintf(stderr, "Error: Could not open file %s\n", fname);
                fclose(card);
                return 1; // Or appropriate error handling
            }
        }
        if (img != NULL)
        {
            fwrite(buffer, 1, BUFFER_SIZE, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
}
