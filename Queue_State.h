#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int tm = 0;

typedef struct Queue {
    struct State *S;
    struct Queue *prox;
} queue;

void inicializa_fila(queue **F) {
	*F = NULL;
}

void imprime_fila_estados(queue **F) {
    int count = 0;
    queue *E;
    E = *F;
    printf("\n**************************\n"); 
    while (E != NULL) {
        count++;
        imprime_estado(&(E->S));
        printf("(%d)\n**************************\n", count); 
        E = E->prox;
    }
}

// função que insere item no final da Fila
void insere_fila(queue **F, state *E) {
	queue *P, *N;
    tm++;
	// aloca memória para armazenar o novo no e atribui o endereço alocado para N
	N = (queue *) malloc (sizeof(queue)); 
	N->S = E; // Insere o valor no novo no
	N->prox = NULL; // como sera inserido no final da Fila, link do novo no recebe NULL
	 
	// se a Fila estiver vazia, o novo no será o primeiro da Fila
	if (*F == NULL){ // verifica se Fila vazia
		*F = N;
	}
	else { // se a Fila não estiver vazia, é preciso encontrar o final da Fila para inserir o novo item
		P = *F;	// P recebe o endereco do primeiro no da lista
	
		while(P->prox != NULL) {
			P = P->prox;
		}
		// o while é interrompido quando P apontar para o último nó da Fila
		P->prox = N; 	// o link do nó apontado por P recebe o endereço do novo nó
	} 
}

int verifica_estado_fechados(queue **F, state *X){
    queue *Y;
    state *aux;
    int i, j, n = 0;
    char p1[3], p2[3], p3[3];
    char pilha1[3], pilha2[3], pilha3[3];
    Y = *F;
    aux = X;
    for (i = 0; i < tm; i++){
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