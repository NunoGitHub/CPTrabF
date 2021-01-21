#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0032
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
    byte *rgb;
};
typedef struct Matrix Matrix;

struct Pixel{
    Matrix **matrix;
}pixel;



int main()
{
    int sharpenKernel[3][3];
    sharpenKernel[0][0]=0; sharpenKernel[1][0]=-1;sharpenKernel[1][1]=-5;sharpenKernel[1][2]=-1;
    sharpenKernel[0][1]= -1;sharpenKernel[2][0]=0;sharpenKernel[2][1]=-1;sharpenKernel[2][2]=0;
    sharpenKernel[0][2]=0;
    char *width= (char*)malloc(sizeof (char));
    char height[3]={0};
    const char* nameFile= "/home/np/Desktop/mestrado/trabf/trabf/2.ppm";

    FILE *fptr;
    fptr = fopen(nameFile,"r");
    fseek(fptr, 0, SEEK_END);
    int length = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    // fread(&width, 3, 5, fptr);
    fseek(fptr, 3, SEEK_SET);
    fread(width, 4, 1, fptr);
    fseek(fptr, 7, SEEK_SET);
    fread(height, 8, 1, fptr);
    fclose(fptr);

    short widthAux=atoi(width);
    short heightAux = atoi(height);



    if(fptr == NULL)
    {
        printf("Error!");
        //exit(1);
    }

    pixel.matrix = (Matrix**)malloc((sizeof (Matrix*))*(heightAux));
    for (int i = 0; i < heightAux; i++)
    {
        pixel.matrix[i] = (Matrix*)malloc((sizeof (Matrix))*(widthAux));
        for (int j = 0; j < widthAux; j++){
            pixel.matrix[i][j].rgb = (byte*)malloc((sizeof (byte)*3));
            for(int k = 0; k < 3; k++){

                pixel.matrix[i][j].rgb[k]=0;

            }

        }
    }
    fptr = fopen(nameFile,"r");
    unsigned char header[15]={0};
    fseek(fptr, 0, SEEK_SET);
    fread(header, 15, 1, fptr);


    for (int i = 0; i < heightAux; i++)
    {
        for (int j = 0; j < widthAux; j++){
            for(int k = 0; k < 3; k++){
                pixel.matrix[i][j].rgb[k]=fgetc(fptr);
            }

        }
    }
    fclose(fptr);


    FILE *fout = fopen("/home/np/Desktop/mestrado/trabf/trabf/3.ppm", "wb");
    fwrite(header, 1, 15, fout);
    for (int i = 0; i < heightAux; i++)
    {
        for (int j = 0; j < widthAux; j++){

            fwrite( (const void*)pixel.matrix[i][j].rgb, 1, sizeof (byte)*3, fout);

        }
    }
    fclose(fout);


    return 0;
}
