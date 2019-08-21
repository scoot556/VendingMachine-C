/******************************************************************************
** Student name: 	Scott Djuric
** Student number: 	s3600531
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"

List * initList();

Node * makeNode(Stock * stock, Node * node);

void addStock(List * list, Node * node);

void assignStock(char * data, Stock * stock);

void sortStock(VmSystem * system);

void sortStockByID(VmSystem * system);

void freeNode(Node * node);

void freeIntList(List * list);

void printStock(List * list);

void sortID(VmSystem * system);

#endif
