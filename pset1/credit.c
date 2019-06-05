/**
 * Solition of Credit Assigment for Harvard CS50 Class
 *
 * Name  : Ridvan Altun
 * Date  : 06/05/2019
 * Email : ridvanaltun@outlook.com
 */

#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Prototypes
bool is_valid(long num);
bool is_valid_length(long num);
int get_digit_count(long num);
int get_digit(long num, int n);
void print_card_type(long num);

int main(void)
{
    long num = get_long("Number: ");
    bool isValid = is_valid(num);
	
	if(isValid == false)
	{
		printf("INVALID\n");
		return 0;
	}
	else
	{
		// Check for Visa, Mastercard or American Express.
		print_card_type(num);
        return 0;
	}
}

// Verify valid card number.
bool is_valid(long num)
{
	bool isValid = is_valid_length(num);
	
	if(isValid == false)
	{
		return false;
	}
	else
	{
		// Luhn's Algorithm
		
		int sum = 0;
		int digit = 0;
        int numDigit = 0;
		int numDigitCount = get_digit_count(num);
		
		for(int i = 1; i < numDigitCount; i += 2)
		{
            numDigit = get_digit(num, i);            
            int digitCount = get_digit_count(numDigit * 2);
            
            for(int j = 0; j < digitCount; j++)
            {
                digit = get_digit(numDigit * 2, j);
                sum += digit;
            }
		}
        
        for(int k = 0; k < numDigitCount; k += 2)
        {
            digit = get_digit(num, k);
            sum += digit;
        }
        
        if(sum % 10 == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
	}
}

// Verify card number length.
bool is_valid_length(long num)
{
    int digitCount = get_digit_count(num);
	
	// American Express -> 15, Visa -> 13 and 16, MasterCard -> 16
	if(digitCount > 16 || digitCount < 13 || digitCount == 14)
    {
		return false;
	}
	else
	{
		return true;
	}
}

// Get digit count of card number.
int get_digit_count(long num)
{
    int digitCount = 0;
    
    while(num != 0)
    {
        num = num / 10;
        digitCount++;
    }
    
    return digitCount;
}

// Get digit of card number.
int get_digit(long num, int n)
{
    long r, t1, t2;

    t1 = pow(10, n+1);
    r = num % t1;

    if (n > 0)
    {
        t2 = pow(10, n);
        r = r / t2;
    }

    return r;
}

// Print credit card's type, e.g. Visa or American Express.
void print_card_type(long num)
{
	int numDigitCount = get_digit_count(num);
	int first = get_digit(num, numDigitCount - 1);
	int second = get_digit(num, numDigitCount - 2);
	int headerNum = (first * 10) + second;
	
	if(headerNum == 34 && headerNum == 37)
	{
		printf("AMEX\n");
	}
	else if(headerNum >= 51 || headerNum <= 55 )
	{
		printf("MASTERCARD\n");
	}
	else if(first == 4)
	{
		printf("VISA\n");
	}
	else
	{
		printf("INVALID\n");
	}
}