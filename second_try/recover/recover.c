#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Couldn't open the file.\n");
        return 2;
    }

    BYTE buffer[512];
    int counter = 0;
    char filename[12];

    FILE* img = NULL;

    while(fread(buffer, 1, 512, card) == 512)
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if(img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", counter);
            counter++;
            img = fopen(filename, "w");
        }

        if(img != NULL)
        {
            fwrite(buffer, 1, 512, img); 
        }
    }

    if(img != NULL)
    {
        fclose(img);
    }

    fclose(card);

    return 0;
}
