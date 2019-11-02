/*
 * Implementation 2: C++ version
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Pixel.h"

static const bool show_header_info = true;

void read_file(std::string& filename) {
    // Open input file in binary mode:
    std::ifstream data(filename, std::ios_base::binary);
    data >> std::noskipws;
    if (data.fail()) {
        std::cout << "Could not open " << filename << "." << std::endl;
        exit (1);
    }

    // Store each byte (char) in a vector:
    std::vector<unsigned char> info;
    unsigned char temp;
    while (!data.eof()) {
        data >> temp;
        info.push_back(temp);
    }
    data.close();

    //
    int width = *((int*)(&info[18])); 
    int height = *((int*)(&info[22]));
    if (show_header_info) {
        std::cout << "=============HEADER INFO==================\n";
        std::cout << "Size of vector : " << info.size() << std::endl;
        std::cout << "Width : " << width << std::endl;
        std::cout << "Height : " << height << std::endl;
        std::cout << "Starting address of pixels : " << (int)info[10] << std::endl;
        std::cout << "==========================================\n\n";
    }

    std::vector<Pixel> pixels;
    for (int i = 122; i < info.size(); i += 3) {
        int r, g, b;
        b = info[i];
        g = info[i + 1];
        r = info[i + 2];
        pixels.push_back(Pixel(r, g, b));
    }

    std::string str = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    float multiplier = (float)(str.length()) / 255.0000; 
    int index = 0;

    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0 ; j < width; j++) {
            index = (int)((float)(pixels[(width * (i % width)) + (j % height)].get_average() * multiplier)) - 1;
            if (index < 0)
                index = 0;
            std::cout << str[index];
        }
        std::cout << std::endl;
    }

}

int main() {
    std::cout << "Filename: ";
    std::string filename;
    getline(std::cin, filename);
    read_file(filename);
    return 0;
}
