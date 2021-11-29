#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "Stack_State.h"
#include "Queue_State.h"

stack *abertos;
queue *fechados;

void estado_aleatorio(state *S) {
    no *P;
    int choice;
    int turn = 0;
    char letter, letter1, letter2, letter3, x;
    letter = 'A' + (char)(rand()%3);
    letter1 = letter;
    do {
        choice = rand()%3;
        switch (choice) {
            case 0:
                PUSH(&(S->P1), letter);
                break;
            case 1:
                PUSH(&(S->P2), letter);
                break;
            case 2:
                PUSH(&(S->P3), letter);
                break;
            default:
                printf("%d\n", choice);
                break;
        }

        letter2 = letter;

        // Verifica qual das pilhas possui um bloco.
        if (S->P1 != NULL) {
            P = S->P1;
        }
        if (S->P2 != NULL) {
            P = S->P2;
        }
        if (S->P3 != NULL) {
            P = S->P3;
        }

        // Verifica qual bloco está na pilha, para aleatorizar o valor do próximo bloco.
        if (P->block == 'A') {
            letter = 'B' + (char)(rand()%2);
        }
        else if (P->block == 'B') {
            letter = (char)(rand() & 3) ? 'A' : 'C'; 
        }
        else if (P->block == 'C') {
            letter = 'A' + (char)(rand()%2);  
        }
        turn++;
    } while(turn < 2);

    if((letter1 == 'A') && (letter2 == 'B')) {
        letter3 = 'C';
    }
    else if ((letter1 == 'B') && (letter2 == 'A')) {
        letter3 = 'C';
    }
    else if((letter1 == 'A') && (letter2 == 'C')) {
        letter3 = 'B';
    }
    else if ((letter1 == 'C') && (letter2 == 'A')) {
        letter3 = 'B';
    }
    else if((letter1 == 'B') && (letter2 == 'C')) {
        letter3 = 'A';
    }
    else if ((letter1 == 'C') && (letter2 == 'B')){
        letter3 = 'A';
    }
    
    choice = rand()%3;
    switch (choice) {
        case 0:
            PUSH(&(S->P1), letter3);
            break;
        case 1:
            PUSH(&(S->P2), letter3);
            break;
        case 2:
            PUSH(&(S->P3), letter3);
            break;
        default:
            printf("%d\n", choice);
            break;
    }
}    

void verifica_estado (state **S) {
    state *N;
    N = *S;
    if ((abertos != NULL) && (fechados != NULL)) {
        if (verifica_estado_abertos(&abertos, N) == 0) {
            if (verifica_estado_fechados(&fechados, N) == 0) {
                empilha(&abertos, N);
            }
            else {
               return;
            }
        }
        else {
            return;
        }
    }
    else if (abertos != NULL) {
        if (verifica_estado_abertos(&abertos, N) == 0) {
            empilha(&abertos, N);
        }
        else {
            return;
        }
    }
    else if (fechados != NULL) {
        if (verifica_estado_fechados(&fechados, N) == 0) {
            empilha(&abertos, N);
        }
        else {
            return;
        }
    }
    else {
        empilha(&abertos, N);
    }
}        

void P1_P2(state *S, char pilha1[3], char pilha2[3], char pilha3[3]) {
    state *N;

    if (pilha1[2] != '\0') {
        if (pilha1[0] != '\0') {
            pilha2[2] = pilha1[0];
            pilha1[0] = '\0';
        }
        else if ((pilha1[1] != '\0') && (pilha2[2] != '\0')) {
            pilha2[1] = pilha1[1];
            pilha1[1] = '\0';
        }
        else if (pilha1[1] != '\0') {
            pilha2[2] = pilha1[1];
            pilha1[1] = '\0';
        }
        else if (pilha2[1] != '\0') {
            pilha2[0] = pilha1[2];
            pilha1[2] = '\0';
        }
        else if (pilha2[2] != '\0') {
            pilha2[1] = pilha1[2];
            pilha1[2] = '\0';
        }
        else if (pilha1[2] != '\0') {
            pilha2[2] = pilha1[2];
            pilha1[2] = '\0';
        }
        N = cria_estado(pilha1, pilha2, pilha3);
        state_insere (S, N);
        verifica_estado(&N);
        /*printf("Vou imprimir N (P1-P2):\n");
        imprime_estado(&N);*/
    }
}

