SDIR=source
IDIR=include
ODIR=obj
LDIR=
BDIR=bin
LIBS= -lGL -lglut -lGLU -lGLEW -lX11

CC=g++
CFLAGS= -g -Wall -ansi -I$(IDIR)

_DEPS = cube.h vsMathLib.h vsShaderLib.h vsResSurfRevLib.h vsResourceLib.h vsLogLib.h drawable.h map.h riverlog.h game.h car.h frog.h	##ADD .h's here
_OBJ = frogger.o vsMathLib.o vsShaderLib.o vsResSurfRevLib.o vsResourceLib.o vsLogLib.o  map.o riverlog.o game.o car.o frog.o			##ADD .o's here


DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

build: frogger

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

frogger: $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LIBS)
	
run: build
	./$(BDIR)/frogger

clean:
	rm -f $(ODIR)/*.o *~ $(SDIR)/*~ $(IDIR)/*~ $(BDIR)/*
