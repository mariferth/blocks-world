#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>

/* Define o tipo de dado no */
typedef struct NoTag {
    char block;
    struct NoTag *link;
} no;

/*             0     1    2     3   4      5     6       7         8      */
typedef enum{BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,
LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE} COLORS;
/* 9         10        11        12        13          14    15          */
static int __BACKGROUND = BLACK;
static int __FOREGROUND = LIGHTGRAY;

void textcolor (int letra, int fundo){
    __FOREGROUND = letra;
    __BACKGROUND = fundo;
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
    letra + (__BACKGROUND << 4));
}

void inicializa_Pilha(no **L) {
/* atribui NULL ao ponteiro L */
    *L = NULL;
}

void fecha_cenario () {
    textcolor(15, 0);
    printf(" |");
}

void PUSH(no **L, char x) {
    /* declara um ponteiro denominado N */
    no *N;
    /* aloca memória para armazenar o novo nó e atribui o endereço da área reservada para N */
    N = (no *) malloc (sizeof(no));
    /* armazena a informação no novo nó */
    N->block = x;
    /* o link do novo nó recebe o endereço do nó apontado por L */
    N->link = *L;
    /* L recebe o endereço de N */
    *L = N;
}

void POP(no **L, char *n) {
    no *AUX;
    if (*L != NULL) {
        *n = (*L)->block;
        AUX = *L;
        *L = (*L)->link;
        AUX = NULL;
        //free(AUX);
    }
}

void percorre_Pilha(no **L, char p[3]) {
    no *P;
    int i;
    P = *L;
    for(i = 0; i < 3; i++){
        if (P != NULL) {
            p[i] = P->block;
        }
        else {
            return;
        }
        P = P->link;   
    }
}
