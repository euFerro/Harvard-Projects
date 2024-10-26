#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

string plaintext;
string key;
bool checkKey(string aKey);
bool checkRep(string thisKey);
string encrypt(string text, string withKey);

//main method that print stuff in the screen

int main(int argc, string argv[])
{
    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    else if (argc == 2)
    {
        key = argv[1];
        if (strlen(key) != 26)
        {
            printf("Key must contain 26 characters\n");
            return 1;
        }
        else if (checkKey(key) == false)
        {
            printf("Key must contain only distinct letters and not contain numbers\n");
            return 1;
        }
        else if (checkKey(key) == true)
        {
            plaintext = get_string("plaintext: ");
            string result = encrypt(key, plaintext);
            printf("ciphertext: %s\n", result);
            return 0;
        }
    }

    else if (argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

//use the checkRep function to give boolean anwers

bool checkKey(string aKey)
{
    bool result;
    bool repetition = checkRep(aKey);
    for (int i = 0; i < strlen(aKey); i++)
    {
        if ((aKey[i] >= 'A' && aKey[i] <= 'Z') || (aKey[i] >= 'a' && aKey[i] <= 'z'))
        {
            if (repetition == false)
            {
                result = true;
            }
            else
            {
                result = false;
                break;
            }
        }
        else
        {
            result = false;
            break;
        }
    }
    return result;
}

//check if the key has repeated characters

bool checkRep(string thisKey)
{
    bool result;
    int counter = 0;
    for (int i = 0; i < strlen(thisKey) - 1; i++)
    {
        for (int j = i + 1; j < strlen(thisKey); j++)
        {
            if (thisKey[i] == thisKey[j])
            {
                counter = 1;
            }
        }
    }
    if (counter == 0)
    {
        result = false;
    }
    else
    {
        result = true;
    }
    return result;
}

//encrypts the text

string encrypt(string withKey, string text)
{
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < strlen(alpha); i++)
    {
        for (int j = 0; j < strlen(alpha); j++)
        {
            if (toupper(text[i]) == toupper(alpha[j]))
            {
                if (isupper(text[i]) != 0)
                {
                    text[i] = toupper(withKey[j]);
                    break;
                }
                else
                {
                    text[i] = tolower(withKey[j]);
                    break;
                }
            }
        }
    }
    return text;
}






