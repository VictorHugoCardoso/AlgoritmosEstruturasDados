#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TAM 20

typedef struct {
	int matricula;
	char nome[50];
} aluno;

typedef struct {
	int k;
	aluno r; 
	int ocupado; 
} slot;

typedef slot TabelaHash[TAM];

int hash(int k){
	return k%TAM;
}

int hashSondagemLinear(int k,int i){
	return (hash(k) + i)%TAM;
}

int hashSondagemQuadratica(int k,int i){
	return (hash(k) + i + i*i)%TAM;
}

int hashDuplo(int k,int i){
	return (hash(k) + (i * hash(k)))%TAM;
}

void inicializaTabelaHash(TabelaHash T){
	for(int i = 0; i < TAM; i++){
		T[i].k = -1;
		T[i].ocupado = 0;
	}
}

void inserir(TabelaHash T, int k, aluno r){
	int chave = hash(k);
	T[chave].k = k;
	T[chave].r = r;
	T[chave].ocupado = 1;
}

void inserir_sondagem_linear(TabelaHash T, int k, aluno r){
	for (int i=0;i<TAM;i++){
    	int j = hashSondagemLinear(k,i);
    	if(T[j].ocupado == 0){
    		T[j].k = k;
			T[j].r = r;
			T[j].ocupado = 1;
			break;
    	}
	}
}

void inserir_sondagem_quadratica(TabelaHash T, int k, aluno r){
	for (int i=0;i<TAM;i++){
    	int j = hashSondagemQuadratica(k,i);
    	if(T[j].ocupado == 0){
    		T[j].k = k;
			T[j].r = r;
			T[j].ocupado = 1;
			break;
    	}
	}
}	

void inserir_hash_duplo(TabelaHash T, int k, aluno r){
	for (int i=0;i<TAM;i++){
    	int j = hashDuplo(k,i);
    	if(T[j].ocupado == 0){
    		T[j].k = k;
			T[j].r = r;
			T[j].ocupado = 1;
			break;
    	}
	}
}	

void remover(TabelaHash T, int k){
	int chave = hash(k);
	T[chave].k = -1;
	T[chave].ocupado = 0;

}

int buscar(TabelaHash T, int k){
	int chave = hash(k);

	if(T[chave].k == k){
		return chave;
	}else{
		return -1;
	}

}

int main(){

	TabelaHash tab;
	inicializaTabelaHash(tab);

	aluno a1,a2;
	
	strcpy(a1.nome, "a");
	a1.matricula = 1234;
	
	strcpy(a2.nome, "b");
	a2.matricula = 4321;	

	/*
	inserir_hash_duplo(tab, 26, a2);
	inserir_hash_duplo(tab, 27, a2);
	inserir_hash_duplo(tab, 28, a2);
	inserir_hash_duplo(tab, 46, a2);
	*/

	/*
	inserir_sondagem_quadratica(tab, 26, a2);
	inserir_sondagem_quadratica(tab, 27, a2);
	inserir_sondagem_quadratica(tab, 28, a2);
	inserir_sondagem_quadratica(tab, 46, a2);
	*/

	/*
	inserir_sondagem_linear(tab, 26, a1);
	inserir_sondagem_linear(tab, 27, a2);	
	inserir_sondagem_linear(tab, 28, a2);
	inserir_sondagem_linear(tab, 46, a2);
	*/


	int resp=1;
	int chave;
	
	while(1){
        system("cls");
        printf(" \nTAM = [%d]\n\n",TAM);
        printf("*--------------------------------------------*\n");
        printf("| |01| - Imprimir Tabela Hash                |\n");
        printf("| |02| - Inserir Valor                       |\n");
        printf("| |03| - Remover Valor                       |\n");
        printf("| |04| - Buscar Valor                        |\n");
        printf("*--------------------------------------------*\n\n");
        printf("ESCOLHA: ");
        fflush(stdin);
        scanf("%d", &resp);
        system("cls");
        
        switch(resp){
			case 1:
				
				for(int i=0;i<TAM;i++){
					printf("[%d] = %d\n", i, tab[i].k);
				}

				scanf("%*c");   // serve apenas para impressao
                scanf("%*c");
				break;
			case 2:

				printf("Entre com a Chave: \n");
				scanf("%d",&chave);
				printf("// aqui entrariam os dados satelite\n");
				printf("Inserido!\n");

				inserir(tab, chave, a1);

				scanf("%*c");   // serve apenas para impressao
                scanf("%*c");
				break;
			case 3:

				printf("Entre com a Chave: \n");
				scanf("%d",&chave);
				printf("Removido!\n");

				remover(tab, chave);
				scanf("%*c");   // serve apenas para impressao
                scanf("%*c");
				break;
			case 4:

				printf("Entre com a Chave: \n");
				scanf("%d",&chave);

				printf("\nEsta na posicao [%d] da Tabela Hash de tamanho [%d]\n", buscar(tab, chave), TAM);

				scanf("%*c");   // serve apenas para impressao
                scanf("%*c");
				break;

			case 0:
				exit(1);
			default:
                printf("Invalido\n");
        }

    }
    
	return 0;
}
