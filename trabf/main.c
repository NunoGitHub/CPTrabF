#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
int main()
{
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
