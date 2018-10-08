#include "listaarquivo.h"

struct Elemento {
	int numero;
	char texto[256];
} typedef Elemento;

void listar(ListaArquivo *lista) {
	Elemento e;
	No no = primeiroNo(lista, &e);
	puts("Listagem: ");
	while (noValido(no)) {
		printf(" - %d: %s", e.numero, e.texto);
		no = proximoNo(no, &e);
	}
}

void inserir(ListaArquivo *lista) {
	Elemento e;
	printf("Numero: ");
	scanf("%d%*c", &e.numero);
	printf("Texto: ");
	fgets(e.texto, 256, stdin);
	listaInsere(lista, &e);
}

void remover(ListaArquivo *lista) {
	Elemento e;
	int numero;
	printf("Numero: ");
	scanf("%d%*c", &numero);
	No no = primeiroNo(lista, &e);
	while (noValido(no)) {
		if (e.numero == numero) {
			removeNo(no);
			puts("No removido");
			return;
		}
		no = proximoNo(no, &e);
	}
	puts("No nao encontrado");
}

int menu(ListaArquivo *lista) {
	int opcao;
	do {
		puts("1. Listar elementos");
		puts("2. Inserir elemento");
		puts("3. Remover elemento");
		puts("4. Sair");
		scanf("%d%*c", &opcao);
		switch (opcao) {
			case 1: listar(lista); break;
			case 2: inserir(lista); break;
			case 3: remover(lista); break;
		}
	} while (opcao!=4);
}

int main() {
	ListaArquivo *lista = abrirListaArquivo("Lista.bin", sizeof(Elemento));
	menu(lista);
	fechaListaArquivo(lista);
}
