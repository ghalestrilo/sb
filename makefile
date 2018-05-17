
EXECNAME = bin/compiler.exe
ifeq ($(OS), Windows_NT)
	EXEC = $(EXECNAME)
else
	EXEC = ./$(EXECNAME)
endif

SRCF = $(wildcard src/*.cpp)
OBJF = $(patsubst src/%.cpp, obj/%.o, $(SRCF))

# GDB = -g -ggdb
# CFLAGS = -std=c++11 -Wall -ansi
GLOBALFLAGS = -std=c++11 $(GDB)

LFLAGS = -Wall $(GLOBALFLAGS)
CFLAGS = -Wall $(GLOBALFLAGS)
LFLAGS = -Wall $(GLOBALFLAGS)


PROG_OP     = -o
PROG_INPUT  = ./res/bin
PROG_OUTPUT = ./res/bin_res
PROG_ARGS   = $(PROG_OP) $(PROG_INPUT) $(PROG_OUTPUT)

all: clean build run

run:
	$(EXEC) $(PROG_ARGS)

build: $(OBJF)
	g++ $^ -o $(EXEC)

obj/%.o: 
	g++ $(patsubst obj/%.o, src/%.cpp, $@) $(CFLAGS) -c -o $@ 

ifeq ($(OS), Windows_NT)
clean:
	cls
	rd /s /q "obj"
	mkdir "obj"
else
clean:
	rm -f obj/*.o
endif
run:

