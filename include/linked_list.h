#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#define TYPE_VAR char*

// estrutura de nó para lista encadeada
typedef struct no {
	void* info; 
	struct no *prox;
} LinkedList;

// Testa se uma lista é vazia
// Entrada: lista
// Retorno: 1 se a lista é vazia ou 0 caso contrário
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int ll_is_empty(LinkedList* l);

// Insere um elemento na lista
// Entrada: lista e elemento a ser inserido
// Retorno: lista alterada
// Pré-condição: nenhuma
// Pós-condição: elemento é inserido na lista
LinkedList* ll_insert(LinkedList* l, void* info);

// Remove um elemento da lista
// Entrada: lista e elemento a ser removido
// Retorno: lista alterada
// Pré-condição: nenhuma
// Pós-condição: elemento é removido da lista
LinkedList* ll_remove(LinkedList* l, void* info);

// Imprime os elementos da lista
// Entrada: lista
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: os elementos são impressos no console
void ll_print(LinkedList* l);

// Deleta todos os elementos da lista
// Entrada: lista
// Retorno: nenhum
// Pré-condições: nenhuma
// Pós-condições: elementos da lista desalocados e desencadeados
void ll_delete(LinkedList* l);

#endif