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

struct node* createOperatorNode(char operator);
struct node* createNumberNode(int number);

struct node* findFirstPointOperator(struct node* head); // NULL, wenn nicht gefunden
struct node* findFirstDashOperator(struct node* head); // NULL, wenn nicht gefunden

struct node* findPreviousNode(struct node* head, struct node* node);
void removeAfterNode(struct node* node);

struct node* addLast(struct node* head, struct node* newNode);

void printList(struct node* head);

int main(void)
{
	return 0;
}
