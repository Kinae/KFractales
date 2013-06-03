CC=g++

ifdef DEBUG 
	CFLAGS= -ansi -W -g    
else
	CFLAGS= -ansi -W -g
endif

LFLAGS= -lsfml-graphics -lsfml-system -lsfml-window	

BINDIR=bin/
OBJDIR=obj/
SRCDIR=src/

EXEC=$(BINDIR)KFractales
OBJ=$(OBJDIR)main.o $(OBJDIR)fractale.o $(OBJDIR)processor.o $(OBJDIR)mandelbrot_processor.o $(OBJDIR)juliaset_processor.o

all: $(EXEC)

$(BINDIR)KFractales:	$(OBJ)
											$(CC) -o $@ $^ $(LFLAGS)

$(OBJDIR)processor.o:	$(SRCDIR)processor.cpp $(SRCDIR)processor.h
											  $(CC) -o $@ -c $< $(CFLAGS)

$(OBJDIR)fractale.o:	$(SRCDIR)fractale.cpp $(SRCDIR)fractale.h $(SRCDIR)mandelbrot_processor.h $(SRCDIR)juliaset_processor.h
											  $(CC) -o $@ -c $< $(CFLAGS)
											  
$(OBJDIR)mandelbrot_processor.o:	$(SRCDIR)mandelbrot_processor.cpp $(SRCDIR)mandelbrot_processor.h $(SRCDIR)processor.h
											  $(CC) -o $@ -c $< $(CFLAGS)
											  
$(OBJDIR)juliaset_processor.o:	$(SRCDIR)juliaset_processor.cpp $(SRCDIR)juliaset_processor.h $(SRCDIR)processor.h
											  $(CC) -o $@ -c $< $(CFLAGS)

$(OBJDIR)main.o: $(SRCDIR)main.cpp $(SRCDIR)fractale.h $(OBJDIR)fractale.o
								 $(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean: 
	rm -rf $(OBJDIR)*.o

mrproper: clean
	rm -rf $(EXEC)
