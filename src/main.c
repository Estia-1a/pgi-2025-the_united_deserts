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
  check_file();  // <= Si tu veux la rendre fonctionnelle, pense à lui passer le fichier

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

  if (strcmp(configuration.command, "color_desaturate") == 0) {
    color_desaturate(configuration.filenames[0]);
  }

  return 0;
}