#ifndef LISTAARQUIVO_C
#define LISTAARQUIVO_C

#include "listaarquivo.h"

/*
 * Carrega, do arquivo, os dados do cabeçalho da lista.
 * Pré-condições: A lista deve ter sido inicializada com a função "abrirListaArquivo" e não pode ser
 um endereço nulo.
 * Entrada: O endereço de uma lista.
 */
void carregaCabecalho(ListaArquivo *lista) {

	// Posiciona o ponteiro de leitura e gravação no início do arquivo, onde fica gravado o
	// cabeçalho.
	fseek(lista->arquivo, 0L, SEEK_SET);

	// Carrega do arquivo os dados binários do cabeçalho.
	fread(&lista->cabecalho, sizeof(CabecalhoArquivo), 1, lista->arquivo);
}

/*
 * Grava os dados do cabeçalho da lista no arquivo.
 * Pré-condições: A lista deve ter sido inicializada com a função "abrirListaArquivo" e não pode ser
 um endereço nulo.
 * Entrada: O endereço de uma lista.
 */
void salvaCabecalho(ListaArquivo *lista) {

	// Posiciona o ponteiro de leitura e gravação no início do arquivo, onde fica gravado o
	// cabeçalho.
	fseek(lista->arquivo, 0L, SEEK_SET);

	// Grava os dados binários do cabeçalho no arquivo.
	fwrite(&lista->cabecalho, sizeof(CabecalhoArquivo), 1, lista->arquivo);
}

/*
 * Carrega as informações de um nó da lista de arquivo.
 * Pré-condições:
 	- O nó deve ter o endereço de uma lista inicializada com a função "abrirListaArquivo";
 	- O nó deve ter seu campo "posicao" inicializado;
 	- O campo "info" deve conter o endereço de uma informação ou NULL.
 * Pós-condições:
 	- O cabeçalho do nó será gravado em sua respectiva posição no arquivo, e, caso haja um indereço
 	válido no campo "info" será gravado também como informação do nó.
 */
void carregaNo(No *no) {
	if (no->posicao==0)
		return;
	ListaArquivo *lista = no->lista;
	FILE *arquivo = lista->arquivo;
	// Calcula a posição em que o ponteiro de leitura e gravação deve estar.
	// Pula o cabeçalho do arquivo, subtrai 1 da posição e multiplica pelo tamanho total de um nó.
	int posicao = sizeof(CabecalhoArquivo) + (no->posicao - 1) * lista->tamanho_no;


	fseek(arquivo, posicao, SEEK_SET);
	fread(&no->cabecalho, sizeof(CabecalhoNo), 1, arquivo);

	// Se o nó contém informações elas são gravadas logo após o cabeçalho do nó.	
	if (no->info!=NULL)
		fread(no->info, lista->tamanho_info, 1, arquivo);
}

/*
 * Grava as informações de um nó da lista no arquivo.
 * Pré-condições:
 	- O nó deve ter o endereço de uma lista inicializada com a função "abrirListaArquivo";
 	- O nó deve ter seu campo "posicao" inicializado;
 	- O campo "info" deve conter o endereço de uma informação ou NULL.
 * Pós-condições:
 	- O cabeçalho do nó será carregado com informações da sua respectiva posição no arquivo, e, caso
 	haja um indereço válido no campo "info" os próximos bytes do arquivo serão copiados para este
 	endereço de memória como informação do nó.
 */
void salvaNo(No *no) {
	if (no->posicao==0)
		return;
	ListaArquivo *lista = no->lista;
	FILE *arquivo = lista->arquivo;
	// Calcula a posição em que o ponteiro de leitura e gravação deve estar.
	// Pula o cabeçalho do arquivo, subtrai 1 da posição e multiplica pelo tamanho total de um nó.
	int posicao = sizeof(CabecalhoArquivo) + (no->posicao - 1) * lista->tamanho_no;

	fseek(arquivo, posicao, SEEK_SET);
	fwrite(&no->cabecalho, sizeof(CabecalhoNo), 1, arquivo);

	// Se o nó contém um endereço para as informações os seguintes bytes do arquivo serão lidos para
	// este endereço.
	if (no->info!=NULL)
		fwrite(no->info, lista->tamanho_info, 1, arquivo);
}

