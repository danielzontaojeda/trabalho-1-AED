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

// Retorna string com tamanho do item escrito por extenso
// Entrada: enum representando tamanho do pedido
// Retorno: String com tamanho do item escrito por extenso
// Pré-condições: size e um valor valido de enum size
// Pós-condições: string retornada
static char *get_size_str(enum size size){
	if(size == small) return "pequeno";
	if(size == medium) return "medio";
	if(size == large) return "grande";
	return "";
}

// Escreve em stdout as informacoes de um item de pedido
// Entrada: Estrutura de item de pedido
// Retorno: Nenhum
// Pré-condições: Arquivo de itens de pedido existe
// Pós-condições: Informacoes do item do pedido impressas em stdout
void print_item_order(Order_items *item){
	Product *product = find_product(item->type, item->id_product);
	if(product != NULL){
		printf("tipo: %-9s\t ",get_product_type_name(item->type));
		printf("id: %-3u\t ",item->id_product);
		printf("quantidade: %3u\t ",item->quantity);
		printf("nome: %s ",product->name);
		if(!strcmp(item->type, "SD") || !strcmp(item->type, "BB"))
			printf("tamanho: %s", get_size_str(item->size));
		printf("\n");
	}else{
		printf("Produto de id %d nao encontrado.\n",item->id_product);
	}
}

// Recebe char representando tamanho e retorna enum representando tamanho
// Entrada: char p, m ou g maiusculos ou minusculos
// Retorno: enum size de tamanho do item
// Pré-condições: size_str deve ser um caractere valido de tamanho de item
// Pós-condições: Valor de enum size retornado
static enum size set_item_size(char size_str){
	if(size_str == 'p' || size_str == 'P') return small;
	if(size_str == 'm' || size_str == 'M') return medium;
	if(size_str == 'g' || size_str == 'G') return large;
	printf("size_str in set_item_size not recognized");
	exit(1);
	return -1;
}

// Recebe uma string do tipo (tipo, id, quantidade, tamanho?) e insere estas
// informacoes em uma lista encadeada dentro da estrutura Order
// Entrada: Estrutura de pedido e string com item do pedido
// Retorno: Nenhum
// Pré-condições: String de item de pedido deve ter valores validos
// Pós-condições: Estrutura encadeada de Order_items inserida em order
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

// Imprime em stdout as informacoes de um pedido, incluindo seus itens
// Entrada: Estrutura de pedido
// Retorno: Nenhum
// Pré-condições: Estrutura de pedido valida
// Pós-condições: Informacoes de pedido impressas em stdout
void print_order(Order *order){
	print_separator();
	printf("tipo: %s\n",order->type);
	printf("id: %u\n",order->id);
	printf("cpf: %s\n",order->cpf);
	printf("next: %d\n",order->next);
	printf("pedido: \n");
	LinkedList *actual = order->list_products;
	while(actual != NULL){
		Order_items *item = actual->info;
		print_item_order(item);
		actual = actual->prox;
	}
	print_separator();
}


// Recebe lista encadeada com strings como informacao. As strings tem formato do tipo:
// PD;1;11111111111;(SD,1,2,M);(SD,2,1,P);(BB,2,3,M);(EX,3,4);(SM,2,2)
// estas informacoes sao separadas, estruturas de Order sao criadas e uma lista encadeada
// destas estruturas e retornada
// Entrada: Lista encadeada com string como informacao
// Retorno: Lista encadeada com estruturas de pedido
// Pré-condições: commands deve ter formato valido
// Pós-condições: Lista encadeada alocada dinamicamente, e cada lista tem uma estrutura Order tambem alocada dinamicamente
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

// Executa fluxo de programa para pegar as informacoes de um pedido por stdin
// Entrada: Nenhuma
// Retorno: Estrutura de pedido
// Pré-condições: cpf digitado deve ter 11 digitos, item do pedido digitado deve ter formato correto
// Pós-condições: Estrutura de pedido alocada dinamicamente e retornada
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

