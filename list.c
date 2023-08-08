#include "list.h"

int test(){
	return 1;
}

//this func changes each time nodeCOntent definition changes
void printContent(nodeContent c){
	printf("\n[x]: %d [y]: %d", c.x, c.y);
}

list createList(nodeContent val){
	//faltan errores
	list lst;
	if(NULL == (lst = malloc(sizeof(listRoot)))){
		perror("error on malloc");
		return 0;
	}

	//lst->content = val;
	//printf("%d",lst->content);
	lst->next = NULL;
	lst->last = NULL;
	lst->length = 1;

	return lst;
}

//if length == 0 falta
int pushToList(nodeContent val, list list){
	node * temp;
	node * lastNode;

	if(NULL == (temp = malloc(sizeof(node)))){
		perror("error on malloc");
		return 0;
	}

	if(list == NULL){
		fprintf(stderr, "pushToList: list is null\n");
		return 0;
	}

	temp->content = val;
	temp->next = NULL;

	if(list->length == 1){
		list->last = temp;
		list->next = temp;
	}else if(list->length > 1){
		lastNode = list->last;
		lastNode->next = temp;
		list->last = temp;
	}

	list->length++;
	return 1;
}


nodeContent getFromList(list list){
	node * temp;
	nodeContent result;

	if(list->length <= 0){
		exit -1;
	}else if(list->length > 1){
		temp = list->next;
		//result = list->content;
		result = temp->content;

		list->next = temp->next;
		//list->content = temp->content;
		list->length --;
		return result;
	}
}



void printList(list list){
	node * temp = list->next;
	//printf("[ %d",list->content);
	//printContent(list->content);

	while(temp != NULL){
		//printf(", %d",temp->content);
		printContent(temp->content);
		temp = temp->next;
	}
	printf("\n");
}


int freeList(list lst){
	node * temp = lst->next;
	node * delete;	

	if(lst == NULL){
		perror("freeList: list is alredy empty");
		return 0;
	}


	if(lst->length > 1){
		while(temp->next != NULL){
			delete = temp;
			temp = temp->next;
			free(delete);
		}
	}

	free(lst);

	return 1;
}
