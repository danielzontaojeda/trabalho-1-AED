#ifndef __HEADER_H
#define __HEADER_H

#include <stdio.h>

#define EMPTY -1

typedef struct header{
	int pos_head;
	int pos_top;
	int pos_free;
} Header;

Header *read_header(FILE *database);

void create_header(FILE* database);

#endif