void P1_P3(state *S, char pilha1[3], char pilha2[3], char pilha3[3]) {
    state *N;

    if (pilha1[2] != '\0') {
        if (pilha1[0] != '\0') {
            pilha3[2] = pilha1[0];
            pilha1[0] = '\0';
        }
        else if ((pilha1[1] != '\0') && (pilha3[2] != '\0')) {
            pilha3[1] = pilha1[1];
            pilha1[1] = '\0';
        }
        else if (pilha1[1] != '\0') {
            pilha3[2] = pilha1[1];
            pilha1[1] = '\0';
        }
        else if (pilha3[1] != '\0') {
            pilha3[0] = pilha1[2];
            pilha1[2] = '\0';
        }
        else if (pilha3[2] != '\0') {
            pilha3[1] = pilha1[2];
            pilha1[2] = '\0';
        }
        else if (pilha1[2] != '\0') {
            pilha3[2] = pilha1[2];
            pilha1[2] = '\0';
        }
        N = cria_estado(pilha1, pilha2, pilha3);
        state_insere (S, N);
        verifica_estado(&N);
        /*printf("Vou imprimir N2 (P1-P3):\n");
        imprime_estado(&N);*/
    }
}

void P2_P1(state *S, char pilha1[3], char pilha2[3], char pilha3[3]) {
    state *N;

    if (pilha2[2] != '\0') {
        if (pilha2[0] != '\0') {
            pilha1[2] = pilha2[0];
            pilha2[0] = '\0';
        }
        else if ((pilha2[1] != '\0') && (pilha1[2] != '\0')) {
            pilha1[1] = pilha2[1];
            pilha2[1] = '\0';
        }
        else if (pilha2[1] != '\0') {
            pilha1[2] = pilha2[1];
            pilha2[1] = '\0';
        }
        else if (pilha1[1] != '\0') {
            pilha1[0] = pilha2[2];
            pilha2[2] = '\0';
        }
        else if (pilha1[2] != '\0') {
            pilha1[1] = pilha2[2];
            pilha2[2] = '\0';
        }
        else if (pilha2[2] != '\0') {
            pilha1[2] = pilha2[2];
            pilha2[2] = '\0';
        }
        N = cria_estado(pilha1, pilha2, pilha3);
        state_insere (S, N);
        verifica_estado(&N);
        /*printf("Vou imprimir N (P2-P1):\n");
        imprime_estado(&N);*/
    }
}

void P2_P3(state *S, char pilha1[3], char pilha2[3], char pilha3[3]) {
    state *N;

    if (pilha2[2] != '\0') {
        if (pilha2[0] != '\0') {
            pilha3[2] = pilha2[0];
            pilha2[0] = '\0';
        }
        else if ((pilha2[1] != '\0') && (pilha3[2] != '\0')) {
            pilha3[1] = pilha2[1];
            pilha2[1] = '\0';
        }
        else if (pilha2[1] != '\0') {
            pilha3[2] = pilha2[1];
            pilha2[1] = '\0';
        }
        else if (pilha3[1] != '\0') {
            pilha3[0] = pilha2[2];
            pilha2[2] = '\0';
        }
        else if (pilha3[2] != '\0') {
            pilha3[1] = pilha2[2];
            pilha2[2] = '\0';
        }
        else if (pilha2[2] != '\0') {
            pilha3[2] = pilha2[2];
            pilha2[2] = '\0';
        }
        N = cria_estado(pilha1, pilha2, pilha3);
        state_insere (S, N);
        verifica_estado(&N);
        /*printf("Vou imprimir N (P2-P3):\n");
        imprime_estado(&N);*/
    }
}

