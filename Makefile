# * set default goal
.DEFAULT_GOAL:=build-obj

# * compiler and options
CC=gcc
CFLAGS=-Wall -Wextra -I$(INCDIR) -L$(OBJDIR)
LIBFLAG=-lm

# * directories
SRCDIR=src
INCDIR=include
OBJDIR=obj
EXEDIR=bin
LIBDIR=lib

# * specific output files
EXE=serve
LIB=libserver.a
_DEPS=cmd.h const.h http.h util.h server.h
DEPS=$(patsubst %,$(INCDIR)/%,$(_DEPS))
_OBJS=main.o cmd.o http.o util.o server.o
OBJS=$(patsubst %,$(OBJDIR)/%,$(_OBJS))

# * rules for object and static library files
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
$(LIBDIR)/$(LIB): $(OBJS)
	ar -rcs $(LIBDIR)/$(LIB) $^

# * compile executable
.PHONY: build
build:
	$(CC) -o $(EXEDIR)/$(EXE) $(SRCDIR)/* $(CFLAGS) $(LIBFLAG)

# * build object files and link them, outputting executable
.PHONY: build-obj
build-obj: $(OBJS)
	$(CC) -o $(EXEDIR)/$(EXE) $^ $(CFLAGS) $(LIBFLAG)

# * build object files, store them in an archive (static library), and link the library, outputting executable
.PHONY: build-lib
build-lib: $(LIBDIR)/$(LIB) $(OBJS)
	$(CC) -o $(EXEDIR)/$(EXE) $< $(CFLAGS) $(LIBFLAG)

# * run using user-inputted args
.PHONY: run
run:
	./$(EXEDIR)/$(EXE) $(ARGS)

# * clean object files, static library files, and executable files
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(EXEDIR)/$(EXE) $(LIBDIR)/$(LIB)

# * compile test files
.PHONY: test
test:
	$(CC) -o $(EXEDIR)/$@ $(FILES) $(CFLAGS)