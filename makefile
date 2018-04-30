

SRCF = $(wildcard src/*.cpp)
OBJF = $(patsubst $(SRCF)/%.cpp, obj/%.o, $(SRCF))

all: build

build: $(OBJF)
	gcc $(OBJF) -o bin/compiler.exe

%.o: $(patsubst obj/%.o, src/%.cpp, $@)
	gcc -c $(patsubst obj/%.o, src/%.cpp, $@) -o -Wall -ansi


run:
