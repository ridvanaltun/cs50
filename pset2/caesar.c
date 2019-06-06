/**
 * Solition of Caesar Assigment for Harvard CS50 Class
 *
 * Name  : Ridvan Altun
 * Date  : 06/06/2019
 * Email : ridvanaltun@outlook.com
 */
 
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Defines
#define filename argv[0]
#define key argv[1]
#define offset 48

// Prototypes
int strtoint(string text);
bool isnum(string text);

int main(int argc, string argv[])
{
    bool iskeynum = false;
    
    if (argc == 2)
    {
        iskeynum = isnum(key);  
    }

    if (argc == 2 && iskeynum == true)
    {
        int num = strtoint(key);
        string plain = get_string("plaintext:  ");
        char cipher[strlen(plain)];
        
        // Crypter.
        for (int i = 0; i < strlen(plain); i++)
        {
            // If char is not space or comma.
            if (plain[i] != 32 && plain[i] != 44)
            {
                int place = plain[i] + num;
                
                // Map characters in ASCII.
                if ((place < 123 && place > 96) || (place < 91))
                {
                    cipher[i] = plain[i] + num;   
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
        
        printf("ciphertext: %s\n", cipher);
        return 0;
    }
    else
    {
        printf("Usage: %s key\n", filename);
        return 1;
    }
}

// Convert string to int.
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
        sum += (text[i] - offset) * mul;
    }
    
    return sum;
}

// Return true if string value is a number.
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
