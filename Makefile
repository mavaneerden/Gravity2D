PROGNAME = main
SRCFILES = main.cpp screen.cpp color.cpp vec2.cpp vertex.cpp body.cpp mouse.cpp

CC = g++

WARNFLAGS = -Wall -pedantic-errors -std=c++17
CFLAGS = -g -O2 $(WARNFLAGS) -Iinclude/
LDFLAGS= -lGL -lglut -lGLEW

# Do some substitution to get a list of .o files from the given .cpp files.
OBJFILES = $(patsubst %.cpp,%.o,$(SRCFILES))

.PHONY: all run clean

all: $(PROGNAME)

$(PROGNAME): $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -fv $(PROGNAME) *.o