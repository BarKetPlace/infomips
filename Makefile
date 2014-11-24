TARGET = projet

CFLAGS = -g -std=c99 -I$(INCDIR)/ -Wall -Wextra -DDEBUG -DVERBOSE
LFLAGS=-lreadline -lm -lcurses
INCDIR=./include
SRCDIR= src/memoire src/cmd src/emul src/is_ src/dico src/fct


SRC=$(foreach nom, $(SRCDIR), $(wildcard $(nom)/*.c))
OBJ_DBG=$(SRC:.c=.o)

test_reg: ./tests/test_reg.o ./src/reg.o
	gcc $^ -o $@

test_is: ./src/is_/is_plage.o
	gcc $^ -o $@

test_loadmemory: ./tests/memoire/test_loadmemory.o $(OBJ_DBG) ./src/is_/is_sym.o ./src/is_/is_elf.o
	gcc $^ -o $@
#./src/is_/is_sym.o ./src/is_/is_elf.o ./src/is_/is_hexa.o ./src/is_/is_conform_line.o
main: main.o $(OBJ_DBG) 
	gcc $^ $(LFLAGS) -g -o $@
	clear

%.o:%.c
	gcc $< $(CFLAGS) -c -o $(basename $<).o


clean:
	rm main.o
	find ./src -name "*.o" -type f | xargs rm
