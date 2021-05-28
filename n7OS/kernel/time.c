#include <n7OS/time.h>
#include <stdio.h>
#include <inttypes.h>
#include <n7OS/irq.h>
#include <n7OS/cpu.h>

int cpt;
extern void handler_TIME();

void init_timer() {
    int f_osc = 0x1234BD;
    int frequence = f_osc/1000;

    outb(0x34, 0x43);

    //Affectation de la fréquence, poids faible, au Channel 0
    outb(frequence & 0xFF, 0x40);

    //Affectation de la fréquence, poids faible, au Channel 0
    outb(frequence>>8, 0x40);

    init_irq_entry(0x20, (uint32_t)handler_TIME);

    //Activation de l’IT duTimer
    outb(inb(0x21)&0xfe, 0x21);
}

void traitement_IT() {

    //ack de l’IT du PIC Master
    outb(0x20, 0x20);
    cpt++;
}

void conversion_timer(int* heure,int* min, int* sec) {
    *sec = cpt/1000;
    *sec = *sec % 60;
    *min = (*sec % 3600)/60;
    *heure = *sec/3600;
}