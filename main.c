#include <stdio.h>
#include <stdlib.h>

enum node_type
{
	operator_type,
	number_type
};

struct node
{
	char operator;          // Jeder Knoten enthält immer nur entweder einen
	int number;             // Operator oder eine Zahl, nicht beides
	enum node_type type;
	struct node* next;
};

struct node* initNode(void)
{
	return (struct node*)malloc( sizeof(struct node*) );
}

struct node* createOperatorNode(char operator)
{
	struct node* newNode = initNode();
	
	newNode->type = operator_type;
	newNode->operator = operator;
	newNode->next = NULL;
	
	return newNode;
}

struct node* createNumberNode(int number)
{
	struct node* newNode = initNode();
	
	newNode->type = number_type;
	newNode->number = number;
	newNode->next = NULL;
	
	return newNode;
}

int isValidOperator(char operator)
{
	return operator=='+' || 
		operator=='-' ||
		operator=='*' ||
		operator=='/' ||
		operator=='=' ?
		1 : 0;
}

int isPointOperator(char operator)
{
	return operator=='*' || operator=='/' ? 1 : 0;
}

int isDashOperator(char operator)
{
	return operator=='+' || operator=='-' ? 1 : 0;
}

int isPointOperatorNode(struct node* node)
{
	return node->type==operator_type && isPointOperator(node->operator) ? 1 : 0;
}

int isDashOperatorNode(struct node* node)
{
	return node->type==operator_type && isDashOperator(node->operator) ? 1 : 0;
}

struct node* findFirstPointOperator(struct node* head) // NULL, wenn nicht gefunden
{
	struct node* current = head;
	
	while( current!=NULL && !isPointOperatorNode(current) )
	{
		current = current->next;
	}
	
	return current;
}

struct node* findFirstDashOperator(struct node* head) // NULL, wenn nicht gefunden
{
	struct node* current = head;
	
	while( current!=NULL && !isDashOperatorNode(current) )
	{
		current = current->next;
	}
	return current;
}

struct node* findPreviousNode(struct node* head, struct node* node)
{
	for(; head!=NULL && head->next!=node; head=head->next);
	return head;
}

/*
void removeAfterNode(struct node* node)
{
}
*/

struct node* removeNode(struct node* head, struct node* node)
{
	if(head!=NULL && node!=NULL)
	{
		if(head==node)
			head = head->next;
		else
			findPreviousNode(head, node)->next = node->next;
			
		free(node);
	}
	
	return head;
}

struct node* addLast(struct node* head, struct node* newNode)
{
	if(head==NULL)
		head = newNode;
	else
	{
		struct node* current = head;
		while(current->next != NULL)
			current = current->next;
		current->next = newNode;
	}
	return head;
}

void printList(struct node* head)
{
	while(head != NULL)
	{
		switch(head->type)
		{
			case operator_type: printf("%c", head->operator); break;
			case number_type  : printf("%i", head->number  ); break;
			default: printf("[node type unknown]"); break;
		}
		head = head->next;
	}
	printf("\n");
}

void evaluate(struct node* head)
{
	// evaluate all point operations
	for( struct node* operatorNode = findFirstPointOperator(head);
			operatorNode != NULL;
			operatorNode = findFirstPointOperator(head) )
	{
		struct node* operand1 = findPreviousNode(head, operatorNode);
		struct node* operand2 = operatorNode->next;
		
		switch(operatorNode->operator)
		{
			case '*':
				operand1->number = operand1->number * operand2->number;
			break;
				
			case '/':
				operand2->number = operand2->number == 0 ? 1 : operand2->number;
				operand1->number = operand1->number / operand2->number;
			break;
		}
		
		head = removeNode(head, operatorNode);
		head = removeNode(head, operand2);
		
		printf("\nPoint operator result: ");
		printList(head);
	}
	
	// evaluate all dash operations
	for( struct node* operatorNode = findFirstDashOperator(head);
			operatorNode != NULL;
			operatorNode = findFirstDashOperator(head) )
	{
		struct node* operand1 = findPreviousNode(head, operatorNode);
		struct node* operand2 = operatorNode->next;
		
		switch(operatorNode->operator)
		{
			case '+':
				operand1->number = operand1->number + operand2->number;
			break;
				
			case '-':
				operand1->number = operand1->number - operand2->number;
			break;
		}
		
		head = removeNode(head, operatorNode);
		head = removeNode(head, operand2);
		
		printf("\nDash operator result: ");
		printList(head);
	}
	
	if (head!=NULL)
	{
		printf("\nFinal result: %i", head->number);
		free(head);
	}
	else
		printf("\nFinal result: %i", 0);
}

int main(void)
{
	struct node* lee = NULL;
	
	int number;
	char operator;
	
	do
	{
		printf("\nEnter number: ");
		scanf("%i", &number);
		lee = addLast( lee, createNumberNode(number) );
		
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
			lee = addLast( lee, createOperatorNode(operator) );
			printf("\nCurrent list: ");
			printList(lee);
		}
	}
	while ( operator != '=' );
	
	evaluate(lee);
	
	return 0;
}
