#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

typedef unsigned char byte;

struct Pixel {
    public:
        Pixel() : rgba(nullptr) {}
        Pixel(unsigned int bytesPerPixel)
            : bytesPerPixel(bytesPerPixel)
        {
            this->rgba = new byte[bytesPerPixel];
        }

        ~Pixel() {
            if (this->rgba) delete[] this->rgba;
        }

        inline void setRGBA(byte* rgba) { this->rgba = rgba; }
        inline byte* getRGBA() const { return this->rgba; }
        unsigned int getAverage() const {
            return (rgba[bytesPerPixel - 1] + rgba[bytesPerPixel - 2] + rgba[bytesPerPixel - 3]) / 3;
        }
    private:
        unsigned int bytesPerPixel;
        byte* rgba;
};

bool readFile(const std::string& filename) {
    // Open input file in binary mode:
    std::ifstream data(filename, std::ios_base::binary);
    data >> std::noskipws; // Don't interpret whitespace
    if (data.fail()) {
        std::cout << "Could not open " << filename << "." << std::endl;
        return false;
    }

    auto throwAwayBytes = [&](int numBytes) {
        byte temp;
        for (int i = 0; i < numBytes; i++) data >> temp;
    };

    throwAwayBytes(2);
    unsigned int sizeInBytes; data.read((char*)&sizeInBytes, 4); // 0x02 -> 0x05
    throwAwayBytes(4);
    unsigned int startingAddress; data.read((char*)&startingAddress, 4); // 0x0A -> 0x0D
    unsigned int sizeOfHeader; data.read((char*)&sizeOfHeader, 4); // 0x0E -> 0x11
    unsigned int width; data.read((char*)&width, 4); // 0x12 -> 0x15
    unsigned int height; data.read((char*)&height, 4); // 0x16 -> 0x19
    throwAwayBytes(2);
    unsigned short bpp; data.read((char*)&bpp, 2); // 0x1C -> 0x1D 30 bytes total
    unsigned short bytesPerPixel = bpp / 8;
    throwAwayBytes(4);
    unsigned int imageSize; data.read((char*)&imageSize, 4); // 0x22 -> 0x25 38 bytes total
    throwAwayBytes(startingAddress - 38);

    auto calculatePadding = [&]() {
        if (!((width * bytesPerPixel) % 4)) return 0;
        int padding = 1;
        while (((width * bytesPerPixel) + padding) % 4) padding++;
        return padding;
    };
    int padding = calculatePadding();
    size_t arrSize = imageSize * sizeof(byte) - (height * padding);
    byte* pixelData = new byte[arrSize];
    for (unsigned int i = 0; i < arrSize; i++) {
        pixelData[i] = 69;
    }

    byte temp;
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width * bytesPerPixel; j++) {
            data.read((char*)&temp, 1);
            pixelData[i * (width * bytesPerPixel) + j] = temp;
        }
        for (int j = 0; j < padding; j++) data.read((char*)&temp, 1);
    }

    data.close();

    //unsigned int numPixels = (imageSize / bytesPerPixel) - (padding * height);
    unsigned int numPixels = (imageSize - (padding * height)) / bytesPerPixel;
    Pixel* pixels = new Pixel[numPixels];

    for (unsigned int i = 0; i < numPixels; i++) {
        byte* currentPixelData = new byte[bytesPerPixel];
        for (unsigned int j = 0; j < bytesPerPixel; j++) {
            currentPixelData[j] = pixelData[(i * bytesPerPixel) + j];
        }
        pixels[i] = Pixel(bytesPerPixel);
        pixels[i].setRGBA(currentPixelData);
    }

    std::string str = " ^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    const float divider = (255.0f / (float)str.length());

    for (int i = height - 1; i >= 0; i--) {
        for (unsigned int j = 0; j < width; j++) {
            unsigned int arrIndex = pixels[i * width + j].getAverage() / divider;
            arrIndex = (arrIndex == str.length() ? arrIndex - 1 : arrIndex);
            std::cout << str[arrIndex];
        }
        std::cout << std::endl;
    }

    delete[] pixels;
    delete[] pixelData;
    return true;
}

int main(int argc, char** argv) {
    if (argc < 2)
        std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    else
        readFile(argv[1]);
    return 0;
}
