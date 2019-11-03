/*
 * Implementation 2: C++ version
 */

#include <iostream>
#include <iomanip>
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

    int width = *((int*)(&info[18]));
    int row_width = width;
    while ((row_width * 3) % 4 != 0) {
        row_width++;
    }
    int amount_ignore = row_width - width;
    
    // Header info:
//    int width = *((int*)(&info[18]));
    //if (width % 4 != 0) {
        // Round width up to the nearest number divisible by 4:
      //  width += 4 - (width % 4);
    //}
    while (width % 4 != 0) {
        width++;
    }
    std::cout << "Width * 3: " << width * 3 << std::endl;
    // Round so that 
//    while ((width - (int)info[10]) % 4 != 0) {
//        width += 3;
//    }

//    width += (width % 4);
    int height = *((int*)(&info[22]));
    int starting_address = (int)info[10];
    int r1_end = starting_address + (width * 3);
    int r1_end2 = starting_address + (row_width * 3);
    if (show_header_info) {
        std::cout << "=============HEADER INFO==================\n";
        std::cout << "Size of vector : " << info.size() << std::endl;
        std::cout << "Width : " << width << std::endl;
        std::cout << "Height : " << height << std::endl;
        std::cout << "Starting address of pixels : " << starting_address << std::endl;
        std::cout << "Ignore size: " << amount_ignore << std::endl;
        std::cout << "Address of last pixel in r1: " << "0x" << std::hex << r1_end << std::endl;
        std::cout << "Address of end of r1: " << "0x" << std::hex << r1_end2 << std::endl;
        std::cout << "==========================================\n\n";
    }

    std::vector<Pixel> pixels;
    unsigned char throwaway = 0;

    std::cout << std::dec;

    /*int iteration = 0;
    while (iteration != info.size()) {
        for (int i = 0; i < width; i++) {
            int r, g, b;
            b = info[i];
            g = info[i + 1];
            r = info[i + 2];
//            std::cout << r << " " << g << " " << b << std::endl;
            pixels.push_back(Pixel(r, g, b));
        }
        iteration += width + amount_ignore;
//        std::cout << iteration << std::endl;
    }*/

    for (int i = (int)info[10]; i < info.size(); i += 3) {
        int r, g, b;
        b = info[i];
        g = info[i + 1];
        r = info[i + 2];
        //std::cout << r << " " << g << " " << b << std::endl;
        pixels.push_back(Pixel(r, g, b));
    }

    std::string str = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    float multiplier = (float)(str.length()) / 255.0000; 
    int vector_index = 0;
    int string_index = 0;

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            vector_index = (width * j/*beginning index of containing row*/) + (i % width/*horizontal index in the row*/);
            //std::cout << findex << " ";
            string_index = (int)((float)(pixels[vector_index].get_average() * multiplier)) - 1;
            if (string_index < 0)
                string_index = 0;
//            std::cout << vector_index << " ";
//            std::cout << pixels[vector_index].get_average() << " ";
            std::cout << str[string_index];
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    // Command Format: ./ascii2 [filepath]
    if (argc >= 2) { // Correct Use
        std::string filename(argv[1]);
        read_file(filename);
    }
    else {
        std::cout << argv[0] << ": No input file!\n"
            << "\tUsage: " << argv[0] << " [filename]\n";
        return 1;
    }
    return 0;
}
