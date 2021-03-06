TARGET = projet

CFLAGS = -g -std=c99 -I$(INCDIR)/  -DDEBUG -DVERBOSE
LFLAGS= -lreadline -lm -lcurses
INCDIR=./include
SRCDIR= src/memoire src/cmd src/emul src/is_ src/dico src/fct


SRC=$(foreach nom, $(SRCDIR), $(wildcard $(nom)/*.c))
OBJ_DBG=$(SRC:.c=.o)

#test_reg: ./tests/test_reg.o ./src/reg.o
#	gcc $^ -o $@

#test_is: ./src/is_/is_plage.o
#	gcc $^ -o $@

#test_loadmemory: ./tests/memoire/test_loadmemory.o $(OBJ_DBG) ./src/is_/is_sym.o ./src/is_/is_elf.o
	#gcc $^ -o $@

#./src/is_/is_sym.o ./src/is_/is_elf.o ./src/is_/is_hexa.o ./src/is_/is_conform_line.o

#fct: fct_jal.o $(OBJ_DBG)
#	gcc $^ $(LFLAGS) -g -o $@
#	clear

#f_add: $(OBJ_DBG) $(INCDIR) ./src/fct/add.c
#	gcc $^ $(LFLAGS) -g -o $@
#	clear

main: main.o $(OBJ_DBG)
	gcc $^ $(LFLAGS) -g -o $@
	clear

dico: ./src/dico/dico.o 
	gcc $^ $(LFLAGS) -g -o $@

test_reg: ./tests/test_reg.o ./src/reg.o
	gcc $^ -o $@

test_is: ./src/is_/is_plage.o
	gcc $^ -o $@

test_loadmemory: ./tests/memoire/test_loadmemory.o $(OBJ_DBG) ./src/is_/is_sym.o ./src/is_/is_elf.o
	gcc $^ -o $@
#./src/is_/is_sym.o ./src/is_/is_elf.o ./src/is_/is_hexa.o ./src/is_/is_conform_line.o


%.o:%.c
	gcc $< $(CFLAGS) -c -o $(basename $<).o


clean:
	rm main.o
	find ./src -name "*.o" -type f | xargs rm
	#find . -name "*~" -type f | xargs rm
	#find ./tests/ -name "*.out" -type f | xargs rm
 
# créé l'archive à envoyer à votre tuteur (pas de rar SVP! et interdiction absolu d'envoyer autre chose qu'une archive, il ne doit y avoir qu'un seul fichier joint dans l'e-mail !)
#archive:
	#make clean
#	tar -czvf ../$(notdir $(PWD) )-`whoami`-`date +%d-%m-%H-%M`.tgz
#	echo "Fichier archive ../emulMips-`whoami`-`date +%d-%m-%H-%M`.tgz genere"



archive : 
	#make clean 
	tar -czvf ../$(notdir $(PWD) )-pichat_honore-`date +%d-%m-%H-%M`.tgz .
	echo "Fichier archive ../emulMips-`pichat_honore`-`date +%d-%m-%H-%M`.tgz genere"
	
	

