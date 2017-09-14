CPP=gcc
OBJECTS=bitmapG.o
BINS=usaBitmapG

CPPFLAGS=-Wall -O9 -g -DNDEBUG
DEST=.

%.o: %.c
	$(CPP) $(CPPFLAGS) -c $< -o $@

all: bin

bin: $(OBJECTS) $(BINS)

usaBitmapG:
	gcc $(CPPFLAGS) -o $(DEST)/usaBitmapG usaBitmapG.c $(OBJECTS) -lm

clean:
	rm -f $(OBJECTS) $(BINS)
	cd $(DEST); rm -f *.a $(BINS)
