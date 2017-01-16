$FLAGS = -std=gnu99 -g Wall
$CC=gcc

mfind: mfind.o linkedl.o
		$(CC) $(FLAGS) mfind.o linkedl.o -o mfind

mfind.o: mfind.c linkedl.c linkedl.h mfind.h
		$(CC) $(FLAGS) -c mfind.c 

linkedl.o: linkedl.c linkedl.h
		$(CC) $(FLAGS) -c linkedl.c linkedl.h

clean: -rm -f *.o mfind
