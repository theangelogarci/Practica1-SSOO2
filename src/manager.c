#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(){
    int pid;
    for(int i=0;i<2;i++){
        pid=fork();
    }
    switch (pid){
        
        case 0:
        printf("%d\n",pid);
        printf("Soy %d ",getpid());
        PA();   
        break;
        default:
        printf("Soy el padre\n");
        break;
    }
}

int PA(void) {
    const char* filename = "estudiantes_p1.text";
    char delimitador[] = " ";
    int contador=0;
    FILE* input_file = fopen(filename, "r");
    if (!input_file)
        exit(EXIT_FAILURE);
    
    char *contents = NULL;
    size_t len = 0;
    while (getline(&contents, &len, input_file) != -1){
        char *token = strtok(contents, delimitador);
        
        if(token != NULL){
        mkdir(token, S_IRWXU);
    }
    }

    fclose(input_file);
    free(contents);

    exit(EXIT_SUCCESS);
}
