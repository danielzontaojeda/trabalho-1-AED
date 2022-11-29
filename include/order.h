#ifndef __ORDER_H
#define __ORDER_H

#include "linked_list.h"
#include "product.h"

// enum de escolhas do usuario
enum choice_order {exit_order, create_enum, search_order, 
		print_fulfilled, fulfill_next, print_queue, drop};

// estrutura de no de arquivo para itens de um pedido
typedef struct {
	char type[3];				// tipo do item
	unsigned id_product;		// id do item
	unsigned quantity;			// quantidade de itens no pedido
	enum size size;				// tamanho do item quando relevante
	int next;					// posicao do proximo item do pedido, -1 caso seja ultimo
} Order_items;

// estrutura de no de arquivo para pedidos
typedef struct{
	unsigned id;				// id do pedido
	char type[3];				// tipo (PD)
	char cpf[12];				// cpf do cliente realizando pedido
	int head_item;				// posicao da cabeca de lista encadeada de itens de pedido
	int next;					// posicao do proximo pedido
	double price_total;			// preco total do pedido
} Order_file;

// estrutura de no de memoria para pedido
typedef struct order{
	unsigned id;				// id do pedido
	char type[3];				// tipo (PD)
	char cpf[12];				// cpf do cliente realizando pedido
	LinkedList* list_products;	// lista encadeada de itens do pedido
	int next;					// posicao do proximo pedido em arquivo binario
	double price_total;			// preco total do pedido
} Order;

// Recebe lista encadeada com strings como informacao. As strings tem formato do tipo:
// PD;1;11111111111;(SD,1,2,M);(SD,2,1,P);(BB,2,3,M);(EX,3,4);(SM,2,2)
// estas informacoes sao separadas, estruturas de Order sao criadas e uma lista encadeada
// destas estruturas e retornada
// Entrada: Lista encadeada com string como informacao
// Retorno: Lista encadeada com estruturas de pedido
// Pré-condições: commands deve ter formato valido
// Pós-condições: Lista encadeada alocada dinamicamente, e cada lista tem uma estrutura Order tambem alocada dinamicamente
LinkedList *create_order_from_file(LinkedList *commands);

// Imprime em stdout as informacoes de um pedido, incluindo seus itens
// Entrada: Estrutura de pedido
// Retorno: Nenhum
// Pré-condições: Estrutura de pedido valida
// Pós-condições: Informacoes de pedido impressas em stdout
void print_order(Order *order);

// Deleta todos os pedidos do cliente da fila de pedidos
// Entrada: cpf do cliente
// Retorno: Nenhum
// Pré-condições: Nenhum
// Pós-condições: Todos os pedidos do cliente marcados como deletados
static void drop_order(char *cpf);

// Imprime em stdout todos os pedidos ainda nao atendidos em ordem de chegada
// Entrada: Nenhuma
// Retorno: Nenhum
// Pré-condições: Nenhum
// Pós-condições: Todos os pedidos ainda nao atendidos impressos em stdout
void print_order_queue();

// Converte uma estrutura Order_file para Order
// Entrada: Estrutura de Order_file
// Retorno: Estrutura Order
// Pré-condições: Nenhuma
// Pós-condições: Estrutura Order alocada dinamicamente
Order *convert_order(Order_file *order_file);

// Cria lista encadeada de itens de um pedido
// Entrada: Ponteiro para arquivo de itens de pedido e posicao da cabeca da lista de itens
// Retorno: Lista encadeada com estruturas de Order_items
// Pré-condições: deve existir item do pedido na posicao head
// Pós-condições: Lista encadeada e estruturas de Order_item alocadas dinamicamente
LinkedList *get_item_list_from_file(FILE *database, int head);

// Escreve em stdout as informacoes de um item de pedido
// Entrada: Estrutura de item de pedido
// Retorno: Nenhum
// Pré-condições: Arquivo de itens de pedido existe
// Pós-condições: Informacoes do item do pedido impressas em stdout
void print_item_order(Order_items *item);

// Processa a escolha do usuario no menu de pedidos
// Entrada: enum com escolha do usuario
// Retorno: Nenhum
// Pré-condições: escolha do usuario corresponde a um valor de enum
// Pós-condições: Fluxo de programa para a escolha do usuario executada
void process_submenu_order(enum choice_order choice);

// Retorna estrutura de Order com id passado por parametro. Retorna NULL caso nao encontre
// Entrada: id do pedido
// Retorno: Estrtura de pedido
// Pré-condições: Nenhuma
// Pós-condições: Estrutura Order alocada dinamicamente
Order *find_order(unsigned id);

#endif
