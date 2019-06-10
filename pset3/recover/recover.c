/**
 * Solition of Recover Assigment for Harvard CS50 Class
 *
 * Name  : Ridvan Altun
 * Date  : 10/06/2019
 * Email : ridvanaltun@outlook.com
 */
 
#include <stdio.h>
#include <stdlib.h>

// Defines
#define FILENAME argv[0]
#define RAW argv[1]
#define BUFFER_SIZE 512
#define true 1
#define false 0
#define bool int

// Prototypes
int recover(char *filename);
char *createname(int num);
int digitcount(int num);
int getdigit(int num, int th);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s image\n", FILENAME);
        return 1;
    }
    
    int err = recover(RAW);
    
    if (err)
    {
        return err;
    }
    
    return 0;
}

// Recovers jpeg files from raw data. Returns error code, if any.
int recover(char *filename)
{   
    // open raw file
    FILE *raw = fopen(filename, "r");
    if (!raw)
    {
        fprintf(stderr, "Could not open %s.\n", filename); 
        return 2;
    }
    
    // create buffer
    unsigned char buffer[BUFFER_SIZE];
    
    // for naming purpose
    int counter = 0;
    
    // file
    FILE *image;
    
    // readed size
    size_t size;
    
    // find first jpeg
    while (true)
    {
        fread(&buffer, BUFFER_SIZE, 1, raw);
            
        // find first jpeg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe0)
        {
            break;
        }
    }
    
    // go on the process
    while (true)
    { 
        // ensure jpeg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe0)
        {
            if (counter != 0)
            {
                fclose(image);
            }
            
            // create a new file
            image = fopen(createname(counter), "w");
            
            counter++;
        }
        
        // write buffer to image
        fwrite(&buffer, BUFFER_SIZE, 1, image);
        
        // read raw data and write to buffer
        size = fread(&buffer, BUFFER_SIZE, 1, raw);
        
        // EOF 
        if (size != 1)
        {
            // save last image
            fclose(image);
            
            // break the loop
            break;
        }
    }

    fclose(raw);

    return 0;
}

// Create a name for a file. Returns e.g. 025.jpg, 009.jpg so on.
char *createname(int num)
{   
    // 3 + 1 bytes
    char *name = malloc(sizeof(char) * 3 + 1);
    
    int one = getdigit(num, 1);
    int two = getdigit(num, 2);
    int three = getdigit(num, 3);
    
    sprintf(name, "%i%i%i.jpg", three, two, one);
        
    return name;
}

// Returns digit count.
int digitcount(int num)
{
    int count = 0;
    
    while (num != 0)
    {
        num /= 10;
        count++;
    }

    return count;
}

// Returns .th digit, it works right to left, e.g. 123 -> 3 -> 1.th
int getdigit(int num, int th)
{
    int count = digitcount(num);
    
    // ensure th value is not big from digit count
    if (count - th < 0)
    {
        // if th value wrong, returns 0
        return 0;
    }
    
    // if the number has only one digit, returns number itself
    if (count == 1)
    {
        return num;
    }
    
    // main logic of this function
    for (int i = 0; i < th - 1; i++)
    {
        num /= 10;
    }
    
    return num % 10;
}
