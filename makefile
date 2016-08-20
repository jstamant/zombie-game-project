# Refer to this makefile tutorial for further help:
#     http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC = g++
CFLAGS = -Wall

DEPS = main.h character.h defines.h
OBJ = main.o character.o

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o sfml-app.out -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $a -c $< $(DEPS)
 
clean:
	rm *.o
