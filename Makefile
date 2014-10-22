SDIR=source
IDIR=include
ODIR=obj
LDIR=
BDIR=bin
LIBS= -lGL -lglut -lGLU -lGLEW -lX11

CC=g++
CFLAGS= -g -std=c++11 -Wall -ansi -I$(IDIR)

OUT_DIRS= obj bin
_DEPS = *.h	##ADD .h's here
_OBJ = frogger.o light.o vsMathLib.o vsShaderLib.o vsResSurfRevLib.o vsResourceLib.o vsLogLib.o  map.o riverlog.o game.o car.o frog.o			##ADD .o's here


DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

init:
	mkdir -p $(OUT_DIRS)

build: init frogger

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

frogger: $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LIBS)
	
run: build
	./$(BDIR)/frogger

clean:
	rm -f $(SDIR)/*~ $(IDIR)/*~
	rm -r $(OUT_DIRS)
