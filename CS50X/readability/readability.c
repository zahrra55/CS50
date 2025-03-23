#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void Coleman_Liau(int w, int l, int s);

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

    Coleman_Liau(words, letters, sentences);
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
    return n + 1;
}

int count_sentences(string text)
{
    // Return the number of sentences in text
    int n = 0;
    for (int i = 0; text[i] != '\0'; i++)
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            n++;
    return n;
}

void Coleman_Liau(int w, int l, int s)
{
    float L = ((float) l / (float) w) * 100;
    float S = ((float) s / (float) w) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int g = round(index);
    if (g < 1)
        printf("Before Grade 1\n");
    else if (g > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", g);
}
