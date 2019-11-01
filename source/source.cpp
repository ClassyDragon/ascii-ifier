
#include <iostream>
#include <vector>
#include "Pixel.h"

static bool debug_mode = true;

void Debug_Log(std::string message) {
    if (debug_mode) {
        std::cout << message << std::endl;
    }
}

void read_bitmap(const char* filename, unsigned char info[], std::vector<Pixel>& pixels, unsigned char* data) {
    FILE* pfile = fopen(filename, "rb"); // Open bitmap in read binary mode.
    if (pfile == NULL) { // Exit program if file is not found.
        std::cout << "Could not open file: " << filename << std::endl;
    }
    // Check that file is a bitmap:
    std::string s(filename);
    if (s.size() < 4) {
        std::cout << "File is not a bitmap image." << std::endl;
        exit(1);
    }
    if (s.substr(s.size() - 4, 4) != ".bmp") {
        std::cout << "File is not a bitmap image." << std::endl;
        exit(1);
    }

    /*
     * fread usage: fread(void* ptr, size_t size, size_t count, FILE* file)
     * void* ptr: pointer to block of memory to write to, converted to void* type.
     * size_t size: Size of each element.
     * sizez_t count: number of elements.
     * FILE* file: File stream to read from.
     */
    fread(info, sizeof(unsigned char), 122, pfile);

    int width = *((int*)(&info[18])) + 1;
    int height = *((int*)(&info[22]));
    int size = 3 * width * height;

    data = new unsigned char[size];
    fread(data, sizeof(unsigned char), size, pfile);

    int r, g, b;
    for (int i = 0; i < size; i += 3) {
        b = data[i];
        g = data[i + 1];
        r = data[i + 2];
        pixels.push_back(Pixel(r, g, b));
    }

    fclose(pfile);
}

void display_data(const char* filename) {
}

int main(int argc, char** argv) {
    unsigned char info[122];
    std::vector<Pixel> pixels;
    unsigned char* data;
    if (argc >= 2) {
        read_bitmap(argv[1], info, pixels, data);
    }
    else {
        std::cout << "ascii_ifier: No input file!\n"
            << "\tUsage: ascii_ifier <filename>\n";
        return 1;
    }

    /*
     * The width is a 4-byte value stored at offset 18.
     * The height is a 4-byte value stored at offset 22.
     */
    int width = *((int*)(&info[18])) + 1;
    int height = *((int*)(&info[22]));
    unsigned char bpp = info[28]; // *((unsigned char*)&info[28]);
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Bits per Pixel: " << (int)bpp << std::endl;

    std::cout << "Pixels:\n";
    for (int i = 0; i < pixels.size(); i++) {
        std::cout << "#: " << i << " ";
        pixels[i].print();
    }

    std::cout << "Number of Pixels: " << pixels.size() << std::endl;
    std::string str = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    int index = 0;
    float multiplier = (float)(str.length()) / 255.0000; 
    std::cout << "Length of String: " << str.length() << std::endl;
    std::cout << "Multiplier: " << multiplier << std::endl;
    /*for (int i = 0; i < width; i++) {
        for (int j = height - 1; j > 0; j--) {
            index = (int)((float)(pixels[(width * (i % width)) + (j % height)].get_average() * multiplier)) - 1;
            if (index < 0)
                index = 0;
//            std::cout << "Index: " << index << std::endl;
            std::cout << str[index];
        }
        std::cout << std::endl;
    }
    */
    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0 ; j < width; j++) {
            index = (int)((float)(pixels[(width * (i % width)) + (j % height)].get_average() * multiplier)) - 1;
            if (index < 0)
                index = 0;
            std::cout << str[index];
        }
        std::cout << std::endl;
    }


    return 0;
}
