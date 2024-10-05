/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "IntStore.h"
#include <stdio.h>
#include <stdlib.h>

int itterateThroughList(int pos, Node *cur);
int printAllNodes(void);


Node *head;
Node *tail;
int size = 0;
int hasInitialized = 0;

char **
append_intstore_1_svc(arr *argp, struct svc_req *rqstp)
{
	printf("top of append \n");
	static char *result;

	Node *first = (Node *)malloc(sizeof(Node));
	// printf("%d\n",argp->Arr[0]);
	first->data = argp->Arr[0];

	Node *second = (Node *)malloc(sizeof(Node));
	second->data = argp->Arr[1];

	Node *third = (Node *)malloc(sizeof(Node));
	third->data = argp->Arr[3];

	Node *fourth = (Node *)malloc(sizeof(Node));
	fourth->data = argp->Arr[4];

	Node *fith = (Node *)malloc(sizeof(Node));
	fith->data = argp->Arr[5];

	Node *sixth = (Node *)malloc(sizeof(Node));
	sixth->data = argp->Arr[2];

	Node *seventh = (Node *)malloc(sizeof(Node));
	seventh->data = argp->Arr[6];

	Node *eigth = (Node *)malloc(sizeof(Node));
	eigth->data = argp->Arr[7];

	first->next = second;
	second->next = third;
	third->next = fourth;
	fourth->next = fith;
	fith->next = sixth;
	sixth->next = seventh;
	seventh->next = eigth;

	second->prev = first;
	third->prev = second;
	fourth->prev = third;
	fith->prev = fourth;
	sixth->prev = fith;
	seventh->prev = sixth;
	eigth->prev = seventh;

	if (head->data == -1)
	{
		head = first;
		tail = eigth;
	}
	else
	{
		tail->next = first;
		first->prev = tail;
		tail = eigth;
	}
	head->prev = NULL;
	tail->next = NULL;
	size += 8;
	printAllNodes();

	//sortAllNodes();

	//printAllNodes();

	result = "success";

	return &result;
}

char **
query_intstore_1_svc(int *argp, struct svc_req *rqstp)
{
	static char *result;
	char buff[500];

	Node *cur = head;

	int atPlace;

	printf("befor itteration\n");
	atPlace = itterateThroughList(*argp, cur);
	printf("done with itteration\n");
	sprintf(buff, "%d", atPlace);
	printf("what in buff %s\n", buff);
	result = buff;
	// itoa(argp,result, 10);
	printf("sending back %s\n", result);
	return &result;
}

char **
remove_intstore_1_svc(int *argp, struct svc_req *rqstp)
{
	static char *result;
	Node *cur = head;
	Node *temp = cur;
	int atPlace;
	char *outOfRange = "Out of range";

	printf("head's data %d\n", cur->data);
	if (cur->next == NULL || cur->data == -1)
	{
		result = outOfRange;
		return &result;
	}
	else if (cur->next->data == -1)
	{
		result = outOfRange;
		return &result;
	}

	for (int i = 0; i <= *argp; i++)
	{
		cur = temp;
		printf("start of iterate %d with cur data at %d\n", i, cur->data);

		if (cur->next != NULL)
		{
			printf("in if\n");
			temp = cur->next;
		}
		else if (i != *argp && cur->next == NULL)
		{
			printf("in else if\n");
			result = outOfRange;
			return &result;
		}

		printf("updated cur\n");
	}
	printf("currents data befor return is %d\n", cur->data);
	if (cur->prev != NULL)
	{
		printf("if cur->prev != NULL\n");
		cur->prev->next = cur->next;
	}
	if (cur->next != NULL)
	{
		printf("if cur->next != NULL\n");
		cur->next->prev = cur->prev;
	}
	if (cur->prev == NULL && cur->next != NULL)
	{
		head = cur->next;
	}
	if (cur->next == NULL && cur->prev != NULL)
	{
		tail = cur->prev;
	}
	if (cur->next == NULL && cur->prev == NULL)
	{
		head->data = -1;
		head->next = NULL;
		head->prev = NULL;
		tail = head;
	}
	free(cur);
	size--;
	printf("befor print\n");
	printAllNodes();
	return &result;
}

char **
checkin_intstore_1_svc(void *argp, struct svc_req *rqstp)
{
	static char *result;
	if(hasInitialized == 0){
	head = (Node *)malloc(sizeof(Node));
	// Assigning data
	head->data = -1;
	head->next = NULL;
	head->prev = NULL;
	tail = head;
	result = "succesful connection and allocation";
	hasInitialized = 1;
	}
	else{
		result = "succesful connection";
	}

	

	return &result;
}

int printAllNodes(void)
{
	printf("Linked List: ");
	Node *temp = head;
	while (temp)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
	printf("Done with print\n");
	return 1;
}

/*int sortAllNodes(void)
{
	int isSorted = 0;
	int hasSwapped = 0;
	int tempInt = tail->data;
	Node *curNode = head;
	Node *tempNode;
	int i = 0;
	while (isSorted == 0)
	{
		printf("in loop %d\n", i);
		i++;
		hasSwapped = 0;
		curNode = head;
		for (int j = 0; j < size - 1; j++)
		{
			printf("in inner loop %d\n", j);
			if (curNode->data > curNode->next->data)
			{
				swapNodes(curNode, curNode->next);
				hasSwapped = 1;
				curNode = curNode->prev;
			}
			curNode = curNode->next;
		}
		if (hasSwapped == 0)
		{
			isSorted = 1;
		}
	}
	return 1;
}*/

// specifically swap ajacent nodes
/*int swapNodes(Node *cur, Node *next)
{
	Node *temp;
	// check if cur head and next is tail
	if (cur->prev == NULL && next->next == NULL)
	{
		head = next;
		head->prev = NULL;
		tail = cur;
		cur->next = NULL;
		cur->prev = next;
		next->next = cur;
	}
	else if (cur->prev == NULL)
	{
		head = next;
		head->prev = NULL;
		cur->next = next->next;
		next->next = cur;
		cur->prev = next;
		cur->next->prev = cur;
	}
	else if (next->next == NULL)
	{
		tail = cur;
		tail->next = NULL;
		next->prev = cur->prev;
		cur->prev = next;
		next->next = cur;
		next->prev->next = next;
	}
	else
	{
		temp = cur->prev;
		next->prev = temp;
		cur->next = next->next;
		next->next = cur;
		cur->prev = next;
		cur->next->prev = cur;
		temp->next = next;
	}

	return 1;
}*/

int itterateThroughList(int pos, Node *cur)
{
	Node *temp = cur;
	printf("head's data %d\n", cur->data);
	if (cur->next == NULL)
	{
		return -1;
	}
	else if (cur->next->data == -1)
	{
		return -1;
	}

	for (int i = 0; i <= pos; i++)
	{
		cur = temp;
		printf("start of iterate %d with cur data at %d\n", i, cur->data);

		printf("in proper through\n");
		if (cur->next != NULL)
		{
			temp = cur->next;
		}
		else if (i != pos && cur->next == NULL)
		{
			return -1;
		}

		printf("updated cur\n");
	}
	printf("currents next befor return is %d\n", cur->data);
	return cur->data;
}