#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the key matrix (3x3)
int key[3][3] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}};

// Function to encrypt a 3x3 Hill Cipher
void encrypt(char *input, char *output) {
    int len = strlen(input);

    // Check if the input length is divisible by 3
    if (len % 3 != 0) {
        printf("Input length must be divisible by 3.\n");
        return;
    }

    for (int i = 0; i < len; i += 3) {
        int plain1 = input[i] - 'a';
        int plain2 = input[i + 1] - 'a';
        int plain3 = input[i + 2] - 'a';

        int cipher1 = (key[0][0] * plain1 + key[0][1] * plain2 + key[0][2] * plain3) % 26;
        int cipher2 = (key[1][0] * plain1 + key[1][1] * plain2 + key[1][2] * plain3) % 26;
        int cipher3 = (key[2][0] * plain1 + key[2][1] * plain2 + key[2][2] * plain3) % 26;

        output[i] = cipher1 + 'a';
        output[i + 1] = cipher2 + 'a';
        output[i + 2] = cipher3 + 'a';
    }

    output[len] = '\0';
}


// function declerations
int **getKey(const char *filename);

int main(int argc, char *argv[]) {
    /* char input[100]; */
    /* char output[100]; */

    /* printf("Enter plaintext (in lowercase, divisible by 3): "); */
    /* scanf("%s", input); */

    /* encrypt(input, output); */

    /* printf("Encrypted text: %s\n", output); */

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
