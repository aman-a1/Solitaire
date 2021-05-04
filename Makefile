all: game winnable advance check

game: game.cpp check.h config.hh 
	g++ -I/share/cs327/include -o game game.cpp /share/cs327/lib/libtermbox.a

winnable: winnable.cpp check.h config.hh
	g++ -o winnable winnable.cpp

advance: advance.o
	gcc -o advance advance.o

check: check.o check.h
	gcc -o check check.o

check.o: check.c check.h
	gcc -c -Wall -g check.c

advance.o: advance.c check.h
	gcc -c -Wall -g advance.c
