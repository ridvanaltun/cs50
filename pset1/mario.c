/**
 * Solution of Mario Assignment for Harvard CS50 Class
 *
 * Name  : Ridvan Altun
 * Date  : 06/04/2019
 * Email : ridvanaltun@outlook.com
 */

#include <cs50.h>
#include <stdio.h>

// Prototypes
int get_height(int min, int max);
void print_bricks(int height);

int main(void)
{
    int height = get_height(1, 8);
    print_bricks(height);
}

// Get value from the user until get an appropriate value.
int get_height(int min, int max)
{
    int num;

    do
    {
        num = get_int("Height : "); 
    }
    while (num < min || num > max);

    return num;
}

// Print hash bricks.
void print_bricks(int height)
{
    for (int i = 0; i < height; i++)
    {
        // Print left bricks.
        for (int j = 0; j < height; j++)
        {
            if (height - 1 - i > j)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        
        // Print middle space.
        printf("  ");
        
        // Print right bricks.
        for (int k = 0; k < height; k++)
        {
            if (i < k)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        // Jump to next line.
        printf("\n");
    }
}
