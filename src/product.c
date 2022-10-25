#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "util.h"

static void get_name(Product* product){
	printf("Digite o nome do produto.\n");
	fgets(product->name, sizeof(product->name), stdin);
	remove_new_line(product->name);
}

static void get_description(Product* product){
	if(strcmp(product->type, "SD") == 0){
		printf("Digite a descricao do produto.\n");
		fgets(product->description, sizeof(product->description), stdin);
		remove_new_line(product->description);
	}
}

static void get_availability(Product* product){
	printf("Produto disponivel? (1 = SIM, 0 = NAO)\n");
	scanf("%d%*c",&product->is_available);
}

static void get_price(Product* product){
	double price[2];
	char temp[200];
	char price_str[2][10];
	if(!strcmp(product->type, "SD") || !strcmp(product->type, "BB")){
		printf("Digite os precos para o produto pequeno, medio e grande.\n");
		fgets(temp, sizeof(temp), stdin);
		sscanf(temp, "%[^;];%[^;];%[^\n]%*c", price_str[0], price_str[1], price_str[2]);
		for(int i=0;i<3;i++){
			replace_char(price_str[i], ',', '.');
			price[i] = strtod(price_str[i], NULL);
			product->price[i] = price[i];
			printf("%lf\n",price[i]);
		}
	}else{
		printf("Digite o preco do produto.\n");
		fgets(temp, sizeof(temp), stdin);
		replace_char(temp, ',', '.');
		price[0] = strtod(temp, NULL);
		product->price[0] = price[0];
	}
}

void print_product(Product* product){
	printf("-------------------------------------------\n");
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

Product* create_product(char* type){
	Product* product = malloc(sizeof(Product));
	strcpy(product->type, type);
	get_name(product);
	get_description(product);
	get_availability(product);
	get_price(product);
	print_product(product);
	return product;
}

Product* create_product(char* name, char* description, 
						int availability, double price){
	Product* product = malloc(sizeof(Product));
	strcpy(product->type, type);
	get_name(product);
	get_description(product);
	get_availability(product);
	get_price(product);
	print_product(product);
	return product;
}


void process_submenu_choice(int choice, char* type){
	if(choice == create){
		Product* product = create_product(type);
		//TODO: gravar em arquivo
	}
	//TODO: imprimir todos
}