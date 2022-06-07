#makefile
CC=g++
CCFLAGS=-std=c++2a

Templates.o: Templates.cpp
	$(CC) -c Templates.cpp -o Templates.o $(CCFLAGS)

temp.exe: Templates.o
	$(CC) Templates.o -o temp.exe $(CCFLAGS)
run:
	./temp.exe

clean:
	rm *.o *.exe