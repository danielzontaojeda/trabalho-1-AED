#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"
#include "util.h"

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

static double* get_price(const char* type){
	double* price = malloc(sizeof(double)*2);
	char temp[200];
	char price_str[2][10];
	if(!strcmp(type, "SD") || !strcmp(type, "BB")){
		printf("Digite os precos para o produto pequeno, medio e grande.\n");
		fgets(temp, sizeof(temp), stdin);
		sscanf(temp, "%[^;];%[^;];%[^\n]%*c", price_str[0], price_str[1], price_str[2]);
		for(int i=0;i<3;i++){
			replace_char(price_str[i], ',', '.');
			price[i] = strtod(price_str[i], NULL);
		}
	}else{
		printf("Digite o preco do produto.\n");
		fgets(temp, sizeof(temp), stdin);
		replace_char(temp, ',', '.');
		price[0] = strtod(temp, NULL);
	}
	return price;
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

Product* get_product_keyboard(const char* type){
	char* name = get_name();
	char* description = get_description(type);
	int is_available = get_availability();
	double* price = get_price(type);
	Product* product = create_product(type, name, description, is_available, price);	
	free(name);
	free(description); 
	free(price);
	print_product(product);
	return product;
}

Product* create_product(char* type, char* name, char* description, 
						int is_available, double* price){
	Product* product = malloc(sizeof(Product));
	strcpy(product->type, type);
	strcpy(product->name, name);
	strcpy(product->description, description);
	product->is_available = is_available;
	if(!strcmp(type, "SD") || !strcmp(type, "BB")){
		for(int i=0; i<3; i++)
			product->price[i] = price[i];
	}else{
		product->price[0] = price[0];
	}
	return product;

}


void process_submenu_choice(int choice, char* type){
	if(choice == create){
		Product* product = get_product_keyboard(type);
		//TODO: gravar em arquivo
	}
	//TODO: imprimir todos
}