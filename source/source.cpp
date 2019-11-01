
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

    int width = *((int*)(&info[18]));
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
    int width = *((int*)(&info[18]));
    int height = *((int*)(&info[22]));
    unsigned char bpp = info[28]; // *((unsigned char*)&info[28]);
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Bits per Pixel: " << (int)bpp << std::endl;

    std::cout << "Pixels:\n";
    for (auto& i : pixels) {
        i.print();
    }

    std::string str = "`^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            std::cout << str[pixels[(i%width) + (j/height)].get_average() % str.length()];
        }
        std::cout << std::endl;
    }


    return 0;
}
