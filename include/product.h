#ifndef __PRODUCT_H
#define __PRODUCT_H

#include "linked_list.h"

// tamanho maximo do campo name
#define SIZE_NAME sizeof(char)*50
// tamanho maximo do campo description
#define SIZE_DESCRIPTION sizeof(char)*200
// tamanho maximo que uma linha de comandos do arquivo texto
#define SIZE_LINE (int)(SIZE_NAME + SIZE_DESCRIPTION + 100)

// significado das escolhas recebidas
enum choice_enum {create = 1, print};

// estrutura de no para os produtos
typedef struct product{
	char type[2]; 						// tipo do produto (SD, BB, EX, SM ou PD)
	int id;								// id no produto no arquivo
	char name[SIZE_NAME];				// nome do produto
	char description[SIZE_DESCRIPTION];	// descricao do produto apenas para sanduiches
	int is_available;					// 1 = disponivel, 0 = nao disponivel
	double price[2];					// preco[0] = pequeno, preco[1] = medio, preco[2] = grande
										// preco de produtos sem tamanho vao em preco[0]
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
Product* get_product_keyboard(const char* type);

// Executa o fluxo do programa correto para a escolha realizada
// Entrada: escolha selecionada e tipo do produto
// Retorno: nenhum
// Pré-condições: escolha valida de acordo com enum choices
// Pós-condições: nenhum
void process_submenu_choice(int choice, char* type);

// Cria entidade produto
// Entrada: tipo do produto e seus valores
// Retorno: entidade produto
// Pré-condições: tipo do produto valido
// Pós-condições: produto retornado
Product* create_product(const char* type, int id, char* name,
	char* description, int is_available, double* price);


// Cria lista encadeada com produtos utilizando comandos de list_commands
// Entrada: lista encadeada contendo os comandos do arquivo de entrada
// Retorno: lista encadeada contendo produtos
// Pré-condições: lista de comandos nao nula com formato valido
// Pós-condições: lista encadeada contendo produtos retornada
LinkedList* create_product_from_file(LinkedList* list_commands);

#endif