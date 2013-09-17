# JelGamal Makefile
# JB Gericke

IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) -static -L $(LDIR) -std=c99 -pedantic -Wall -Wpointer-arith -Wstrict-prototypes -O2

ODIR=obj
LDIR =../lib

LIBS=-lbigdigits

_DEPS = jelgamal.h jelcrypt.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = jelgamal.o jelcrypt.o jeldriver.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

jelgamal: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

jelcrypt: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

jeldriver: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
