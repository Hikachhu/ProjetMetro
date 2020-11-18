CFLAGS=-Wall -lncursesw -lm -lpthread
CC=gcc 
EXE=SimulateurCompile
INCLUDE=Includes

SRC  := $(wildcard src/*/*.c) main.c
OBJS := $(patsubst src/%.c, obj/%.o, $(SRC))

.PHONY: all
all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(CFLAGS) -I $(INCLUDE)

obj/%.o: src/%.c
	$(CC) -o $@ -c -g $^ $(CFLAGS)

TEST:
	@echo $(SRC)
	@echo $(OBJS)

clean:
	rm obj/*/*.o

exec:
	./$(EXE)
	reset

help:
	@echo "all -> compilation du projet\nclean-> supprime les .o\nexec -> execute le projet compilé\n"

debug:
	@gdb ./$(EXEC)