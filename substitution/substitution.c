#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1; // Return 1 to indicate an error
    }

    string key = argv[1];
    int key_len = strlen(key);

    if (key_len < 26)
        printf("Key must contain 26 characters.\n");





    return 0;
}

bool duplication(string txt)
{
    for(int i = 0; i < key_len; i++)
        for (int j = i+1; j < key_len; j++)
            if(key[i] == key[j])
                return true;
}

bool alpha(string txt)
{
    for(int i = 0; i < key_len; i++)
        if(!isalpha(key[i]))
            break;
            printf("Usage: ./substitution key\n");
}
