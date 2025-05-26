#include <estia-image.h>
#include <stdio.h>
#include <stdlib.h>

#include "estia-image.h"
#include "features.h"
#include "utils.h"

/**
 * @brief Here, you have to code features of the project.
 * Do not forget to commit regurlarly your changes.
 * Your commit messages must contain "#n" with: n = number of the corresponding feature issue.
 * When the feature is totally implemented, your commit message must contain "close #n".
 */

void helloWorld() {
    printf("Hello World !");
}  

void dimension(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("dimension: %d, %d\n", width, height);
    }
}


void stat_report(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;
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
    return 0;
}
int min_component(unsigned char *data, int total_pixels, int channels, int component) {
    return 0;
}
