#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//Main
int main(void)
{
    //Get text and store in a string
    string text = get_string("Text: ");
    //Print the text in the terminal
    printf("%s\n", text);
    //declared the methods that we'll use
    int count_letters(string s);
    int count_words(string s);
    int count_sentences(string s);
    //declared doubles (letters/100 words) and (sentences/100 words)
    double L = 0;
    double S = 0;
    //if there is letters in the text execute
    if (count_letters(text) != 0)
    {
        //calculates the Letters/100 Words and Sentences/100 Words
        L = ((double)count_letters(text) / (double)count_words(text)) * 100;
        S = ((double)count_sentences(text) / (double)count_words(text)) * 100;
        //calculates the index and round up
        double index = 0.0588 * L - 0.296 * S - 15.8;
        int roundedIndex = round(index);
        //check the index and print propriete result
        if (roundedIndex < 1)
        {
            printf("Before Grade 1\n");
        }
        if (roundedIndex >= 1)
        {
            printf("Grade %i\n", roundedIndex);
        }
        if (roundedIndex > 16)
        {
            printf("Grade 16+\n");
        }
    }
    //else print the zeroed results
    else
    {
        printf("%i letter(s)\n", count_letters(text));
        printf("%i word(s)\n", count_words(text));
        printf("%i sentence(s)\n", count_sentences(text));
    }
}



//METHODS
//COUNTS LETTERS IN TEXT STRING
int count_letters(string s)
{
    int letterCounter = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
        {
            letterCounter++;
        }
    }
    return letterCounter;
}

//COUNT WORDS IN TEXT STRING
int count_words(string s)
{
    int wordCounter = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == ' ')
        {
            wordCounter++;
        }
    }
    if (count_letters(s) > 0 && wordCounter == 0)
    {
        return wordCounter + 1;
    }
    else if (count_letters(s) > 0 && wordCounter > 0)
    {
        return wordCounter + 1;
    }
    return wordCounter;
}

//COUNT SENTENCES IN TEXT STRING
int count_sentences(string s)
{
    int sentenceCounter = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] == '!' || s[i] == '.' || s[i] == '?')
        {
            sentenceCounter++;
        }
    }
    return sentenceCounter;
}