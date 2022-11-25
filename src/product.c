#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "product.h"
#include "util.h"
#include "binary_file.h"
#include "screen.h"
#include "header.h"

// Pega valor do id do produto de stdin
// Entrada: Nenhuma
// Retorno: id do produto
// Pré-condições: nenhuma
// Pós-condições: id retornado
static int get_id(){
	int id = 0;
	printf("Digite o id do produto.\n");
	scanf("%d%*c",&id);
	return id;
}

// Pega nome do produto de stdin. E necessario desalocar o retorno.
// Entrada: nenhuma
// Retorno: nome do produto em vetor dinamicamente alocado
// Pré-condições: nenhuma
// Pós-condições: nome retornado
static char *get_name(){
	char *name = malloc(SIZE_NAME);
	printf("Digite o nome do produto.\n");
	fgets(name, SIZE_NAME, stdin);
	remove_new_line(name);
	return name;
}

// Pega descricao do produto de stdin. E necessario desalocar o retorno.
// Entrada: nenhuma
// Retorno: descricao do produto em vetor dinamicamente alocado
// Pré-condições: nenhuma
// Pós-condições: descricao retornado
static char *get_description(const char *type){
	char *description = malloc(SIZE_DESCRIPTION);
	if(strcmp(type, "SD") == 0){
		printf("Digite a descricao do produto.\n");
		fgets(description, SIZE_DESCRIPTION, stdin);
		remove_new_line(description);
	}
	return description;
}

// Verifica com o usuario se o produto esta disponivel
// Entrada: Nenhuma
// Retorno: Valor 0 (nao disponivel) ou 1 (disponivel)
// Pré-condições: nenhuma
// Pós-condições: disponibilidade retornada
static unsigned get_availability(){
	unsigned is_available;
	printf("Produto disponivel? (1 = SIM, 0 = NAO)\n");
	scanf("%u%*c",&is_available);
	return is_available;
}

// Converte string em vetor de double representando preco
// Entrada: tipo do produto e string com seu(s) preco(s) separados por ;
// Retorno: vetor de double dinamicamente alocado
// Pré-condições: type e algum tipo de produto
//				  preco_str e um preco ou tres precos separados por ;
// Pós-condições: vetor de doubles com preco retornado
static double *get_price_from_str(const char *type, char *price_str){
	assert(is_type_of_product(type));
	char price_split[2][10];
	double *price = calloc(3,sizeof(double));
	if(!strcmp(type, "SD") || !strcmp(type, "BB")){
		sscanf(price_str, "%[^;];%[^;];%[^\n]%*c", price_split[0], price_split[1], price_split[2]);
		for(int i=0;i<3;i++){
			replace_char(price_split[i], ',', '.');
			price[i] = strtod(price_split[i], NULL);
		}
	}else{
		replace_char(price_str, ',', '.');
		price[0] = strtod(price_str, NULL);
	}
	return price;
}

// Pega o(s) valor(es) do(s) preco(s) de stdin
// Entrada: tipo do produto
// Retorno: vetor de double dinamicamente alocado
// Pré-condições: type e um tipo valido de produto
// Pós-condições: vetor com os precos retornado
static double *get_price(const char *type){
	assert(is_type_of_product(type));
	double *price;
	char temp[SIZE_LINE];
	if(!strcmp(type, "SD") || !strcmp(type, "BB")){
		printf("Digite os precos para o produto pequeno, medio e grande.\n");
		fgets(temp, sizeof(temp), stdin);
		price = get_price_from_str(type, temp);
	}else{
		printf("Digite o preco do produto.\n");
		fgets(temp, sizeof(temp), stdin);
		price = get_price_from_str(type, temp);
	}
	return price;
}

// Retorna nome inteiro do tipo do produto
// Entrada: tipo do produto
// Retorno: string com o nome inteiro do tipo do produto
// Pré-condições: type e um tipo valido de produto
// Pós-condições: nome inteiro do tipo do produto retornado
char *get_product_type_name(const char *type){
	assert(is_type_of_product(type));
	if(!strcmp(type,"SD")) return "sanduiche";
	if(!strcmp(type,"BB")) return "bebida";
	if(!strcmp(type,"EX")) return "extra";
	if(!strcmp(type,"SM")) return "sobremesa";
	return NULL;
}

// Imprime em stdout as informacoes de product
// Entrada: ponteiro para estrutura de produto
// Retorno: nenhum
// Pré-condições: nenhuma
// Pós-condições: informacoes do produto impressas em stdout
void print_product(Product *product){
	printf("-------------------------------------------\n");
	printf("id: %d\n",product->id);
	printf("tipo: %s\n", get_product_type_name(product->type));
	printf("nome: %s\n", product->name);
	if(strcmp(product->type, "SD") == 0)
		printf("description: %s\n", product->description);
	printf("disponivel: %s\n", (product->is_available?"sim":"nao"));
	if(!strcmp(product->type, "SD") || !strcmp(product->type, "BB")){
		printf("preco: ");
		for(int i=0;i<3;i++)
			printf("%.2lf ", product->price[i]);
		printf("\n");
	}else
		printf("preco: %.2lf\n", product->price[0]);
	#ifdef __DEBUG
		printf("next: %d\n",product->next);
	#endif
	printf("-------------------------------------------\n");
}

