#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "filters.h"

void print_usage() {
    printf("Usage: ./imgproc <input.png> <operation> [options] <output.png>\n");
    printf("Operations:\n");
    printf("  -median <size>      Median filter (3 or 5)\n");
    printf("  -gauss <size>       Gaussian blur (3 or 5)\n");
    printf("  -edges <threshold>  Edge detection (0-255)\n");
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        print_usage();
        return 1;
    }
    
    char *input_file = argv[1];
    char *operation = argv[2];
    char *output_file = argv[4];
    
    Image *img = load_image(input_file);
    if (!img) {
        printf("Error: Cannot load %s\n", input_file);
        return 1;
    }
    
    Image *result = create_image(img->width, img->height, img->channels);
    if (!result) {
        printf("Error: Cannot create output\n");
        free_image(img);
        return 1;
    }
    
    if (strcmp(operation, "-median") == 0) {
        int size = atoi(argv[3]);
        median_filter(img, result, size);
    } else if (strcmp(operation, "-gauss") == 0) {
        int size = atoi(argv[3]);
        gaussian_filter(img, result, size, 1.0f);
    } else if (strcmp(operation, "-edges") == 0) {
        int threshold = atoi(argv[3]);
        detect_edges(img, result, threshold);
    } else {
        printf("Error: Unknown operation %s\n", operation);
        print_usage();
        free_image(img);
        free_image(result);
        return 1;
    }
    
    if (save_image(result, output_file)) {
        printf("Saved to %s\n", output_file);
    } else {
        printf("Error saving to %s\n", output_file);
    }
    
    free_image(img);
    free_image(result);
    return 0;
}
