/******************************************************************************
** Student name: 	Scott Djuric
** Student number: 	s3600531
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm.h"

#define MENU_SIZE 9

int main(int argc, char ** argv)
{
	VmSystem vm;
	MenuItem menu[MENU_SIZE];
	MenuFunction option;
	
	/* loadData(&system, argv[1], argv[2]); */
	
	systemInit(&vm);
	if (argc != 2)
	{
		printf("USAGE: ./vm <stock.dat>\n");
		return EXIT_FAILURE;
	}
	
	if(!loadData(&vm, argv[1], NULL))
	{
		printf("Stock file failed to load\n");
		exit(0);
	}
	if(!loadStock(&vm, argv[1]))
	{
		return EXIT_FAILURE;
	}
	
	initMenu(menu);
	while(TRUE)
	{
		mainMenu(menu);
		option = getMenuChoice(menu);
		
		if(option == saveAndExit)
		{
			break;
		}
		else if(option == NULL)
		{
			continue;
		}
		else
		{
			(*option)(&vm);
		}
	}
	
	(*option)(&vm);
	printf("Goodbye. \n\n");	
	
    return EXIT_SUCCESS;
}
