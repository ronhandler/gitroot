SRCDIR=./src
OBJDIR=./obj
BINDIR=./build
EXECUTABLE=temp.exe
SOURCES=\
	main.cpp\

LIBS=\

CC=g++
CFLAGS=-g -c -Wall -Werror\

LDFLAGS=-g\

VPATH=$(OBJDIR) $(SRCDIR) $(BINDIR)
TEMPOBJECTS=$(SOURCES:.cpp=.o)
OBJECTS=$(TEMPOBJECTS:%=$(OBJDIR)/%)

all: $(SOURCES) $(EXECUTABLE)
# Create unlinked objects.
.cpp.o:
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@ 
# Link compiled objects.
$(EXECUTABLE): $(TEMPOBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINDIR)/$@ \
	  $(LIBS)

.PHONY: wipe clean
wipe : clean
	rm -f $(BINDIR)/$(EXECUTABLE)
clean :
	rm -f $(OBJDIR)/*.o

