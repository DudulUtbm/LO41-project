#my general makefile template :: -Wall -Werror -ansi -pedantic -fpic -g
CXX = gcc
CFLAGS = -pthread -std=c99 -g
LIBSDIR = -L. -L/usr/lib
INCLUDEDIR = -I. -I/usr/include

#Library-related macros
LIBTARGET = vehicule
LIBTARGETCFILE = $(LIBTARGET:=.c)
LIBTARGETOFILE = $(LIBTARGET:=.o)
LIBTARGETAFILE = $(LIBTARGET:=.a)

LIBTARGET2 = echangeur
LIBTARGET2CFILE = $(LIBTARGET2:=.c)
LIBTARGET2OFILE = $(LIBTARGET2:=.o)
LIBTARGET2AFILE = $(LIBTARGET2:=.a)

#Application-related macros
TARGET = LO41_project.exe
EXESOURCE = main
EXESOURCECFILE = $(EXESOURCE:=.c)
EXESOURCEOFILE = $(EXESOURCE:=.o)

#Running the program
run: $(TARGET)
	@echo "\n Executing the executable " $(TARGET)
	./$(TARGET)

#Generating the executable
$(TARGET): $(EXESOURCEOFILE) $(LIBTARGETAFILE) $(LIBTARGET2AFILE)
	@echo "\n Generating the executable " $@
	$(CXX)  $(EXESOURCEOFILE) $(LIBTARGETAFILE) $(LIBTARGET2AFILE) -o $(TARGET) $(CFLAGS)

#Generating library
$(LIBTARGETAFILE) : $(LIBTARGETOFILE)
	@echo "\n Generating the library " $@
	ar -q $(LIBTARGETAFILE) $(LIBTARGETOFILE)

$(LIBTARGET2AFILE) : $(LIBTARGET2OFILE)
	@echo "\n Generating the library " $@
	ar -q $(LIBTARGET2AFILE) $(LIBTARGET2OFILE)


#Generating an object file from a C file having the same name
.c.o:
	@echo "\n Generating " $@ " from " $<
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

#Cleaning the content of the current directory
clean:
	@echo "\n Cleaning temporary files"
	rm -rf *.o *~ *.swp *.exe *.a
