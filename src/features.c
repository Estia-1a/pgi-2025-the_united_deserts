#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>

#include "estia-image.h"
#include "features.h"
#include "utils.h"

void helloWorld() {
    printf("Hello World !");
}

void dimension(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("dimension: %d, %d\n", width, height);
        free(data);
    }
}

void stat_report(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        return;
    }

    int total_pixels = width * height;
    int maxPix = max_pixel(data, total_pixels, channels);
    int minPix = min_pixel(data, total_pixels, channels);
    int maxR = max_component(data, total_pixels, channels, 0);
    int maxG = max_component(data, total_pixels, channels, 1);
    int maxB = max_component(data, total_pixels, channels, 2);
    int minR = min_component(data, total_pixels, channels, 0);
    int minG = min_component(data, total_pixels, channels, 1);
    int minB = min_component(data, total_pixels, channels, 2);

    FILE *f = fopen("stat_report.txt", "w");
    if (f == NULL) {
        free(data);
        return;
    }

    fprintf(f, "max_pixel: %d\n", maxPix);
    fprintf(f, "min_pixel: %d\n", minPix);
    fprintf(f, "max_component R: %d\n", maxR);
    fprintf(f, "max_component G: %d\n", maxG);
    fprintf(f, "max_component B: %d\n", maxB);
    fprintf(f, "min_component R: %d\n", minR);
    fprintf(f, "min_component G: %d\n", minG);
    fprintf(f, "min_component B: %d\n", minB);

    fclose(f);
    free(data);
}

int max_pixel(unsigned char *data, int total_pixels, int channels) {
    return 0; 
}

int min_pixel(unsigned char *data, int total_pixels, int channels) {
    return 0; 
}

int max_component(unsigned char *data, int total_pixels, int channels, int component) {
    int max = -1;
    for (int i = 0; i < total_pixels; i++) {
        int index = i * channels + component;
        if (data[index] > max) {
            max = data[index];
        }
    }
    return max;
}

int min_component(unsigned char *data, int total_pixels, int channels, int component) {
    int min = 256;
    for (int i = 0; i < total_pixels; i++) {
        int index = i * channels + component;
        if (data[index] < min) {
            min = data[index];
        }
    }
    return min;
}

void print_pixel(char *source_path, int x, int y) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) return;

    pixelRGB* pixel = get_pixel(data, width, height, channels, x, y);
    if (pixel != NULL) {
        printf("print_pixel (%d, %d): %d, %d, %d\n", x, y, pixel->R, pixel->G, pixel->B);
    }

    free(data);
}

void min_component_with_position(char *source_path, char component) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) return;

    int comp_index = (component == 'R') ? 0 : (component == 'G') ? 1 : 2;
    int min_val = 256, min_x = -1, min_y = -1;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels + comp_index;
            int val = data[index];
            if (val < min_val) {
                min_val = val;
                min_x = x;
                min_y = y;
            }
        }
    }

    if (min_x >= 0 && min_y >= 0) {
        printf("min_component %c (%d, %d): %d\n", component, min_x, min_y, min_val);
    }

    free(data);
}

void max_component_with_position(char *source_path, char component) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) return;

    int comp_index = (component == 'R') ? 0 : (component == 'G') ? 1 : 2;
    int max_val = -1, max_x = -1, max_y = -1;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels + comp_index;
            int val = data[index];
            if (val > max_val) {
                max_val = val;
                max_x = x;
                max_y = y;
            }
        }
    }

    if (max_x >= 0 && max_y >= 0) {
        printf("max_component %c (%d, %d): %d\n", component, max_x, max_y, max_val);
    }

    free(data);
}

void min_pixel_with_position(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) return;

    int min_sum = 256 * 3 + 1;
    int min_x = -1, min_y = -1;
    int r_val = 0, g_val = 0, b_val = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels;
            int r = data[index];
            int g = data[index + 1];
            int b = data[index + 2];
            int sum = r + g + b;

            if (sum < min_sum) {
                min_sum = sum;
                min_x = x;
                min_y = y;
                r_val = r;
                g_val = g;
                b_val = b;
            }
        }
    }

    if (min_x >= 0 && min_y >= 0) {
        printf("min_pixel (%d, %d): %d, %d, %d\n", min_x, min_y, r_val, g_val, b_val);
    }

    free(data);
}

void max_pixel_with_position(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) return;

    int max_sum = -1;
    int max_x = -1, max_y = -1;
    int r_val = 0, g_val = 0, b_val = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * channels;
            int r = data[index];
            int g = data[index + 1];
            int b = data[index + 2];
            int sum = r + g + b;

            if (sum > max_sum) {
                max_sum = sum;
                max_x = x;
                max_y = y;
                r_val = r;
                g_val = g;
                b_val = b;
            }
        }
    }

    if (max_x >= 0 && max_y >= 0) {
        printf("max_pixel (%d, %d): %d, %d, %d\n", max_x, max_y, r_val, g_val, b_val);
    }

    free(data);
}
