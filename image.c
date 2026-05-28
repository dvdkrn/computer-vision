#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdlib.h>
#include <stdio.h>

Image* load_image(const char *filename) {
    Image *img = (Image*)malloc(sizeof(Image));
    if (!img) return NULL;
    
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    if (!img->data) {
        free(img);
        return NULL;
    }
    
    return img;
}

int save_image(Image *img, const char *filename) {
    return stbi_write_png(filename, img->width, img->height, img->channels, img->data, img->width * img->channels);
}

void free_image(Image *img) {
    if (img) {
        if (img->data) stbi_image_free(img->data);
        free(img);
    }
}

Image* create_image(int width, int height, int channels) {
    Image *img = (Image*)malloc(sizeof(Image));
    if (!img) return NULL;
    
    img->width = width;
    img->height = height;
    img->channels = channels;
    img->data = (unsigned char*)calloc(width * height * channels, 1);
    
    return img;
}
