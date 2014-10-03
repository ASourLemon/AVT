SDIR=source
IDIR=include
ODIR=obj
LDIR=
BDIR=bin
LIBS= -lGL -lglut -lGLU -lGLEW -lX11

CC=g++
CFLAGS= -g -Wall -ansi -I$(IDIR)

_DEPS = cube.h		##ADD .h's here
_OBJ = exercise1.o 	##ADD .o's here


DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

exercise1: $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LIBS)

run: exercise1
	./$(BDIR)/exercise1

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~ $(BDIR)/*
