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

void second_line(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) return;

    if (height < 2 || channels < 3) {
        printf("Image trop petite ou canaux insuffisants.\n");
        free(data);
        return;
    }

    int index = width * channels;  // début de la 2e ligne (pixel 0,1)
    int r = data[index];
    int g = data[index + 1];
    int b = data[index + 2];

    printf("second_line: %d, %d, %d\n", r, g, b);

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

void color_desaturate(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Erreur de lecture de l'image.\n");
        return;
    }

    // Création d'une nouvelle image
    unsigned char *new_data = malloc(width * height * channels);
    if (new_data == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        free(data);
        return;
    }

    for (int i = 0; i < width * height; i++) {
        int r = data[i * channels];
        int g = data[i * channels + 1];
        int b = data[i * channels + 2];

        int min_val = (r < g) ? ((r < b) ? r : b) : ((g < b) ? g : b);
        int max_val = (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
        int new_val = (min_val + max_val) / 2;

        new_data[i * channels] = new_val;
        new_data[i * channels + 1] = new_val;
        new_data[i * channels + 2] = new_val;

        if (channels == 4) {
            new_data[i * channels + 3] = data[i * channels + 3]; // Alpha
        }
    }

    write_image_data("image_out.bmp", new_data, width, height);

    free(data);
    free(new_data);
}

void color_gray_luminance(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Erreur de lecture de l'image.\n");
        return;
    }

    unsigned char *gray_data = malloc(width * height * channels);
    if (gray_data == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        free(data);
        return;
    }

    for (int i = 0; i < width * height; i++) {
        int r = data[i * channels];
        int g = data[i * channels + 1];
        int b = data[i * channels + 2];

        // Formule de luminance pondérée
        unsigned char value = (unsigned char)(0.21 * r + 0.72 * g + 0.07 * b);

        gray_data[i * channels] = value;
        gray_data[i * channels + 1] = value;
        gray_data[i * channels + 2] = value;

        if (channels == 4) {
            gray_data[i * channels + 3] = data[i * channels + 3]; // Conserver alpha
        }
    }

    write_image_data("image_out.bmp", gray_data, width, height);

    free(data);
    free(gray_data);
}

void color_invert(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Erreur de lecture de l'image.\n");
        return;
    }

    unsigned char *inverted_data = malloc(width * height * channels);
    if (inverted_data == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        free(data);
        return;
    }

    for (int i = 0; i < width * height; i++) {
        inverted_data[i * channels]     = 255 - data[i * channels];     // R
        inverted_data[i * channels + 1] = 255 - data[i * channels + 1]; // G
        inverted_data[i * channels + 2] = 255 - data[i * channels + 2]; // B

        if (channels == 4) {
            inverted_data[i * channels + 3] = data[i * channels + 3]; // conserver alpha
        }
    }

    write_image_data("image_out.bmp", inverted_data, width, height);

    free(data);
    free(inverted_data);
}

void color_gray(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Erreur de lecture de l'image.\n");
        return;
    }

    unsigned char *gray_data = malloc(width * height * channels);
    if (gray_data == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        free(data);
        return;
    }

    for (int i = 0; i < width * height; i++) {
        int r = data[i * channels];
        int g = data[i * channels + 1];
        int b = data[i * channels + 2];

        // Moyenne simple
        unsigned char value = (r + g + b) / 3;

        gray_data[i * channels] = value;
        gray_data[i * channels + 1] = value;
        gray_data[i * channels + 2] = value;

        if (channels == 4) {
            gray_data[i * channels + 3] = data[i * channels + 3]; // conserver alpha
        }
    }

    write_image_data("image_out.bmp", gray_data, width, height);

    free(data);
    free(gray_data);
}

void color_blue(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Erreur de lecture de l'image.\n");
        return;
    }

    unsigned char *blue_data = malloc(width * height * channels);
    if (blue_data == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        free(data);
        return;
    }

    for (int i = 0; i < width * height; i++) {
        blue_data[i * channels]     = 0; // R
        blue_data[i * channels + 1] = 0; // G
        blue_data[i * channels + 2] = data[i * channels + 2]; // B

        if (channels == 4) {
            blue_data[i * channels + 3] = data[i * channels + 3]; // Alpha
        }
    }

    write_image_data("image_out.bmp", blue_data, width, height);

    free(data);
    free(blue_data);
}

void color_green(char *source_path) {
    unsigned char *data = NULL;
    int width = 0, height = 0, channels = 0;

    if (!read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("Erreur de lecture de l'image.\n");
        return;
    }

    unsigned char *green_data = malloc(width * height * channels);
    if (green_data == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        free(data);
        return;
    }

    for (int i = 0; i < width * height; i++) {
        green_data[i * channels]     = 0;                           // R
        green_data[i * channels + 1] = data[i * channels + 1];     // G
        green_data[i * channels + 2] = 0;                           // B

        if (channels == 4) {
            green_data[i * channels + 3] = data[i * channels + 3]; // Alpha
        }
    }

    write_image_data("image_out.bmp", green_data, width, height);

    free(data);
    free(green_data);
}