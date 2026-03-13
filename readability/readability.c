#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_stringgg(char fullText[], int size);
double coleman_liau_index(double lettersss, double wordsss, double sentencesss);

int main(void)
{
    char text[10000];
    get_stringgg(text, 10000);
    // printf("%s\n", text);

    // get len
    int len = strlen(text);
    double words = 0, letters = 0, sentences = 0, mis = 0;

    // get words, letters, sentences, mis by looping through the array of string, noting that there
    // is '\n'
    for (int i = 0; i + 1 < len; i++)
    {
        // to check if i is letter
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters += 1;
        }
        // for spacing which means words
        else if (text[i] == ' ')
        {
            words += 1;
        }
        // to check if i indicates that it is a sentence
        else if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentences += 1;
        }
        // find characters that just exist but dont indicate letters/words/sentences
        else
        {
            // printf("mis: %c\n", text[i]);
            mis += 1;
        }
    }
    // bc there is an extra word not accounted for due to the lack of spacing at the end. so to
    // account for that, simply +1
    words += 1;
    // printf("letters: %f, words: %f, sentences: %f, mis: %f\n\n", letters, words, sentences, mis);

    double indexxx = coleman_liau_index(letters, words, sentences);
    // printf("index: %f \n", indexxx);

    if (indexxx < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (indexxx > 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    else
    {
        int grade = (int) round(indexxx);
        printf("Grade %d\n", grade);
    }

    return 0;
}

double coleman_liau_index(double lettersss, double wordsss, double sentencesss)
{
    double L = (lettersss / wordsss) * 100.0;
    double S = (sentencesss / wordsss) * 100.0;
    double index = (0.0588 * L) - (0.296 * S) - 15.8;
    // printf("L: %f, S: %f, index in coleman: %f\n", L, S, index);

    // printf("index: %d \n", grade);
    return index;
}

// Coleman-Liau index. The Coleman-Liau index of a text is designed to output that (U.S.)
// grade level that is needed to understand some text. The formula is

// index = 0.0588 * L - 0.296 * S - 15.8
// where L is the average number of letters per 100 words in the text,
// and S is the average number of sentences per 100 words in the text.

void get_stringgg(char fullText[], int size)
{

    printf("Text: ");

    fgets(fullText, size, stdin);
}
