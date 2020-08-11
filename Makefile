tui-chess.o:
	gcc -c -lncurses src/main.c -o src/tui-chess.o
tui-chess: tui-chess.o
	gcc src/tui-chess.o -lncurses -o tui-chess
clean:
	rm src/*.o
	rm tui-chess