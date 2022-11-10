
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "header.h"
#include "debug.h"

void create_header(FILE* database){
	Header *header = malloc(sizeof(Header));
	header->pos_top = 0;
	header->pos_head = EMPTY;
	header->pos_free = EMPTY;
	assert(fwrite(header, sizeof(Header), 1, database));
	free(header);
	#ifdef __DEBUG
		printf("DEBUG: Header written\n");
	#endif
}

Header *read_header(FILE *database){
	Header *header = malloc(sizeof(Header));
	fseek(database, 0, SEEK_SET);
	fread(header, sizeof(Header), 1, database);
	assert(header);
	#ifdef __DEBUG
		printf("DEBUG: read_head -> top = %d, head = %d, free = %d\n", header->pos_top, header->pos_head, header->pos_free);
	#endif
	return header;
}
