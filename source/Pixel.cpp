
#include "Pixel.h"

Pixel::Pixel(int r, int g, int b) : r(r), g(g), b(b) {
    average = (r + g + b) / 3;
}

Pixel::~Pixel() {
}

void Pixel::print() {
    std::cout << r << " " << g << " " << b << std::endl;
}

int Pixel::get_average() {
    return average;
}
