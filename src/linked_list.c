#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

int ll_is_empty(LinkedList* l){
	return l == NULL;
}

// LinkedList* ll_insert(LinkedList* l, void* info){
// 	LinkedList* no = malloc(sizeof(LinkedList));
// 	no->info = info;
// 	if(ll_is_empty(l)) no->prox = NULL;
// 	else no->prox = l;	
// 	return no;
// }

LinkedList* ll_insert(LinkedList* l, void* info){
	if(l == NULL){
		LinkedList* node = malloc(sizeof(LinkedList));
		node->info = info;
		node->prox = NULL;
		return node;
	} 
	l->prox = ll_insert(l->prox, info);
}

int ll_length(LinkedList* l){
	if(l == NULL) return 0;
	if(l->prox == NULL) return 1;
	return ll_length(l->prox) + 1;
}


void ll_print(LinkedList* l){
	if(ll_is_empty(l)) return;
	if(ll_is_empty(l->prox)) {
		printf("%s",((TYPE_VAR)l->info));
		printf("\n");
		return;
	}
	printf("%s",((TYPE_VAR)l->info));
	ll_print(l->prox);
}

LinkedList* ll_remove(LinkedList* l, void* info){
	if(ll_is_empty(l)) return NULL;
	if(l->info == info){
		LinkedList* temp = NULL;
		if(!ll_is_empty(l->prox)) temp = l->prox;
		free(l);
		l = NULL;
		return temp;
	}
	l->prox = ll_remove(l->prox, info);
	return l;	
}

void ll_delete(LinkedList* l){
	if(l == NULL) return;
	LinkedList* next = l->prox;
	free(l->info);
	l->info = NULL;
	free(l);
	l = NULL;
	ll_delete(next);
}