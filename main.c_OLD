#include <stdlib.h>
#include <stdio.h>

enum nodeType
{
	operator_type,
	number_type
};

struct node
{
	enum nodeType type;
	int val;
	char operator;
	struct node *next;
};

struct list
{
	struct node *head;
	struct node *tail;
};

struct list* initList(void)
{
	struct list *newList = (struct list*)malloc( sizeof(struct list) );
	newList->head = NULL;
	newList->tail = NULL;
	
	return newList;
}

int isEmpty(struct list *list)
{
	return list->head == NULL ? 1 : 0;
}

void addOperator(struct list *list, char operator)
{
	// create new node with val
	struct node *newNode = (struct node*)malloc( sizeof(struct node) );
	newNode->type      = operator_type;
	newNode->operator  = operator;
	newNode->next      = NULL; // as newNode will become last item on the list
	
	// make newNode the new tail in the list
	if ( !isEmpty(list) )
		list->tail->next = newNode;
	else
		list->head = newNode;
	list->tail = newNode;
}

void addNumber(struct list *list, int number)
{
	// create new node with val
	struct node *newNode = (struct node*)malloc( sizeof(struct node) );
	newNode->type = number_type;
	newNode->val  = number;
	newNode->next = NULL; // as newNode will become last item on the list
	
	// make newNode the new tail in the list
	if ( !isEmpty(list) )
		list->tail->next = newNode;
	else
		list->head = newNode;
	list->tail = newNode;
}

void printList(struct list *list)
{
	struct node *current = list->head;

	while( current != NULL )
	{
		if (current->type==number_type)
			printf("%i", current->val);
		else if (current->type==operator_type)
			printf("%c", current->operator);
		current = current->next;
	}
	
	printf("\n");
}

void clearList(struct list *list)
{
	struct node *current = list->head;

	while( current != NULL )
	{
		struct node *temp = current;
		current = current->next;
		free(temp);
	}
	
	free(list);
}

void evaluate(struct list *list)
{
	
}

int isValidOperator(char c)
{
	return c=='+' || c=='-' || c=='*' || c=='/' || c=='=' ? 1:0;
}

int main(void)
{
	struct list* lee = initList();
	
	int number;
	char operator;
	
	do
	{
		printf("\nEnter number: ");
		scanf("%i", &number);
		addNumber(lee, number);
		
		printf("\nCurrent list: ");
		printList(lee);
		
		do
		{
			printf("\nEnter operator: ");
			scanf(" %c", &operator);
		}
		while ( !isValidOperator(operator) );
		
		if (operator != '=')
		{
			addOperator(lee, operator);
			printf("\nCurrent list: ");
			printList(lee);
		}
	}
	while ( operator != '=' );
	
	evaluate(lee);
	
	clearList(lee);
	
	return 0;
}
