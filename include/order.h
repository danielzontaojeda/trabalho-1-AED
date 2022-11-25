#ifndef __ORDER_H
#define __ORDER_H

#include "linked_list.h"
#include "product.h"

typedef struct {
	char type[3];
	unsigned id;
	unsigned quantity;
	enum size size;
	int next;
} Order_itens;

typedef struct order{
	char cpf[12];
	LinkedList* list_products;
	double price_total;
} Order;

Order *create_new_order(char *cpf);

Order *get_latest_3_orders(char *cpf);

void print_order(Order *order);

void print_all_orders();

int remove_order(char *cpf);

#endif
