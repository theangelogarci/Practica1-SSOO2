/*********************************************
*   Project: Sistemas Operativos II - Practica 1
*
*   Program name: demonio.c
*
*   Author: Ángel García Collado
*
*   Date created: 12-03-2022
*
*   Porpuse: Demonio que hace copia de seguridad de todo lo ocurrido.
*
*   Revision History: Esta disponible en el repositorio de Github, pero tengo pocos commits por problemas con el PC.
|*********************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>



int main(int argc, char *argv[]){

    while(1){
        printf("[DEMON] MI PID ES : %ld\n",(long)getpid());
        sleep(60);
        
        if(system("cp -r estudiantes ./backup")==-1){
            fprintf(stderr,"Error al ejecutar proceso demonio\n");
            exit(EXIT_FAILURE);
        }
    }
    
    return EXIT_SUCCESS;       
}
