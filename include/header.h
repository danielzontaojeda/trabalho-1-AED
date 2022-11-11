#ifndef __HEADER_H
#define __HEADER_H

#include <stdio.h>

// macro para definir valor da posicao vazia 
// na estrutura de cabecalho
#define EMPTY -1

// estrutura do cabecalho do arquivo
typedef struct header{
	int pos_head;	// posicao da cabeca da lista
	int pos_top;	// posicao da primeira posicao livre no arquivo
	int pos_free;	// cabeca da lista de posicoes vazias
} Header;

// Caso database esteja vazia, retorna NULL
// caso contrario, retorna seu cabecalho
// Entrada: ponteiro para banco de dados
// Retorno: ponteiro para estrutura de cabecalho do arquivo
// Pré-condições: database e um ponteiro para arquivo valido
// Pós-condições: estrutura de cabecalho alocada e retornada
Header *read_header(FILE *database);

// Cria, inicializa e grava um cabecalho em database caso
// um cabecalho ainda nao exista
// Entrada: ponteiro para arquivo de banco de dados
// Retorno: nenhum
// Pré-condições: database e um ponteiro para arquivo valido
// Pós-condições: cabecalho gravado em database caso 
// 				  ele ainda nao tenha um cabecalho
void create_header(FILE* database);

#endif