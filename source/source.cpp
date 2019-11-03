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

    int starting_address = (int)info[10];
    int width = *((int*)(&info[18]));
    int row_width = width;
    if (width % 4 != 0) {
        int temp = row_width * 3;
        //while (((row_width * 3) + starting_address) % 4 != 0) {
        while (temp % 4 != 0) {
            row_width++;
            temp++;
        }
    }
    int amount_ignore = (row_width - width) * 1;
    int height = *((int*)(&info[22]));
    int r1_end = starting_address + (width * 3);
    int r1_end2 = starting_address + (row_width * 3);
    int bpp = *((int*)(&info[28]));
    if (show_header_info) {
        std::cout << "=============HEADER INFO==================\n";
        std::cout << "Size of vector : " << info.size() << std::endl;
        std::cout << "Width : " << width << std::endl;
        std::cout << "Height : " << height << std::endl;
        std::cout << "Bits per pixel: " << bpp << std::endl;
        std::cout << "Row Width : " << row_width << std::endl;
        std::cout << "Starting address of pixels : " << starting_address << std::endl;
        std::cout << "Ignore size: " << amount_ignore << std::endl;
        std::cout << "Address of last pixel in r1: " << "0x" << std::hex << r1_end << std::endl;
        std::cout << "Address of end of r1: " << "0x" << std::hex << r1_end2 << std::endl;
        std::cout << "==========================================\n\n";
    }

    std::vector<Pixel> pixels;
    unsigned char throwaway = 0;

    std::cout << std::dec;

    int iteration = 0;
    while (iteration < info.size() - starting_address - 1) {
        for (int i = 0; i < width * 3; i += 3) {
            int r, g, b;
            b = info[i + iteration + starting_address];
            g = info[i + 1 + iteration + starting_address];
            r = info[i + 2 + iteration + starting_address];
            pixels.push_back(Pixel(r, g, b));
        }
        iteration += (width * 3) + amount_ignore;
    }

    std::string str = " ^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    float multiplier = (float)(str.length()) / 255.0000; 
    int vector_index = 0;
    int string_index = 0;

    for (int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            vector_index = (width * j/*beginning index of containing row*/) + (i % width/*horizontal index in the row*/);
            string_index = (int)((float)(pixels[vector_index].get_average() * multiplier)) - 1;
            if (string_index < 0)
                string_index = 0;
            std::cout << str[string_index];
        }
        std::cout << std::endl;
    }
    if (show_header_info) {
        std::cout << std::dec;
        std::cout << "=============HEADER INFO==================\n";
        std::cout << "Size of vector : " << info.size() << std::endl;
        std::cout << "Width : " << width << std::endl;
        std::cout << "Height : " << height << std::endl;
        std::cout << "Bits per pixel: " << bpp << std::endl;
        std::cout << "Row Width : " << row_width << std::endl;
        std::cout << "Starting address of pixels : " << starting_address << std::endl;
        std::cout << "Number of pixels: " << pixels.size() << std::endl;
        std::cout << "Ignore size: " << amount_ignore << std::endl;
        std::cout << "Address of last pixel in r1: " << "0x" << std::hex << r1_end << std::endl;
        std::cout << "Address of end of r1: " << "0x" << std::hex << r1_end2 << std::endl;
        std::cout << "Testing: " << info.size() - starting_address << std::endl;
        std::cout << "==========================================\n\n";
    }
}

int main(int argc, char** argv) {
    // Command Format: ./ascii2 [filepath]
    if (argc >= 2) { // Correct Use
        std::string filename(argv[1]);
        read_file(filename);
    }
    else {
        std::cout << "==========ASCII-ifier by Caleb Geyer==========" << std::endl
            << "| Note: To run from command line: ./ascii-ifier <filepath>" << std::endl
            << "|\n"
            << "| Input a filepath. This program supports .bmp images in\n"
            << "| 24 bits per pixel format.\n";
        std::string filepath;
        getline(std::cin, filepath);
        read_file(filepath);
    }
    return 0;
}
