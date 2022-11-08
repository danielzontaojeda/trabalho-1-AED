#ifndef __UTIL_H
#define __UTIL_H

// Substitui primeira ocorrencia de oldchar por newchar
// Entrada: string a ser alterada, oldchar e newchar
// Retorno: nenhum
// Pré-condições: nenhum
// Pós-condições: primeira ocorrencia de oldchar substituido por newchar
void replace_char(char *string, char oldchar, char newchar);

// Remove \n do fim da string
// Entrada: string com \n
// Retorno: nenhum
// Pré-condições: string com \n no final
// Pós-condições: \n removido do final da string
void remove_new_line(char *buffer);

#endif