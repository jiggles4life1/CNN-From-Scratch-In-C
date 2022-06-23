#include <stdio.h>
#include "Matrice.h"
//The size of mat is the max size the matrix can be


void printMatrix(struct Matrix *matrix){
    printf("\n");
    printf("LabelOfImage: %hu\n", matrix->label);
    //print out the matrice in the format of
    for(int i = 0; i < matrix->width; i++){
        printf("----");
    } 
    for(int i = 0; i < matrix->height; i++){
        printf("\n|");
        for(int j = 0; j < matrix->width; j++){
            if(j == matrix->width-1){

            if(matrix->mat[i][j] >= 10000){
                printf("%d", matrix->mat[i][j]);

            } 
            else if(matrix->mat[i][j] >= 1000){
                printf("%d ", matrix->mat[i][j]);

            }           
            else if(matrix->mat[i][j] >= 100){
                printf("%d  ", matrix->mat[i][j]);
            }
            else if(matrix->mat[i][j] >= 10){
                printf("%d   ", matrix->mat[i][j]);
            }
            else{
                printf("%d    ", matrix->mat[i][j]);
            }
            }
            else{
                            
            if(matrix->mat[i][j] >= 10000){
                printf("%d ", matrix->mat[i][j]);

            } 
            else if(matrix->mat[i][j] >= 1000){
                printf("%d  ", matrix->mat[i][j]);

            }           
            else if(matrix->mat[i][j] >= 100){
                printf("%d   ", matrix->mat[i][j]);
            }
            else if(matrix->mat[i][j] >= 10){
                printf("%d   ", matrix->mat[i][j]);
            }
            else{
                printf("%d    ", matrix->mat[i][j]);
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



struct Matrix muliplyMatrices(struct Matrix *m1, struct Matrix *m2){
    //matrices can only be multiplied if the #rows and #columns are equal to one another respectively
    struct Matrix result;
    result.width = m1->height;
    result.height = m2->width;

    //if(m1->height == m2->width){
    if(1 == 2){
        result.width = m1->height;
        result.height = m2->width;

        for (int row = 0; row < m1->width; row++){

            for(int i = 0; i < m2->height; i++){

                int total = 0;
                for(int col = 0; col < m1->height; col++){
                    total += (m1->mat[col][row] * m2->mat[i][col]);
                }
                result.mat[i][row] = total;

            }
        }

    }
    else if(m1->width == m2->height){
        result.height = m1->height;
        result.width = m2->width;

        //for every column in m1
        for(int col = 0; col < m1->height; col++){

            //for every row in m2
            for(int i = 0; i < m2->width; i++){

                int total = 0;
                for(int row = 0; row < m1->width; row++){
                    total += (m1->mat[col][row] * m2->mat[row][i]);
                }

                result.mat[col][i] = total;
            }

        }
    }
    else{
        printf("ERROR: Can't multiply matrices of this size");
        return;
    }

    return result;


}
    