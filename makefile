LIBS=-lpng -lm -lstdc++ -lsfml-system -lsfml-window -lsfml-graphics
CFLAGS=-c -Wall -std=c++11
CC=$(CROSS)g++

SRCS=src/main.cpp\
     src/Fractal.cpp\
     src/Mandelbrot.cpp\
     src/Julia.cpp\
     src/Gradient.cpp
OBJ=$(subst src/,output/, $(subst .cpp,.o, $(SRCS)))

all: createdirs mandelbrot

createdirs:
	@mkdir -p .d
	@mkdir -p output

mandelbrot: $(OBJ)
	$(CC) -o mandelbrot output/*.o $(LIBS)

output/%.o: src/%.cpp .d/%.d
	$(CC) $(CFLAGS) $< -o $@

.d/%.d: src/%.cpp
	@$(CC) $(CFLAGS) -MM $< -MF $@

clean:
	rm -f output/*.o
	rm -f mandelbrot

re: clean mandelbrot

install:
	cp ./mandelbrot /usr/bin/mandelbrot
remove:
	rm -f /usr/bin/mandelbrot

.PHONY: clean

-include $(OBJECTS:%.o=.d/%.d)
-include $(LOBJECTS:%.o=.d/%.d)
