CC=gcc

hiragana: hiragana.o map.o string.o
hiragana.o: hiragana.c map.h string.h consts.h
map.o: map.c map.h string.h
string.o: string.c string.h map.h

clean:
	rm hiragana *.o

