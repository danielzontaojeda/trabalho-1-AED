#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "linked_list.h"
#include "order.h"
#include "product.h"
#include "debug.h"

// PD;1;11111111111;(SD,1,2,M);(SD,2,1,P);(BB,2,3,M);(EX,3,4);(SM,2,2)
LinkedList *create_order_from_file(LinkedList *commands){
	assert(commands);
	char type[3], cpf[12], item_order[SIZE_LINE];
	unsigned id;
	sscanf(commands->info, "%[^;];%d;%[^;];%[^\n]%*c",type, id, cpf, item_order);
}