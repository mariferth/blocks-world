#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <conio.h>
#include "Stack_Block.h"

int tam = 0;

typedef struct State {
    struct NoTag *P1;
    struct NoTag *P2;
    struct NoTag *P3;
    struct State *f;
    struct State *i; 
} state;

typedef struct Stack {
    struct State *S;
    struct Stack *prox;
} stack;

void inicializa_estado(state **S) {
    inicializa_Pilha(&(*S)->P1);
    inicializa_Pilha(&(*S)->P2);
    inicializa_Pilha(&(*S)->P3);
    (*S)->f = NULL;
    (*S)->i = NULL;
}

void inicializa_pilha_estado(stack **P) {
    *P = NULL;
}

void imprime_cenario (state **S) {
    char pilha1[3], pilha2[3], pilha3[3], P[3][3];
    no *p1, *p2, *p3;
    int i, j, t1 = 0, t2 = 0, t3 = 0;

    p1 = (*S)->P1;
    p2 = (*S)->P2;
    p3 = (*S)->P3;

    textcolor(15, 0);
    printf("\n");

    for (i = 2; i >= 0; i--) {
		printf("|");
		for (j = 0; j < 3; j++){
            if ((j == 0) && (p1 != NULL)){
                pilha1[i] = p1->block;
                P[i][j] = pilha1[i];
                p1 = p1->link;
            }
            else if ((j == 1) && (p2 != NULL)){
                pilha2[i] = p2->block;
                P[i][j] = pilha2[i];
                p2 = p2->link;
            }
            else if ((j == 2) && (p3 != NULL)){
                pilha3[i] = p3->block;
                P[i][j] = pilha3[i];
                p3 = p3->link;
            }
            else {
                P[i][j] = '\0';
            }
            
			switch (P[i][j]) {
            case 'A':
                textcolor(9, 0);
                printf("%*c", 4, P[i][j]); 
                fecha_cenario();
                break;
            case 'B':
                textcolor(10, 0);
                printf("%*c", 4, P[i][j]); 
                fecha_cenario();
                break;
            case 'C':
                textcolor(12, 0);
                printf("%*c", 4, P[i][j]); 
                fecha_cenario();
                break;
            default:
                textcolor(15, 0);
                printf("     |");
                break;
            }
        }
        printf("\n");
	}
    printf("\n"); 
}

void imprime_estado(state **S) {
    imprime_cenario(S);
}

void imprime_estados(stack **P) {
    int count = 0;
    stack *E;
    E = *P;
    printf("\n=======================\n"); 
    while (E != NULL) {
        count++;
        imprime_cenario (&(E->S));
        printf("(%d)\n=======================\n", count); 
        E = E->prox;
    }
}

state* cria_estado(char pilha1[3], char pilha2[3], char pilha3[3]) {
    // declara um ponteiro denominado N 
    int i;
    // aloca memória para armazenar o novo estado e atribui o endereço da área reservada para N 
    state *N = (state *) malloc (sizeof(state));
    // armazena a informação no novo estado
    N->P1 = NULL;
    N->P2 = NULL;
    N->P3 = NULL;
    // o link do novo estado recebe o endereço do estado apontado por S 
    N->f = NULL; //S
    N->i = NULL;
    for (i = 2; i >= 0; i--) {
        if (pilha1[2] != '\t') {
            PUSH(&N->P1, pilha1[i]);
        }
        if (pilha2[2] != '\t') {
            PUSH(&N->P2, pilha2[i]);
        }
        if (pilha3[2] != '\t') {
            PUSH(&N->P3, pilha3[i]);
        }
    }
    return N;
}

void state_insere (state *S, state *N) {
    S->i = N->f;
    N->f = S;
}

void empilha(stack **P, state *E) {
    //no *P;
    /* declara um ponteiro denominado N */
    stack *N;
    /* aloca memória para armazenar o novo nó e atribui o endereço da área reservada para N */
    N = (stack *) malloc (sizeof(stack));
    /* armazena a informação no novo nó */
    N->S = E;
    /* o link do novo nó recebe o endereço do nó apontado por S */
    N->prox = *P;
    /* S recebe o endereço de N */
    *P = N;
    tam++;
}

void desempilha(stack **P, state **E) {
    tam--;
    stack *AUX;
    if (*P != NULL) {
        *E = (*P)->S;
        AUX = *P;
        *P = (*P)->prox;
        free(AUX);
    }
}

int verifica_estado_abertos(stack **S, state *X) {
    stack *Y;
    state *aux;
    int i, j, n = 0;
    char p1[3], p2[3], p3[3];
    char pilha1[3], pilha2[3], pilha3[3];
    Y = *S;
    aux = X;
   for (i = 0; i < tam; i++){
        // Verifica se esse estado já foi armazenado na pilha de estados.
        percorre_Pilha(&Y->S->P1, p1);
        percorre_Pilha(&aux->P1, pilha1);
        percorre_Pilha(&Y->S->P2, p2);
        percorre_Pilha(&aux->P2, pilha2);
        percorre_Pilha(&Y->S->P3, p3);
        percorre_Pilha(&aux->P3, pilha3);
        for (j = 0; j < 3; j++) {
            if (p1[j] == pilha1[j]) {
                n++;
            }
            if (p2[j] == pilha2[j]) {
                n++;
            }
            if (p3[j] == pilha3[j]) {
                n++;
            }
        }
        if (n == 9) {
            return 1;  
        }
        else {
            n = 0;
        } 
        if (Y->prox != NULL){
            Y = Y->prox;
        }
        else {
            return 0;
        }
    }
    return 0;
}