#ifndef __PRODUCT_H
#define __PRODUCT_H

#include "linked_list.h"

// tamanho maximo do campo name
#define SIZE_NAME 51
// tamanho maximo do campo description
#define SIZE_DESCRIPTION 201
// tamanho maximo que uma linha de comandos do arquivo texto
#define SIZE_LINE (SIZE_NAME + SIZE_DESCRIPTION + 100)

// significado das escolhas recebidas
enum choice_enum {back, create, print};

// estrutura de no para os produtos
typedef struct product{
	char type[3]; 						// tipo do produto (SD, BB, EX, SM ou PD)
	int id;								// id no produto no arquivo
	char name[SIZE_NAME];				// nome do produto
	char description[SIZE_DESCRIPTION];	// descricao do produto apenas para sanduiches
	int is_available;					// 1 = disponivel, 0 = nao disponivel
	double price[3];					// preco[0] = pequeno, preco[1] = medio, preco[2] = grande
										// preco de produtos sem tamanho vao em preco[0]
	int next;							// posicao do proximo no no arquivo
} Product;

// Imprime em stdout as informacoes de product
// Entrada: ponteiro para estrutura de produto
// Retorno: nenhum
// Pré-condições: nenhuma
// Pós-condições: informacoes do produto impressas em stdout
void print_product(Product *product);

// Chama o fluxo necessario para criar o produto a partir do terminal
// Entrada: tipo do produto a ser criado
// Retorno: estrutura de produto 
// Pré-condições: tipo do produto valido
// Pós-condições: estrutura de produto retornada
Product *get_product_keyboard(const char *type);

// Executa o fluxo do programa correto para a escolha realizada
// Entrada: escolha selecionada e tipo do produto
// Retorno: nenhum
// Pré-condições: escolha valida de acordo com enum choices
// Pós-condições: nenhum
void process_submenu_choice(int choice, char *type);

// Cria entidade produto
// Entrada: tipo do produto e seus valores
// Retorno: entidade produto
// Pré-condições: tipo do produto valido
// Pós-condições: produto retornado
Product *create_product(const char *type, int id, char *name,
	char *description, int is_available, double *price);

// Cria lista encadeada com produtos utilizando comandos de list_commands
// Entrada: lista encadeada contendo os comandos do arquivo de entrada
// Retorno: lista encadeada contendo produtos
// Pré-condições: lista de comandos nao nula com formato valido
// Pós-condições: lista encadeada contendo produtos retornada
LinkedList *create_product_from_file(LinkedList *list_commands);

// Retorna 1 caso type seja um tipo de produto
// caso contrario retorna 0
// Entrada: tipo do produto
// Retorno: 1 ou 0
// Pré-condições: nenhuma
// Pós-condições: 1 ou 0 retornado
int is_type_of_product(const char *type);

// Retorna nome inteiro do tipo do produto
// Entrada: tipo do produto
// Retorno: string com o nome inteiro do tipo do produto
// Pré-condições: type e um tipo valido de produto
// Pós-condições: nome inteiro do tipo do produto retornado
char *get_product_type_name(const char *type);

#endif