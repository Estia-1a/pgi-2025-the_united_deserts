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

void min_component_with_position(char *source_path, char component) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        return;
    }

    int comp_index;
    if (component == 'R') comp_index = 0;
    else if (component == 'G') comp_index = 1;
    else if (component == 'B') comp_index = 2;
    else {
        free(data);
        return;
    }

    int min_val = 256;
    int min_x = -1, min_y = -1;

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

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        return;
    }

    int comp_index;
    if (component == 'R') comp_index = 0;
    else if (component == 'G') comp_index = 1;
    else if (component == 'B') comp_index = 2;
    else {
        free(data);
        return;
    }

    int max_val = -1;
    int max_x = -1, max_y = -1;

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
