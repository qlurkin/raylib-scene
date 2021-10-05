CC=clang++
RAYLIB=../raylib
LIBRAYLIB=$(RAYLIB)/src/libraylib.a
RAYLIBINCLUDE=$(RAYLIB)/src
CFLAGS=-I$(RAYLIBINCLUDE) -O3 -std=c++17
FRAMEWORK = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
DEPS = Cube.h Object.h
OBJ = main.o Object.o Cube.o

app: $(OBJ)
	$(CC) $(CFLAGS) $(FRAMEWORK) -o $@ $^ $(LIBRAYLIB)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o

mrproper: clean
	rm -f app
