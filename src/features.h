#ifndef FEATURES_H
#define FEATURES_H


void helloWorld();
void dimension(char *source_path);
void stat_report(char *source_path);

int max_pixel(unsigned char *data, int total_pixels, int channels);
int min_pixel(unsigned char *data, int total_pixels, int channels);
int max_component(unsigned char *data, int total_pixels, int channels, int component);
int min_component(unsigned char *data, int total_pixels, int channels, int component);

#endif
