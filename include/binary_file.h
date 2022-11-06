#include <stdio.h>

#include "linked_list.h"
#include "product.h"

FILE* get_database_product();

FILE* get_database_completed_orders();

FILE* get_queue_orders();

void create_database_directory();

void write_product_list_to_file(LinkedList* list_products);

Product* get_product();

