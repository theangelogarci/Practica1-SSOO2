/*********************************************
*   Project: Sistemas Operativos II - Practica 1
*
*   Program name: manager.c
*
*   Author: Ángel García Collado
*
*   Date created: 12-03-2022
*
*   Porpuse: Programa que genera todos los hijos necesarios para la practica.
*
*   Revision History: Esta disponible en el repositorio de Github, pero tengo pocos commits por problemas con el PC.
|*********************************************/

#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <definitions.h>

#define PROCESO_APAGADO -1
pid_t GB_pids[4];

void instalarSignal();
void finalizarProcesos(int signal);
void ejecutarProceso(char *proceso, int tuberia[]);
void waitProceso();
void matarProceso(pid_t pid);

int main()
{

    char respuesta_c[100];
    int tuberia[2];

    instalarSignal();
    ejecutarProceso(PA, tuberia);
    waitProceso();

    ejecutarProceso(PB, tuberia);
    ejecutarProceso(PC, tuberia);
    waitProceso();
    waitProceso();

    read(tuberia[0], respuesta_c, 100);
    escribirLog(respuesta_c);
    escribirLog("------------------------------FIN DE PROGRAMA------------------------------");
    return 0;
}

void ejecutarProceso(char *proceso, int tuberia[])
{
    char *path;
    int pid;
    pipe(tuberia);
    if (strcmp(proceso, PA) == 0)
    {
        path = PA_PATH;
        pid = fork();
        GB_pids[0] = pid;
    }
    else if (strcmp(proceso, PB) == 0)
    {
        path = PB_PATH;
        pid = fork();
        GB_pids[1] = pid;
    }
    else if (strcmp(proceso, PC) == 0)
    {
        dup2(tuberia[1], STDOUT_FILENO);
        path = PC_PATH;
        pid = fork();
        GB_pids[2] = pid;
    }
    else if (strcmp(proceso, PD) == 0)
    {
        path = PD_PATH;
        pid = fork();
        GB_pids[3] = pid;
    }
    else
    {
        fprintf(stderr, "[MANAGER] Proceso no encontrado.\n");
    }

    switch (pid)
    {
    case -1:
        fprintf(stderr, "[MANAGER] Error creando el proceso A\n");
        exit(EXIT_FAILURE);
        break;
    case 0:
        execl(path, proceso, NULL, NULL);
        fprintf(stderr, "[MANAGER] Return no esperado. Ha fallado al ejecución del proceso.\n");
        break;

    default:
        break;
    }
}

void waitProceso()
{
    int pid = wait(NULL);
    if (pid == GB_pids[0])
    {
        escribirLog("Creación de directorios finalizada.");
        GB_pids[0] = -1;
    }
    else if (pid == GB_pids[1])
    {
        escribirLog("Copia de modelos de examen, finalizada.");
        GB_pids[1] = -1;
    }
    else if (pid == GB_pids[2])
    {
        escribirLog("Creación de archivos con nota necesaria para alcanzar la nota de corte, finalizada.");
        GB_pids[2] = -1;
    }
    else if (pid == GB_pids[3])
    {
        escribirLog("Proceso interrumpido eliminando directorio");
    }
    else
    {
        escribirLog("Proceso no esperado");
    }
}

void instalarSignal()
{
    if (signal(SIGINT, finalizarProcesos) == SIG_ERR)
    {
        fprintf(stderr, "[MANAGER] Error instalando la señal");
        exit(EXIT_FAILURE);
    }
}
void inicializarPids()
{
    int i;
    for (i = 0; i < 4; i++)
    {
        GB_pids[i] = PROCESO_APAGADO;
    }
}
void finalizarProcesos(int signal)
{
    matarProceso(GB_pids[0]);
    matarProceso(GB_pids[1]);
    matarProceso(GB_pids[2]);

    GB_pids[3] = fork();
    switch (GB_pids[3])
    {
    case -1:
        fprintf(stderr, "[MANAGER] Error creando el proceso A\n");
        exit(EXIT_FAILURE);
        break;
    case 0:
        execl(PD_PATH, PD, NULL, NULL);
        fprintf(stderr, "[MANAGER] Return no esperado. Ha fallado al ejecución del proceso.\n");
        break;

    default:
        waitProceso();
        break;
    }
}
void matarProceso(pid_t pid)
{
    if (pid != PROCESO_APAGADO)
    {
        if (kill(pid, SIGKILL) == -1)
        {
            fprintf(stderr, "No se puedo matar al proceso %d.\n", pid);
        }
    }
}