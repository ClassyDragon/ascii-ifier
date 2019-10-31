
#include <iostream>

static bool debug_mode = true;

void Debug_Log(std::string message) {
    if (debug_mode) {
        std::cout << message << std::endl;
    }
}

void read_bitmap(const char* filename, unsigned char info[]) {
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
    fread(info, sizeof(unsigned char), 54, pfile);

    fclose(pfile);
}

void display_data(const char* filename) {
}

int main(int argc, char** argv) {
    unsigned char info[54];
    if (argc >= 2) {
        read_bitmap(argv[1], info);
    }
    else {
        return 1;
    }

    /*
     * The width is a 4-byte value stored at offset 18.
     * The height is a 4-byte value stored at offset 22.
     */
    int width = *((int*)(&info[18]));
    int height = *((int*)(&info[22]));
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    //int total_pixels = width * height;
    //int size_of_array = total_pixels * 3;
    //unsigned char* pixel_data = new unsigned char[size_of_array];

    //fread(pixel_data, sizeof(unsigned char), size_of_array, pfile);
    return 0;
}
