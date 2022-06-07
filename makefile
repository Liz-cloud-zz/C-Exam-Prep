# This is a Makefile comment

# Declare some variables to help construct our compile command
CC=g++         # the compiler
LIBS=-std=c++2a   # the libraries we will ref

# Follow convention to add other topics' examples.
# compiles all .cpp files in the directory to correspondingly named .o files and links to .exe files.

#SRCS    = $(wildcard *.cpp)
#OBJS    = ${SRCS:.cpp=.o}
#
#.PHONY: all
#all: $(patsubst %.o,%,$(OBJS))
#%.o: %.cpp
#	$(CC) -c $< -o $@ && $(CC) $@ -o $(addsuffix .exe $(basename $@ .o))

#SRC_FILES := $(wildcard *.cpp)
#OBJ_FILES := $(patsubst %.cpp,%.o,$(SRC_FILES))
#test: $(OBJ_FILES)
#	$(CC) -o $@ $^ #&& $(CC) $@ -o $(addsuffix .exe $(basename $@ .o))

ExamPractice: ExamPractice.cpp
	$(CC) -c ExamPractice.cpp $(LIBS) && $(CC) ExamPractice.o -o ExamPractice.exe $(LIBS)

inheritance: Inheritance.cpp
	$(CC) -c Inheritance.cpp $(LIBS) && $(CC) Inheritance.o -o Inheritance.exe && ./Inheritance.exe

pointers: pointers.cpp
	$(CC) -c pointers.cpp $(LIBS) && $(CC) pointers.o -o pointers.exe && ./pointers.exe

playground: playground.cpp
	$(CC) -c playground.cpp $(LIBS) && $(CC) playground.o -o playground.exe && ./playground.exe

containers: containers.cpp
	$(CC) -c containers.cpp $(LIBS) && $(CC) containers.o -o containers.exe && ./containers.exe

operatorOverloading: operatorOverloading.cpp
	$(CC) -c operatorOverloading.cpp $(LIBS) && $(CC) operatorOverloading.o -o operatorOverloading.exe && ./operatorOverloading.exe

raii: raii.cpp
	$(CC) -c raii.cpp $(LIBS) && $(CC) raii.o -o raii.exe && ./raii.exe

templates: templates.cpp
	$(CC) -c templates.cpp $(LIBS) && $(CC) templates.o -o templates.exe && ./templates.exe


all: pointers inheritance ExamPractice containers playground
	@echo "Targets ran:" $^;

# deletes all the object code files
clean:
	@rm -f *.o
	@rm *.exe

# copies/moves the relevant binaries and/or libraries to the correct folders
run: default
	./ExamPractice.exe $ARGS
