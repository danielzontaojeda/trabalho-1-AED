
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "input_file.h"

#define SIZE_LINE sizeof(char)*500

LinkedList *read_file(char *filename){
	FILE *file = fopen(filename, "r");
	assert(file != NULL);

	char *line = malloc(SIZE_LINE);
	LinkedList *commands_from_file = NULL;

	while(fgets(line, SIZE_LINE, file) != NULL){
		commands_from_file = ll_insert(commands_from_file, line);
		line = malloc(SIZE_LINE);
	}
	fclose(file);
	#ifdef __DEBUG
		printf("DEBUG: Read %d lines from file %s\n", ll_length(commands_from_file), filename);
	#endif
	return commands_from_file;
}