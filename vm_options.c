/******************************************************************************
** Student name: 	Scott Djuric
** Student number: 	s3600531
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_options.h"

#define MAX_STOCK_LENGTH 512
#define MAX_PRICE_LENGTH 4

/**
 * vm_options.c this is where you need to implement the system handling
 * functions (e.g., init, free, load, save) and the main options for
 * your program. You may however have some of the actual work done
 * in functions defined elsewhere.
 **/

/**
 * Initialise the system to a known safe state. Look at the structure
 * defined in vm_system.h.
 **/
Boolean systemInit(VmSystem * system)
{
    system->itemList = initList();
	/*initCoin(system->cashRegister);*/
	system->stockFileName = NULL;
	/*system->coinFileName = NULL;*/
	
	return TRUE;
}

/**
 * Free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind.
 **/
void systemFree(VmSystem * system)
{	
	Node *current = system->itemList->head;
	Node *previous = NULL;

	while (current != NULL) {
		previous = current;
		current = current->next;
		free(previous->data);
		free(previous);
	}


	free(system->itemList);
	
	/*free(system);*/
}

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName)
{
    system->stockFileName = stockFileName;
	/*system->coinFileName = coinFileName;*/
	return TRUE;
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem * system, const char * fileName)
{	
	char stocks[MAX_STOCK_LENGTH];
	Node * nodeIn;
	Stock * stockIn;
	
	FILE * fileIn;
	fileIn = fopen(fileName, "r");
	
	if(fileIn == NULL)
	{
		printf("No stock file found!\n");
		return FALSE;
	}
	
	system->stockFileName = fileName;
	
	while(fgets(stocks, sizeof(stocks), fileIn) != NULL)
	{
		nodeIn = malloc(sizeof(Node));
		stockIn = malloc(sizeof(Stock));
		assignStock(stocks, stockIn);
		
		makeNode(stockIn, nodeIn);
		addStock(system->itemList, nodeIn);
	}
	
	sortStock(system);
	
	fclose(fileIn);
	return TRUE;
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem * system, const char * fileName)
{
    return FALSE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem * system)
{
	FILE * fp;
	Node * node;
	
	sortStock(system);
	
	printf("Writing to file...\n");
	fp = fopen(system->stockFileName, "w");
	
	node = system->itemList->head;
	
	while(node != NULL)
	{
		fprintf(fp, "%s|%s|%s|%u.%02u|%u\n", 
		node->data->id, 
		node->data->name, 
		node->data->desc, 
		node->data->price.dollars, 
		node->data->price.cents, 
		node->data->onHand);
		
		node = node->next;
	}
	
	fclose(fp);
	systemFree(system);
	
    return TRUE;
}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem * system)
{
    return FALSE;
}

/**
 * This option allows the user to display the items in the system.
 * This is the data loaded into the linked list in the requirement 2.
 **/
void displayItems(VmSystem * system)
{ 
	printStock(system->itemList);
	/*sortStock(system);*/
	
}

/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem * system)
{
	Boolean buyItem;
	Boolean foundItem = FALSE;
	Boolean avail = TRUE;
	char itemInput[ID_LEN + EXTRA_SPACES];
	Node * curr;
	
	printf("Purchase Item\n");
	printf("--------------\n");
	
	while(!foundItem)
	{
		curr = system->itemList->head;
		
		printf("Please enter the id of the item you want to purchase: ");
		fgets(itemInput, sizeof(itemInput), stdin);
		
		if(strcmp(itemInput, "\n\0") == 0)
		{
			printf("Returning to the Main Menu...\n");
			return;
		}
		
		if(itemInput[strlen(itemInput) - 1] != '\n')
		{
			printf("Invalid input\n");
			readRestOfLine();
		}
		else
		{
			itemInput[strlen(itemInput) - 1] = '\0';
			while(curr != NULL)
			{
				if(strcmp(itemInput, curr->data->id) == 0)
				{
					printf("Item Found\n");
					
					if(curr->data->onHand == 0)
					{
						printf("Sorry, no stock of %s\n", curr->data->name);
						avail = FALSE;
						break;
					}
					
					
					printf("You have chosen item \"%s\t%s\". This costs $%d.%02d.\n", curr->data->name, curr->data->desc, curr->data->price.dollars, curr->data->price.cents);
					
					printf("Please give the required money -- Type in the value of each note and coin in cents.\n\n");
					printf("If you do not wish to purchase this item, press enter to cancel\n\n");
					
					buyItem = itemPayment(curr);
					
					if(buyItem)
					{
						curr->data->onHand--;
					}
					else
					{
						curr->data->onHand--;
					}
					
					foundItem = TRUE;
					break;
				}
				curr = curr->next;
			}
			if(!avail)
			{
				continue;
			}
			else if(!foundItem)
			{
				printf("Item not found, please try again\n");
			}
		}
	}
}

