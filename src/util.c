#include <string.h>

#include "util.h"
#include "ctype.h"

// Substitui primeira ocorrencia de oldchar por newchar
// Entrada: string a ser alterada, oldchar e newchar
// Retorno: nenhum
// Pré-condições: nenhum
// Pós-condições: primeira ocorrencia de oldchar substituido por newchar
void replace_char(char *string, char oldchar, char newchar){
	char *position = strchr(string, oldchar);
	if(position != NULL)
		 *position = newchar;
}

// Remove \n do fim da string
// Entrada: string com \n
// Retorno: nenhum
// Pré-condições: string com \n no final
// Pós-condições: \n removido do final da string
void remove_new_line(char *string){
	string[strcspn(string, "\n")] = 0;
}

void remove_whitespace(char *dest, char *src){
	int j = 0;
	for(int i=0;src[i] != '\0';i++){
		if(!isspace(src[i])){
			dest[j] = src[i];
			j++;
		}
	}
	dest[j] = '\0';
}