#ifndef __PRODUCT_H
#define __PRODUCT_H

// #include "linked_list.h"

// significado das escolhas recebidas
enum choice_enum {create = 1, print};

// estrutura de no para os produtos
typedef struct product{
	char type[2]; 			// tipo do produto (SD, BB, EX, SM ou PD)
	int id;					// id no produto no arquivo
	char name[50];			// nome do produto
	char description[200];	// descricao do produto apenas para sanduiches
	int is_available;		// 1 = disponivel, 0 = nao disponivel
	double price[2];		// preco[0] = pequeno, preco[1] = medio, preco[2] = grande
							// preco de produtos sem tamanho vao em preco[0]
	int next;				// endereco no arquivo do proximo elemento da lista
							// -1 caso nao exista proximo
} Product;

// Imprime informacoes do produto na tela
// Entrada: estrutura de produto
// Retorno: nenhum
// Pré-condições: nenhum
// Pós-condições: informacoes impressas na tela
void print_product(Product* product);

// Chama o fluxo necessario para criar o produto a partir do terminal
// Entrada: tipo do produto a ser criado
// Retorno: estrutura de produto 
// Pré-condições: tipo do produto valido
// Pós-condições: estrutura de produto retornada
Product* create_product(char* type);

// Executa o fluxo do programa correto para a escolha realizada
// Entrada: escolha selecionada e tipo do produto
// Retorno: nenhum
// Pré-condições: escolha valida de acordo com enum choices
// Pós-condições: nenhum
void process_submenu_choice(int choice, char* type);

#endif