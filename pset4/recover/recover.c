/*
    This program will recover jpeg images from a file. In the usual case, this is a .raw forensic dump of the afflicted storage.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check for correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover file.raw\n");
        return 1;
    }

    // filename from input
    char *infile = argv[1];
    // !!! have to create outfile's size for sprintf to function correctly
    char outfile[8] = { };

    // open recovery file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open file for recovery\n");
        return 2;
    }

    // 512 byte buffer (!!! has to be unsigned to get the full 512 out of it)
    unsigned char buffer[512];

    // jpeg counter
    int jpgCount = 0;

    // jpeg found
    bool jpgFound = false;

    // jpeg file pointer
    FILE *outptr;

    // read into buffer as long as we haven't hit EOF (when fread returns less than the amount of bytes we want)
    while(fread(buffer, 1, 512, inptr) == 512)
    {
        // check for jpeg
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // first run through of finding a jpeg, state that we've found one
            if (!jpgFound)
            {
                jpgFound = true;
            }
            // open output file using current jpgCount as name
            sprintf(outfile, "%03i.jpg", jpgCount);
            outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Couldn't open %s for writing", outfile);
                return 2;
            }
            // increment our jpeg counter
            jpgCount += 1;
            // write the current buffer to our newly opened file
            fwrite(buffer, 1, 512, outptr);

        }
        else if (!jpgFound)
        {
            // drop this buffer because we haven't found a jpeg yet
        }
        else
        {
            // we've already found a jpeg and we don't have the start of a jpeg, so write the 512 bytes to file
            fwrite(buffer, 1, 512, outptr);
        }
    }

    fclose(outptr);
    return 0;
}

