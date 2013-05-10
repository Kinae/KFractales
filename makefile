CC=g++

ifdef DEBUG 
	CFLAGS= -ansi -W -g    
else
	CFLAGS= -ansi -W  
endif

LFLAGS= -lsfml-graphics -lsfml-system -lsfml-window	

BINDIR=bin/
OBJDIR=obj/
SRCDIR=src/

EXEC=$(BINDIR)KFractales
OBJ=$(OBJDIR)main.o $(OBJDIR)mandelbrot.o 

all: $(EXEC)

$(BINDIR)KFractales:	$(OBJ)
											$(CC) -o $@ $^ $(LFLAGS)

$(OBJDIR)mandelbrot.o:	$(SRCDIR)mandelbrot.cpp $(SRCDIR)mandelbrot.h
											  $(CC) -o $@ -c $< $(CFLAGS)

$(OBJDIR)main.o: $(SRCDIR)main.cpp $(SRCDIR)mandelbrot.h $(OBJDIR)mandelbrot.o
								 $(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean: 
	rm -rf $(OBJDIR)*.o

mrproper: clean
	rm -rf $(EXEC)
