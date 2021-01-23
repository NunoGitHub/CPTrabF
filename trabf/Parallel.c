#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>


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
}pixel, pixelAux;


void hd(FILE*,const char*,char*, char*);
void matrizes(short,short);
void PreenchePixeis(FILE*,const char*,short,short,unsigned char*);
void Kernel(int [3][3],short,short);
void EscreveFicheiro(const char*,short,short);

int main()
{
    int sharpenKernel[3][3];
    char *width= (char*)malloc(sizeof (char));
    char height[3]={0};
    FILE *fptr;
    const char* nameFile= "/home/rui/Desktop/TP/CPTrabF/trabf/2.ppm";
    short widthAux;
    short heightAux;
    unsigned char header[15]={0};

    printf("%d\t%d\n",*width,*height);
    hd(fptr,&nameFile[0],width,&height[0]);
    printf("%d\t%d\n",*width,*height);

    widthAux=atoi(width);
    heightAux = atoi(height);

    matrizes(heightAux,widthAux);
    PreenchePixeis(fptr,nameFile,heightAux,widthAux,header);
    Kernel(&sharpenKernel[0][0],heightAux,widthAux);
    EscreveFicheiro(&header[0],heightAux,widthAux);
    return 0;
}



    void hd(FILE *fptr,const char* nameFile,char *width,char* height)
    {



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





    if(fptr == NULL)
    {
        printf("Error!");
        //exit(1);
    }
    }

    void matrizes(short heightAux,short widthAux)
    {

    pixel.matrix = (Matrix**)malloc((sizeof (Matrix*))*(heightAux));
    pixelAux.matrix = (Matrix**)malloc((sizeof (Matrix*))*(heightAux));
    for (int i = 0; i < heightAux; i++)
    {
        pixel.matrix[i] = (Matrix*)malloc((sizeof (Matrix))*(widthAux));
         pixelAux.matrix[i] = (Matrix*)malloc((sizeof (Matrix))*(widthAux));
        for (int j = 0; j < widthAux; j++){
            pixel.matrix[i][j].rgb = (byte*)malloc((sizeof (byte)*3));
             pixelAux.matrix[i][j].rgb = (byte*)malloc((sizeof (byte)*3));
            for(int k = 0; k < 3; k++){

                pixel.matrix[i][j].rgb[k]=0;
                 pixelAux.matrix[i][j].rgb[k]=0;

            }

        }
    }
    }

    void PreenchePixeis(FILE *fptr,const char *nameFile,short heightAux,short widthAux, unsigned char* header)
    {
    fptr = fopen(nameFile,"r");

    fseek(fptr, 0, SEEK_SET);
    fread(header, 15, 1, fptr);


    for (int i = 0; i < heightAux; i++)
    {
        for (int j = 0; j < widthAux; j++){
            for(int k = 0; k < 3; k++){
                pixel.matrix[i][j].rgb[k]=fgetc(fptr);
                if(i<1)
                printf("%d ", pixel.matrix[i][j].rgb[k] );
            }


        }
        if(i<1)
        printf("\n\n");
    }
    fclose(fptr);
    }

void Kernel(int sharpenKernel[3][3], short heightAux,short widthAux)
{
    sharpenKernel[0][0]=0; sharpenKernel[1][0]=-1;sharpenKernel[1][1]=5;sharpenKernel[1][2]=-1;
    sharpenKernel[0][1]= -1;sharpenKernel[2][0]=0;sharpenKernel[2][1]=-1;sharpenKernel[2][2]=0;
    sharpenKernel[0][2]=0;


    //apply kernel
    float weightedSum=0;
    int divider=0;
    int r=0;


    omp_set_num_threads(4);
    #pragma omp parallel for
    for (int i = 0; i < heightAux; i++)
    {
        for (int j = 0; j < widthAux; j++){


            for(int rgb = 0; rgb < 3; rgb++){

                for (int kX=-1; kX<2;kX++){
                    for (int kY=-1; kY<2;kY++){
                        if ((i+kX)<0) kX=0;
                        if((i+kX)>=heightAux)break;
                        if(j+kY<0) kY=0;
                        if(j+kY>= widthAux) break;
                        divider++;
                        weightedSum+= (pixel.matrix[i+kX][j+kY].rgb[rgb]*sharpenKernel[kX+1][kY+1]);

                    }
                }
                if(divider<=8)weightedSum=weightedSum*0.5;

                int weightedSumAux = (int)(abs(weightedSum));
                pixelAux.matrix[i][j].rgb[rgb]= weightedSumAux%256;
                divider=0;
                weightedSum=0;

            }


        }
    }
}

void EscreveFicheiro(const char *header, short heightAux,short widthAux)
{
    FILE *fout = fopen("/home/rui/Desktop/TP/CPTrabF/trabf/novo2.ppm", "wb");
    fwrite(header, 1, 15, fout);
    for (int i = 0; i < heightAux; i++)
    {
        for (int j = 0; j < widthAux; j++){

            fwrite( (const void*)pixelAux.matrix[i][j].rgb, 1, sizeof (byte)*3, fout);

        }
    }
    fclose(fout);
}





