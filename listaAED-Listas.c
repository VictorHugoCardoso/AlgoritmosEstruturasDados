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

Lista* remover(Lista *l,int info){
	Lista* no = l;
	Lista* ant = l;
	while(no!=NULL && no->info != info){
		ant = no;
		no = no->prox;
	}
	if(no!=NULL){
		if(no == l){
			l = l->prox;
		}
		else{
			ant->prox = no->prox;
		}
		free(no);
	}
	return l;
}

Lista* invertelista(Lista* l){
	Lista* aux = l;
	Lista* nova = NULL;
	while(!vazia(aux)){
		nova = insere(aux,aux->info);
		aux = aux->prox;
	}
	return nova;
}

Lista* inserir_apos(Lista * l, int info_ref, int info){
	
	Lista* aux = (Lista *)malloc(sizeof(Lista));
	Lista* ant = l;
	Lista* p = l;
	
	while(p!=NULL && p->info != info_ref){
		ant = p;
		p = p->prox;
	}
	if(p!=NULL){// elemento encontrado
		if(p->prox != NULL){// elemento encontrado no meio
			aux->info = info;
			aux->prox = p->prox;
			p->prox = aux;
		
		}else{// elemento encontrado no fim
			aux->info = info;
			aux->prox = NULL;
			p->prox = aux;
		}
		
	}else{ // elemento n encontrado, insere no fim da lista
		aux->info = info;
		aux->prox = NULL;
		ant->prox = aux;
	}
	
	return l;
}

Lista* menores(Lista * l, int val_ref){
	
	Lista *p = l;
	Lista *result = NULL;
	
	while(p!=NULL){
		if(p->info < val_ref){
			result = insere(result,p->info);
		}
		p = p->prox;
	}
	return result;
}

int busca(Lista* l, int x){
	
	Lista *p = l;
	int flag = 0;
	
	while(p!=NULL){
		if(p->info == x){
			flag = 1;
		}
		p = p->prox;
	}
	return flag;
}

Lista * eliminar_repetidos(Lista* l){
	
	Lista *result = NULL;
	
	if(!vazia(l)){
		Lista *p = l;
		while(p!=NULL){
			if(busca(result,p->info) == 0){
				result = insere(result,p->info);
			}
			p = p->prox;
		}
	}
	
	return result;
}

Lista* concatena(Lista* l1, Lista* l2){
	
	Lista* p = l1;
	while(p->prox!=NULL){
		p = p->prox;
	}
	p->prox = l2;
	return l1;

}

int contar_ocorrencias(Lista* l, int x){
	int cont = 0;
	
	Lista* p = l;
	
	while(p!=NULL){
		if(p->info == x){
			cont++;
		}
		p = p->prox;
	}
	
	return cont;
}

int main(){
	Lista *l = NULL;
	Lista *r = NULL;
	Lista *c = NULL;
	
	l = insere(l,5);
	l = insere(l,8);
	l = insere(l,2);
	l = insere(l,2);
	l = insere(l,2);
	l = insere(l,10);
	r = insere(r,1);
	r = insere(r,2);
	r = insere(r,3);
	imprimelista(l);
	printf("\n\n");
	imprimelista(r);
	printf("\n\n");
	c = concatena(l,r);
	imprimelista(c);
	
	//l = eliminar_repetidos(l);

	printf("\n\nNumero de ocorrencias de %d: %d", 2,contar_ocorrencias(c,2));
	//l = inserir_apos(l,2,3);
	//printf("\n\n");
	//imprimelista(l);
	//printf("\n\n");
	//l = menores(l,5);
	//imprimelista(l);
	return 0;
}
