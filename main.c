#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function declerations
int **getKey(const char *filename, int *key_length);
char *grabPlaintext(const char *filename);

int main(int argc, char *argv[]) {

    // check if proper parameters set
    if(argc < 2){
        printf("usage: %s key plaintext\n", argv[0]);
        return 0;
    }

    int **key;
    char *plaintext;
    int key_length;

    key = getKey(argv[1], &key_length);
    plaintext = grabPlaintext(argv[2]);

    // print key for debuging
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    // print plaintext for debugging
    printf("%s\n", plaintext);

    return 0;
}

// function to grab key from file
// also gets the key_length for the user
int **getKey(const char *filename, int *key_length) {
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
    *key_length = size;
    key = malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i++){
        key[i] = malloc(sizeof(int) * size);
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

// function to grab plaintext from file
// only grabs letters
char *grabPlaintext(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL; // Error opening the file
    }

    char *plaintext = malloc(sizeof(char) * 10000);
    char ch;
    int i = 0;
    while((ch = fgetc(file)) != EOF){
        if(isalpha(ch)){
            ch = tolower(ch);
            plaintext[i] = ch;
            i++;
        }
    }

    plaintext[i] = '\0';
    return plaintext;
}
