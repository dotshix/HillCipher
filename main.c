
/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: dotshix
| Language: c
|
| To Compile: gcc -o pa01 pa01.c
|
| To Execute: ./pa01 kX.txt pX.txt
|
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2023
| Instructor: McAlpin
| Due Date: 8/10/2023
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function declerations
int **getKey(const char *filename, int *key_length);
char *getPlaintext(const char *filename);
char *encrypt(char *input, int **key, int key_length);
void addPadding(char **plaintext, int key_length);
void printKey(int **key, int key_length);
void printText(char *plaintext, char *output);

int main(int argc, char *argv[]) {
    // check if proper parameters set
    if(argc < 2){
        printf("usage: %s key plaintext\n", argv[0]);
        return 0;
    }

    int **key;
    char *plaintext;
    char *res;
    int key_length;
    int plaintext_length;

    key = getKey(argv[1], &key_length);
    plaintext = getPlaintext(argv[2]);

    printKey(key, key_length);

    addPadding(&plaintext, key_length);

    res = encrypt(plaintext, key, key_length);

    printText(plaintext, res);

    for(int i = 0; i < key_length; i++){
        free(key[i]);
    }

    free(key);
    free(plaintext);
    free(res);
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
char *getPlaintext(const char *filename){
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL; // Error opening the file
    }

    char *plaintext = malloc(sizeof(char) * 10000 + 1);
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

// function to add padding if needed
void addPadding(char **plaintext, int key_length) {
    int plaintext_length = strlen(*plaintext);

    if (plaintext_length % key_length != 0) {
        // Calculate how many characters are needed for padding
        int remainder = key_length - (plaintext_length % key_length);

        // Allocate memory for padding
        char *padding = malloc(sizeof(char) * (remainder + 1));

        // Fill the padding with 'x' characters
        for (int i = 0; i < remainder; i++) {
            padding[i] = 'x';
        }

        // Terminate the padding string correctly
        padding[remainder] = '\0';

        // Concatenate the padding to the plaintext
        *plaintext = realloc(*plaintext, plaintext_length + remainder + 1);
        strcat(*plaintext, padding);

        // Free the memory allocated for padding
        free(padding);
    }
}

// Function to encrypt a 3x3 Hill Cipher
char *encrypt(char *input, int **key, int key_length) {
    int len = strlen(input);
    int inc = key_length;
    char *output = malloc(sizeof(char) * (len + 1)); // +1 for the null terminator
    output[len] = '\0';

        int *plain = malloc(sizeof(int) * inc);
        int *cipher = malloc(sizeof(int) * inc);
    for (int i = 0; i < len; i += inc) {

        for (int j = 0; j < inc; j++) {
            plain[j] = input[i + j] - 'a';
        }

        for (int x = 0; x < inc; x++) {
            cipher[x] = 0;
            for (int y = 0; y < inc; y++) {
                cipher[x] += (key[x][y] * plain[y]);
            }
            cipher[x] %= 26; // Apply modulus operation
        }

        for (int j = 0; j < inc; j++) {
            output[i + j] = cipher[j] + 'a';
        }

    }

        free(plain);
        free(cipher);
    return output;
}

// function to print matrix key
void printKey(int **key, int key_length){
    printf("\nKey matrix:\n");
    for(int i = 0; i < key_length; i++){
        for(int j = 0; j < key_length; j++){
            printf("%4d ", key[i][j]);
        }
        printf("\n");
    }
}

// simple functiont to print plaintext and ciphertext
void printText(char *plaintext, char *output){
    printf("\nPlaintext: \n");

    int b = 0;
    while(*plaintext){
        if(b == 80){
            printf("\n");
            b = 0;
        }
        printf("%c", *plaintext);
        plaintext++;
        b++;
    }

    printf("\n\nCiphertext:\n");
    b = 0;

    while(*output){
        if(b == 80){
            printf("\n");
            b = 0;
        }
        printf("%c", *output);
        output++;
        b++;
    }

    printf("\n");
}
