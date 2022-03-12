#define EXAMENES "./Examenes"
#define ESTUDIANTES "./Estudiantes"
#define FICHERO "./estudiantes_p1.text"
#define PA "PA"
#define PA_PATH "./exec/pa"
#define PB "PB"
#define PB_PATH "./exec/pb"
#define PC "PC"
#define PC_PATH "./exec/pc"
#define PD "PD"
#define PD_PATH "./exec/pd"

void escribirLog(char * mensaje){
  FILE *stlog;
  if((stlog = fopen("./log.txt", "at")) != NULL){
    fprintf(stlog,"%s \n", mensaje);
  }
  fclose(stlog);
}