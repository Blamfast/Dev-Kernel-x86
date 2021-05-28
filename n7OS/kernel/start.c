#include <n7OS/cpu.h>
#include <inttypes.h>
#include <n7OS/processor_structs.h>
#include <stdio.h>
#include <unistd.h>
#include <n7OS/irq.h>
#include <n7OS/sys.h>
#include <n7OS/console.h>
#include <n7OS/time.h>


extern void handler_IT();


void init_irq() {
    init_irq_entry(50, (uint32_t)handler_IT);
}

void handler_en_C() {
    printf("Interruption 50\n");
}



void kernel_start(void)
{
    init_timer();
    sti();
    init_syscall();
    init_irq();
    printf("\f");
    // on ne doit jamais sortir de kernel_start
    if (example() == 1) {
        printf("Appel systeme example ok\n");
    }

    //shutdown(1);

    printf("Bonjour le sang de la veine\n");
    __asm__ ("int $50");
    while (1) {
        timer();
        // cette fonction arrete le processeur
        hlt();
    }
}
