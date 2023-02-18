#include<stdio.h>
#include<stdlib.h>
#include "fonctions.h"

void main(int argc , char* argv[]){
    char *path = ""; //the path to your program file.txt
    TOKEN token;
    tokenNum = 0;
    tmp=0;
    ligne=0;
    init(path);
    Pile *maPile = initialiser();
    PROGRAM();

    if(lexicale() == EOF_TOKEN){
        printf("The code is correct !\n");
    }else{
        printf("The code is incorrect !\n");
    }

    fclose(fichier);
}
