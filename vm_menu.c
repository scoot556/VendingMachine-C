/******************************************************************************
** Student name: 	Scott Djuric
** Student number: 	s3600531
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/
void initMenu(MenuItem * menu)
{
	menu[0].function = displayItems;
	menu[1].function = purchaseItem;
	menu[2].function = saveAndExit;
	menu[3].function = addItem;
	menu[4].function = removeItem;
	menu[5].function = displayCoins;
	menu[6].function = resetStock;
	menu[7].function = resetCoins;
	menu[8].function = abortProgram;
	
	strcpy(menu[0].text, "Display Items");
	strcpy(menu[1].text, "Purchase Items");
	strcpy(menu[2].text, "Save and Exit");
	strcpy(menu[3].text, "Add Item");
	strcpy(menu[4].text, "Remove Item");
	strcpy(menu[5].text, "Display Coins");
	strcpy(menu[6].text, "Reset Stocks");
	strcpy(menu[7].text, "Reset Coins");
	strcpy(menu[8].text, "Abort Program");
}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem * menu)
{
    char input[1 + EXTRA_SPACES];
	int option = 0;
	
	while (TRUE)
	{
		printf("Select your option(1-9): ");
		fgets(input, sizeof(input), stdin);
		
		if(input[strlen(input)-1] != '\n')
		{
			printf("Invalid input, please try again\n");
			readRestOfLine();
			break;
		}
		else
		{
			option = (int) strtol(input, NULL, 10);
			
			if(option == 0)
			{
				printf("Invalid input, please try again\n");
				break;
			}
			else
			{
				return menu[option - 1].function;
			}
		}
	}
		return NULL;		
}

void mainMenu(MenuItem * menu)
{
	int i;
	int count = 0;
	
	for (i=0; i<sizeof(menu[0]) / sizeof(menu) + 1; i++)
	{
		if(count == 0 && i == 0)
		{
			printf("Main Menu:\n");
			count++;
			i--;
		}
		else if(count == 1 && i == 3)
		{
			printf("Administrator-Only Menu:\n");
			count++;
			i--;
		}
		else
		{
			printf("%d. %s\n", i + 1, menu[i].text);
		}
	}
}
