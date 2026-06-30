CC = gcc
_dirIcklib 	= ./libs/icklib
_dirScrns  	= ./libs/scrns
objects    	= main.o ickclock.o ickutils.o scrn_init.o
executable: $(objects)
	$(CC) -o executable $(objects) \
				-lncurses
main.o: main.c
	$(CC) -c main.c \
				-I $(_dirIcklib)\
				-I $(_dirScrns)
ickclock.o: $(_dirIcklib)/ickclock.c
	$(CC) -c $(_dirIcklib)/ickclock.c
ickutils.o: $(_dirIcklib)/ickutils.c
	$(CC) -c $(_dirIcklib)/ickutils.c
scrn_init.o: $(_dirScrns)/scrn_init.c
	$(CC) -c $(_dirScrns)/scrn_init.c \
				-I $(_dirIcklib)
clean:
	rm -f *.o
