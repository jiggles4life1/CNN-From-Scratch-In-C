#ifndef Matrice
#define Matrice

struct Matrix{
    unsigned short mat[32][32];
    unsigned short height;
    unsigned short width;

};

void printMatrix(struct Matrix *matrix);

void initMatrixWithZeros(struct Matrix *matrix);

#endif