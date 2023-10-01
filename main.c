#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function declerations
int **getKey(const char *filename);

int main(int argc, char *argv[]) {

    // check if proper parameters set
    if(argc < 2){
        printf("usage: %s key plaintext\n", argv[0]);
        return 0;
    }

    int **key = getKey(argv[1]);


    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}

// function to grab key from file
int **getKey(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL; // Error opening the file
    }

    int **key;
    int size;
    int num;

    // grab first number to get proper size and create char array for key
    fscanf(file, "%d", &size);
    key = malloc(sizeof(char**) * size);
    for(int i = 0; i < size; i++){
        key[i] = malloc(sizeof(char *) * size);
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            fscanf(file, "%d", &num);
            key[i][j] = num;
        }
    }

    fclose(file);
    return key;
}
