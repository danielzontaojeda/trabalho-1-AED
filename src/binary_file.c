
#include <stdio.h>
#include <stdlib.h>

#include "binary_file.h"


FILE  *get_database_product(){
	FILE  *file;
}

FILE *get_database_completed_orders();

FILE *get_queue_orders();

void create_database_directory(){
	char *name = "database";
	#ifdef __linux__
       mkdir(name, 777); 
   #else
       _mkdir(name);
   #endif
}

void write_product_list_to_file(LinkedList *list_products){
	create_database_directory();
	// create_database_product();
}

Product *get_product();

