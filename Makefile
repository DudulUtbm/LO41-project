#my general makefile template :: -Wall -Werror -ansi -pedantic -fpic -g
CXX = gcc
CFLAGS = -pthread -std=c99
LIBSDIR = -L. -L/usr/lib
INCLUDEDIR = -I. -I/usr/include


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
$(TARGET): $(EXESOURCEOFILE)
	@echo "\n Generating the executable " $@
	$(CXX) $(CFLAGS) $(EXESOURCEOFILE) -o $(TARGET)

#Generating an object file from a C file having the same name
.c.o:
	@echo "\n Generating " $@ " from " $<
	$(CXX) $(CFLAGS) $(INCLUDEDIR) -c -o $@ $<

#Cleaning the content of the current directory
clean:
	@echo "\n Cleaning temporary files"
	rm -rf *.o *~ *.so *.exe
