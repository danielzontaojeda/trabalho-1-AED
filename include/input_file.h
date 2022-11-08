
#ifndef __INPUT_FILE_H
#define __INPUT_FILE_H


#include "linked_list.h"

// pega os comandos de um arquivo texto
// Entrada: nome do arquivo texto
// Retorno: lista encadeada com os elementos do arquivo texto
// Pré-condições: arquivo texto existe
// Pós-condições: nenhuma
LinkedList *read_file(char* filename);

#endif