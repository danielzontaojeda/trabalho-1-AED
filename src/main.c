#include <stdio.h>

#include "input_file.h"
#include "linked_list.h"
#include "screen.h"
#include "product.h"
#include "binary_file.h"

enum choices {sandwich = 1, drink, dessert, extra, order, load_file};

LinkedList *load_from_file(char *filename){
	LinkedList *commands_from_file = NULL;
	commands_from_file = read_file(filename);
	return commands_from_file;
}

void clear_linked_list(LinkedList *ll){
	ll_delete(ll);
	ll = NULL;
}

void process_choice(int choice){
	int submenu_choice;
	switch (choice){
	case sandwich:
		print_sandwich_menu();
		scanf("%d%*c",&submenu_choice);
		process_submenu_choice(submenu_choice, "SD");
		break;
	case drink:
		print_drink_menu();
		scanf("%d%*c",&submenu_choice);
		process_submenu_choice(submenu_choice, "BB");
		break;
	case dessert:
		print_dessert_menu();
		scanf("%d%*c",&submenu_choice);
		process_submenu_choice(submenu_choice, "SM");
		break;
	case extra:
		print_extra_menu();
		scanf("%d%*c",&submenu_choice);
		process_submenu_choice(submenu_choice, "EX");
		break;
	case order:
		print_order_menu();
		scanf("%d%*c",&submenu_choice);
		break;
	case load_file:
		;
		LinkedList *commands = NULL;
		LinkedList *list_product = NULL;
		commands =  load_from_file("dados.txt");
		list_product = create_product_from_file(commands);
		write_product_list_to_file(list_product);
		break;
	}
}

int main(){
	int option;

	print_menu();
	scanf("%d", &option);
	process_choice(option);
	printf("DEBUG: terminou\n");
	return 0;
}