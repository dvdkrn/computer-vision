#include "filters.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

int compare_ints(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void median_filter(Image *input, Image *output, int kernel_size) {
    int w = input->width;
    int h = input->height;
    int c = input->channels;
    int offset = kernel_size / 2;
    int *pixels = (int*)malloc(kernel_size * kernel_size * sizeof(int));
    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int ch = 0; ch < c; ch++) {
                int count = 0;
                for (int ky = -offset; ky <= offset; ky++) {
                    for (int kx = -offset; kx <= offset; kx++) {
                        int px = x + kx;
                        int py = y + ky;
                        if (px >= 0 && px < w && py >= 0 && py < h) {
                            pixels[count++] = input->data[(py * w + px) * c + ch];
                        }
                    }
                }
                qsort(pixels, count, sizeof(int), compare_ints);
                output->data[(y * w + x) * c + ch] = pixels[count / 2];
            }
        }
    }
    free(pixels);
}

void gaussian_filter(Image *input, Image *output, int kernel_size, float sigma) {
    int w = input->width;
    int h = input->height;
    int c = input->channels;
    int offset = kernel_size / 2;
    
    float *kernel = (float*)malloc(kernel_size * kernel_size * sizeof(float));
    float sum = 0;
    
    for (int i = -offset; i <= offset; i++) {
        for (int j = -offset; j <= offset; j++) {
            float val = exp(-(i*i + j*j) / (2 * sigma * sigma));
            kernel[(i + offset) * kernel_size + (j + offset)] = val;
            sum += val;
        }
    }
    
    for (int i = 0; i < kernel_size * kernel_size; i++) {
        kernel[i] /= sum;
    }
    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int ch = 0; ch < c; ch++) {
                float result = 0;
                for (int ky = -offset; ky <= offset; ky++) {
                    for (int kx = -offset; kx <= offset; kx++) {
                        int px = x + kx;
                        int py = y + ky;
                        if (px >= 0 && px < w && py >= 0 && py < h) {
                            result += kernel[(ky + offset) * kernel_size + (kx + offset)] * 
                                      input->data[(py * w + px) * c + ch];
                        }
                    }
                }
                if (result < 0) result = 0;
                if (result > 255) result = 255;
                output->data[(y * w + x) * c + ch] = (unsigned char)result;
            }
        }
    }
    free(kernel);
}

void detect_edges(Image *input, Image *output, int threshold) {
    int w = input->width;
    int h = input->height;
    int c = input->channels;
    
    int sobel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    
    for (int y = 1; y < h - 1; y++) {
        for (int x = 1; x < w - 1; x++) {
            for (int ch = 0; ch < c; ch++) {
                int gx = 0, gy = 0;
                for (int ky = -1; ky <= 1; ky++) {
                    for (int kx = -1; kx <= 1; kx++) {
                        int px = x + kx;
                        int py = y + ky;
                        int val = input->data[(py * w + px) * c + ch];
                        gx += val * sobel_x[ky + 1][kx + 1];
                        gy += val * sobel_y[ky + 1][kx + 1];
                    }
                }
                int magnitude = (int)sqrt(gx * gx + gy * gy);
                if (magnitude > threshold) {
                    output->data[(y * w + x) * c + ch] = 255;
                } else {
                    output->data[(y * w + x) * c + ch] = 0;
                }
            }
        }
    }
}

void convolution(Image *input, Image *output, float *kernel, int kernel_size) {
    int w = input->width;
    int h = input->height;
    int c = input->channels;
    int offset = kernel_size / 2;
    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int ch = 0; ch < c; ch++) {
                float result = 0;
                for (int ky = -offset; ky <= offset; ky++) {
                    for (int kx = -offset; kx <= offset; kx++) {
                        int px = x + kx;
                        int py = y + ky;
                        if (px >= 0 && px < w && py >= 0 && py < h) {
                            result += kernel[(ky + offset) * kernel_size + (kx + offset)] * 
                                      input->data[(py * w + px) * c + ch];
                        }
                    }
                }
                if (result < 0) result = 0;
                if (result > 255) result = 255;
                output->data[(y * w + x) * c + ch] = (unsigned char)result;
            }
        }
    }
}
