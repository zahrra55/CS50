#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check if the program received exactly one command-line argument (the key)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1; // Return 1 to indicate an error
    }

    // If we reach this point, argc == 2, meaning the key was supplied correctly
    string key = argv[1];
    int key_len = strlen(key);

    // Print the key length (just for debugging purposes)
    printf("Key length: %d\n", key_len);

    // Additional code to validate the key itself can be added here
    return 0;
}
