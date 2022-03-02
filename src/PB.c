#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(void) {
    
    int data1 =0;
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
        char *token2 = strtok(NULL, delimitador);
        printf("%s\n",token2);
        sprintf
    
    }

    fclose(input_file);
    free(contents);

    exit(EXIT_SUCCESS);
}