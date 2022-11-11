#include <string.h>

#include "util.h"

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