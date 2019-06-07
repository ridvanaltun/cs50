/**
 * Solition of Vigenere Assigment for Harvard CS50 Class
 *
 * Name  : Ridvan Altun
 * Date  : 07/06/2019
 * Email : ridvanaltun@outlook.com
 */
 
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defines
#define FILENAME argv[0]
#define KEYWORD argv[1]

// Prototypes
bool isword(char *word);
char *crypter(char *plain, char *keyword);
char *createkeys(char *keyword);

const char *BIG_C = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char *LITTLE_C = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, char *argv[])
{
    bool iskeywordvalid = false;
    
    if (argc == 2)
    {
        iskeywordvalid = isword(KEYWORD);
    }
    
    if (iskeywordvalid)
    {
        char *plain = get_string("plaintext:  ");
        char *cipher = crypter(plain, KEYWORD);
        printf("ciphertext: %s\n", cipher);
        return 0;
    }
    else
    {
        printf("Usage: %s keyword\n", FILENAME);
        return 1;
    }
}

// Returns true if text created using only alphabet.
bool isword(char *word)
{
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isdigit(word[i]) > 0)
        {
            return false;
        }
    }
    
    return true;
}

// Returns crypted text.
char *crypter(char *plain, char *keyword)
{
    char *cipher = (char *)malloc(strlen(plain) * sizeof(char *));
    char *keys = createkeys(keyword);
    int counter = 0, offset = 0;
    
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        // If character is space.
        if (plain[i] == 32)
        {
            cipher[i] = 32;
        }
        else
        {
            if (counter == strlen(keyword))
            {
                counter = 0;
            }
            
            offset = keys[counter] + plain[i];
            
            if ((offset < 123 && offset > 96) || (offset < 91 && offset > 64))
            {
                cipher[i] = offset;
            }
            else
            {
                cipher[i] = plain[i] - keys[counter] + 2;
            }
 
            counter++;
        }
    }
        
    return cipher;      
}

// Returns keys as a single string.
char *createkeys(char *keyword)
{
    char *keys = (char *)malloc(strlen(keyword) * sizeof(char *));
    
    for (int i = 0, n = strlen(keyword); i < n; i++)
    {
        if (isupper(keyword[i]) > 0)
        {
            // 26 represent letter count. 
            for (int j = 0; j < 26; j++)
            {
                if (keyword[i] == BIG_C[j])
                {
                    keys[i] = j;
                    break;
                }
            } 
        }
        else
        {
            // 26 represent letter count. 
            for (int k = 0; k < 26; k++)
            {
                if (keyword[i] == LITTLE_C[k])
                {
                    keys[i] = k;
                    break;
                }
            } 
        }
    }
    
    return keys;
}