void P3_P1(state *S, char pilha1[3], char pilha2[3], char pilha3[3]) {
    state *N;

    if (pilha3[2] != '\0') {
        if (pilha3[0] != '\0') {
            pilha1[2] = pilha3[0];
            pilha3[0] = '\0';
        }
        else if ((pilha3[1] != '\0') && (pilha1[2] != '\0')) {
            pilha1[1] = pilha3[1];
            pilha3[1] = '\0';
        }
        else if (pilha3[1] != '\0') {
            pilha1[2] = pilha3[1];
            pilha3[1] = '\0';
        }
        else if (pilha1[1] != '\0') {
            pilha1[0] = pilha3[2];
            pilha3[2] = '\0';
        }
        else if (pilha1[2] != '\0') {
            pilha1[1] = pilha3[2];
            pilha3[2] = '\0';
        }
        else if (pilha3[2] != '\0') {
            pilha1[2] = pilha3[2];
            pilha3[2] = '\0';
        }
        N = cria_estado(pilha1, pilha2, pilha3);
        state_insere (S, N);
        verifica_estado(&N);
        /*printf("Vou imprimir N (P3-P1):\n");
        imprime_estado(&N);*/
    }
}

void P3_P2(state *S, char pilha1[3], char pilha2[3], char pilha3[3]) {
    state *N;
    
    if (pilha3[2] != '\0') {
        if (pilha3[0] != '\0') {
            pilha2[2] = pilha3[0];
            pilha3[0] = '\0';
        }
        else if ((pilha3[1] != '\0') && (pilha2[2] != '\0')) {
            pilha2[1] = pilha3[1];
            pilha3[1] = '\0';
        }
        else if (pilha3[1] != '\0') {
            pilha2[2] = pilha3[1];
            pilha3[1] = '\0';
        }
        else if (pilha2[1] != '\0') {
            pilha2[0] = pilha3[2];
            pilha3[2] = '\0';
        }
        else if (pilha2[2] != '\0') {
            pilha2[1] = pilha3[2];
            pilha3[2] = '\0';
        }
        else if (pilha3[2] != '\0') {
            pilha2[2] = pilha3[2];
            pilha3[2] = '\0';
        }
        N = cria_estado(pilha1, pilha2, pilha3);
        state_insere (S, N);
        verifica_estado(&N);
        /*printf("Vou imprimir N (P3-P2):\n");
        imprime_estado(&N);*/
    }
}

