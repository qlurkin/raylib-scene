DEPS = Cube.h Object.h
OBJ = main.o Object.o Cube.o

PLATFORM_OS=BSD
ifeq ($(OS),Windows_NT)
   PLATFORM_OS=WINDOWS
   RAYLIB=C:/raylib/raylib
   LIBRAYLIB=$(RAYLIB)/
   RAYLIBINCLUDE=-I. -I$(RAYLIB)/src -I$(RAYLIB)/src/external
   CC=C:/raylib/mingw/bin/g++
   CFLAGS=-Wall -Wno-missing-braces -s -O3 -std=c++17 $(RAYLIBINCLUDE)
   LIBRAYLIB=-L. -L$(RAYLIB)/src -lraylib -lopengl32 -lgdi32 -lwinmm C:/raylib/raylib/src/raylib.rc.data
else
   UNAMEOS=$(shell uname)
   ifeq ($(UNAMEOS),Darwin)
      PLATFORM_OS=OSX
      RAYLIB=../raylib
      CC=clang++
      LIBRAYLIB=$(RAYLIB)/src/libraylib.a -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
      RAYLIBINCLUDE=-I$(RAYLIB)/src
      CFLAGS=-O3 -std=c++17 $(RAYLIBINCLUDE)
   endif
   ifeq ($(UNAMEOS),Linux)
      PLATFORM_OS=LINUX
   endif
endif

app: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBRAYLIB)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o

mrproper: clean
	rm -f app
