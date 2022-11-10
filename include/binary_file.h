#ifndef __BINARY_FILE_H
#define __BINARY_FILE_H

#include <stdio.h>

#include "linked_list.h"
#include "product.h"

#define DATABASE_FOLDER "./database"

int _mkdir(const char *pathname);

FILE *get_database_product();

FILE *get_database_completed_orders();

// Cria pasta 'database' se ela nao existir
// Entrada: Nenhuma
// Retorno: Nenhum
// Pré-condições: Nenhuma
// Pós-condições: Pasta 'database' criada
void create_database_directory();

void write_product_list_to_file(LinkedList *list_products);

void write_product_to_file(Product *product, FILE *database_product);

int is_file_empty(FILE *database);

#endif