
EXECNAME = bin/compiler.exe
ifeq ($(OS), Windows_NT)
	EXEC = $(EXECNAME)
else
	EXEC = ./$(EXECNAME)
endif

SRCF = $(wildcard src/*.cpp)
OBJF = $(patsubst src/%.cpp, obj/%.o, $(SRCF))

GDB = -g -ggdb
# CFLAGS = -std=c++11 -Wall -ansi
GLOBALFLAGS = -std=c++11 $(GDB)

LFLAGS = -Wall $(GLOBALFLAGS)
CFLAGS = -Wall $(GLOBALFLAGS)
LFLAGS = -Wall $(GLOBALFLAGS)


OP     = p
PROG_INPUT  = ./res/bin
PROG_OUTPUT = ./res/out/bin_res
PROG_ARGS   = -$(OP) $(PROG_INPUT) $(PROG_OUTPUT)

all: clean build run

run:
	$(EXEC) $(PROG_ARGS)

build: $(OBJF)
	g++ $^ -o $(EXEC)

obj/%.o: 
	g++ $(patsubst obj/%.o, src/%.cpp, $@) $(CFLAGS) -c -o $@ 

ifeq ($(OS), Windows_NT)
clean:
	rd /s /q "obj"
	mkdir "obj"

clearscreen:
	cls
else
clean:
	rm -f obj/*.o

clearscreen:
	clear
endif
run:

