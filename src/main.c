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
    check_file();  // <= À adapter si tu veux valider le fichier

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

    return 0;

}

