#include <n7OS/console.h>
#include <inttypes.h>
#include <n7OS/cpu.h>
#include <string.h>
#include <n7OS/time.h>
const int MAX_LIGNE = 24;
const int MAX_COLONNE = 80;
int ligne = 10;
int colonne = 0;
int pos = 0;
uint16_t *scr_tab = (uint16_t *) 0xB8000;

void set_pos_cursor(int p) {
    outb(0x0F,0x3D4);
    outb(p & 0xFF,0x3D5);
    outb(0x0E,0x3D4);
    outb((p >> 8) & 0xFF, 0x3D5);
}

void timer() {
    int h,m,s;
    conversion_timer(&h,&m,&s);
    if (h<10) {
        scr_tab[72] = (0x52<<8)|'0';
        scr_tab[73] = (0x52<<8)|('0' + h);
    } else {
        scr_tab[72] = (0x52<<8)|('0' + (h/10));
        scr_tab[73] = (0x52<<8)|('0' + (h%10));
    }
    scr_tab[74] = (0x52<<8)|':';
    if (m<10) {
        scr_tab[75] = (0x52<<8)|'0';
        scr_tab[76] = (0x52<<8)|('0' + m);
    } else {
        scr_tab[75] = (0x52<<8)|('0' + (m/10));
        scr_tab[76] = (0x52<<8)|('0' + (m%10));
    }
    scr_tab[77] = (0x52<<8)|':';
    if (s<10) {
        scr_tab[78] = (0x52<<8)|'0';
        scr_tab[79] = (0x52<<8)|('0' + s);
    } else {
        scr_tab[78] = (0x52<<8)|('0' + (s/10));
        scr_tab[79] = (0x52<<8)|('0' + (s%10));
    }
}

int calcul_pos_cursor(int l, int c) {
    return (80*l + c);
}

void console_putchar(const char c) {
    if (c > 31 && c < 127) {
        scr_tab[pos] = (0x52<<8)|c;
        colonne++;
        if (colonne > MAX_COLONNE) {
            colonne=0;
            ligne++;
        }

    } else if (c == '\n') {
        colonne=0;
        ligne++;
        
    } else if (c == '\r') {
        colonne=0;
    } else if (c == '\b') {
        colonne--;
        if (colonne < 0) {
            colonne = 0;
        }

    } else if (c == '\t') {
        for (int j = 0; j < 8; j++) {
            colonne++;
            if (colonne > MAX_COLONNE) {
                colonne=0;
                ligne++;
            }
        }

    } else if (c == '\f') {
        for (int j = 0; j < 2000; j++) {
            scr_tab[j] = (0x52<<8)|' ';
            colonne=0;
            ligne=0;
        }
    }
    if (ligne > MAX_LIGNE) {
        memcpy(scr_tab, scr_tab+MAX_COLONNE, MAX_LIGNE*MAX_COLONNE*2);
            for (int i = 1920; i < 2000;  i++)
                scr_tab[i] = (0x52<<8)|' ';
            ligne = MAX_LIGNE;
            colonne = 0;
    }
    pos = calcul_pos_cursor(ligne,colonne);
    set_pos_cursor(pos);
}

void console_putbytes(const char *s, int len) {
  for (int i = 0; i < len; i++) {
      console_putchar(s[i]);
  }
}