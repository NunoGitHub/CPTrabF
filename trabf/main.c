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
struct Matrix{
    byte *bgr;
};
typedef struct Matrix Matrix;

struct Pixel{
    Matrix **matrix;
}pixel;



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

    int paddedRowSize = 4 * (*width) * (*height);//(int)(4 * ceil((float)(*width) / 4.0f))*(*bytesPerPixel);


    fclose(imageFile);

}

int main()
{
    // test();
    byte *pixels;
    int32 width;
    int32 height;
    int32 bytesPerPixel;
    ReadImage("/home/np/Desktop/mestrado/trabf/trabf/1.bmp", &pixels, &width, &height,&bytesPerPixel);

    FILE *fptr;
    fptr = fopen("/home/np/Desktop/mestrado/trabf/trabf/1.bmp","r");
    if(fptr == NULL)
    {
        printf("Error!");
        //exit(1);
    }

    pixel.matrix = (Matrix**)malloc((sizeof (Matrix*))*height);
    for (int i = 0; i < height; i++)
    {
        pixel.matrix[i] = (Matrix*)malloc((sizeof (Matrix))*width);
        for (int j = 0; j <(int) width; j++){
            pixel.matrix[i][j].bgr = (byte*)malloc((sizeof (byte)*3));
            for(int k = 0; k < 3; k++){

                pixel.matrix[i][j].bgr[k]=0;

            }

        }
    }
    fseek(fptr, 0, SEEK_END);
    int length = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    unsigned char header[54]={0};
    for (int h =0;h<54;h++){
        header[h]=fgetc(fptr);
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){

            for(int k = 0; k < 3; k++){
                pixel.matrix[i][j].bgr[k]=fgetc(fptr);
            }

        }
    }
    fclose(fptr);
    int size=  height * width * 4;
    FILE *fout = fopen("/home/np/Desktop/mestrado/trabf/trabf/32bit.bmp", "wb");
    fwrite(header, 1, 54, fout);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){

            fwrite( (const void*)pixel.matrix[i][j].bgr, 1, sizeof (byte)*3, fout);
        }
    }
    fclose(fout);


    return 0;
}
