SOURCES=vm.c vm_menu.c vm_options.c vm_stock.c vm_coin.c utility.c
DOCUMENTS = requirement13.txt requirement13part2.txt readme.txt
OBJECTS=vm.o vm_menu.o vm_options.o vm_stock.o vm_coin.o utility.o
HEADERS=vm.h vm_menu.h vm_options.h vm_stock.h vm_coin.h utility.h vm_system.h
PROGRAM=vm
DEBUG=-g
FLAGS=-ansi -pedantic -Wall $(DEBUG)

all:$(PROGRAM)

$(PROGRAM): $(OBJECTS)
	gcc $(FLAGS) -o $(PROGRAM) $(OBJECTS)
	
vm.o:vm.c $(HEADERS)
	gcc $(FLAGS) -c vm.c
	
vm_menu.o:vm_menu.c $(HEADERS)
	gcc $(FLAGS) -c vm_menu.c
	
vm_options.o:vm_options.c $(HEADERS)
	gcc $(FLAGS) -c vm_options.c
	
vm_stock.o:vm_stock.c $(HEADERS)
	gcc $(FLAGS) -c vm_stock.c
	
vm_coin.o:vm_coin.c $(HEADERS)
	gcc $(FLAGS) -c vm_coin.c
	
vm_utility.o:vm_utility.c $(HEADERS)
	gcc $(FLAGS) -c vm_utility.c

clean:
	rm $(PROGRAM)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) $(DOCUMENTS) Makefile
