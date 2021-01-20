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
    byte *bgr;
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
    char width[3]={0};
    char height[3]={0};
    //ReadImage("/home/np/Desktop/mestrado/trabf/trabf/1.bmp", &pixels, &width, &height,&bytesPerPixel);

    FILE *fptr;
    fptr = fopen("/home/np/Desktop/mestrado/trabf/trabf/2.ppm","r");
    fseek(fptr, 0, SEEK_END);
    int length = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
   // fread(&width, 3, 5, fptr);
    fseek(fptr, 3, SEEK_SET);
    fread(width, 4, 1, fptr);
    fseek(fptr, 7, SEEK_SET);
    fread(height, 9, 1, fptr);


    if(fptr == NULL)
    {
        printf("Error!");
        //exit(1);
    }

    pixel.matrix = (Matrix**)malloc((sizeof (Matrix*))*((int)height+1));
    for (int i = 0; i < (int)height; i++)
    {
        pixel.matrix[i] = (Matrix*)malloc((sizeof (Matrix))*((int)width+1));
        for (int j = 0; j <(int) width; j++){
            pixel.matrix[i][j].bgr = (byte*)malloc((sizeof (byte)*5));
            for(int k = 0; k < 5; k++){

                pixel.matrix[i][j].bgr[k]=0;

            }

        }
    }
    fclose(fptr);

    unsigned char header[14]={0};
    for (int h =0;h<14;h++){
        header[h]=fgetc(fptr);
    }
/*
    int auxKernel[3][3];
    int cout=0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){
             //fseek( fptr, sizeof (byte)*2, SEEK_SET );

            for(int k = 0; k < 5; k++){


                pixel.matrix[i][j].bgr[k]=fgetc(fptr);//fgetc(fptr);//fgetc(fptr);//rand() % 256;
                //pixel.matrix[i][j].bgr[0]=255;
                //pixel.matrix[i][j].bgr[1]=0;
               // pixel.matrix[i][j].bgr[2]=255;
                //printf("%d",pixel.matrix[i][j].bgr[k]);
            }




        }
    }
    fclose(fptr);
    int size=  height * width * 4;
    FILE *fout = fopen("/home/np/Desktop/mestrado/trabf/trabf/32bit.bmp", "wb");
    fwrite(header, 1, 53, fout);
    unsigned char bmppad[3] = {0,0,0};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++){

            fwrite( (const void*)pixel.matrix[i][j].bgr, 1, sizeof (byte)*5, fout);

        }
    }
    fclose(fout);
*/

    return 0;
}
