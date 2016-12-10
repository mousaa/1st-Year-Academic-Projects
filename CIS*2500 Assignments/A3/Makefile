all: program 

program: src/checkFile.c src/checkWindow.c src/curses.c src/main.c src/parsing.c src/playerMove.c src/userInterface.c src/endMsg.c src/enemyMove.c src/combat.c
	gcc -lncurses src/checkFile.c src/checkWindow.c src/curses.c src/main.c src/parsing.c src/playerMove.c src/userInterface.c src/endMsg.c src/enemyMove.c src/combat.c -Iinclude -Wall -std=c99 

run: program         
	./a.out assets/level.txt