/*********************************************
*   Project: Sistemas Operativos II - Practica 1
*
*   Program name: pd.c
*
*   Author: Ángel García Collado
*
*   Date created: 12-03-2022
*
*   Porpuse: Eliminación de los subdirectorios de los estudiantes.
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

    if(system("rm -rf estudiantes/")==-1){
        fprintf(stderr,"[PD] Error al eliminar estudiantes\n");
    }
    printf("[PD] El directorio estudiantes ha sido borrado.\n");
    
    return EXIT_SUCCESS;       
}