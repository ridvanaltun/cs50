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
int strtoint(char *text);
bool isnum(char *text);
char *crypter(char *plain, char *key);

int main(int argc, char *argv[])
{
    bool iskeyvalid = false;
    
    if (argc == 2)
    {
        iskeyvalid = isnum(KEY);  
    }

    if (iskeyvalid)
    {
        char *plain = get_string("plaintext:  ");
        char *cipher = crypter(plain, KEY);
        printf("ciphertext: %s\n", cipher);
        
        free(cipher);
        return 0;
    }
    else
    {
        printf("Usage: %s key\n", FILENAME);
        return 1;
    }
}

// Converts string to int.
int strtoint(char *text)
{
    int sum = 0, mul = 1;
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        mul = 1;  
        
        for (int j = i + 1, m = strlen(text); j < m; j++)
        {
            mul *= 10;
        }
        sum += (text[i] - OFFSET) * mul;
    }
    
    return sum;
}

// Returns true if string value is a number.
bool isnum(char *text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isdigit(text[i]) == 0)
        {
            return false;
        }
    }
    
    return true;
}

// Returns crypted text.
char *crypter(char *plain, char *key)
{
    int num = strtoint(key);
    char *cipher = malloc((strlen(plain) + 1) * sizeof(char));
        
    for (int i = 0, n = strlen(plain); i < n; i++)
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
