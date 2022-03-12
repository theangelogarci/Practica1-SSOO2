/*********************************************
*   Project: Sistemas Operativos II - Practica 1
*
*   Program name: pb.c
*
*   Author: Ángel García Collado
*
*   Date created: 28-02-2022
*
*   Porpuse: Copiar en los subdirectorio de los estudiantes sus modelos de examenes
*            correspondientes.
*
*   Revision History: Esta disponible en el repositorio de Github, pero tengo pocos commits por problemas con el PC.
|*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <definitions.h>

#define A "MODELOA.pdf"
#define B "MODELOB.pdf"
#define C "MODELOC.pdf"

#define TBUFFER 2048
#define MAX_PATH 1024

void asignarExamen(char examen[], char alumno[]);
void copiar(char examen[], char alumno[]);
void leerEstudiantes();

int main(int argc, char *argv[])
{
    leerEstudiantes();
    return 0;
}

void leerEstudiantes()
{
    FILE *ficheroAlu;
    char *alumno;
    char *fichero;
    char linea[64];
    if ((ficheroAlu = fopen(FICHERO, "r")) == NULL)
    {
        fprintf(stderr,"No se ha podido leer el archivo %s.\n", FICHERO);
        exit(EXIT_FAILURE);
    }
    while (fgets(linea, 64, (FILE *)ficheroAlu))
    {
        alumno = strtok(linea, " ");
        fichero = strtok(NULL, " ");
        if (alumno != NULL && fichero != NULL)
        {
            asignarExamen(fichero, alumno);
        }
    }
    fclose(ficheroAlu);
}

void asignarExamen(char examen[], char alumno[])
{
    if (strcmp(examen, "A") == 0)
    {
        copiar(A, alumno);
    }
    else if (strcmp(examen, "B") == 0)
    {
        copiar(B, alumno);
    }
    else if (strcmp(examen, "C") == 0)
    {
        copiar(C, alumno);
    }
}

void copiar(char examen[], char alumno[])
{
    int nbytes;
    char buffEscritura[TBUFFER];

    FILE *fExamen;
    FILE *fExamenAsignado;

    char rutaExamen[MAX_PATH];
    char examenAsignado[MAX_PATH];

    sprintf(rutaExamen, "%s/%s", EXAMENES, examen);
    sprintf(examenAsignado, "%s/%s/%s", ESTUDIANTES, alumno, examen);

    if ((fExamen = fopen(rutaExamen, "r")) == NULL)
    {
        fprintf(stderr,"No se puede copiar el modelo de examen.\n");
        exit(EXIT_FAILURE);
    }

    if ((fExamenAsignado = fopen(examenAsignado, "wb")) == NULL)
    {
        fprintf(stderr,"No se ha podido asignar el modelo de examen al estudiante.\n");
        exit(EXIT_FAILURE);
    }
    while (!feof(fExamen))
    {
        nbytes = fread(buffEscritura, 1, sizeof(buffEscritura), fExamen);
        fwrite(buffEscritura, 1, nbytes, fExamenAsignado);
    }
    fclose(fExamen);
    fclose(fExamenAsignado);
}