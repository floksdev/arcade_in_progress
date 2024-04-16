CC = g++
CFLAGS = -std=c++17 -Wall -fPIC
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
INCLUDE = -I../../

sfml.so: sfml_wrapper.cpp ../abstract_graphical_lib.h
	$(CC) $(CFLAGS) $(INCLUDE) -shared -o $@ sfml_wrapper.cpp $(LIBS)

clean:
	rm -f sfml.so
