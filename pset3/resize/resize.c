/**
 * Solition of Resize Assigment for Harvard CS50 Class
 *
 * Name  : Ridvan Altun
 * Date  : 09/06/2019
 * Email : ridvanaltun@outlook.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bmp.h"

// Defines
#define FILENAME argv[0]
#define bool int
#define true 1
#define false 0

// Prototypes
bool isvalid(char *inp);
int resize(int size, char *infile, char *outfile);

int main(int argc, char *argv[])
{
    // size
    char *f = argv[1];

    // ensure proper usage
    if (argc != 4 || !isvalid(f))
    {
        printf("Usage: %s f infile outfile\n", FILENAME);
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    int err = resize(atoi(f), infile, outfile);

    if (err)
    {
        return err;
    }
    
    return 0;
}

// Returns true if input is valid.
bool isvalid(char *inp)
{
    for (int i = 0, n = strlen(inp); i < n; i++)
    {
        // character can be digit or dot else returns false 
        if (!isdigit(inp[i]) && inp[i] != '.')
        {
            return false;
        }
        
        // last character can not be dot
        if (i == n - 1 && inp[i] == '.') 
        {
            return false;
        }
    }

    // input must be between 0 and 100
    if (!(atof(inp) >= 0 && atof(inp) <= 100))
    {
        return false;
    }
        
    return true;
}

// Resize image.
int resize(int f, char *infile, char *outfile)
{
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfo;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // bfo -> outfile's bitmap file header
    bfo = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bio;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // bio -> outfile's bitmap info header
    bio = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int paddi = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddo = (4 - (bi.biWidth * f * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update output file's header information
    bio.biWidth = bi.biWidth * f;
    bio.biHeight = bi.biHeight * f;
    bio.biSizeImage = (bio.biWidth * sizeof(RGBTRIPLE) + paddo) * abs(bio.biHeight);
    bfo.bfSize = bio.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight) * f; i < biHeight; i++)
    {
        // iterate over current scanline f times
        for (int j = 0; j < f; j++)
        {
            // iterate over input value
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile f times
                for (int l = 0; l < f; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add padding to outfile, if any
            for (int k = 0; k < paddo; k++)
            {
                fputc(0x00, outptr);
            }

            // back to top in infile until come to last iteration in current scanline
            if (j < f - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }       
        }

        // skip over padding of infile, if any
        fseek(inptr, paddi, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}