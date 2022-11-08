#include "linked_list.h"

typedef struct order{
	char cpf[11];
	LinkedList* list_products;
	double price_total;
} Order;

Order *create_new_order(char *cpf);

Order *get_latest_3_orders(char *cpf);

void print_order(Order *order);

void print_all_orders();

int remove_order(char *cpf);





