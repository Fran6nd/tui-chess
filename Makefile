main.o:
	gcc -c src/main.c -o src/main.o
playground.o:
	gcc -c src/playground.c -o src/playground.o
tui-chess: main.o playground.o
	gcc src/main.o src/playground.o -lncurses -Lsrc/playground.h -o tui-chess
clean:
	rm src/*.o
	rm tui-chess