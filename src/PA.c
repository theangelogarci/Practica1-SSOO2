 /*********************************************
*   Project: Sistemas Operativos II - Practica 1
*
*   FIle name: pa.c
*
*   Author: Ángel García Collado
*
*   Date created: 21-02-2022
*
*   Porpuse: Crea los subdirectorios necesarios para cada estudante.
*
*   Revision History: Esta disponible en el repositorio de Github, pero tengo pocos commits por problemas con el PC.
|*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <definitions.h>

void crearDirectorio(char directorio_raiz[]);
void generarDirectorios();

int main(int argc, char *argv[])
{

    struct stat st = {0};

    if (stat(ESTUDIANTES, &st) == -1)
    {
        crearDirectorio(ESTUDIANTES);
    }
    generarDirectorios();

    return 0;
}

void generarDirectorios()
{
    struct stat st = {0};
    FILE *ficheroAlu;
    char *alumno;
    char linea[64];
    char nuevo_directorio[64];

    if ((ficheroAlu = fopen("estudiantes_p1.text", "r")) == NULL)
    {
        perror("No se ha podido leer el fichero Estudiantes.txt.\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(linea, 64, (FILE *)ficheroAlu))
    {
        alumno = strtok(linea, " ");
        if (alumno != NULL)
        {
            sprintf(nuevo_directorio, "%s/%s", ESTUDIANTES, alumno);
            if (stat(nuevo_directorio, &st) == -1)
            {
                crearDirectorio(nuevo_directorio);
            }
        }
    }
    fclose(ficheroAlu);
}

void crearDirectorio(char directorio[])
{
    if (mkdir(directorio, 0777) != 0)
    {
        fprintf(stderr, "Error creando el directorio del estudiante %s.\n", directorio);
        exit(EXIT_FAILURE);
    }
}