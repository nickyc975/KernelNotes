#include <stdio.h>

#define BUFFER_SIZE 20

const char *FILE_NAME = "test.txt";

int main() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        fprintf(stderr, "Open file %s failed: ", FILE_NAME);
        perror("");
        return 0;
    }

    char content[BUFFER_SIZE] = {0};
    size_t nread = fread(content, sizeof(char), BUFFER_SIZE, file);
    printf("%s", content);
    fclose(file);
    return 0;
}