csnake: csnake.c snake.o
	gcc -Wall csnake.c -o csnake snake.o -L. -llistadt -lncurses

snake.o: snake.c
	gcc -Wall snake.c -c -L. -llistadt

clean:
	rm csnake snake.o
