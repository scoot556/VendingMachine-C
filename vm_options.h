/******************************************************************************
** Student name: 	Scott Djuric
** Student number: 	s3600531
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_OPTIONS_H
#define VM_OPTIONS_H

#include "vm_stock.h"

Boolean systemInit(VmSystem * system);
void systemFree(VmSystem * system);
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName);
Boolean loadStock(VmSystem * system, const char * fileName);
Boolean loadCoins(VmSystem * system, const char * fileName);
Boolean saveStock(VmSystem * system);
Boolean saveCoins(VmSystem * system);

void displayItems(VmSystem * system);
void purchaseItem(VmSystem * system);
Boolean validatePrice(char priceInString[]);
Boolean itemPayment(Node * node);
Boolean checkPayment(Node *itemToBuy, unsigned dollars, unsigned cents);
void saveAndExit(VmSystem * system);
void addItem(VmSystem * system);
char * makeID(VmSystem * system, char itemID[]);
void removeItem(VmSystem * system);
void displayCoins(VmSystem * system);
void resetStock(VmSystem * system);
void resetCoins(VmSystem * system);
void abortProgram(VmSystem * system);

#endif
