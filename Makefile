default: prog

get-deps:
	# Assuming Debian or Ubuntu here
	sudo apt-get install -y build-essential check

dictionary.o: dictionary.c
	gcc -Wall -c dictionary.c dictionary.h

spell.o: spell.c
	gcc -Wall -c spell.c

main.o: main.c
	gcc -Wall -g -c main.c

prog: dictionary.o spell.o main.o
	gcc -Wall -g -o spell_check dictionary.o spell.o main.o

clean:
	rm dictionary.o spell.o main.o check_spell.o

cleanall:clean
	rm spell_check
	
