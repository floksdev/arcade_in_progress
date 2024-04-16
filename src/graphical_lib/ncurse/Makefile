CC = g++
CFLAGS = -std=c++17 -Wall -fPIC
LIBS = -lncurses
INCLUDE = -I../../

ncurse.so: ncurse_wrapper.cpp ../abstract_graphical_lib.h
	$(CC) $(CFLAGS) $(INCLUDE) -shared -o $@ ncurse_wrapper.cpp $(LIBS)

clean:
	rm -f ncurse.so
