
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "binary_file.h"

#define __DEBUG

FILE  *get_database_product(){
	char filename[100];
	strcpy(filename, DATABASE_FOLDER);
	strcat(filename, "/product");
	FILE *file = fopen(filename, "w+b");
	assert(file);
	return file;
}

void create_product_header(FILE* database_product){
	Header *header = malloc(sizeof(Header));
	header->pos_top = 0;
	header->pos_head = 0;
	header->pos_free = -1;
	fwrite(header, sizeof(header), 1, database_product);
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

void write_product_list_to_file(LinkedList *list_products){
	create_database_directory();
	FILE* database_product = get_database_product();
	create_product_header(database_product);
}

Product *get_product();