Boolean itemPayment(Node * node)
{
	char priceInput[MAX_PRICE_LENGTH + EXTRA_SPACES];
	unsigned price = 0;
	unsigned dollars = 0;
	unsigned cents = 0;
	Boolean pValid = FALSE;
	Boolean pLimit = FALSE;
	
	while(!pValid)
	{
		printf("You need to give $%d.%02d: ", node->data->price.dollars, node->data->price.cents);
		fgets(priceInput, sizeof(priceInput), stdin);
		
		if(strcmp("\n\0", priceInput) == 0)
		{
			printf("Returning to the main menu\n");
			return FALSE;
		}
		
		if(priceInput[strlen(priceInput) - 1] != '\n')
		{
			printf("Invalid input, try again please\n");
			readRestOfLine();
			continue;
		}
		else
		{
			priceInput[strlen(priceInput) - 1] = '\0';
			price = (unsigned) strtol(priceInput, NULL, 10);
			
			dollars = price / 100;
			cents = price % 100;
			
			if(!validatePrice(priceInput))
			{
				printf("Error: $%d.%02d is not a valid denomination of money\n", dollars, cents);
				continue;
			}
			else
			{
				pValid = TRUE;
			}
		}
		
		pLimit = checkPayment(node, dollars, cents);
		if (!pLimit) 
		{
			printf("Returning to Main Menu...\n");
			return pLimit;
		}
	}
	return pLimit;
}


Boolean checkPayment(Node * itemToBuy, unsigned dollars, unsigned cents) 
{
   Boolean totalAmount = FALSE;

   unsigned price = dollars * 100 + cents;

   int dollarAmount = itemToBuy->data->price.dollars;
   int centAmount = itemToBuy->data->price.cents;

   unsigned change = 0;
   unsigned dChange = 0;
   unsigned cChange = 0;

   char priceInput[MAX_PRICE_LENGTH + EXTRA_SPACES];

   while (!totalAmount) 
   {
      if (dollars > dollarAmount) 
	  {
        totalAmount = TRUE;
      } 
	  else 
	  {
         dollarAmount = dollarAmount - dollars;
         centAmount = centAmount - cents;

         if (centAmount <= 0 && dollarAmount <= 0) 
		 {
            price = 0;
            break;
         }

         if (centAmount < 0) 
		 {
            centAmount = centAmount + 100;
            dollarAmount--;
         }

         printf("You still need to give us $%d.%02d: ", dollarAmount, centAmount);
         fgets(priceInput, sizeof(priceInput), stdin);

         if (strcmp(priceInput, "\n\0") == 0) 
		 {
            return FALSE;
         }

         if (priceInput[strlen(priceInput) - 1] != '\n') 
		 {
            printf("Invalid, please try again\n");
            readRestOfLine();
         } 
		 else 
		 {
            priceInput[strlen(priceInput) - 1] = '\0';
            price = (unsigned) strtol(priceInput, NULL, 10);
            dollars = price / 100;
            cents = price % 100;

            if (!validatePrice(priceInput)) 
			{
               printf("Error: $%d.%02d is not a valid denomination of money\n", dollars, cents);
               dollarAmount = dollarAmount + dollars;
               centAmount = centAmount + cents;
               continue;
            }

            if (dollars > dollarAmount) 
			{
               totalAmount = TRUE;
            }

         }
      }

   }
   change = price - (dollarAmount * 100 + centAmount);
   dChange = change / 100;
   cChange = change % 100;

   printf("Thank you, here is your %s, and your change of $%d.%02d.\n", itemToBuy->data->name, dChange, cChange);
   printf("Please come back soon.\n");

   return totalAmount;
   
   
   
}
	
	

