
#include "product.h"

typedef struct header{
	int head;
	int top;
	int empty;
} Header;

typedef struct node{
	void* info;
	int next;
} Node;