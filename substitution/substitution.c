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

    if (key_len != 26)
    {
            printf("Key must contain 26 characters.\n");
            return 1;
    }

    else if (not_alpha(key, key_len))
    {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
    }

    else if(duplication(key, key_len))
    {
            printf("the key should not contain duplicates\n");
            return 1;
    }

    else
    {
        string plain = get_string("plaintext: ");
    }

    return 0;
}

bool duplication(string key, int len)
{
    for(int i = 0; i < len; i++)
        for (int j = i+1; j < len; j++)
            if(key[i] == key[j])
                return true;
    return false;
}

bool not_alpha(string key, int len)
{
    for(int i = 0; i < len; i++)
        if(!isalpha(key[i]))
            return true;
    return false;
}

void encryption(string plain)
{
    for (int i = 0;)
}

//void decryption(string cypher) { string a = "v";}
