#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key = argv[1];
    int key_len = strlen(key);
    if (key == ' ')
        printf("Usage: ./substitution key\n");
    if (key_len < 26)
        printf("Key must contain 26 characters.\n");
    else
    {
        for(int i = 0; i < key_len; i++)
        {

        }
    }

    //printf("%s\n",argv[1]);
}
