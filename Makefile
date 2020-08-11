tui-chess.o:
	gcc -c src/main.c -o src/tui-chess.o
tui-chess: tui-chess.o
	gcc src/tui-chess.o -lncursesw -o tui-chess
clean:
	rm src/*.o
	rm tui-chess