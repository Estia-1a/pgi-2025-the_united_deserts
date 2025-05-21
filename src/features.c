#include <estia-image.h>
#include <stdio.h>

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

    // read_image_data va lire les données de l'image
    if (read_image_data(source_path, &data, &width, &height, &channels)) {
        printf("dimension: %d, %d\n", width, height);
    }
}
