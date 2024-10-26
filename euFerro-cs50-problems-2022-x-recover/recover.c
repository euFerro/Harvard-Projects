#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check cmd-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover file_name\n");
        return 1;
    }
    // Open file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    // JPEG count
    int count = 0;

    // Create buffer
    typedef uint8_t BYTE;
    const int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];

    // Output variables
    char *file_name = malloc(8 * sizeof(char));
    FILE *output_file = NULL;

    // Loop
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if ((buffer[0] == 0xff &&  buffer[1] == 0xd8) && (buffer[2] == 0xff && (0xe3 & 0xf0) == 0xe0))
        {
            // first img
            if (count == 0)
            {
                sprintf(file_name, "%03i.jpg", count);
                output_file = fopen(file_name, "w");
                fwrite(buffer, 1, 512, output_file);
            }
            else
            {
                // For other JPEG other than the first one
                fclose(output_file);
                sprintf(file_name, "%03i.jpg", count);
                output_file = fopen(file_name, "w");
                fwrite(buffer, 1, 512, output_file);
            }
            count++;
        }
        else
        {
            // If already found a file and block isn't a JPEG
            if (count > 0)
            {
                fwrite(buffer, 1, 512, output_file);
            }
        }
    }
    // Close input streams and free some memory
    free(file_name);
    fclose(input);
    fclose(output_file);
    return 0;
}