/**
 * Solition of Caesar Assigment for Harvard CS50 Class
 *
 * Name  : Ridvan Altun
 * Date  : 06/06/2019
 * Email : ridvanaltun@outlook.com
 */
 
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defines
#define FILENAME argv[0]
#define KEY argv[1]
#define OFFSET 48

// Prototypes
int strtoint(string text);
bool isnum(string text);
string crypter(string plain, string key);

int main(int argc, string argv[])
{
    bool iskeyvalid = false;
    
    if (argc == 2)
    {
        iskeyvalid = isnum(KEY);  
    }

    if (iskeyvalid == true)
    {
        string plain = get_string("plaintext:  ");
        string cipher = crypter(plain, KEY);
        printf("ciphertext: %s\n", cipher);
        return 0;
    }
    else
    {
        printf("Usage: %s key\n", FILENAME);
        return 1;
    }
}

// Converts string to int.
int strtoint(string text)
{
    int sum = 0;
    int mul = 1;
    
    for (int i = 0; i < strlen(text); i++)
    {
        mul = 1;  
        
        for (int j = i + 1; j < strlen(text); j++)
        {
            mul *= 10;
        }
        sum += (text[i] - OFFSET) * mul;
    }
    
    return sum;
}

// Returns true if string value is a number.
bool isnum(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isdigit(text[i]) == 0)
        {
            return false;
        }
    }
    
    return true;
}

// Returns crypted text.
string crypter(string plain, string key)
{
    int num = strtoint(key);
    string cipher = (char *)malloc(strlen(plain) * sizeof(char *));
        
    for (int i = 0; i < strlen(plain); i++)
    {
        
        // If char is not space or comma.
        if (plain[i] != 32 && plain[i] != 44)
        {
            int c = plain[i] + num;
            
            // Map characters in ASCII.
            if ((c < 123 && c > 96) || (c < 91))
            {
                cipher[i] = c;  
            }
            else
            {
                cipher[i] = plain[i] - num;
            }
        }
        else
        {
            cipher[i] = plain[i];
        } 
    }
    
    return cipher;
}
