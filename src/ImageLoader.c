#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
#include "ImageLoader.h"

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

unsigned char* readTrainingLabelsIntoBuffer(){
    FILE *fileptr;
    unsigned char *buffer;
    long filelen;
    fileptr = fopen("C:/Users/thegr/Desktop/CNN-From-Scratch-In-C/src/TrainingImages/train-labels.idx1-ubyte", "r");  // Open the file in binary mode
    fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file

    filelen = ftell(fileptr);             // Get the current byte offset in the file
    rewind(fileptr);                      // Jump back to the beginning of the file

    buffer = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    fread(buffer, filelen, 1, fileptr); // Read in the entire file
    fclose(fileptr); // Close the file
    return buffer;
}

struct Image *getNImages(int n){
    //test opening file
    //FILE *images = fopen("/TrainingImages/train-images.idx3-ubyte", "r");



    char *buffer = readTrainingImagesIntoBuffer();
    char *labels = readTrainingLabelsIntoBuffer();
    //printf("everything is working");
    unsigned short pixelVal = (unsigned short) buffer[16];

    //struct Image *imageArray[n];
    struct Image *imageArray;
    imageArray = malloc(sizeof(struct Image) * n);

    //data start at 16 and 8 respectively, so init them there
    int curImage = 16;
    int curLabel = 8;
    int arrCounter = 0;
    //struct Image *image = (struct Image*) malloc(sizeof(struct Image));
    
    //eadImage(buffer, image, curImage);
    //imageArray[arrCounter] = image;
    //arrCounter++;
    //printImage(&image);

    for(int i = 0; i < n; i++){
        //image = malloc(sizeof(struct Image));
        readImage(buffer, &imageArray[arrCounter], curImage);
        setLabelOfImage(labels, &imageArray[arrCounter], curLabel);
        //imageArray[arrCounter] = image;
        
        curImage += (28*28);
        curLabel += 1;
        arrCounter++;


    }
    printf("\n\n DATA LOADED\n\n");

    return imageArray;



}

struct Matrix ***convertImageBatchToConLayerFormat(struct Image *images, int batchSize){
    struct Matrix ***m = malloc(sizeof(struct Matrix*) * batchSize);

    for(int i = 0; i < batchSize; i++){
        m[i] = malloc(sizeof(struct Matrix*));
        m[i][0] = convertImageToMatrix(&images[i]);
        
    }

    return m;
    

}


