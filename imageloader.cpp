#include "imageloader.h"
#include <iostream>
#include <fstream>

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {}

Image::~Image() {
    delete[] pixels;
}

Image* loadBMP(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "File not found" << endl;
        return nullptr;
    }

    char header[54];
    file.read(header, 54);

    int dataPos = *(int*)&(header[0x0A]);
    int imageSize = *(int*)&(header[0x22]);
    int width = *(int*)&(header[0x12]);
    int height = *(int*)&(header[0x16]);

    if (imageSize == 0) imageSize = width * height * 3;
    if (dataPos == 0) dataPos = 54;

    char* data = new char[imageSize];
    file.seekg(dataPos);
    file.read(data, imageSize);
    file.close();

    // Konversi BGR ke RGB krn gl lama
    for (int i = 0; i < imageSize; i += 3) {
        char temp = data[i];
        data[i] = data[i + 2];
        data[i + 2] = temp;
    }

    return new Image(data, width, height);
}

void colors(Image* image) { //pewarnaan red green blue opsi selain konversi bgr
    for (int i = 0; i < image->width * image->height; i++) {
        unsigned char* r = (unsigned char*)&image->pixels[i * 3];
        unsigned char* g = (unsigned char*)&image->pixels[i * 3 + 1];
        unsigned char* b = (unsigned char*)&image->pixels[i * 3 + 2];

        // Menggunakan rumus penghitungan grayscale yang memperhitungkan persepsi manusia
        unsigned char gray = (unsigned char)(0.299f * (*r) + 0.587f * (*g) + 0.114f * (*b));
        *r = gray;
        *g = gray;
        *b = gray;
    }
}
