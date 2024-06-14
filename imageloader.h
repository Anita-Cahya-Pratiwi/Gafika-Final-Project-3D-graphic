#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

class Image {
public:
    Image(char* ps, int w, int h);
    ~Image();
    char* pixels;
    int width;
    int height;
};

Image* loadBMP(const char* filename);
void colors(Image* image);

#endif