// Cria lista encadeada de itens de um pedido
// Entrada: Ponteiro para arquivo de itens de pedido e posicao da cabeca da lista de itens
// Retorno: Lista encadeada com estruturas de Order_items
// Pré-condições: deve existir item do pedido na posicao head
// Pós-condições: Lista encadeada e estruturas de Order_item alocadas dinamicamente
static LinkedList *get_item_list_from_file(FILE *database, int head){
	int item_pos = head;
	LinkedList *list_items = NULL;
	while(item_pos != EMPTY){
		Order_items *item = calloc(1, sizeof(Order_items));
		fseek(database, sizeof(Header) + item_pos*sizeof(Order_items), SEEK_SET);
		fread(item, sizeof(Order_items), 1, database);
		list_items = ll_insert(list_items, item);
		item_pos = item->next;
	}
	return list_items;
}

// Converte uma estrutura Order_file para Order
// Entrada: Estrutura de Order_file
// Retorno: Estrutura Order
// Pré-condições: Nenhuma
// Pós-condições: Estrutura Order alocada dinamicamente
static Order *convert_order(Order_file *order_file){
	if(order_file == NULL) return NULL;
	FILE *database_items = get_database(DATABASE_ITEM_PD);
	Order *order = calloc(1, sizeof(Order));
	order->id = order_file->id;
	strcpy(order->type, order_file->type);
	strcpy(order->cpf, order_file->cpf);
	order->price_total =  order_file->price_total;
	order->list_products = get_item_list_from_file(database_items, order_file->head_item);
	order->next = order_file->next;
	fclose(database_items);
	return order;
}

// Retorna estrutura de Order com id passado por parametro. Retorna NULL caso nao encontre
// Entrada: id do pedido
// Retorno: Estrtura de pedido
// Pré-condições: Nenhuma
// Pós-condições: Estrutura Order alocada dinamicamente
Order *find_order(unsigned id){
	FILE *database = get_database(DATABASE_PD);
	Header_queue *header = read_header_queue(database);
	Order_file *order_file = seek_order(database, header->pos_head);
	Order *order = convert_order(order_file);
	int next;
	while(order_file->next != EMPTY){
		if(order->id == id){
			free(header);
			fclose(database);
			free(order_file);
			return order;
		}
		next = order_file->next;
		free(order);
		free(order_file);
		order_file = seek_order(database, next);
		order = convert_order(order_file);
	}
	if(order->id == id){
		free(header);
		fclose(database);
		free(order_file);
		return order;
	}
	free(header);
	free(order_file);
	free(order);
	fclose(database);
	return NULL;
}

static void add_empty_position_to_header(FILE *database, Header_queue *header, int pos){
	if(header->pos_free == EMPTY){
		header->pos_free = pos;
		fseek(database, 0, SEEK_SET);
		fwrite(header, sizeof(Header), 1, database);
	}else{
		Order_file *order = seek_order(database, header->pos_free);
		int next = order->next;
		printf("pos %d\n",pos);
		printf("next %d\n",next);
		while(next != EMPTY){
			free(order);
			order = seek_order(database, next);
			next = order->next;
		}
		order->next = pos;
		fseek(database, sizeof(Header) + next*sizeof(Order_file), SEEK_SET);
		fwrite(order, sizeof(Order_file), 1, database);
		free(order);
	}
}


