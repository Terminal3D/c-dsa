#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Check the number of command line arguments
    if (argc != 4) {
        printf("Usage: frame <height> <width> <text>\n");
        return 1;
    }

    // Read the size of the frame and the text from the command line arguments
    int height, width;
    sscanf(argv[1], "%d", &height);
    sscanf(argv[2], "%d", &width);
    char* text = argv[3];

    // Check if the text fits in the frame
    if (strlen(text) > width - 2) {
        printf("Error: text does not fit in frame\n");
        return 1;
    }

    // Calculate the number of spaces to add before and after the text
    int spaces = (width - 2 - strlen(text)) / 2;

    // Print the top of the frame
    for (int i = 0; i < width; i++) {
        putchar('#');
    }
    putchar('\n');

    // Print the middle of the frame
    for (int i = 0; i < height - 2; i++) {
        putchar('#');
        for (int j = 0; j < spaces; j++) {
            putchar(' ');
        }
        printf("%s", text);
        for (int j = 0; j < spaces; j++) {
            putchar(' ');
        }
        putchar('#');
        putchar('\n');
    }

    // Print the bottom of the frame
    for (int i = 0; i < width; i++) {
        putchar('#');
    }
    putchar('\n');

    return 0;
}
