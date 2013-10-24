FLAGS = -O3 -Wall -g

./tde: hash.o function.o tde.o dered.o
	gcc $(FLAGS) hash.o function.o tde.o dered.o -o tde
hash.o: hash.c
	gcc $(FLAGS) -c hash.c -o hash.o
function.o: function.c
	gcc $(FLAGS) -c function.c -o function.o
tde.o: tde.c
	gcc $(FLAGS) -c tde.c -o tde.o
dered.o: de_redundance.c de_redundance.h hash.c hash.h
	gcc $(FLAGS) -c de_redundance.c -o dered.o

clean:
	rm *.o tde
ar:
	tar cvzf "./bak/`date +"%Y%m%d_%H%M%S"`.tar.gz" *.c *.h Makefile
