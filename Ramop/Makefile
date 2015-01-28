SRCDIR=./src
OBJDIR=./obj
BINDIR=./build
EXECUTABLE=temp.exe
SOURCES=\
	main.cpp\
	application_handler.cpp\
	entity_handler.cpp\
	shader_handler.cpp\
	time_handler.cpp\
	path_handler.cpp\

LIBS=\
	`sdl2-config --libs`\
	-mwindows\
	-lboost_system\
	-lboost_filesystem\
	-lglew32\
	-lopengl32\
	-lglu32\

CC=g++
CFLAGS=-g -c -Wall -Werror\
	`sdl2-config --cflags`\

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

