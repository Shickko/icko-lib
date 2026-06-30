## Example-01
A simple showcase of ickutils & ickclock's usages.

## Dependencies
assuming you are in a linux environment with gcc & ncurses installed.
  Arch:     `$ sudo pacman -S gcc ncurses`
  Ubuntu:   `$ sudo apt-get install gcc ncurses-bin`
### Compiling the program
either using the makefile provided directly throught `$ make` or manually compile the executable
`gcc -c ./libs/icklib/ickclock.c
 gcc -c ./libs/icklib/ickutils.c
 gcc -c ./libs/scrns/scrn_init.c -I ./libs/icklib
 gcc -c main.c -I ./libs/icklib/ -I ./libs/scrns
 gcc -o executable main.o ickclock.o ickutils.o scrn_init.o -lncurses`
