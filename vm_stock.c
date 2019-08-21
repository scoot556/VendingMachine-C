/******************************************************************************
** Student name: 	Scott Djuric
** Student number: 	s3600531
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_stock.h"

/**
 * vm_stock.c this is the file where you will implement the
 * interface functions for managing the stock list.
 **/

/**
 * Some example functions:
 * create list, free list, create node, free node, insert node, etc...
 */

List * initList()
{
	List * list = malloc(sizeof(List));
	if(list == NULL)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		list->head = NULL;
		list->size = 0;
	}
	return list;
}
 
void addStock(List * list, Node * node)
{
	Node * temp = NULL;
	
	node->next = NULL;
	
	if(list->head == NULL)
	{
		list->head = node;
	}
	else 
	{
		temp = list->head;
		while (TRUE)
		{
			if(temp->next == NULL)
			{
				temp->next = node;
				break;
			}
			temp = temp->next;
		}
	}
	list->size++;
}

Node * makeNode(Stock * stock, Node * node)
{
	node->data = stock;
	node->next = NULL;
	return node;
}


void assignStock(char * data, Stock * stock)
{
	char * id;
	char * name;
	char * desc;
	char * priceString;
	char * dollarString;
	char * centString;
	char * onHandString;
	
	unsigned dollars;
	unsigned cents;
	unsigned onHand;
	
	id = strtok(data, STOCK_DELIM);
	name = strtok(NULL, STOCK_DELIM);
	desc = strtok(NULL, STOCK_DELIM);
	priceString = strtok(NULL, STOCK_DELIM);
	onHandString = strtok(NULL, STOCK_DELIM);
	
	dollarString = strtok(priceString, ".");
	centString = strtok(NULL, ".");
	
	dollars = (unsigned) strtol(dollarString, NULL, 10);
	cents = (unsigned) strtol(centString, NULL, 10);
	onHand = (unsigned) strtol(onHandString, NULL, 10);
	
	strcpy(stock->id, id);
	strcpy(stock->name, name);
	strcpy(stock->desc, desc);
	stock->price.dollars = dollars;
	stock->price.cents = cents;
	stock->onHand = onHand;
}


void sortStock(VmSystem * system)
{
	Node * curr;
	Stock * tempStock;
	int i = 0;
	
	for (i = 0; i < system->itemList->size; i++)
	{
		curr = system->itemList->head;
		while(curr->next != NULL)
		{
			if(strcmp(curr->data->name, curr->next->data->name) > 0)
			{
				tempStock = curr->data;
				curr->data = curr->next->data;
				curr->next->data = tempStock;
			}
			curr = curr->next;
		}
	}
}


void sortStockByID(VmSystem * system)
{
	Node * curr;
	Stock * tempStock;
	int i = 0;
	
	for (i = 0; i < system->itemList->size; i++)
	{
		curr = system->itemList->head;
		while(curr->next != NULL)
		{
			if(strcmp(curr->data->id, curr->next->data->id) > 0)
			{
				tempStock = curr->data;
				curr->data = curr->next->data;
				curr->next->data = tempStock;
			}
			curr = curr->next;
		}
	}
}


void printStock(List * list)
{
	Node * curr = list->head;
    int idWidth=strlen("ID");
	int nameWidth=strlen("Name");
	int stockWidth=strlen("Available");
    int temp;
    while(curr != NULL) {
        temp = strlen(curr->data->id);
        idWidth = (idWidth > temp ? idWidth : temp); 

        temp = strlen(curr->data->name);
        nameWidth = (nameWidth > temp ? nameWidth : temp);  

        temp = (int) getNumLength(curr->data->onHand);
        stockWidth = (stockWidth > temp ? stockWidth : temp);  

        curr = curr->next;
    } 

    curr = list->head;

    printf("Items Menu\n\n");

    printf("%-*s | %-*s | %-*s | %s\n", 
            idWidth,"ID",
            nameWidth,"Name",
            stockWidth,"Available",
            "Price");
    printf("--------------------------------------------------\n");

    while (curr != NULL) {
        printf("%-*s | %-*s | %-*u | $ %u.%02u\n", 
                idWidth,curr->data->id,
                nameWidth,curr->data->name,
                stockWidth,curr->data->onHand,
                curr->data->price.dollars,
                curr->data->price.cents);
        curr = curr->next;
    }
    printf("\n");
}

void freeIntList(List * list)
{
	Node * current = list->head;
    Node * temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    free(list);
}

void freeNode(Node * node)
{
	free(node);
}

void sortID(VmSystem * system)
{
	int id = 0;
	int size = 0;
	Node * curr = system->itemList->head;
	char newID[ID_LEN + NULL_SPACE];
	char idToString[4 + NULL_SPACE];
	
	sortStockByID(system);
	
	while(curr != NULL)
	{
		id++;
		strcpy(newID, "I");
		
		size = 3;
		if (id >= 10 && id < 100)
		{
			size = 2;
		}
		else if(id >= 100 && id < 1000)
		{
			size = 1;
		}
		else if(id > 1000)
		{
			size = 0;
		}
		
		while(size > 0)
		{
			strcat(newID, "0");
			size--;
		}
		
		sprintf(idToString, "%d", id);
		strcat(newID, idToString);
		
		strcpy(curr->data->id, newID);
		
		curr = curr->next;
	}
}