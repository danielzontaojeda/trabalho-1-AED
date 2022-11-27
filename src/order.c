#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "linked_list.h"
#include "order.h"
#include "product.h"
#include "debug.h"
#include "screen.h"
#include "binary_file.h"
#include "header.h"

static char *get_size_str(enum size size){
	if(size == small) return "pequeno";
	if(size == medium) return "medio";
	if(size == large) return "grande";
	return "";
}

void print_item_order(Order_items *item){
	printf("tipo: %-9s\t ",get_product_type_name(item->type));
	printf("id: %-3u\t ",item->id_product);
	printf("quantidade: %3u\t ",item->quantity);
	if(!strcmp(item->type, "SD") || !strcmp(item->type, "BB"))
		printf("tamanho: %s", get_size_str(item->size));
	printf("\n");
}

static enum size set_item_size(char size_str){
	if(size_str == 'p' || size_str == 'P') return small;
	if(size_str == 'm' || size_str == 'M') return medium;
	if(size_str == 'g' || size_str == 'G') return large;
	printf("size_str in set_item_size not recognized");
	exit(1);
	return -1;
}

static void parse_item_string(Order *order, char *item_order){
	char *token = strtok(item_order, ";");
	char size_str;
	char type[3];
	while(token != NULL){
		Order_items *item = calloc(1, sizeof(Order_items));
		sscanf(token, "%[^,]" ,type);
		if(!strcmp(type, "SD") || !strcmp(type, "BB")){
			sscanf(token, "(%[^,],%u,%u,%c%*c",item->type, &item->id_product, &item->quantity, &size_str);
			item->size = set_item_size(size_str);
		}else
			sscanf(token, "(%[^,],%u,%u)",item->type, &item->id_product, &item->quantity);
		token = strtok(NULL, ";");
		order->list_products = ll_insert(order->list_products, item);
	}
}

void print_order(Order *order){
	print_separator();
	printf("tipo: %s\n",order->type);
	printf("id: %u\n",order->id);
	printf("cpf: %s\n",order->cpf);
	printf("pedido: \n");
	LinkedList *actual = order->list_products;
	while(actual != NULL){
		Order_items *item = actual->info;
		print_item_order(item);
		actual = actual->prox;
	}
	print_separator();
}

// PD;1;11111111111;(SD,1,2,M);(SD,2,1,P);(BB,2,3,M);(EX,3,4);(SM,2,2)
LinkedList *create_order_from_file(LinkedList *commands){
	assert(commands);
	char type[3], cpf[12], item_order[SIZE_LINE];
	unsigned id;
	LinkedList *command = commands;
	LinkedList *list_order = NULL;
	while(command != NULL){ 
		sscanf(command->info, "%[^;]", type);
		if(!strcmp(type, "PD")){
			Order *order = calloc(1, sizeof(Order));
			order->list_products = NULL;
			sscanf(command->info, "%[^;];%u;%[^;];%[^\n]%*c",type, &id, cpf, item_order);
			parse_item_string(order, item_order);
			order->id = id;
			strcpy(order->type, type);
			strcpy(order->cpf, cpf);
			// print_order(order);
			list_order = ll_insert(list_order, order);
		}
		command = command->prox;
	}
	return list_order;
}

static Order *get_order_from_keyboard(){
	clear_screen();
	Order *order = calloc(1, sizeof(Order));
	char order_items[SIZE_LINE];
	strcpy(order->type, "PD");
	printf("Digite o id do pedido.\n");
	scanf("%u%*c",&order->id);
	printf("Digite o cpf do cliente. (11 digitos sem pontuacao)\n");
	fgets(order->cpf, sizeof(char)*13, stdin);
	printf("Digite items do pedido (tipo, id, quantidade, tamanho?) separados por ;\n");
	fgets(order_items, SIZE_LINE, stdin);	
	parse_item_string(order, order_items);
	return order;
}

void process_submenu_order(enum choice_order choice){
	switch (choice){
	case create_enum:
		;
		Order *order = get_order_from_keyboard();
		FILE *database_order = get_database(DATABASE_PD);
		FILE *database_item_order = get_database(DATABASE_ITEM_PD);
		print_order(order);
		create_header_queue(database_order);
		create_header(database_item_order);
		write_order_to_file(database_order, database_item_order, order);
		fclose(database_order);
		fclose(database_item_order);
		free(order);
		press_enter_to_continue();
		break;
	case search_order:
		printf("Digite o id do pedido.\n");

		break;
	case print_fulfilled:
		break;
	case fulfill_next:
		break;	
	default:
		break;
	}
}