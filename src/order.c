#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "linked_list.h"
#include "order.h"
#include "product.h"
#include "debug.h"
#include "util.h"

void print_item_order(Order_items *item){
	for(int i=0;i<100;i++) printf("=");
	printf("\n");
	printf("tipo: %s\n",item->type);
	printf("id: %u\n",item->id);
	printf("quantidade: %u\n",item->quantity);
	printf("size: %d\n", item->size);
	for(int i=0;i<100;i++) printf("=");
	printf("\n");
}

static enum size set_item_size(char size_str){
	if(size_str == 'p' || size_str == 'P') return small;
	if(size_str == 'm' || size_str == 'M') return medium;
	if(size_str == 'g' || size_str == 'G') return large;
	return -1;
}

static void parse_item_string(Order_items *item, char *item_order){
	char *token = strtok(item_order, ";");
	char size_str;
	while(token != NULL){
		sscanf(token, "(%[^,],%u,%u,%c%*c",item->type, &item->id, &item->quantity, &size_str);
		item->size = set_item_size(size_str);
		assert(item->size != -1);
		print_item_order(item);
		token = strtok(NULL, ";");
	}
}

// PD;1;11111111111;(SD,1,2,M);(SD,2,1,P);(BB,2,3,M);(EX,3,4);(SM,2,2)
LinkedList *create_order_from_file(LinkedList *commands){
	assert(commands);
	char type[3], cpf[12], item_order[SIZE_LINE];
	unsigned id;
	LinkedList *command = commands;
	LinkedList *order_items = NULL;
	while(command != NULL){ 
		sscanf(command->info, "%[^;]", type);
		if(!strcmp(type, "PD")){
			Order_items *item = calloc(1, sizeof(Order_items));
			Order *order = calloc(1, sizeof(Order));
			sscanf(command->info, "%[^;];%u;%[^;];%[^\n]%*c",type, &id, cpf, item_order);
			#ifdef __DEBUG
				// printf("type: %s, id: %u, cpf: %s, item_order: %s\n",type, id, cpf, item_order);	
			#endif
			parse_item_string(item, item_order);
		}
		command = command->prox;
	}
}