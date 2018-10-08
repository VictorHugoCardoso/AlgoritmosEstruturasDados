#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct no* arvore;

struct no {
	int info;
	struct no* esq;
	struct no* dir;
};

int vazia(arvore r){
	return (r == NULL);
}

arvore* insere(arvore* a, int info){

}

arvore* remove(arvore* a, int info){

}

void imprime_in_ordem(arvore* a){

}

void imprime_pre_ordem(arvore* a){

}

void imprime_pos_ordem(arvore* a){

}

int maximo(arvore* a){

}

int minimo(arvore* a){

}

int altura(arvore* a){

}

int soma(arvore* a){

}

void imprimeNiveis(arvore* a){

}

int isCheia(arvore* a){

}

int isEstritamenteBinaria(arvore* a){

}

int main(){

	arvore *a = NULL;
    
	// a = insere(a,5);

	return 0;
}
