#include "Vector.h"
#include<stdio.h>
#include<stdlib.h>

void initVector(int size, struct Vector *vec){
    vec->size = size;
    vec->vec = (double*) malloc(sizeof(double) * vec->size);


}


double dot(struct Vector *vecOne, struct Vector *vecTwo){
    double total = 0;

    for(int i = 0; i < vecOne->size; i++){
        double x = *(vecOne->vec+i);
        double y = *(vecTwo->vec+i);
        total += (x * y);

        printf("\n cur = %f * %f\n", x, y);
    }

    return total;
}

void printVector(struct Vector *vec){
    printf("\n vector size = %d ", vec->size);
    for(int i = 0; i < vec->size; i++){
        printf("\n%f", vec->vec[i]);
    }
}

void freeVector(struct Vector *vec){
    free(vec->vec);
}

