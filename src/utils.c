#include <estia-image.h>
#include <stdlib.h>
#include "utils.h"

pixelRGB* get_pixel(unsigned char* data, const unsigned int width, const unsigned int height, const unsigned int n, const unsigned int x, const unsigned int y) {
    if (data == NULL || x >= width || y >= height) {
        return NULL;
    }

    return (pixelRGB*) &data[(y * width + x) * n];
}