static void delete_order_position(FILE *database, int pos){
	Header_queue *header = read_header_queue(database);
	int actual;
	if(header->pos_head == pos){
		// caso item seja primeiro da lista
		Order_file *order = seek_order(database, header->pos_head);
		int next = order->next;
		actual = header->pos_head;
		header->pos_head = next;
		// atualiza cabeca da fila
		fseek(database, 0, SEEK_SET);
		fwrite(header, sizeof(Header_queue), 1, database);
		order->next = EMPTY;
		// proximo do pedido deletado para -1
		fseek(database, sizeof(Header) + actual*sizeof(Order_file), SEEK_SET);
		fwrite(order, sizeof(Order_file), 1, database);
		free(order);
		order = seek_order(database, header->pos_head);
		order->next = EMPTY;
		// cabeca da fila aponta para -1
		fseek(database, sizeof(Header_queue) + actual*sizeof(Order_file), SEEK_SET);
		fwrite(order, sizeof(Order_file), 1, database);
		free(order);
		add_empty_position_to_header(database, header, actual);
	}else{
		Order_file *order = seek_order(database, header->pos_tail);
		while(order->next != pos){
			actual = order->next;
			free(order);
			order = seek_order(database, actual);
		}
		int next = order->next;
		free(order);
		order = seek_order(database, next);
		next = order->next;
		free(order);
		if(next != EMPTY){
			// caso item nao seja ultimo da lista
			order = seek_order(database, next);
			order->next = actual;
			fseek(database, sizeof(Header_queue) + next*sizeof(Order_file), SEEK_SET);
			fwrite(order, sizeof(Order_file), 1, database);
			free(order);
		}else{
			// caso item a deletar seja ultimo da lista
			order = seek_order(database, actual);
			order->next = EMPTY;
			fseek(database, sizeof(Header_queue) + next*sizeof(Order_file), SEEK_SET);
			fwrite(order, sizeof(Order_file), 1, database);
			free(order);
		}
		order = seek_order(database, actual);
		next = order->next;
		free(order);
		order = seek_order(database, next);
		order->next = EMPTY;
		add_empty_position_to_header(database, header, next);
	}
	free(header);
}

static int remove_next_order(){
	FILE *database = get_database(DATABASE_PD);
	Header_queue *header = read_header_queue(database);
	int pos = header->pos_head;
	free(header);
	Order_file *order_file = seek_order(database, pos);
	Order *order = convert_order(order_file);
	delete_order_position(database, pos);
	printf("Pedido atendido: \n");
	print_order(order);
	free(order);
	free(order_file);
	fclose(database);
	return pos;
}

void print_order_queue(){
	FILE *database = get_database(DATABASE_PD);
	Header_queue *header = read_header_queue(database);
	Order_file *order_file = seek_order(database, header->pos_head);
	Order *order = convert_order(order_file);
	if(order == NULL) printf("Nao ha pedidos na fila.\n");
	while(order->next != EMPTY){
		print_order(order);
		int next = order_file->next;
		free(order_file);
		free(order);
		order_file = seek_order(database, next);
		order = convert_order(order_file);
	}
	print_order(order);
	free(order_file);
	free(order);
}

// Processa a escolha do usuario no menu de pedidos
// Entrada: enum com escolha do usuario
// Retorno: Nenhum
// Pré-condições: escolha do usuario corresponde a um valor de enum
// Pós-condições: Fluxo de programa para a escolha do usuario executada
void process_submenu_order(enum choice_order choice){
	Order *order;
	switch (choice){
	case create_enum:
		;
		order = get_order_from_keyboard();
		FILE *database_order = get_database(DATABASE_PD);
		FILE *database_item_order = get_database(DATABASE_ITEM_PD);
		create_header_queue(database_order);
		create_header(database_item_order);
		write_order_to_file(database_order, database_item_order, order);
		clear_screen();
		printf("Novo pedido adicionado: \n");
		print_order(order);
		fclose(database_order);
		fclose(database_item_order);
		free(order);
		press_enter_to_continue();
		break;
	case search_order:
		;
		unsigned id;
		printf("Digite o id do pedido.\n");
		scanf("%u%*c",&id);
		clear_screen();
		order = find_order(id);
		if(order) print_order(order);
		else{
			printf("Pedido nao encontrado.\n");
			press_enter_to_continue();
			break;
		}
		ll_delete(order->list_products);
		free(order);
		press_enter_to_continue();
		break;
	case print_fulfilled:
		break;
	case fulfill_next:
		remove_next_order();
		press_enter_to_continue();
		break;
	case print_queue:
		print_order_queue();
		press_enter_to_continue();
	default:
		break;
	}
}