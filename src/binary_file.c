
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "binary_file.h"
#include "header.h"
#include "order.h"

// Cria stream para database_name localizado na pasta DATABASE_FOLDER
// Entrada: nenhuma
// Retorno: pointeiro para stream do arquivo de banco de dados dos produtos
// Pré-condições: nenhuma
// Pós-condições: ponteiro para o arquivo retornado
FILE *get_database(char *database_name){
	char filename[100];
	sprintf(filename, "%s/%s", DATABASE_FOLDER, database_name);
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
// Entrada: nenhuma
// Retorno: nenhum
// Pré-condições: nenhuma
// Pós-condições: pasta 'database' criada
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
// caso type seja nulo, imprime todos os produtos
// Entrada: ponteiro para o banco de dados de produtos
//        	tipo do produto
// Retorno: nenhum
// Pré-condições: type e um tipo de produto valido ou NULL
//                database_product e um ponteiro valido
// Pós-condições: todos os produtos do tipo type impressos em stdout 
void print_all_products_in_file(FILE *database_product){
	assert(database_product);
	Header *header = read_header(database_product);
	Product *product = read_node(database_product, header->pos_head);
	if(product == NULL) printf("Nenhum produto encontrado.\n");
	while(product){
		int next = product->next;
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
	FILE* database_sd = get_database(DATABASE_SD);
	FILE* database_bb = get_database(DATABASE_BB);
	FILE* database_ex = get_database(DATABASE_EX);
	FILE* database_sm = get_database(DATABASE_SM);
	LinkedList *ll = list_products;
	create_header(database_sd);
	create_header(database_bb);
	create_header(database_ex);
	create_header(database_sm);
	while(ll != NULL){
		Product *product = ll->info;
		if(!strcmp(product->type, "SD"))
			write_product_to_file(ll->info, database_sd);
		else if(!strcmp(product->type, "BB"))
			write_product_to_file(ll->info, database_bb);
		else if(!strcmp(product->type, "EX"))
			write_product_to_file(ll->info, database_ex);
		else if(!strcmp(product->type, "SM"))
			write_product_to_file(ll->info, database_sm);
		ll = ll->prox;
		size++;
	}
	#ifdef __DEBUG
		print_all_products_in_file(database_product, NULL);
	#endif
	printf("%d produtos adicionados ao banco de dados!\n", size);
	fclose(database_sd);
	fclose(database_bb);
	fclose(database_sm);
	fclose(database_ex);
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

static int insert_items_order(FILE *database_item_order, LinkedList *list_items){
	Header *header = read_header(database_item_order);
	assert(header);
	#ifdef __DEBUG
		printf("header: head: %d top: %d free: %d\n",header->pos_head, header->pos_top, header->pos_free);
	#endif
	LinkedList *ll = list_items;
	Order_items *item = list_items->info;
	item->next = -1;
	while(ll != NULL){
		if(header->pos_free == EMPTY){
			fseek(database_item_order, sizeof(Header) + header->pos_top*sizeof(Order_items), SEEK_SET);
			fwrite(item, sizeof(Order_items), 1, database_item_order);
			#ifdef __DEBUG
				printf("written pos: %d, next: %d\n",header->pos_top, item->next);
			#endif
			header->pos_head = header->pos_top;
			header->pos_top += 1;
			fseek(database_item_order, 0, SEEK_SET);
			fwrite(header, sizeof(Header), 1, database_item_order);
			ll = ll->prox;
			if(ll != NULL){
				item = ll->info;
				item->next = header->pos_head;
			}
		}else{
			// TODO
		}
	}
	int head = header->pos_head;
	free(header);
	return head;
}

static Order_file *create_order(Order *order){
	Order_file *order_file = calloc(1, sizeof(Order_file));
	order_file->id = order->id;
	order_file->head_item = -1;
	strcpy(order_file->cpf, order->cpf);
	strcpy(order_file->type, order->type);
	order_file->price_total = order->price_total;	
	return order_file;
}

void write_order_to_file(FILE *database_order, FILE *database_item_order, Order *order){
	Header *header = read_header(database_order);
	assert(header);
	Order_file *order_file = create_order(order);
	order_file->head_item = insert_items_order(database_item_order, order->list_products);
	if(header->pos_free == EMPTY){
		order_file->next = header->pos_head;
		fseek(database_order, sizeof(Header) + header->pos_top*sizeof(Order_file), SEEK_SET);
		fwrite(order_file, sizeof(Order_file), 1, database_order);
		printf("pos: %d next: %d\n",header->pos_top, header->pos_head);
		header->pos_head = header->pos_top;
		header->pos_top += 1;
		fseek(database_order, 0, SEEK_SET);
		fwrite(header, sizeof(Header), 1, database_order);
	}
}

void write_order_list_to_file(LinkedList *list_order){
	assert(list_order);
	FILE *database_order = get_database(DATABASE_PD);
	FILE *database_item_order = get_database(DATABASE_ITEM_PD);
	create_header(database_order);
	create_header(database_item_order);
	LinkedList *ll = list_order;
	while(ll != NULL){
		write_order_to_file(database_order, database_item_order, ll->info);
		ll = ll->prox;
	}
	fclose(database_order);
	fclose(database_item_order);
}