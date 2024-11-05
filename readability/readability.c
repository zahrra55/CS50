#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index

    // Print the grade level
    printf("the number of letters = %i\n", letters);
    printf("the number of words = %i\n", words);
}

int count_letters(string text)
{
    int n = 0;
    // Return the number of letters in text
    for (int i = 0; text[i] != '\0'; i++)
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        n++;
    return n;
}

int count_words(string text)
{
    // Return the number of words in text
    int n = 0;
    for (int i = 0; text[i] != '\0'; i++)
        if (text[i] == 32)
        n++;
    return n+1;
}

int count_sentences(string text)
{
    // Return the number of sentences in text
        return 0;
}
