#ifndef LISTAARQUIVO_H
#define LISTAARQUIVO_H

#include <stdio.h>
#include <stdlib.h>

/*
 * Uma lista em arquivo possui um cabeçalho e em seguida um conjunto de nós;
 * A posição de cada nó é registrada como um número inteiro iniciando em 1, assim posição significa
 posição inválida ou nula.
 * A lista armazena em sua estrutura dados que serão gravados no arquivo e dados que não serão.
 * Os dados que serão gravados no arquivo estão dentro de uma estrutura interna chamada
 "CabecalhoArquivo".
 
 * A organização do arquivo se dá da seguinte forma:
 	+-------------------+----------------------------+----------------------------+-----
 	| CABEÇALHO ARQUIVO | NÓ / Posição vazia         | NÓ / Posição vazia         | ...
 	+-------------------+----------------------------+----------------------------+-----
 
 * Um nó é organizado no arquivo da seguinte forma:
 	+-----------+-------------------------------+
 	| Cabeçalho | Info                          |
 	+-----------+-------------------------------+
 */

// Estrutura que será armazenada no início do arquivo de lista contendo as informações necessárias
// para gerenciar o arquivo.
typedef struct CabecalhoArquivo {
	int cabeca; // Posição do primeiro nó da lista do arquivo (posições começam em 1).
	int pe; // Posição do último nó adicionado na lista.
	int tamanho_lista; // Número de nós no arquivo que fazem parte da lista.
	int tamanho_arquivo; // Número de nós na lista (contando nós de posições vazias).
	int cabeca_pilha; // Topo da pilha de posições vazias.
} CabecalhoArquivo;

// Estrutura de controle de uma lista encadeada dupla genérica em arquivo.
typedef struct ListaArquivo {
	CabecalhoArquivo cabecalho;
	int tamanho_info; // Número de bytes das informações armazenadas nos nós da lista.
	int tamanho_no; // Número de bytes que um nó ocupa no arquivo de lista (cabeçalho + conteúdo).
	FILE * arquivo; // Referencia o arquivo da lista.
} ListaArquivo;

// Estrutura que será armazenada no início de cada nó indicando o próximo e o anterior da lista.
typedef struct CabecalhoNo {
	int proximo;
	int anterior;
} CabecalhoNo;

// Estrutura que contém um item da lista e as informações do nó no arquivo.
typedef struct No {
	CabecalhoNo cabecalho;
	int posicao; // Posição do nó na lista.
	ListaArquivo *lista; // Endereço da lista do nó.
	void *info; // Área de memória contendo os bytes da informação do nó.
} No;

/*
 * Carrega, do arquivo, os dados do cabeçalho da lista.
 * Pré-condições: A lista deve ter sido inicializada com a função "abrirListaArquivo" e não pode ser
 um endereço nulo.
 * Entrada: O endereço de uma lista.
 */
void carregaCabecalho(ListaArquivo *lista);

/*
 * Grava os dados do cabeçalho da lista no arquivo.
 * Pré-condições: A lista deve ter sido inicializada com a função "abrirListaArquivo" e não pode ser
 um endereço nulo.
 * Entrada: O endereço de uma lista.
 */
void salvaCabecalho(ListaArquivo *lista);

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
void carregaNo(No *no);

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
void salvaNo(No *no);

/*
 * Aloca uma lista dupla em arquivo e retonra o endereço da estrutura que contém os dados de
 controle. Caso a lista não puder ser abrta o retorno é nulo.
 * Entradas:
 	- nomeArquivo: String contendo o nome do arquivo;
 	- tamanho_info: Inteiro contendo o número de bytes da estrutura que será armazenada na lista.
 * Saída: Um ponteiro contendo uma estrutura de controle da lista ou nulo.
 */
ListaArquivo *abrirListaArquivo(char nomeArquivo[], int tamanho_info);

/*
 * Verifica se um nó é um nó válido da lista.
 */
int noValido(No no);

/*
 * Retorna o primeiro nó da lista.
 * Pré-condições:
 	- A lista deve ter sido inicializada com a função "abrirListaArquivo".
 * Entrada:
 	- lista: O endereço de uma lista de arquivo;
 	- info: O endereço da memória para onde os bytes de informação devem ser copiados, ou NULL.
 * Saída: O primeiro nó da lista.
 */
No primeiroNo(ListaArquivo *lista, void *info);

/*
 * Retorna o próximo nó na lista.
 * Pré-condições:
 	- O nó de referência deve ter sido obtido atravéz da função "primeiroNo" ou "proximoNo";
 * Entrada:
 	- no: Uma estrutura de nó da lista;
 	- info: endereço de memória para onde as informações deverão ser copiadas, ou NULL.
 * Saída: o próximo nó da lista;
 */
No proximoNo(No no, void *info);

/*
 * Remove um nó da lista, conectando o anterior ao próximo e inserindo na lista de posições vazias.
 * Pré-condições:
 	- O nó de referência deve ter sido obtido atravéz da função "primeiroNo" ou "proximoNo";
 * Entrada:
 	- no: Uma estrutura de nó da lista;
 */
void removeNo(No no);

/*
 * Insere uma informação no final da lista.
 * Pré-condições:
 	- A lista deve ter sido inicializada com a função "abrirListaArquivo";
 	- info deve conter um endereço de uma informação váldia ou NULL.
 * Entrada:
 	- lista: Uma lista em arquivo;
 	- info: Endereço de memória de uma informação ou NULL.
 */
void listaInsere(ListaArquivo *lista, void *info);

/*
 * Fecha o arquivo da lista e libera a memória usada pela estrutura de controle lista.
 * Pré-condições:
 	- A lista deve ter sido inicializada com a função "abrirListaArquivo".
 * Pós-condições:
 	- Os dados estarão salvos no arquivo, que não estará mais aberto, e a memória estará desalocada.
 */
void fechaListaArquivo(ListaArquivo *lista);

#include "listaarquivo.c"
#endif // LISTAARQUIVO_H
