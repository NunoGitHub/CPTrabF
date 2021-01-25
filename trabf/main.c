﻿#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string.h>


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
static int headerLenght=0;

int main()
{
    double wtime;

    int sharpenKernel[3][3];
    char *width= (char*)malloc(sizeof (char));
    char height[3]={0};
    FILE *fptr;
    const char* nameFile= "/home/np/Desktop/mestrado/trabf/trabf/teste3.ppm";
    short widthAux;
    short heightAux;
    unsigned char* header= (unsigned char*)(malloc(sizeof (byte)*78));
    fptr = fopen(nameFile,"r");
    int count=0;
    int auxCount=0;
    byte auxHeader [78]={0};

    //obter o header e o seu tamanho
    while(auxCount!=3 ){
        auxHeader[count]=fgetc(fptr);
        if(auxHeader[count]==10) auxCount++;
        count++;
       headerLenght=count;
    }
    auxHeader[headerLenght+1]=NULL;
    memcpy(header,auxHeader,sizeof (unsigned char*)*headerLenght);

    hd(fptr,&nameFile[0],width,&height[0]);

    widthAux=atoi(width);
    heightAux = atoi(height);

    matrizes(heightAux,widthAux);
    PreenchePixeis(fptr,nameFile,heightAux,widthAux,header);

    wtime = omp_get_wtime();
    Kernel(&sharpenKernel[0][0],heightAux,widthAux);
    wtime = omp_get_wtime() - wtime;

    EscreveFicheiro(&header[0],heightAux,widthAux);

    printf("\nTime:%f\n",wtime);
    return 0;
}


//obter a altura e largura das imagens
void hd(FILE *fptr,const char* nameFile,char *width,char* height)
{
    fptr = fopen(nameFile,"r");
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
//fazer a alocação da memoria para as estruturas
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
//copiar os pixeis da imagem para a estrutura pixel
void PreenchePixeis(FILE *fptr,const char *nameFile,short heightAux,short widthAux, unsigned char* header)
{

    fptr = fopen(nameFile,"r");
    byte headerAux[20];
    fseek(fptr, 0, SEEK_SET);
    fread(headerAux, headerLenght, 1, fptr);


    for (int i = 0; i < heightAux; i++)
    {
        for (int j = 0; j < widthAux; j++){
            for(int k = 0; k < 3; k++){
                pixel.matrix[i][j].rgb[k]=fgetc(fptr);
                pixelAux.matrix[i][j].rgb[k]=pixel.matrix[i][j].rgb[k];
            }
        }
    }
    fclose(fptr);
}
// aplicação do kernel na imagem
void Kernel(int sharpenKernel[3][3], short heightAux,short widthAux)
{
    sharpenKernel[0][0]=0; sharpenKernel[1][0]=-1;sharpenKernel[1][1]=5;sharpenKernel[1][2]=-1;
    sharpenKernel[0][1]= -1;sharpenKernel[2][0]=0;sharpenKernel[2][1]=-1;sharpenKernel[2][2]=0;
    sharpenKernel[0][2]=0;

    float weightedSum=0;
    for (int i = 1; i < heightAux; i++)
    {
        for (int j = 1; j < widthAux; j++){
            for(int rgb = 0; rgb < 3; rgb++){

                for (int kX=-1; kX<2;kX++){
                    for (int kY=-1; kY<2;kY++){
                        weightedSum+= (pixel.matrix[i+kX][j+kY].rgb[rgb]*sharpenKernel[kX+1][kY+1]);
                    }
                }
                int weightedSumAux = (int)(abs(weightedSum));
                pixelAux.matrix[i][j].rgb[rgb]= weightedSumAux%256;
                weightedSum=0;
            }
            if((j+2)>= widthAux)j=widthAux;
        }
        if((i+2)>=heightAux)i=heightAux;
    }
}
//criar uma nova imagem com os pixeis resultantes da computação do kernel
void EscreveFicheiro(const char *header, short heightAux,short widthAux)
{
    FILE *fout = fopen("/home/np/Desktop/mestrado/trabf/trabf/3.ppm", "wb");
    fwrite(header, 1, headerLenght, fout);
    for (int i = 0; i < heightAux; i++)
    {
        for (int j = 0; j < widthAux; j++){

            fwrite( (const void*)pixelAux.matrix[i][j].rgb, 1, sizeof (byte)*3, fout);

        }
    }
    fclose(fout);
}





