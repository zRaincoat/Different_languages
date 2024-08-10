#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
  FILE* input = fopen(argv[1], "r");
  if(argc != 2)
  {
    printf("Usage: ./recover IMAGE\n");
    return 1;
  }
  if(input == NULL)
  {
    printf("Can not open the file.\n");
    return 2;
  }
 int n = 0;
 FILE* img = NULL;
 char* filename = malloc(sizeof(char) * 8);
  BYTE buffer[512];
  while(fread(buffer, sizeof(BYTE)*512, 1, input)==1)
  {
    if(buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3]&0xF0) == 0xE0)
    {       if(img != NULL)
            {
                fclose(img);
            }
          sprintf(filename, "%03d.jpg", n++);
          img = fopen(filename, "w");
          fwrite(buffer, sizeof(BYTE)*512, 1, img);
    }
  }
  free(filename);
  fclose(input);
     if (img != NULL)
     {
      fclose(img);
     }

}