/*
 * Aloca uma lista dupla em arquivo e retonra o endereço da estrutura que contém os dados de
 controle. Caso a lista não puder ser abrta o retorno é nulo.
 * Entradas:
 	- nomeArquivo: String contendo o nome do arquivo;
 	- tamanho_info: Inteiro contendo o número de bytes da estrutura que será armazenada na lista.
 * Saída: Um ponteiro contendo uma estrutura de controle da lista ou nulo.
 */
ListaArquivo *abrirListaArquivo(char nomeArquivo[], int tamanho_info) {

	// Tenta abrir o arquivo para a leitura e gravação.
	FILE *arquivo = fopen(nomeArquivo, "r+b");

	// Caso o arquivo não pode ser aberto em modo leitura e gravação isso pode significar que o
	// arquivo não existe, então é feita uma abrir tentativa de abertura em modo de escrita.
	if (arquivo==NULL) {
		arquivo = fopen(nomeArquivo, "w+b");

		// Se ainda assim o arquivo não pode ser aberto retona um endereço nulo.
		if (arquivo==NULL)
			return NULL;

		// Nesta linha de execução a lista acaba de ser criada, então as informações do cabeçalho
		// devem ser inicializadas como uma lista vazia.
		ListaArquivo *lista = (ListaArquivo*) malloc(sizeof(ListaArquivo));
		lista->cabecalho.cabeca          = 0;
		lista->cabecalho.pe              = 0;
		lista->cabecalho.tamanho_lista   = 0;
		lista->cabecalho.tamanho_arquivo = 0;
		lista->cabecalho.cabeca_pilha    = 0;

		lista->arquivo = arquivo;
		lista->tamanho_info = tamanho_info;
		lista->tamanho_no = tamanho_info + sizeof(CabecalhoNo);
		salvaCabecalho(lista);
		return lista;
	} else {
		ListaArquivo *lista = (ListaArquivo*) malloc(sizeof(ListaArquivo));
		lista->arquivo = arquivo;
		lista->tamanho_info = tamanho_info;
		lista->tamanho_no = tamanho_info + sizeof(CabecalhoNo);

		// Nesta linha de execução a lista já existia e foi aberta, então as informações do
		// cabeçalho que estão no arquivo devem ser carregados para a estrutura de controle.
		carregaCabecalho(lista);
		return lista;
	}
}

/*
 * Verifica se um nó é um nó válido da lista.
 */
int noValido(No no) {
	return no.posicao > 0;
}

/*
 * Retorna o primeiro nó da lista.
 * Pré-condições:
 	- A lista deve ter sido inicializada com a função "abrirListaArquivo".
 * Entrada:
 	- lista: O endereço de uma lista de arquivo;
 	- info: O endereço da memória para onde os bytes de informação devem ser copiados, ou NULL.
 * Saída: O primeiro nó da lista.
 */
No primeiroNo(ListaArquivo *lista, void *info) {
	No no;
	no.lista = lista;
	no.posicao = lista->cabecalho.cabeca;
	no.info = info;
	carregaNo(&no);
	return no;
}

/*
 * Retorna o próximo nó na lista.
 * Pré-condições:
 	- O nó de referência deve ter sido obtido atravéz da função "primeiroNo" ou "proximoNo";
 * Entrada:
 	- no: Uma estrutura de nó da lista;
 	- info: endereço de memória para onde as informações deverão ser copiadas, ou NULL.
 * Saída: o próximo nó da lista;
 */
No proximoNo(No no, void *info) {
	no.posicao = no.cabecalho.proximo;
	no.info = info;
	carregaNo(&no);
	return no;
}

/*
 * Remove um nó da lista, conectando o anterior ao próximo e inserindo na lista de posições vazias.
 * Pré-condições:
 	- O nó de referência deve ter sido obtido atravéz da função "primeiroNo" ou "proximoNo";
 * Entrada:
 	- no: Uma estrutura de nó da lista;
 */
