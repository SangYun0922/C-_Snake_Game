CC = g++
CFLAGS = -c
TARGET = main_exe
$(TARGET) : SnakeGame.o main.o
	$(CC) -o  main_exe SnakeGame.o main.o -lncurses
main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp -lncurses
SnakeGame.o : SnakeGame.cpp
	$(CC) $(CFLAGS) SnakeGame.cpp -lncurses
clean :
	rm *.o main_exe
