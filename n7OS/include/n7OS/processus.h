#ifndef __PROCESSUS_H__
#define __PROCESSUS_H__

#include <inttypes.h>

#define MAX_PROCESS 100

typedef uint32_t pid_t;

typedef enum {ELU, PRET, BLOQUE} t_etat_process;

typedef struct {
 char* nom;
 pid_t pid;
 t_etat_process etat;
 uint16_t priorite;
 void* stack;
 uint32_t contexte[5]; 
} t_process;

t_process table_de_processus[MAX_PROCESS];

pid_t creer_processus(char *name);

pid_t get_pid();

#endif