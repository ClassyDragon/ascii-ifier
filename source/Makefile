
ascii-ifier : source.o source1.o Pixel.o
	g++ source.o Pixel.o -o ascii1
	g++ source1.o Pixel.o -o ascii2

source.o : source.cpp Pixel.o
	g++ source.cpp -c -o source.o

source1.o : source1.cpp Pixel.o
	g++ source1.cpp -c -o source1.o

Pixel.o : Pixel.h Pixel.cpp
	g++ Pixel.cpp -c -o Pixel.o
