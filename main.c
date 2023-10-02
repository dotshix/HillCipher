#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function declerations
int **getKey(const char *filename);
char *grabPlaintext(const char *filename);

int main(int argc, char *argv[]) {

    // check if proper parameters set
    if(argc < 2){
        printf("usage: %s key plaintext\n", argv[0]);
        return 0;
    }

    int **key;
    char *plaintext;

    key = getKey(argv[1]);


    // print key for debuging
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    plaintext = grabPlaintext(argv[2]);
    printf("%s\n", plaintext);

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