Boolean validatePrice(char priceInput[]) {
   unsigned price = 0;

   price = (unsigned) strtol(priceInput, NULL, 10);
 
   if (price == 5 || price == 10 || price == 20 || price == 50 ||
       price == 100 || price == 200 || price == 500 || price == 1000) 
	{
      return TRUE;
	} 
	else 
	{
      return FALSE;
   }
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem * system)
{ 
	saveStock(system);
}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem * system)
{
	Stock * addItem = malloc(sizeof(Stock));
	Node * addNode = malloc(sizeof(Node));
	char itemName[NAME_LEN + EXTRA_SPACES];
	char itemDesc[DESC_LEN + EXTRA_SPACES];
	char * delim = ".";
	
	char itemPrice[MAX_PRICE_LENGTH + EXTRA_SPACES + 1];
	unsigned itemDol = 0;
	unsigned itemCent = 0;
	
	char itemID[ID_LEN + NULL_SPACE];
	makeID(system, itemID);
	
	printf("The item you have entered will have the ID of %s.\n", itemID);
	while(TRUE)
	{
		printf("Please enter the item name: ");
		fgets(itemName, sizeof(itemName), stdin);
		if(strcmp("\n\0", itemName) == 0)
		{
			printf("Returning to the main menu...\n");
			free(addItem);
			free(addNode);
			return;
		}
		
		if(itemName[strlen(itemName) - 1] != '\n')
		{
			printf("Invalid input, please try again\n");
			readRestOfLine();
		}
		else
		{
			itemName[strlen(itemName) - 1] = '\0';
			break;
		}
	}
	
		while(TRUE)
		{
			printf("Please enter the item's description: ");
			fgets(itemDesc, sizeof(itemDesc), stdin);
			if(strcmp("\n\0", itemDesc) == 0)
			{
				printf("Returning to the main menu...\n");
				free(addItem);
				free(addNode);
				return;
			}
			
			if(itemDesc[strlen(itemDesc) - 1] != '\n')
			{
				printf("Invalid input, please try again\n");
				readRestOfLine();
			}
			else
			{
				itemDesc[strlen(itemDesc) - 1] = '\0';
				break;
			}
		}
		
		while(TRUE)
		{
			printf("Please enter the item's price: ");
			fgets(itemPrice, sizeof(itemPrice), stdin);
			if(strcmp("\n\0", itemPrice) == 0)
			{
				printf("Returning to the main menu...\n");
				free(addItem);
				free(addNode);
				return;
			}
			
			if(itemPrice[strlen(itemPrice) - 1] != '\n')
			{
				printf("Invalid input, please try again\n");
				readRestOfLine();
			}
			else
			{
				itemPrice[strlen(itemPrice) - 1] = '\0';
				if(itemPrice[strlen(itemPrice) - 3] != *delim)
				{
					printf("Error: Please enter a decimal to separate the dollars and cents\n");
					continue;
				}
				
				itemDol = (unsigned) strtol(strtok(itemPrice, delim), NULL, 10);
				itemCent = (unsigned) strtol(strtok(NULL, delim), NULL, 10);
				
				if(itemCent % 5 != 0)
				{
					printf("You've inputed an invalid cent value\n");
				}
				else
				{
					break;
				}
			}
		}
		strcpy(addItem->id, itemID);
		strcpy(addItem->name, itemName);
		strcpy(addItem->desc, itemDesc);
		addItem->price.dollars = itemDol;
		addItem->price.cents = itemCent;
		addItem->onHand = DEFAULT_STOCK_LEVEL;
		
		printf("The item \"%s --- %s.\" has been added to the system\n", addItem->name, addItem->desc);
		makeNode(addItem, addNode);
		addStock(system->itemList, addNode);
		sortStock(system);	
}

char * makeID(VmSystem * system, char itemID[])
{
	int idLen = 1;
	
	int totalID = system->itemList->size;
	int nextID = totalID + 1;
	char nextString[4 + NULL_SPACE];
	
	int i = 0;
	
	if(nextID >= 10 && nextID < 100)
	{
		idLen = 3;
	}
	else if(nextID >= 100 && nextID < 1000)
	{
		idLen = 2;
	}
	else if(nextID > 1000)
	{
		idLen = 1;
	}
	else 
	{
		idLen = 4;
	}
	
	
	strcpy(&itemID[0], "I");
	idLen--;
	
	for (i = 0; i < idLen; i++)
	{
		strcat(itemID, "0");
	}
	
	sprintf(nextString, "%d", nextID);
	
	strcat(itemID, nextString);
	
	return itemID;
}



/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem * system)
{ 
	Node * itemDel = NULL;
	Node * curr = NULL;
	
	char itemID[ID_LEN + EXTRA_SPACES];
	Boolean findItem = FALSE;
	
	while(!findItem)
	{
		curr = system->itemList->head;
		printf("Please enter the ID of the item you wish to remove: ");
		fgets(itemID, sizeof(itemID), stdin);
		if(strcmp(itemID, "\n\0") == 0)
		{
			printf("Returning to the main menu...\n");
			return;
		}
		
		if(itemID[strlen(itemID) - 1] != '\n')
		{
			printf("Invalid input, please try again\n");
			readRestOfLine();
		}
		else
		{
			itemID[strlen(itemID) - 1] = '\0';
			
			while(curr != NULL)
			{
				if(strcmp(curr->data->id, itemID) == 0)
				{
					itemDel = curr;
					findItem = TRUE;
					break;
				}
				
				curr = curr->next;
				
			}
			
			if(!findItem)
			{
				printf("The items you have requested cannot be found!\n");
			}
		}
	}
	
	curr = system->itemList->head;
	while(curr != NULL)
	{
		if(itemDel == curr)
		{
			system->itemList->head = curr->next;
			break;
		}
		
		else if(curr->next == itemDel)
		{
			if(itemDel->next == NULL)
			{
				curr->next = NULL;
			}
			else
			{
				curr->next = itemDel->next;
			}
			break;
		}
		curr = curr->next;
	}
	
	printf("\"%s - %s %s\" has been removed.\n", itemDel->data->id, itemDel->data->name, itemDel->data->desc);
	
	free(itemDel->data);
	free(itemDel);
	system->itemList->size--;
	sortID(system);
	sortStock(system);
}


/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem * system)
{ 

}

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem * system)
{ 
	Node * curr;
	
	curr = system->itemList->head;
	
	printf("Resetting the stock count...\n");
	while(curr != NULL)
	{
		curr->data->onHand = DEFAULT_STOCK_LEVEL;
		
		curr = curr->next;
	}
}

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code.
 * This requirement implements part 3 of requirement 18 in the
 * assignment specifications.
 **/
void resetCoins(VmSystem * system)
{ 

}

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem * system)
{ 
	printf("Aborting Program...\n");
	systemFree(system);
	exit(0);
}
