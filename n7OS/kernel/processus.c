#include <n7OS/processus.h>
#include <stdio.h>


#define STACK_SIZE 1024


/* Pile d'exécution */
int sommet_pile = STACK_SIZE - 1;

/* Allocation d'un pid */
pid_t allouer_pid() {

 /* Allocation pid possible */
 for (int i = 0 ; i <= MAX_PROCESS ; i++) {
 if (table_de_processus[i].pid != -1) {
 return table_de_processus[i].pid;
 }
 } 

 /* Allocation impossible */
 return -1;
}

/* Création d'un processus */
pid_t creer_processus(char *name) {
 pid_t pid = allouer_pid();
 if (pid == -1) {
 printf("Impossible de créer un nouveau processus\n");
 } else {
 table_de_processus[pid].pid = pid;
 table_de_processus[pid].nom = name;
 //table_de_processus[pid].stack = init_stack();
 table_de_processus[pid].etat = PRET;
 //table_de_processus[pid].ressources = init_ressources();
 table_de_processus[pid].contexte[0] = 0;
 table_de_processus[pid].contexte[1] = sommet_pile;
 table_de_processus[pid].contexte[2] = 0;
 table_de_processus[pid].contexte[3] = 0;
 table_de_processus[pid].contexte[4] = 0;
 sommet_pile --;
 }
 return pid; 
}

/* Obtention du pid du processus élu */
pid_t get_pid() {
 for (int i = 0 ; i <= MAX_PROCESS ; i++) {
 if (table_de_processus[i].etat == ELU) {
 return table_de_processus[i].pid;
 }
 }
 return -1;
}

/* TODO
void arreter() {
    pid_t pid = get_pid();
    if(table_de_processus[pid].etat == ELU) {
        table_de_processus[pid].etat = PRET;
        table_de_processus[pid].stack = stop-process_uc();
        addProcess(pid);
        scheduler();
    }
}
*/
/* TODO 
void bloquer(RESSOURCE_ID rid) {
    pid_t pid = get_pid();


}*/