
ascii-ifier : source.o Pixel.o
	g++ source.o Pixel.o -o ascii-ifier

source.o : source.cpp Pixel.o
	g++ source.cpp -c -o source.o

Pixel.o : Pixel.h Pixel.cpp
	g++ Pixel.cpp -c -o Pixel.o
