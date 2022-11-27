#ifndef __ORDER_H
#define __ORDER_H

#include "linked_list.h"
#include "product.h"

enum choice_order {create_enum=1, search_order, print_fulfilled, fulfill_next, delete_order};

typedef struct {
	char type[3];
	unsigned id_product;
	unsigned quantity;
	enum size size;
	int next;
} Order_items;

typedef struct{
	unsigned id;
	char type[3];
	char cpf[12];
	int head_item;
	int next;
	double price_total;
} Order_file;

typedef struct order{
	unsigned id;
	char type[3];
	char cpf[12];
	LinkedList* list_products;
	int next;
	double price_total;
} Order;

LinkedList *create_order_from_file(LinkedList *commands);

Order *create_new_order(char *cpf);

Order *get_latest_3_orders(char *cpf);

void print_order(Order *order);

void print_all_orders();

int remove_order(char *cpf);

void print_item_order(Order_items *item);

void process_submenu_order(enum choice_order choice);

#endif
