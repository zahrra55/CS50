#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

bool duplication(string key, int len);
bool not_alpha(string key, int len);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1; // Return 1 to indicate an error
    }

    string key = argv[1];
    int key_len = strlen(key);

    else if (key_len < 26)
            printf("Key must contain 26 characters.\n");

    else if ()
            printf("");

    else if(duplication(key, key_len))
            printf("");



    return 0;
}

bool duplication(string key, int len)
{
    for(int i = 0; i < len; i++)
        for (int j = i+1; j < len; j++)
            if(key[i] == key[j])
                return true;
}

bool not_alpha(string key, int len)
{
    for(int i = 0; i < len; i++)
        if(!isalpha(key[i]))
            break;
            return true;
}
