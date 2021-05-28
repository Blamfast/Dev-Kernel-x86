#include <inttypes.h>
#include <n7OS/irq.h>


void init_irq_entry(int irq_num, uint32_t addr) {
    idt_entry_t en;
    en.type_attr = 128+14;
    en.sel_segment = KERNEL_CS;
    en.offset_inf = addr & 0xFFFF;
    en.offset_sup = addr >> 16;

    idt[irq_num] = en.offset_inf + (en.sel_segment<<16) + ((uint64_t)en.type_attr<<40) + ((uint64_t)en.offset_sup<<48);
}
