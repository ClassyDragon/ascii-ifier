
#include <iostream>

void display_data(const char* filename) {
}

int main(int argc, char** argv) {
    FILE* pfile;
    if (argc >= 2) {
        pfile = fopen(argv[1], "rb");
        if (pfile == NULL) {
            std::cout << "An error occurred..." << std::endl;
            return 1;
        }
    }
    else {
        return 1;
    }

    unsigned char info[54];

    fread(info, sizeof(unsigned char), 54, pfile);
    
    int width = *((int*)(&info[18]));
    int height = *((int*)(&info[22]));
    std::cout << "Width: " << width << std::endl;
    std::cout << "Height: " << height << std::endl;

    //int total_pixels = width * height;
    //int size_of_array = total_pixels * 3;
    //unsigned char* pixel_data = new unsigned char[size_of_array];

    //fread(pixel_data, sizeof(unsigned char), size_of_array, pfile);
    fclose(pfile);



    return 0;
}
