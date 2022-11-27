#include <stdio.h>
#include <stdlib.h>

void print_menu(){
	printf("----------------- MENU PRINCIPAL  -----------------\n");
	printf("\n");
	printf("1 - Menu sanduiche\n");
	printf("2 - Menu bebida\n");
	printf("3 - Menu sobremesa\n");
	printf("4 - Menu extra\n");
	printf("5 - Menu pedido\n");
	printf("6 - Carregar de arquivo\n");
	printf("0 - Sair\n");
}


void print_drink_menu(){
	printf("----------------- BEBIDAS -----------------\n");
	printf("\n");
	printf("1 - Cadastrar bebida\n");
	printf("2 - Imprimir bebidas\n");
	printf("0 - Voltar\n");
}

void print_sandwich_menu(){
	printf("----------------- SANDUICHES -----------------\n");
	printf("\n");
	printf("1 - Cadastrar sanduiche\n");
	printf("2 - Imprimir sanduiches\n");
	printf("0 - Voltar\n");
}

void print_dessert_menu(){
	printf("----------------- SOBREMESA -----------------\n");
	printf("\n");
	printf("1 - Cadastrar sobremesa\n");
	printf("2 - Imprimir sobremesas\n");
	printf("0 - Voltar\n");
}

void print_extra_menu(){
	printf("----------------- EXTRA -----------------\n");
	printf("\n");
	printf("1 - Cadastrar extra\n");
	printf("2 - Imprimir extras\n");
	printf("0 - Voltar\n");
}

void print_order_menu(){
	printf("---------------- PEDIDO ----------------\n");
	printf("\n");
	printf("1 - Novo pedido\n");
	printf("2 - Buscar pedido\n");
	printf("3 - Imprimir pedidos atendidos\n");
	printf("4 - Atender proximo pedido\n");
	printf("0 - Voltar\n");
}

void press_enter_to_continue(){
	printf("Digite ENTER para continuar\n");
	getchar();
}

void clear_screen(){
	#ifdef __linux__
		system("clear");
	#else
		system("cls");
	#endif
}

char *get_filename(){
	char *filename = malloc(sizeof(100));
	printf("Digite o nome do arquivo.\n");
	scanf("%[^\n]%*c",filename);
	return filename;
}

void print_separator(){
	for(int i=0;i<100;i++) printf("=");
	printf("\n");
}