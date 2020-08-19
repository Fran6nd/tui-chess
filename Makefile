main.o:
	gcc -g -c src/main.c -o src/main.o
playground.o:
	gcc -g -c src/playground.c -o src/playground.o
position.o:
	gcc -g -c src/position.c -o src/position.o
piece.o:
	gcc -g -c src/piece.c -o src/piece.o
movement.o:
	gcc -g -c src/movement.c -o src/movement.o
tui-chess: main.o playground.o position.o movement.o piece.o
	gcc -g -lncurses -Isrc/ src/main.o src/playground.o src/position.o src/piece.o src/movement.o -o tui-chess
clean:
	rm src/*.o
	rm tui-chess