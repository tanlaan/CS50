/**
 * Resizes a bitmap by whole integer numbers.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    // ensure that n a positive integer and less than 100
    else if (atoi(argv[1]) < 0 || atoi(argv[1]) > 100)
    {
        fprintf(stderr, "n must be a positive integer and less than 100\n");
        return -1;
    }

    // save multiplier
    int mult = atoi(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

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
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // modify outfile's BITMAPINFOHEADER
    BITMAPINFOHEADER biResize = bi;
    // increase width and height of BITMAPINFOHEADER by multiplier
    biResize.biWidth = bi.biWidth * mult;
    biResize.biHeight = bi.biHeight * mult;
    // determine padding for scanlines for original and resize file
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingResize = (4 - (biResize.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // correct resize's biSizeImage
    biResize.biSizeImage = (biResize.biWidth * sizeof(RGBTRIPLE) + paddingResize) * abs(biResize.biHeight);

    // modify outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER bfResize = bf;
    bfResize.bfSize = biResize.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfResize, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biResize, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int i = 0, count = 1, biHeight = abs(bi.biHeight); i < biHeight; count++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            for (int k = 0; k < mult; k++)
            {
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // skip over padding, if any in original file
        fseek(inptr, padding, SEEK_CUR);

        // add resized file padding
        for (int k = 0; k < paddingResize; k++)
        {
            fputc(0x00, outptr);
        }
        // check that we've written a 'mult' amount of height pixels
        if (count == mult)
        {
            count = 0;
            i++;
        }
        // otherwise rewind file input to beginning of width line
        else
        {
            fseek(inptr, (-1 * ((bi.biWidth * sizeof(RGBTRIPLE)) + padding)), SEEK_CUR);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
