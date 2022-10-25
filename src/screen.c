#include <stdio.h>

void print_menu(){
	printf("----------------- MENU PRINCIPAL  -----------------\n");
	printf("\n");
	printf("1 - Menu sanduiche\n");
	printf("2 - Menu bebida\n");
	printf("3 - Menu sobremesa\n");
	printf("4 - Menu extra\n");
	printf("5 - Menu pedido\n");
	printf("6 - Carregar de arquivo\n");
}


void print_drink_menu(){
	printf("----------------- BEBIDAS -----------------\n");
	printf("\n");
	printf("1 - Cadastrar bebida\n");
	printf("2 - Imprimir bebidas\n");
}

void print_sandwich_menu(){
	printf("----------------- SANDUICHES -----------------\n");
	printf("\n");
	printf("1 - Cadastrar sanduiche\n");
	printf("2 - Imprimir sanduiches\n");
}

void print_dessert_menu(){
	printf("----------------- SOBREMESA -----------------\n");
	printf("\n");
	printf("1 - Cadastrar sobremesa\n");
	printf("2 - Imprimir sobremesas\n");
}

void print_extra_menu(){
	printf("----------------- EXTRA -----------------\n");
	printf("\n");
	printf("1 - Cadastrar extra\n");
	printf("2 - Imprimir extras\n");
}

void print_order_menu(){
	printf("---------------- PEDIDO ----------------\n");
	printf("\n");
	printf("1 - Novo pedido\n");
	printf("2 - Buscar pedido\n");
	printf("3 - Imprimir pedidos atendidos\n");
}