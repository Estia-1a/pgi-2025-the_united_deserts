#ifndef FEATURES_H
#define FEATURES_H

void helloWorld();
void dimension(char *source_path);
void stat_report(char *source_path);

int max_pixel(unsigned char *data, int total_pixels, int channels);
int min_pixel(unsigned char *data, int total_pixels, int channels);
int max_component(unsigned char *data, int total_pixels, int channels, int component);
int min_component(unsigned char *data, int total_pixels, int channels, int component);

void print_pixel(char *source_path, int x, int y);
void second_line(char *source_path);
void tenth_pixel(char *source_path);
void first_pixel(char *source_path);    
void min_component_with_position(char *source_path, char component);
void max_component_with_position(char *source_path, char component);
void min_pixel_with_position(char *source_path);
void max_pixel_with_position(char *source_path);

void color_desaturate(char *source_path);
void color_gray_luminance(char *source_path);
void color_invert(char *source_path);
void color_gray(char *source_path);
void color_blue(char *source_path);
void color_green(char *source_path);
void color_red(char *source_path);
#endif
