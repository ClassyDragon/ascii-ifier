
#pragma once

#include <iostream>

class Pixel {
    public:
        Pixel(int r, int g, int b);
        ~Pixel();
        void print();
        int get_average();
    private:
        int r, g, b;
        int average;
};
