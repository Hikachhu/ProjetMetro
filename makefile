CFLAGS=-Wall -lncursesw -lm -lpthread
CC=gcc 
OBJS=obj
EXE=SimulateurCompile


$(OBJS)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -o $@ -c -g $< $(CFLAGS)
all: $(OBJS)/Train.o $(OBJS)/ListeChainee.o $(OBJS)/TourParTour.o $(OBJS)/Affichage.o $(OBJS)/main.o 
	gcc -o $(EXE) $(OBJS)/Train.o $(OBJS)/ListeChainee.o $(OBJS)/TourParTour.o $(OBJS)/Affichage.o $(OBJS)/main.o $(CFLAGS)
clean:
	rm $(OBJS)/*.o
exec:
	./$(EXE)
	reset
help:
	@echo "all -> compilation du projet\nclean-> supprime les .o\nexec -> execute le projet compilé\n"
debug:
	@gdb ./$(EXEC)