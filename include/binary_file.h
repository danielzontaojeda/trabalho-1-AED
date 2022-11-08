#ifndef __BINARY_FILE_H
#define __BINARY_FILE_H

#include <stdio.h>
#include <dirent.h>

#include "linked_list.h"
#include "product.h"

typedef struct header{
	int pos_head;
	int pos_top;
	int pos_free;
} Header;

#define DATABASE_FOLDER "./database"

int _mkdir(const char *pathname);

FILE *get_database_product();

void create_product_header(FILE* database_product);

FILE *get_database_completed_orders();

FILE *get_queue_orders();

// Cria pasta 'database' se ela nao existir
// Entrada: Nenhuma
// Retorno: Nenhum
// Pré-condições: Nenhuma
// Pós-condições: Pasta 'database' criada
void create_database_directory();

void write_product_list_to_file(LinkedList* list_products);

Product *get_product();

#endif