void removeNo(No no) {
	ListaArquivo *lista = no.lista;
	
	// Se o nó era a cabeça da lista então a cabeça passa a ser o seu próximo.
	if (lista->cabecalho.cabeca == no.posicao)
		lista->cabecalho.cabeca = no.cabecalho.proximo;

	// Se o nó era o pé da lista então o pé passa a ser o seu anterior.
	if (lista->cabecalho.pe == no.posicao)
		lista->cabecalho.pe = no.cabecalho.anterior;

	No anterior;
	anterior.posicao = no.cabecalho.anterior;
	anterior.lista = no.lista;
	anterior.info = NULL;

	No proximo;
	proximo.posicao = no.cabecalho.proximo;
	proximo.lista = no.lista;
	proximo.info = NULL;

	// Amarra o anterior com o próximo e o próximo com o anterior, "pulando" o nó entre os dois.
	carregaNo(&anterior);
	carregaNo(&proximo);
	anterior.cabecalho.proximo = proximo.posicao;
	proximo.cabecalho.anterior = anterior.posicao;
	salvaNo(&anterior);
	salvaNo(&proximo);

	// O nó passa a ser a cabeça de pilha de posições vazias.
	no.cabecalho.proximo = lista->cabecalho.cabeca_pilha;
	lista->cabecalho.cabeca_pilha = no.posicao;

	// Salva as alterações feitas no nó removido e no cabeçalho da lista.
	lista->cabecalho.tamanho_lista --;
	salvaNo(&no);
	salvaCabecalho(lista);
}

/*
 * Insere uma informação no final da lista.
 * Pré-condições:
 	- A lista deve ter sido inicializada com a função "abrirListaArquivo";
 	- info deve conter um endereço de uma informação váldia ou NULL.
 * Entrada:
 	- lista: Uma lista em arquivo;
 	- info: Endereço de memória de uma informação ou NULL.
 */
void listaInsere(ListaArquivo *lista, void *info) {
	No no;
	no.lista = lista;

	// Tenta encontrar uma posição vazia na pilha de posições vazias.
	no.posicao = lista->cabecalho.cabeca_pilha;
	if (no.posicao > 0) {
		// Caso exista uma posição vazia, carrega a posição e atualiza a cabeça da pilha como o
		// próximo deste nó, liberando a posição para ser ocupada.
		no.info = NULL;
		carregaNo(&no);
		lista->cabecalho.cabeca_pilha = no.cabecalho.proximo;
	} else {
		// Caso não existam posições vazias o nó é posicionado no final do arquivo.
		lista->cabecalho.tamanho_arquivo ++;
		no.posicao = lista->cabecalho.tamanho_arquivo;
	}

	// Caso a lista esteja vazia o nó vai ser a abrir cabeça da lista.
	if (lista->cabecalho.tamanho_lista == 0) {
		lista->cabecalho.tamanho_lista = 1;
		lista->cabecalho.cabeca = no.posicao;
	} else {
		lista->cabecalho.tamanho_lista ++;
		// Caso a lista não esteja vazia é atualizado o próximo do pé.
		No pe;
		pe.lista = lista;
		pe.info = NULL;
		pe.posicao = lista->cabecalho.pe;
		carregaNo(&pe);
		pe.cabecalho.proximo = no.posicao;
		salvaNo(&pe);
	}

	// Preenche o cabeçalho e a informação do nó e grava no arquivo.
	no.info = info;
	no.cabecalho.anterior = lista->cabecalho.pe;
	no.cabecalho.proximo = 0;
	salvaNo(&no);

	// Torna o novo nó pé da lista e atualiza no arquivo o cabeçalho da lista.
	lista->cabecalho.pe = no.posicao;
	salvaCabecalho(lista);
}

/*
 * Fecha o arquivo da lista e libera a memória usada pela estrutura de controle lista.
 * Pré-condições:
 	- A lista deve ter sido inicializada com a função "abrirListaArquivo".
 * Pós-condições:
 	- Os dados estarão salvos no arquivo, que não estará mais aberto, e a memória estará desalocada.
 */
void fechaListaArquivo(ListaArquivo *lista) {
	if (lista)
		fclose(lista->arquivo);
}

#endif // LISTAARQUIVO_C
