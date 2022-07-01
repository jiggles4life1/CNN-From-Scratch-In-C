#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Matrix.h"
//The size of mat is the max size the matrix can be


void printMatrix(struct Matrix *matrix){
    printf("\n");
    //printf("LabelOfImage: %hu\n", matrix->label);
    //print out the matrice in the format of
    for(int i = 0; i < matrix->width; i++){
        printf("----");
    } 
    for(int i = 0; i < matrix->height; i++){
        printf("\n|");
        for(int j = 0; j < matrix->width; j++){
            if(matrix->mat[i][j] >= 0 ){
                printf("%f,  ", matrix->mat[i][j]);
            }
            else{
                printf("%f, ", matrix->mat[i][j]);
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
        for(int j = 0; j < matrix->width; j++){
            matrix->mat[i][j] = 0;
        }
    }
}



struct Matrix *muliplyMatrices(struct Matrix *m1, struct Matrix *m2){
    //matrices can only be multiplied if the #rows and #columns are equal to one another respectively
    //struct Matrix result;
    //result.width = m1->height;
    //result.height = m2->width;

    struct Matrix *result = newMatrix(m1->height, m2->width);

    int checkOne = (m1->height == m2-> width);
    int checkTwo = (m1->width == m2->height);

    if(!(checkOne || checkTwo)){
        printf("SHAPE ERROR: multiply matrices");
        return result;
    }

    for(int i = 0; i < result->height; i++){
        for(int j = 0; j < result->width; j++){
            float total = 0; 
            for(int k = 0; k < m1->width; k++){
                //printf("\n\n %d \n ", m1->width);
                total += (m1->mat[i][k] * m2->mat[k][j]);
            }
            result->mat[i][j] = total;
        }
    }
    return result;



}

void initMatrixValuesRandomlyBetweenOneAndOne(struct Matrix *m){

    srand(time(NULL));
    float x = ((float)rand()/(float)(RAND_MAX)) * 2.0;
    x -= 1;
    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
                float x = ((float)rand()/(float)(RAND_MAX)) * 2.0;
                x -= 1;
                m->mat[i][j] = x;
        }
    }


}


void transposeMatrix(struct Matrix *m){
    for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            int tmp = m->mat[i][j];
            m->mat[i][j] = m->mat[j][i];
            m->mat[j][i] = tmp;
        }
    }
}


void setShape(struct Matrix *m, int height, int width){
    m->height = height;
    m->width = width;
}


struct Matrix* newMatrix(int height, int width){
    struct Matrix *m = malloc(sizeof(struct Matrix));
    m->height = height;
    m->width = width;
    return m;
}


void addVectorToEachRow(struct Matrix *m, struct Matrix *v){
    if(m->width != v->width){
        printf("ERROR: matrix width and vector width != (addVectorToEachRow()");
        return;
    }
    for(int i = 0; i < m->height; i++){
        for (int j = 0; j < m->width; j++){
            m->mat[i][j] += v->mat[0][j];
        }
    }
}

void initMatrixWithOnes(struct Matrix *m){
        for(int i = 0; i < m->height; i++){
        for(int j = 0; j < m->width; j++){
            m->mat[i][j] = 1.0;
        }
    }
}




