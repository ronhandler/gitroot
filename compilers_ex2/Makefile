SRCDIR=./src
OBJDIR=./obj
BINDIR=./build
EXECUTABLE=a.out
SOURCES=\
	main.c\

LIBS=\

CC=gcc
CFLAGS=-g -c -Wall -Werror -pedantic -std=c11\

LDFLAGS=-g\

VPATH=$(OBJDIR) $(SRCDIR) $(BINDIR)
TEMPOBJECTS=$(SOURCES:.c=.o)
OBJECTS=$(TEMPOBJECTS:%=$(OBJDIR)/%)

all: $(SOURCES) $(EXECUTABLE)
# Create unlinked objects.
.c.o:
	$(CC) $(CFLAGS) $< -o $(OBJDIR)/$@ 
# Link compiled objects.
$(EXECUTABLE): $(TEMPOBJECTS)
	bison -d $(SRCDIR)/parser.y -o $(SRCDIR)/parser.tab.c
	$(CC) $(SRCDIR)/parser.tab.c $(SRCDIR)/lexer.c -o $(BINDIR)/parser
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(BINDIR)/$@ $(LIBS)

.PHONY: wipe clean
wipe : clean
	rm -f $(BINDIR)/$(EXECUTABLE) $(BINDIR)/parser
clean :
	rm -f $(SRCDIR)/parser.tab* $(OBJDIR)/*.o

