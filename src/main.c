#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <estia-image.h>
#include <getopt.h>
 
#include "features.h"
#include "utils.h"
#include "argsparse.h"
 
int main(int argc, char **argv) {
    Config configuration;
    parse_arguments(argc, argv, &configuration);
    check_debug_mode(configuration);
    check_file(); 
 
    if (strcmp(configuration.command, "helloworld") == 0) {
        helloWorld();
    }
 
    if (strcmp(configuration.command, "dimension") == 0) {
        dimension(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "stat_report") == 0) {
        stat_report(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "min_component") == 0) {
        if (configuration.arguments[0] == NULL) {
            printf("Composant couleur manquant (R, G ou B)\n");
            return 1;
        }
        char component = configuration.arguments[0][0];
        min_component_with_position(configuration.filenames[0], component);
    }
 
    if (strcmp(configuration.command, "max_component") == 0) {
        if (configuration.arguments[0] == NULL) {
            printf("Composant couleur manquant (R, G ou B)\n");
            return 1;
        }
        char component = configuration.arguments[0][0];
        max_component_with_position(configuration.filenames[0], component);
    }
 
    if (strcmp(configuration.command, "min_pixel") == 0) {
        min_pixel_with_position(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "max_pixel") == 0) {
        max_pixel_with_position(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "print_pixel") == 0) {
        if (configuration.arguments[0] == NULL || configuration.arguments[1] == NULL) {
            printf("Coordonnées x et y manquantes\n");
            return 1;
        }
        int x = atoi(configuration.arguments[0]);
        int y = atoi(configuration.arguments[1]);
        print_pixel(configuration.filenames[0], x, y);
    }
 
    if (strcmp(configuration.command, "second_line") == 0) {
        second_line(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "tenth_pixel") == 0) {
        tenth_pixel(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "first_pixel") == 0) {
        first_pixel(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "color_desaturate") == 0) {
        color_desaturate(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "color_gray_luminance") == 0) {
        color_gray_luminance(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "color_invert") == 0) {
    color_invert(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "color_gray") == 0) {
        color_gray(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "color_blue") == 0) {
    color_blue(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "color_green") == 0) {
    color_green(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "color_red") == 0) {
    color_red(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "mirror_total") == 0) {
    mirror_total(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "mirror_vertical") == 0) {
    mirror_vertical(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "mirror_horizontal") == 0) {
    mirror_horizontal(configuration.filenames[0]);
    }  
 
    if (strcmp(configuration.command, "rotate_acw") == 0) {
    rotate_acw(configuration.filenames[0]);
    }
 
    if (strcmp(configuration.command, "rotate_cw") == 0) {
    rotate_cw(configuration.filenames[0]);
    }
 
       if (strcmp(configuration.command, "scale_crop") == 0) {
        if (configuration.arguments[0] == NULL || configuration.arguments[1] == NULL ||
            configuration.arguments[2] == NULL || configuration.arguments[3] == NULL) {
            printf("Arguments manquants : center_x center_y width height\n");
            return 1;
        }
 
        int center_x = atoi(configuration.arguments[0]);
        int center_y = atoi(configuration.arguments[1]);
        int width = atoi(configuration.arguments[2]);
        int height = atoi(configuration.arguments[3]);
 
        scale_crop(configuration.filenames[0], center_x, center_y, width, height);
    }
   
    if (strcmp(configuration.command, "scale_bilinear") == 0) {
    if (configuration.arguments[0] == NULL) {
        printf("Facteur d'échelle manquant (ex: 0.5 ou 2.0)\n");
        return 1;
    }
    float scale = atof(configuration.arguments[0]);
    if (scale <= 0) {
        printf("Facteur d'échelle invalide\n");
        return 1;
    }
    scale_bilinear(configuration.filenames[0], scale);
    }

    if (strcmp(configuration.command, "scale_nearest") == 0) {
    if (configuration.arguments[0] == NULL) {
        printf("Facteur d'échelle manquant (ex: 0.5 ou 2.0)\n");
        return 1;
    }
    float scale = atof(configuration.arguments[0]);
    if (scale <= 0) {
        printf("Facteur d'échelle invalide\n");
        return 1;
    }
    scale_nearest(configuration.filenames[0], scale);
    }
 
    return 0;
}
