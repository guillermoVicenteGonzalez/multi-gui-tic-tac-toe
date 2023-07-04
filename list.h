#include <stdlib.h>
#include <stdio.h>
#include "TTTapi.h"

typedef int nodeContent;
//typedef nodeContent;

typedef struct node{
	nodeContent content;
	struct node * next;
}node;

typedef struct listRoot{
	nodeContent content;
	struct node * next;
	struct node * last;
	int length;
}listRoot;

typedef listRoot* list;

list createList(nodeContent val);
int pushToList(nodeContent val, list list);
void printList(list list);
nodeContent getFromList(list list);
int freeList(list list);
