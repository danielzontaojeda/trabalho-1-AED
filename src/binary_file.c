
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "binary_file.h"
#include "debug.h"

#define EMPTY -1

FILE *get_database_product(){
	char filename[100];
	strcpy(filename, DATABASE_FOLDER);
	strcat(filename, "/product");
	FILE *file = fopen(filename, "w+b");
	assert(file);
	return file;
}

static void create_header(FILE* database){
	Header *header = malloc(sizeof(Header));
	header->pos_top = 0;
	header->pos_head = EMPTY;
	header->pos_free = EMPTY;
	assert(fwrite(header, sizeof(Header), 1, database));
	free(header);
	#ifdef __DEBUG
		printf("DEBUG: Header written\n");
	#endif
}

FILE *get_database_completed_orders();

FILE *get_queue_orders();

void create_database_directory(){
	#ifdef __linux__
       mkdir(DATABASE_FOLDER, 777); 
   #else
       _mkdir(DATABASE_FOLDER);
   #endif
}

Product *read_node(FILE *database_product, int pos){
	if(pos == EMPTY) return NULL;
	Product *product = malloc(sizeof(Product));
	fseek(database_product, sizeof(Header) + pos*sizeof(Product), SEEK_SET);
	fread(product, sizeof(Product), 1, database_product);
	#ifdef __DEBUG
		print_product(product);
	#endif
	return product;
}

void print_all_products_in_file(FILE *database_product){
	Header *header = read_header(database_product);
	Product *product = read_node(database_product, header->pos_head);
	while(product){
		int next = product->next;
		free(product);
		product = read_node(database_product, next);
	}
	free(header);
}

void write_product_list_to_file(LinkedList *list_products){
	// TODO: file not empty
	assert(list_products);
	create_database_directory();
	FILE* database_product = get_database_product();
	LinkedList *ll = list_products;
	create_header(database_product);
	while(ll != NULL){
		write_product_to_file(ll->info, database_product);
		ll = ll->prox;
	}
	#ifdef __DEBUG
		printf("DEBUG: All products written\n");
		print_all_products_in_file(database_product);
	#endif
}

Header *read_header(FILE *database){
	Header *header = malloc(sizeof(Header));
	fseek(database, 0, SEEK_SET);
	fread(header, sizeof(Header), 1, database);
	assert(header);
	#ifdef __DEBUG
		printf("DEBUG: read_head -> top = %d, head = %d, free = %d\n", header->pos_top, header->pos_head, header->pos_free);
	#endif
	return header;
}

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
		abort();
	}
	free(header);
}

void write_product_to_file(Product *product, FILE *database_product){
	#ifdef __DEBUG
		printf("DEBUG: write_product_to_file -> product.name = %s, product.id = %d\n",product->name, product->id);		
	#endif
	insert_product(product, database_product);
}

Product *get_product();