char* dfs(state *S) {
    no *p1, *p2, *p3;
    int i;
    char pilha1[3], pilha2[3], pilha3[3], esq[3], cen[3], dir[3], aux;
    int n = 3;
    state *X;
    empilha(&abertos, S);
    while(abertos != NULL){
        desempilha(&abertos, &X);
        p1 = X->P1;
        p2 = X->P2;
        p3 = X->P3;

        for (i = 2; i >= 0; i--) {
            if (p1 != NULL) {
                pilha1[i] = p1->block;
                p1 = p1->link;
            }
            else {
                pilha1[i] = '\0';
            }
            if (p2 != NULL) {
                pilha2[i] = p2->block;
                p2 = p2->link;
            }
            else {
                pilha2[i] = '\0';
            }
            if (p3 != NULL) {
                pilha3[i] = p3->block;
                p3 = p3->link;
            }
            else {
                pilha3[i] = '\0';
            }
        }
        if((pilha1[0] != '\0') && (pilha1[1] != '\0') && (pilha1[2] != '\0')) {
            aux = pilha1[0];
            pilha1[0] = pilha1[2];
            pilha1[2] = aux;
        }
        else if ((pilha1[1] != '\0') && (pilha1[2] != '\0')) {
            aux = pilha1[1];
            pilha1[1] = pilha1[2];
            pilha1[2] = aux;
        }
        if((pilha2[0] != '\0') && (pilha2[1] != '\0') && (pilha2[2] != '\0')) {
            aux = pilha2[0];
            pilha2[0] = pilha2[2];
            pilha2[2] = aux;
        }
        else if ((pilha2[1] != '\0') && (pilha2[2] != '\0')) {
            aux = pilha2[1];
            pilha2[1] = pilha2[2];
            pilha2[2] = aux;
        }
        if((pilha3[0] != '\0') && (pilha3[1] != '\0') && (pilha3[2] != '\0')) {
            aux = pilha3[0];
            pilha3[0] = pilha3[2];
            pilha3[2] = aux;
        }
        else if ((pilha3[1] != '\0') && (pilha3[2] != '\0')) {
            aux = pilha3[1];
            pilha3[1] = pilha3[2];
            pilha3[2] = aux;
        }
        
        if (pilha1[2] == '\0') {
            if ((pilha1[0] != '\0') && (pilha1[1] != 0)) {
                pilha1[2] = pilha1[0];
                pilha1[0] = '\0';
            }
            else if (pilha1[0] != '\0') {
                pilha1[2] = pilha1[0];
                pilha1[0] = '\0';
            }
        }
        if (pilha2[2] == '\0') {
            if ((pilha2[0] != '\0') && (pilha2[1] != 0)) {
                pilha2[2] = pilha2[0];
                pilha2[0] = '\0';
            }
            else if (pilha2[0] != '\0') {
                pilha2[2] = pilha2[0];
                pilha2[0] = '\0';
            }
        }
        if (pilha3[2] == '\0') {
            if ((pilha3[0] != '\0') && (pilha3[1] != 0)) {
                pilha3[2] = pilha3[0];
                pilha3[0] = '\0';
            }
            else if (pilha3[0] != '\0') {
                pilha3[2] = pilha3[0];
                pilha3[0] = '\0';
            }
        }

        //Faz uma cópia de X
        for (i = 2; i >= 0; i--) {
            esq[i] = pilha1[i];
            cen[i] = pilha2[i];
            dir[i] = pilha3[i];
        }
        if ((pilha2[0] == 'A') && (pilha2[1] == 'B') && (pilha2[2] == 'C')) {
            insere_fila(&fechados, X);
            printf("Caminho encontrado do estado inicial at%c o estado final:\n", 130);
            imprime_fila_estados(&fechados);
            return "SUCESSO!!";
        }
        else {
            insere_fila(&fechados, X);
            if (X->P1 != NULL) {
                //P1-P2
                P1_P2(X, esq, cen, dir);
                for (i = 2; i >= 0; i--) {
                    esq[i] = pilha1[i];
                    cen[i] = pilha2[i];
                    dir[i] = pilha3[i];
                }
                //P1-P3
                P1_P3(X, esq, cen, dir);
            
            }
            if (X->P2 != NULL) {
                for (i = 2; i >= 0; i--) {
                    esq[i] = pilha1[i];
                    cen[i] = pilha2[i];
                    dir[i] = pilha3[i];
                }
                //P2-P1
                P2_P1(X, esq, cen, dir);
                for (i = 2; i >= 0; i--) {
                    esq[i] = pilha1[i];
                    cen[i] = pilha2[i];
                    dir[i] = pilha3[i];
                }
                //P2-P3
                P2_P3(X, esq, cen, dir);
            }
            if (X->P3 != NULL) {
                for (i = 2; i >= 0; i--) {
                    esq[i] = pilha1[i];
                    cen[i] = pilha2[i];
                    dir[i] = pilha3[i];
                }
                //P3-P1
                P3_P1(X, esq, cen, dir);
                for (i = 2; i >= 0; i--) {
                    esq[i] = pilha1[i];
                    cen[i] = pilha2[i];
                    dir[i] = pilha3[i];
                }
                //P3-P2
                P3_P2(X, esq, cen, dir);
            }
        }   
    }
    printf("Elementos da fila fechados:\n");
    imprime_fila_estados(&fechados);
    return "FALHA :(";
}

int main () {
    srand(time(NULL));
    int n = 3;
    state *S, *N;
    char p1[3], p2[3], p3[3];
    int i;
    char aux;
    inicializa_estado(&S);
    estado_aleatorio(S);
    inicializa_pilha_estado(&abertos);
    inicializa_fila(&fechados);
    
    for (i = 2; i >= 0; i--) {
        if (S->P1 != NULL) {
            p1[i] = S->P1->block;
            S->P1 = S->P1->link;
        }
        else {
            p1[i] = '\0';
        }
        if (S->P2 != NULL) {
            p2[i] = S->P2->block;
            S->P2 = S->P2->link;
        }
        else {
            p2[i] = '\0';
        }
        if (S->P3 != NULL) {
            p3[i] = S->P3->block;
            S->P3 = S->P3->link;
        }
        else {
            p3[i] = '\0';
        }  
    }
    N = cria_estado(p1, p2, p3);
    printf("ESTADO INICIAL:\n");
    imprime_estado(&N);
    printf("%s", dfs(N));
    return 0;
}