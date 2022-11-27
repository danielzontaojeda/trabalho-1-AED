#ifndef __BINARY_FILE_H
#define __BINARY_FILE_H

#include <stdio.h>

#include "linked_list.h"
#include "product.h"
#include "order.h"

// nome da pasta onde ficarao os banco de dados
#define DATABASE_FOLDER "./database"

// nome do arquivo guardando os dados dos produtos cadastrados
#define DATABASE_SD			"sandwich"
#define DATABASE_BB			"drink"
#define DATABASE_EX			"extra"
#define DATABASE_SM			"dessert"
#define DATABASE_PD 		"order"
#define DATABASE_ITEM_PD 	"item_pd"

// Cabecalho para a funcao do sistema para criar uma pasta
// Entrada: caminho da pasta para ser criada
// Retorno: 1 caso a criacao tenha sucedido, caso contrario 0
// Pré-condições: nenhuma
// Pós-condições: nenhuma
int _mkdir(const char *pathname);

// Cria stream para database_name localizado na pasta DATABASE_FOLDER
// Entrada: nenhuma
// Retorno: pointeiro para stream do arquivo de banco de dados dos produtos
// Pré-condições: nenhuma
// Pós-condições: ponteiro para o arquivo retornado
FILE *get_database(char *database_name);

// Cria pasta 'database' se ela nao existir
// Entrada: nenhuma
// Retorno: nenhum
// Pré-condições: nenhuma
// Pós-condições: pasta 'database' criada
void create_database_directory();

// Coloca todos os produtos na lista encadeada no banco de dados de produtos
// Entrada: lista encadeada com produtos
// Retorno: nenhum
// Pré-condições: list_products->info e um produto
// Pós-condições: todos os produtos inseridos no banco de dados
void write_product_list_to_file(LinkedList *list_products);

// Coloca product em database_product
// Entrada: estrutura de produtos e ponteiro para arquivo
// Retorno: nenhum
// Pré-condições: database_product e um ponteiro valido
// Pós-condições: produto inserido no primeiro lugar vazio do banco de dados
void write_product_to_file(Product *product, FILE *database_product);

// Retorna 1 caso o arquivo esteja vazio, caso contrario retorna 0
// Entrada: ponteiro para o arquivo
// Retorno: 1 ou 0
// Pré-condições: ponteiro para o arquivo valido
// Pós-condições: inteiro booleano retornado 
int is_file_empty(FILE *database);

// Imprime em stdout todos os produtos em database_product
// Entrada: ponteiro para o banco de dados de produtos
//        	tipo do produto
// Retorno: nenhum
// Pré-condições: database_product e um ponteiro valido
// Pós-condições: todos os produtos do arquivo impressos em stdout 
void print_all_products_in_file(FILE *database_product);

// Retorna produto da posicao pos no arquivo database_product
// Entrada: ponteiro para o arquivo de banco de dados dos produtos
// 			posicao no arquivo em que o produto desejado se encontra
// Retorno: estrutura do produto
// Pré-condições: um produto existe nessa posicao
// Pós-condições: estrutura do produto retornada
Product *read_node(FILE *database_product, int pos);

void write_order_list_to_file(LinkedList *list_order);

void write_order_to_file(FILE *database_order, FILE *database_item_order, Order *order);
#endif