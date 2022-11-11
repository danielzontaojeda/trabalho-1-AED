
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "binary_file.h"
#include "debug.h"
#include "header.h"

// Cria stream para banco de dados de produtos caso ele nao exista
// e retorna um ponteiro para tal
// Entrada: nenhuma
// Retorno: pointeiro para stream do arquivo de banco de dados dos produtos
// Pré-condições: nenhuma
// Pós-condições: ponteiro para o arquivo retornado
FILE *get_database_product(){
	char filename[100];
	strcpy(filename, DATABASE_FOLDER);
	strcat(filename, "/product");
	FILE *file = fopen(filename, "r+b");
	if(file == NULL) file = fopen(filename, "w+b");
	assert(file);
	return file;
}

// Retorna 1 caso o arquivo esteja vazio, caso contrario retorna 0
// Entrada: ponteiro para o arquivo
// Retorno: 1 ou 0
// Pré-condições: ponteiro para o arquivo valido
// Pós-condições: inteiro booleano retornado
int is_file_empty(FILE *database){
	assert(database);
	fseek(database, 0, SEEK_END);
	int is_empty = ftell(database) == 0;
	return is_empty;
}

// Cria pasta 'database' se ela nao existir
// Entrada: Nenhuma
// Retorno: Nenhum
// Pré-condições: Nenhuma
// Pós-condições: Pasta 'database' criada
void create_database_directory(){
	#ifdef __linux__
       mkdir(DATABASE_FOLDER, 777); 
   #else
       _mkdir(DATABASE_FOLDER);
   #endif
}

// Retorna produto da posicao pos no arquivo database_product
// Entrada: ponteiro para o arquivo de banco de dados dos produtos
// 			posicao no arquivo em que o produto desejado se encontra
// Retorno: estrutura do produto
// Pré-condições: um produto existe nessa posicao
// Pós-condições: estrutura do produto retornada
Product *read_node(FILE *database_product, int pos){
	if(pos == EMPTY) return NULL;
	Product *product = malloc(sizeof(Product));
	fseek(database_product, sizeof(Header) + pos*sizeof(Product), SEEK_SET);
	fread(product, sizeof(Product), 1, database_product);
	return product;
}

// Imprime em stdout todos os produtos do tipo type em database_product
// Entrada: ponteiro para o banco de dados de produtos
//        	tipo do produto
// Retorno: nenhum
// Pré-condições: type e um tipo de produto valido
//                database_product e um ponteiro valido
// Pós-condições: todos os produtos do tipo type impressos em stdout 
void print_all_products_in_file(FILE *database_product, char *type){
	assert(is_type_of_product(type));
	assert(database_product);
	Header *header = read_header(database_product);
	Product *product = read_node(database_product, header->pos_head);
	if(product == NULL) printf("Nenhum produto encontrado.\n");
	while(product){
		int next = product->next;
		if(!strcmp(product->type, type))
			print_product(product);
		free(product);
		product = read_node(database_product, next);
	}
	free(header);
}

// Coloca todos os produtos na lista encadeada no banco de dados de produtos
// Entrada: lista encadeada com produtos
// Retorno: nenhum
// Pré-condições: list_products->info e um produto
// Pós-condições: todos os produtos inseridos no banco de dados
void write_product_list_to_file(LinkedList *list_products){
	assert(list_products);
	int size = 0;
	create_database_directory();
	FILE* database_product = get_database_product();
	LinkedList *ll = list_products;
	create_header(database_product);
	while(ll != NULL){
		write_product_to_file(ll->info, database_product);
		ll = ll->prox;
		size++;
	}
	#ifdef __DEBUG
		print_all_products_in_file(database_product);
	#endif
	printf("%d produtos adicionados ao banco de dados!\n", size);
	fclose(database_product);
}

// Coloca product em database_product
// Entrada: estrutura de produtos e ponteiro para arquivo
// Retorno: nenhum
// Pré-condições: database_product e um ponteiro valido
// Pós-condições: produto inserido no primeiro lugar vazio do banco de dados
static void insert_product(Product *product, FILE *database_product){
	Header *header = read_header(database_product);
	assert(header);
	if(header->pos_free == EMPTY){
		product->next = header->pos_head;
		fseek(database_product, sizeof(Header) + header->pos_top * sizeof(Product), SEEK_SET);
		fwrite(product, sizeof(Product), 1, database_product);
		#ifdef __DEBUG
			printf("DEBUG: %s inserted in position %d\n",product->name,header->pos_top);
		#endif
		header->pos_head = header->pos_top;
		header->pos_top += 1;
		fseek(database_product, 0, SEEK_SET);
		assert(fwrite(header, sizeof(Header), 1, database_product));
	}else{
		//TODO: implement
		exit(1);
	}
	free(header);
}

// Coloca product em database_product
// Entrada: estrutura de produtos e ponteiro para arquivo
// Retorno: nenhum
// Pré-condições: database_product e um ponteiro valido
// Pós-condições: produto inserido no primeiro lugar vazio do banco de dados
void write_product_to_file(Product *product, FILE *database_product){
	#ifdef __DEBUG
		printf("DEBUG: write_product_to_file -> product.name = %s, product.id = %d\n",product->name, product->id);		
	#endif
	insert_product(product, database_product);
}
