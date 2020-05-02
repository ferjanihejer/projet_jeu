prog:main.o enig.o 
	gcc main.o enig.o -o prog -lSDL -lSDL_ttf -lSDL_mixer -lSDL_image -g
main.o:main.c
	gcc -c main.c -g
enig.o:enig.c
	gcc -c enig.c -g

