CC=g++
CFLAGS=-Wall

all: init destroy set check

init: init.cpp
 $(CC) $(CFLAGS) -o init init.cpp -lrt

destroy: destroy.cpp
 $(CC) $(CFLAGS) -o destroy destroy.cpp -lrt

set: set.cpp
 $(CC) $(CFLAGS) -o set set.cpp -lrt

check: check.cpp
 $(CC) $(CFLAGS) -o check check.cpp -lrt

clean:
 rm -f init destroy set check
