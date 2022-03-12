/*********************************************
*   Project: Sistemas Operativos II - Practica 1
*
*   Program name: pc.c
*
*   Author: Ángel García Collado
*
*   Date created: 12-03-2022
*
*   Porpuse: Calcular la nota mínima que tiene que sacar cada estudiante
*            en el proximo examen y notificarselo con un txt creado en su
*            subdirectorio
*
*   Revision History: Esta disponible en el repositorio de Github, pero tengo pocos commits por problemas con el PC.
|*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <definitions.h>

int GB_nEstudiantes;
float GB_notaTotalAcumulada;

void leerEstudiantes();
void calcNota(float nota, char alumno[]);
void escribirNota(char msg[], char alumno[]);
void notificarMedia();

int main(int argc, char *argv[])
{
    GB_nEstudiantes = 0;
    GB_notaTotalAcumulada = 0;
    leerEstudiantes();
    notificarMedia();
    return 0;
}

void leerEstudiantes()
{
    FILE *ficheroAlu;
    char *alumno;
    char *nota;
    char linea[64];

    if ((ficheroAlu = fopen(FICHERO, "r")) == NULL)
    {
        fprintf(stderr,"No se ha podido leer el fichero %s.\n", FICHERO);
        exit(EXIT_FAILURE);
    }
    while (fgets(linea, 64, (FILE *)ficheroAlu))
    {
        alumno = strtok(linea, " ");
        strtok(NULL, " ");
        nota = strtok(NULL, " ");
        if (alumno != NULL && nota != NULL)
        {
            GB_nEstudiantes = GB_nEstudiantes + 1;
            calcNota(atof(nota), alumno);
        }
    }
    fclose(ficheroAlu);
}
void calcNota(float nota, char alumno[])
{
    float notaMinima = 2 * (5 - (nota / 2));
    GB_notaTotalAcumulada = GB_notaTotalAcumulada + nota;
    char msgNota[124];
    sprintf(msgNota, "La nota que debes obtener en este nuevo examen para superar la prueba es %f\n", notaMinima);
    escribirNota(msgNota, alumno);
}

void escribirNota(char msg[], char alumno[])
{
    FILE *nota;
    char notaEstudiante[64];
    sprintf(notaEstudiante, "%s/%s/%s", ESTUDIANTES, alumno, "nota.txt");
    if ((nota = fopen(notaEstudiante, "wb")) == NULL)
    {
        printf("No se ha podido comunicar la nota.\n");
        exit(EXIT_FAILURE);
    }
    fputs(msg, nota);
    fclose(nota);
}
void notificarMedia()
{
    float notaMedia = GB_notaTotalAcumulada / GB_nEstudiantes;
    printf("La nota media de la clase es: %f", notaMedia);
}