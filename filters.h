#ifndef FILTERS_H
#define FILTERS_H

#include "image.h"

void median_filter(Image *input, Image *output, int kernel_size);
void gaussian_filter(Image *input, Image *output, int kernel_size, float sigma);
void detect_edges(Image *input, Image *output, int threshold);
void convolution(Image *input, Image *output, float *kernel, int kernel_size);

#endif
