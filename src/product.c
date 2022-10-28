#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "product.h"
#include "util.h"

static int get_id(){
	// TODO: validade id
	int id = 0;
	printf("Digite o id do produto.\n");
	scanf("%d%*c",&id);
	return id;
}

static char* get_name(){
	char* name = malloc(SIZE_NAME);
	printf("Digite o nome do produto.\n");
	fgets(name, SIZE_NAME, stdin);
	remove_new_line(name);
	return name;
}

static char* get_description(const char* type){
	char* description = malloc(SIZE_DESCRIPTION);
	if(strcmp(type, "SD") == 0){
		printf("Digite a descricao do produto.\n");
		fflush(stdin);
		fgets(description, SIZE_DESCRIPTION, stdin);
		remove_new_line(description);
	}
	return description;
}

static int get_availability(){
	int is_available;
	printf("Produto disponivel? (1 = SIM, 0 = NAO)\n");
	scanf("%d%*c",&is_available);
	return is_available;
}

static double* get_price_from_str(const char* type, char* price_str){
	char price_split[2][10];
	double* price = malloc(sizeof(double)*2);
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

static double* get_price(const char* type){
	double* price;
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

void print_product(Product* product){
	printf("-------------------------------------------\n");
	printf("id: %d\n",product->id);
	printf("type: %s\n", product->type);
	printf("name: %s\n", product->name);
	if(strcmp(product->type, "SD") == 0)
		printf("description: %s\n", product->description);
	printf("is_available: %d\n", product->is_available);
	if(!strcmp(product->type, "SD") || !strcmp(product->type, "BB")){
		printf("price: ");
		for(int i=0;i<3;i++)
			printf("%.2lf ", product->price[i]);
		printf("\n");
	}else{
		printf("price: %.2lf\n", product->price[0]);
	}
	printf("-------------------------------------------\n");
}

Product* get_product_keyboard(const char* type){
	assert(!(strcmp(type, "SD") && strcmp(type, "BB") &&
		strcmp(type, "SM") && strcmp(type, "EX")));
	int id = get_id();
	char* name = get_name();
	char* description = get_description(type);
	int is_available = get_availability();
	double* price = get_price(type);
	Product* product = create_product(type, id, name, description, is_available, price);	
	free(name);
	free(description); 
	free(price);
	print_product(product);
	return product;
}

Product* create_product(const char* type, int id, char* name, char* description, 
						int is_available, double* price){
	assert(!(strcmp(type, "SD") && strcmp(type, "BB") &&
		strcmp(type, "SM") && strcmp(type, "EX")));
	Product* product = malloc(sizeof(Product));
	product->id = id;
	strcpy(product->type, type);
	strcpy(product->name, name);
	strcpy(product->description, description);
	product->is_available = is_available;
	if(!strcmp(type, "SD") || !strcmp(type, "BB")){
		for(int i=0; i<3; i++)
			product->price[i] = price[i];
	}else
		product->price[0] = price[0];
	return product;
}

LinkedList* create_product_from_file(LinkedList* ll){
	assert(ll);
	LinkedList* list_commands = ll;
	LinkedList* list_products = NULL;
	while(list_commands != NULL){
		char type[3];
		Product* product = NULL;
		sscanf(list_commands->info, "%[^;]", type);
		if(!strcmp(type, "SD") || !strcmp(type, "BB") ||
			!strcmp(type, "SM") || !strcmp(type, "EX")){
				int id;
				char name[SIZE_NAME], description[SIZE_DESCRIPTION], price_str[SIZE_LINE];
				char is_available;
				double* price;
				if(!strcmp(type, "SD"))
					sscanf(list_commands->info, "%[^;];%d;%[^;];%[^;];%c;%[^\n]%*c",
						type, &id, name, description, &is_available, price_str);
				else
					sscanf(list_commands->info, "%[^;];%d;%[^;];%c;%[^\n]%*c",
						type, &id, name,  &is_available, price_str);
				is_available = is_available == 'D';
				price = get_price_from_str(type, price_str);
				product = create_product(type, id, name, description, is_available, price);
				print_product(product);
				list_products = ll_insert(list_products, product);
				free(price);
				list_commands = list_commands->prox;
			}
		else
			list_commands = list_commands->prox;
	}
	return list_products;
}

void process_submenu_choice(int choice, char* type){
	if(choice == create){
		Product* product = get_product_keyboard(type);
		//TODO: gravar em arquivo
	}
	//TODO: imprimir todos
}