
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "header.h"
#include "debug.h"
#include "binary_file.h"

// Cria, inicializa e grava um cabecalho em database caso
// um cabecalho ainda nao exista
// Entrada: ponteiro para arquivo de banco de dados
// Retorno: nenhum
// Pré-condições: database e um ponteiro para arquivo valido
// Pós-condições: cabecalho gravado em database caso 
// 				  database ainda nao tenha um cabecalho
void create_header(FILE* database){
	assert(database);
	Header *header = read_header(database);
	if(header == NULL){
		Header *header = malloc(sizeof(Header));
		header->pos_top = 0;
		header->pos_head = EMPTY;
		header->pos_free = EMPTY;
		assert(fwrite(header, sizeof(Header), 1, database));
		#ifdef __DEBUG
			printf("DEBUG: Header written\n");
		#endif
	}else{
		#ifdef __DEBUG
			printf("DEBUG: Header already exists.\n");
		#endif
	}
	free(header);
}

// Caso database esteja vazia, retorna NULL
// caso contrario, retorna seu cabecalho
// Entrada: ponteiro para banco de dados
// Retorno: ponteiro para estrutura de cabecalho do arquivo
// Pré-condições: database e um ponteiro para arquivo valido
// Pós-condições: estrutura de cabecalho alocada e retornada
Header *read_header(FILE *database){
	assert(database);
	if(is_file_empty(database) == 1) return NULL;
	Header *header = malloc(sizeof(Header));
	fseek(database, 0, SEEK_SET);
	fread(header, sizeof(Header), 1, database);
	assert(header);
	#ifdef __DEBUG
		printf("DEBUG: read_head -> top = %d, head = %d, free = %d\n", 
		header->pos_top, header->pos_head, header->pos_free);
	#endif
	return header;
}
