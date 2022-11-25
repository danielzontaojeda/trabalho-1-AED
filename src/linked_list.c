#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "product.h"

int ll_is_empty(LinkedList *l){
	return l == NULL;
}

// Insere um elemento na lista
// Entrada: lista e elemento a ser inserido
// Retorno: lista alterada
// Pré-condição: nenhuma
// Pós-condição: elemento é inserido na lista
LinkedList *ll_insert(LinkedList *l, void *info){
	if(l == NULL){
		LinkedList *node = malloc(sizeof(LinkedList));
		node->info = info;
		node->prox = NULL;
		return node;
	} 
	l->prox = ll_insert(l->prox, info);
	return l;
}

// Retorna o numero de membros da lista
// Entrada: lista
// Retorno: numero de membros da lista
// Pré-condições: nenhuma
// Pós-condições: numero de membros da lista retornado
int ll_length(LinkedList *l){
	if(l == NULL) return 0;
	if(l->prox == NULL) return 1;
	return ll_length(l->prox) + 1;
}

// Imprime os elementos da lista
// Entrada: lista
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: os elementos são impressos no console
void ll_print(LinkedList *l){
	if(ll_is_empty(l)) return;
	if(ll_is_empty(l->prox)) {
		printf("%s",((TYPE_VAR)l->info));
		printf("\n");
		return;
	}
	printf("%s\n",(TYPE_VAR)l->info);
	ll_print(l->prox);
}

// Remove um elemento da lista
// Entrada: lista e elemento a ser removido
// Retorno: lista alterada
// Pré-condição: nenhuma
// Pós-condição: elemento é removido da lista
LinkedList *ll_remove(LinkedList *l, void *info){
	if(ll_is_empty(l)) return NULL;
	if(l->info == info){
		LinkedList *temp = NULL;
		if(!ll_is_empty(l->prox)) temp = l->prox;
		free(l);
		l = NULL;
		return temp;
	}
	l->prox = ll_remove(l->prox, info);
	return l;	
}

// Deleta todos os elementos da lista
// Entrada: lista
// Retorno: nenhum
// Pré-condições: nenhuma
// Pós-condições: elementos da lista desalocados e desencadeados
void ll_delete(LinkedList *l){
	if(l == NULL) return;
	LinkedList *next = l->prox;
	free(l->info);
	l->info = NULL;
	free(l);
	l = NULL;
	ll_delete(next);
}