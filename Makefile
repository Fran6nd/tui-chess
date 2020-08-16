main.o:
	gcc -g -c src/main.c -o src/main.o
playground.o:
	gcc -g -c src/playground.c -o src/playground.o
tui-chess: main.o playground.o
	gcc -g src/main.o src/playground.o -lncursesw -Lsrc/playground.h -o tui-chess
clean:
	rm src/*.o
	rm tui-chess
