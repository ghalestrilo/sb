
EXEC = ./bin/compiler.exe

SRCF = $(wildcard src/*.cpp)
OBJF = $(patsubst src/%.cpp, obj/%.o, $(SRCF))

# CFLAGS = -std=c++11 -Wall -ansi
GLOBALFLAGS = -std=c++11 

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

clean:
	rm -f obj/*.o

run:
