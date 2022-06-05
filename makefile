all : exec
	./exec
	rm -f *.o
	rm exec
main.o: main.c game.h 
	gcc -c main.c -o main.o
game.o: game.c game.h
	gcc -c game.c -o game.o
exec: main.o game.o
	gcc main.o game.o -o exec
