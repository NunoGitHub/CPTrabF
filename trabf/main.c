#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0

typedef unsigned int int32;
typedef short int16;
typedef unsigned char byte;

void ReadImage(const char *fileName,byte **pixels, int32 *width, int32 *height, int32 *bytesPerPixel)
{
        FILE *imageFile = fopen(fileName, "rb");
        int32 dataOffset;
        fseek(imageFile, DATA_OFFSET_OFFSET, SEEK_SET);
        fread(&dataOffset, 4, 1, imageFile);
        fseek(imageFile, WIDTH_OFFSET, SEEK_SET);
        fread(width, 4, 1, imageFile);
        fseek(imageFile, HEIGHT_OFFSET, SEEK_SET);
        fread(height, 4, 1, imageFile);
        int16 bitsPerPixel;
        fseek(imageFile, BITS_PER_PIXEL_OFFSET, SEEK_SET);
        fread(&bitsPerPixel, 2, 1, imageFile);
        *bytesPerPixel = ((int32)bitsPerPixel) / 8;

        int paddedRowSize = (int)(4 * ceil((float)(*width) / 4.0f))*(*bytesPerPixel);
        int unpaddedRowSize = (*width)*(*bytesPerPixel);
        int totalSize = unpaddedRowSize*(*height);
        *pixels = (byte*)malloc(totalSize);
        int i = 0;
        byte *currentRowPointer = *pixels+((*height-1)*unpaddedRowSize);
        for (i = 0; i < *height; i++)
        {
            fseek(imageFile, dataOffset+(i*paddedRowSize), SEEK_SET);
            fread(currentRowPointer, 1, unpaddedRowSize, imageFile);
            currentRowPointer -= unpaddedRowSize;
        }

        fclose(imageFile);
}

void test()
{
    byte *pixels;
    int32 width;
    int32 height;
    int32 bytesPerPixel;
    ReadImage("/home/np/Desktop/mestrado/Computação Paralela/trabf/trabf/1.bmp", &pixels, &width, &height,&bytesPerPixel);

    printf("%d\n",width);
    printf("%d\n",height);
    printf("%d\n",bytesPerPixel);
}

int main()
{
    test();
    FILE *fptr;
    fptr = fopen("/home/np/Desktop/mestrado/Computação Paralela/trabf/trabf/1.bmp","r");
    if(fptr == NULL)
      {
         printf("Error!");
         //exit(1);
      }
    fseek(fptr, 0, SEEK_END);
    int length = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    unsigned char * ola = malloc( length*sizeof (fptr) );
    for(int i = 0; i < length; i++){
        *(ola+i) = (unsigned char)malloc(sizeof (fgetc(fptr)) );
        //fputc(fgetc(fptr), (unsigned char) ola[i]);
        ola[i]=fgetc(fptr);
        printf("%c", ola[i]);
    }
    fclose(fptr);

    return 0;
}
