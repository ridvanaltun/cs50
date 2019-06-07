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
bool is_valid_len(long num);
int get_digit_count(long num);
int get_digit(long num, int n);
void print_card_type(long num);

int main(void)
{
    long num = get_long("Number: ");
    bool valid = is_valid(num);
    
    if (valid == false)
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
    bool valid = is_valid_len(num);
    
    if (valid == false)
    {
        return false;
    }
    else
    {
        // Luhn's Algorithm
        
        int sum = 0;
        int digit = 0;
        int num_digit = 0;
        int num_digit_count = get_digit_count(num);
        
        for (int i = 1; i < num_digit_count; i += 2)
        {
            num_digit = get_digit(num, i);            
            int digit_count = get_digit_count(num_digit * 2);
            
            for (int j = 0; j < digit_count; j++)
            {
                digit = get_digit(num_digit * 2, j);
                sum += digit;
            }
        }
        
        for (int k = 0; k < num_digit_count; k += 2)
        {
            digit = get_digit(num, k);
            sum += digit;
        }
        
        if (sum % 10 == 0)
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
bool is_valid_len(long num)
{
    int digit_count = get_digit_count(num);
    
    // American Express -> 15, Visa -> 13 and 16, MasterCard -> 16
    if (digit_count > 16 || digit_count < 13 || digit_count == 14)
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
    int digit_count = 0;
    
    while (num != 0)
    {
        num = num / 10;
        digit_count++;
    }
    
    return digit_count;
}

// Get digit of card number.
int get_digit(long num, int n)
{
    long r, t1, t2;

    t1 = pow(10, n + 1);
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
    int num_digit_count = get_digit_count(num);
    int first = get_digit(num, num_digit_count - 1);
    int second = get_digit(num, num_digit_count - 2);
    int header_num = (first * 10) + second;
    
    if (header_num == 34 && header_num == 37)
    {
        printf("AMEX\n");
    }
    else if (header_num >= 51 || header_num <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if (first == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}