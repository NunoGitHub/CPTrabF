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
    /*FILE *fp;
    //fp = fopen("/home/np/Desktop/mestrado/Computação Paralela/trabf/trabf/2.bmp" ,"w");
    */
    char * ola = malloc(sizeof (fptr) );

    for(int i = 0; i < length; i++){
        *(ola+i) = (char)malloc(4*sizeof (fgetc(fptr)) );
        fputc(fgetc(fptr), *(ola+i));
        printf("%c", *(ola+i));
    }
    printf("c%",ola);
    /*fclose(fp);*/
    fclose(fptr);

    int a=0;
    return 0;
}
