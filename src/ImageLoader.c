#include <stdio.h>
#include <stdlib.h>
#include "Matrice.h"

unsigned char* readTrainingImagesIntoBuffer(){
        FILE *fileptr;
    unsigned char *buffer;
    long filelen;
    fileptr = fopen("C:/Users/thegr/Desktop/CNN-From-Scratch-In-C/src/TrainingImages/train-images.idx3-ubyte", "r");  // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file

    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file

    buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    fread(buffer, filelen, 1, fileptr); // Read in the entire file
    fclose(fileptr); // Close the file
    return buffer;
}


//unsigned char* readTrainingLabelsIntoBuffer(){

//}

void readImageToMatrice(unsigned char *buffer, struct Matrix *matrix, int startOfImage){
    matrix->height = 28;
    matrix->width = 28;
    int cur = 0;
    for(int i = 0; i < matrix->height; i++){
        for(int j = 0; j < matrix->width; j++){
            matrix->mat[i][j] = (unsigned short) buffer[cur + startOfImage];
            cur++;
        }
    }
}

int main(){
    //test opening file
    //FILE *images = fopen("/TrainingImages/train-images.idx3-ubyte", "r");



    char *buffer = readTrainingImagesIntoBuffer();
    printf("everything is working");
    unsigned short pixelVal = (unsigned short) buffer[16];

    int curImage = 16;
    struct Matrix image;
    readImageToMatrice(buffer, &image, curImage);
    printMatrix(&image);

    for(int i = 0; i < 60000; i++){
        curImage += (28*28);
        readImageToMatrice(buffer, &image, curImage);
        printMatrix(&image);
        printf("\n");
    }
    printf("\n\n DATA LOADED\n\n");



}


