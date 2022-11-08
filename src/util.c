#include <string.h>

#include "util.h"

void replace_char(char *string, char oldchar, char newchar){
	char *position = strchr(string, oldchar);
	if(position != NULL)
		 *position = newchar;
}

void remove_new_line(char *string){
	string[strcspn(string, "\n")] = 0;
}