CC = g++
CFLAGS = -std=c++17 -Wall
LIBS = -ldl

core: main.cpp
	$(CC) $(CFLAGS) main.cpp -o arcade $(LIBS)
	mv arcade ../../

clean:
	rm -f arcade
