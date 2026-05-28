#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>

typedef struct {
    int width;
    int height;
    int channels;
    unsigned char *data;
} Image;

Image* load_image(const char *filename);
int save_image(Image *img, const char *filename);
void free_image(Image *img);
Image* create_image(int width, int height, int channels);

#endif
