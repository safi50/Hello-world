#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//defining block size
#define BLOCKSIZE 512

int inputError()
{
    printf("Usage ./recover image\n");
    return 1;
}

// defining errors
int fileError(char filename[])
{
    printf("Unable to open file: %s\n", filename);
    return 1;
}

// verifying jpg header
bool isjpgheader(uint8_t buffer[])
{
    // check the header with signature jpg

    return buffer[0] == 0xff
           && buffer[1] == 0xd8
           && buffer[2] == 0xff
           && (buffer[3] & 0xf0) == 0xe0;
}


//command line arguments
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return inputError();
    }

    char *inputFile = argv[1];
    if (inputFile == NULL)
    {
        return inputError();
    }

    FILE *inputptr = fopen(inputFile, "r");
    if (inputFile == NULL)
    {
        return fileError(inputFile);
    }
    // creating a string of 8 chars
    char filename[8];
    FILE *outputptr = NULL;
    uint8_t buffer[BLOCKSIZE];
    int jpgCounter = 0;

    while (fread(buffer, sizeof(uint8_t), BLOCKSIZE, inputptr) || feof(inputptr) == 0)
    {
        if (isjpgheader(buffer))
        {
            if (outputptr != NULL)
            {
                fclose(outputptr);
            }
            sprintf(filename, "%03i.jpg", jpgCounter);
            outputptr = fopen(filename, "w");
            jpgCounter++;
        }
        if (outputptr != NULL)
        {
            //write into image
            fwrite(buffer, sizeof(buffer), 1, outputptr);
        }
    }

    if (inputptr == NULL)
    {
        // closing ptrs to avoid segmentation
        fclose(inputptr);
    }
    if (outputptr == NULL)
    {
        // closing ptr to avoid segmentations
        fclose(outputptr);
    }
    // ending code
    return 0;

}
