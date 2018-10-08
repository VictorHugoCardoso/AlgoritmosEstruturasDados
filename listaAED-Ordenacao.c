#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int info;
	struct no *prox;
} Lista;

int vazia(Lista *l){
	if (l == NULL){
		return 1;
	} else { 
		return 0;
	}
}

void imprimelista(Lista *l){
	if(!vazia(l)){
		printf("| %d | -> ",l->info);
		imprimelista(l->prox);
	}
}

Lista* insere(Lista* l,int info){
	Lista* no = (Lista*) malloc(sizeof(Lista));
	no->info = info;
	no->prox = l;
	return no;
}

void imprime_vetor(int vet[],int n){
	printf("\n-----------------------------------------------------------------------------------------\n");
	for(int i=0;i<n;i++){
		printf("| %d | -> ",vet[i]);
	}
	printf("\n-----------------------------------------------------------------------------------------\n\n");
}

int busca_binaria(int vet[], int n, int x) {

	int e, m, d;

	e = -1; d = n;

	while((e < d-1)&&(d != x)) {

		m = (e+d)/2;

		if (vet[m] > x){
			d = m;
		}else{
			e = m;
		}

	}

	if(vet[d] == x){
		return d;
	}else{
		return -1;
	}
}

int busca_binaria_ex(int vet[], int n) {

	int e, m, d;

	e = -1; d = n;

	while((e < d-1)) {

		m = (e+d)/2;

		printf("[e = %d] [m = %d] [d = %d]", e, m, d);
		printf("	(m = %d  /  vet[m] = %d)\n\n", m, vet[m]);
		if(vet[m] == m){
			return m;
		}
		if (vet[m] > m){
			d = m;
		}else{
			e = m;
		}
	}
}

void insertion_sort(int arr[], int n){
   int i, key, j;
   for (i = 1; i < n; i++){
       key = arr[i];
       j = i-1;
       while (j >= 0 && arr[j] > key){
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}

void insertion_sort_list(Lista *l){

	while(!vazia(l)){
		
		// key = l-pros

		l = l->prox;
	}

}

int main(){

	system("cls");

	int vetBusca[7] = {1,2,3,5,9,52,77};
	// int vetBusca[7] = {1,2,3,23,27,52,77};
	int vet[7] = {22,10,2,23,40,16,5};
	int busca = 5;

	/*

	Lista *l = NULL;
	
	l = insere(l,10);
	l = insere(l,18);
	l = insere(l,5);
	l = insere(l,1);
	l = insere(l,20);
	l = insere(l,3);

	*/
	/*
	printf("\n-----------------------------------------------------------------------------------------\n");
	imprimelista(l);
	printf("\n-----------------------------------------------------------------------------------------\n\n");
	
	insertion_sort_list(l);
	printf("*after insertion sort*\n");

	printf("\n-----------------------------------------------------------------------------------------\n");
	imprimelista(l);
	printf("\n-----------------------------------------------------------------------------------------\n\n");
	*/
	/*
	imprime_vetor(vet,7);
	insertion_sort(vet,7);
	printf("*after insertion sort*\n");
	imprime_vetor(vet,7);
	*/
	
	imprime_vetor(vetBusca,7);
	printf("Encontrado(ou n kekekek) em [%d]\n\n", busca_binaria_ex(vetBusca,7));
	// printf("Busca por (%d): Esta em [%d]\n\n", busca,busca_binaria(vetBusca,7,busca));
	

	return 0;
}
