#include "Image.h"
#include "stdio.h"


void readImage(unsigned char *buffer, struct Image *image, int startOfImage){

    int cur = 0;
    for(int i = 0; i < 28; i++){
        for(int j = 0; j < 28; j++){
            image->mat[i][j] = (int) buffer[cur + startOfImage];
            cur++;
        }
    }
}

void setLabelOfImage(unsigned char *labels, struct Image *image, int curLabel){
    image->label = (unsigned short) labels[curLabel];
}

void printImage(struct Image *image){
    printf("\n");
    printf("LabelOfImage: %hu\n", image->label);
    //print out the matrice in the format of
    for(int i = 0; i < 28; i++){
        printf("----");
    } 
    for(int i = 0; i < 28; i++){
        printf("\n|");
        for(int j = 0; j < 28; j++){
            if(j == 28-1){
          
            if(image->mat[i][j] >= 100){
                printf("%d", image->mat[i][j]);
            }
            else if(image->mat[i][j] >= 10){
                printf("%d ", image->mat[i][j]);
            }
            else{
                printf("%d  ", image->mat[i][j]);
            }
            }
            else{
                                      
            if(image->mat[i][j] >= 100){
                printf("%d ", image->mat[i][j]);
            }
            else if(image->mat[i][j] >= 10){
                printf("%d  ", image->mat[i][j]);
            }
            else{
                printf("%d   ", image->mat[i][j]);
            }
            }
        }
        printf("|\n");
    }
        for(int i = 0; i < 28; i++){
        printf("----");
    } 

    printf("\n");
}