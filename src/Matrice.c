#include <stdio.h>
#include "Matrice.h"
//The size of mat is the max size the matrix can be


void printMatrix(struct Matrix *matrix){
    printf("\n");

    //print out the matrice in the format of
    for(int i = 0; i < matrix->width; i++){
        printf("----");
    } 
    for(int i = 0; i < matrix->height; i++){
        printf("\n|");
        for(int j = 0; j < matrix->width; j++){
            if(j == matrix->width-1){
                            
            if(matrix->mat[i][j] >= 100){
                printf("%hu", matrix->mat[i][j]);
            }
            else if(matrix->mat[i][j] >= 10){
                printf("%hu ", matrix->mat[i][j]);
            }
            else{
                printf("%hu  ", matrix->mat[i][j]);
            }
            }
            else{
                            
            if(matrix->mat[i][j] >= 100){
                printf("%hu ", matrix->mat[i][j]);
            }
            else if(matrix->mat[i][j] >= 10){
                printf("%hu  ", matrix->mat[i][j]);
            }
            else{
                printf("%hu   ", matrix->mat[i][j]);
            }
            }
        }
        printf("|\n");
    }
        for(int i = 0; i < matrix->width; i++){
        printf("----");
    } 

    printf("\n");
}

void initMatrixWithZeros(struct Matrix *matrix){
    for(int i = 0; i < matrix->height; i++){
        printf("\n|");
        for(int j = 0; j < matrix->width; j++){
            matrix->mat[i][j] = 0;
        }
        printf("|\n");
    }
}
    