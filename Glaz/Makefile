MAIN = glaz
UTILSSPATH = ../utils
INCUTILSSPATH = $(UTILSSPATH)/include
SRCUTILSSPATH = $(UTILSSPATH)/src
OBJUTILSSPATH = $(UTILSSPATH)/obj
LIBDIRS = -L/usr/X11R6/lib -L/usr/X11R6/lib64 -L/usr/local/lib
INCDIRS = -I/usr/include -I/usr/local/include -I/usr/include/GL -I$(INCUTILSSPATH)
CC = g++
CFLAGS = -Wall -g -O2 $(INCDIRS)
LIBS = -lX11 -lglut -lGLEW -lGL -lGLU -lm
OBJECTS = $(OBJUTILSSPATH)/shaders.o $(OBJUTILSSPATH)/vecmatrix.o $(OBJUTILSSPATH)/obj.o

$(MAIN): $(OBJECTS) $(MAIN).cpp
	@echo Compilation of $(MAIN).cpp...
	$(CC) $(CFLAGS) $(INCDIRS) $(LIBDIRS) $(OBJECTS) $(MAIN).cpp -o $(MAIN) $(LIBS)
	@echo Compilation $(MAIN).cpp complete

$(OBJUTILSSPATH)/shaders.o: $(SRCUTILSSPATH)/shaders.cpp
	$(CC) -O2 -g -c $(CFLAGS) $(INCDIRS) $(LIBDIRS) $(LIBS) $(SRCUTILSSPATH)/shaders.cpp -o $(OBJUTILSSPATH)/shaders.o
	@echo Compilation shaders.cpp complete
$(OBJUTILSSPATH)/vecmatrix.o: $(SRCUTILSSPATH)/vecmatrix.cpp
	$(CC) -O2 -g -c $(CFLAGS) $(INCDIRS) $(LIBDIRS) $(LIBS) $(SRCUTILSSPATH)/vecmatrix.cpp -o $(OBJUTILSSPATH)/vecmatrix.o
	@echo Compilation vecmatrix.cpp complete
$(OBJUTILSSPATH)/obj.o: $(SRCUTILSSPATH)/obj.cpp
	$(CC) -O2 -g -c $(CFLAGS) $(INCDIRS) $(LIBDIRS) $(LIBS) $(SRCUTILSSPATH)/obj.cpp -o $(OBJUTILSSPATH)/obj.o
	@echo Compilation obj.cpp complete

clean:
	rm -f $(MAIN) $(OBJECTS)