// Chama o fluxo necessario para criar o produto a partir do terminal
// Entrada: tipo do produto a ser criado
// Retorno: estrutura de produto 
// Pré-condições: tipo do produto valido
// Pós-condições: estrutura de produto retornada
Product *get_product_keyboard(const char *type){
	assert(!(strcmp(type, "SD") && strcmp(type, "BB") &&
		strcmp(type, "SM") && strcmp(type, "EX")));
	int id = get_id();
	char *name = get_name();
	char *description = get_description(type);
	unsigned is_available = get_availability();
	double *price = get_price(type);
	Product *product = create_product(type, id, name, description, is_available, price);	
	free(name);
	free(description); 
	free(price);
	return product;
}

// Cria entidade produto
// Entrada: tipo do produto e seus valores
// Retorno: entidade produto
// Pré-condições: tipo do produto valido
// Pós-condições: produto retornado
Product *create_product(const char *type, int id, char *name, char *description, 
						unsigned is_available, double *price){
	assert(!(strcmp(type, "SD") && strcmp(type, "BB") &&
		strcmp(type, "SM") && strcmp(type, "EX")));
	Product *product = NULL;
	product = calloc(1,sizeof(Product));
	product->id = id;
	strcpy(product->type, type);
	strcpy(product->name, name);
	if(!strcmp(type, "SD"))
		strcpy(product->description, description);
	product->is_available = is_available;
	for(int i=0; i<3; i++)
		product->price[i] = price[i];
	return product;
}

// Retorna 1 caso type seja um tipo de produto
// caso contrario retorna 0
// Entrada: tipo do produto
// Retorno: 1 ou 0
// Pré-condições: nenhuma
// Pós-condições: 1 ou 0 retornado
int is_type_of_product(const char *type){
	return(!strcmp(type, "SD") || !strcmp(type, "BB") ||
		!strcmp(type, "SM") || !strcmp(type, "EX"));
}

// Divide parametro de entrada string e coloca as informacoes nos ponteiros passados por parametro
// Entrada: string de entrada e informacoes da struct product
// Retorno: nenhum
// Pré-condições: string e uma string de entrada valida
// Pós-condições: todos os outros parametros recebem seus valores 
static void parse_product_from_string(char *string, char *type, int *id, char *name,
						char *description, char *is_available, char *price_str){
	if(!strcmp(type, "SD"))
		sscanf(string, "%[^;];%d;%[^;];%[^;];%c;%[^\n]%*c",
			type, id, name, description, is_available, price_str);
	else
		sscanf(string, "%[^;];%d;%[^;];%c;%[^\n]%*c",
			type, id, name,  is_available, price_str);
}

// Cria lista encadeada com produtos utilizando comandos de list_commands
// Entrada: lista encadeada contendo os comandos do arquivo de entrada
// Retorno: lista encadeada contendo produtos
// Pré-condições: lista de comandos nao nula com formato valido
// Pós-condições: lista encadeada contendo produtos retornada
LinkedList *create_product_from_file(LinkedList *ll){
	assert(ll);
	LinkedList *list_commands = ll;
	LinkedList *list_products = NULL;
	while(list_commands != NULL){
		char type[3];
		Product *product = NULL;
		sscanf(list_commands->info, "%[^;]", type);
		if(is_type_of_product(type)){ 
				int id;
				char name[SIZE_NAME], description[SIZE_DESCRIPTION], price_str[SIZE_LINE];
				char is_available;
				double *price;
				parse_product_from_string(list_commands->info, type, &id, name, description, &is_available, price_str);
				is_available = is_available == 'D';
				price = get_price_from_str(type, price_str);
				product = create_product(type, id, name, description, is_available, price);
				#ifdef __DEBUG
					print_product(product);
				#endif 
				list_products = ll_insert(list_products, product);
				free(price);
		}
		list_commands = list_commands->prox;
	}
	return list_products;
}

static FILE *get_database_product(char *type){
	FILE *database_product = NULL;
	if(!strcmp(type, "SD"))
		database_product = get_database(DATABASE_SD);	
	else if(!strcmp(type, "BB"))
		database_product = get_database(DATABASE_BB);
	else if(!strcmp(type, "EX"))
		database_product = get_database(DATABASE_EX);
	else if(!strcmp(type, "SM"))
		database_product = get_database(DATABASE_SM);
	return database_product;
}

// Executa o fluxo do programa correto para a escolha realizada
// Entrada: escolha selecionada e tipo do produto
// Retorno: nenhum
// Pré-condições: escolha valida de acordo com enum choices
// Pós-condições: nenhum
void process_submenu_choice(enum submenu_choice choice, char *type){
	if(choice == create){
		Product *product = NULL;
		FILE *database_product = get_database_product(type);
		product = get_product_keyboard(type);
		create_header(database_product);
		write_product_to_file(product, database_product);
		printf("Produto adicionado:\n");
		print_product(product);
		free(product);
		fclose(database_product);
		press_enter_to_continue();
	}else if(choice == print){
		if(is_type_of_product(type)){
			FILE *database_product = get_database_product(type);
			print_all_products_in_file(database_product);
			fclose(database_product);
			press_enter_to_continue();
		}
	}
}