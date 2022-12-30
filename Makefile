# Revelation 2:10
CC=c:\gbdk\bin\lcc
FLAGS=-Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG
C_FILE=main.c
OBJ_FILE=main.o
GAME_FILE=main.gb

main:
	$(CC) $(FLAGS) -o $(GAME_FILE) $(OBJ_FILE)
	$(CC) $(FLAGS) -c -o $(OBJ_FILE) $(C_FILE)