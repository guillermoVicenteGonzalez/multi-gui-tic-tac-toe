#include <stdlib.h>
#include <stdio.h>

typedef struct coords{
	int x;
	int y;
}coords;


typedef coords nodeContent;
//typedef int nodeContent;
//typedef nodeContent;
//typedef  coords nodeContent;

typedef struct node{
	nodeContent content;
	struct node * next;
}node;

typedef struct listRoot{
	struct node * next;
	struct node * last;
	int length;
}listRoot;

typedef listRoot* list;

list createList();
int pushToList(nodeContent val, list list);
void printList(list list);
nodeContent getFromList(list list);
int freeList(list list);
void printContent(nodeContent c);
