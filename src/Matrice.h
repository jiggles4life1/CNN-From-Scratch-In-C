#ifndef Matrice
#define Matrice

struct Matrix{
    unsigned int mat[32][32];
    unsigned short height;
    unsigned short width;
    unsigned short label;

};

void printMatrix(struct Matrix *matrix);

void initMatrixWithZeros(struct Matrix *matrix);


struct Matrix muliplyMatrices(struct Matrix *m1, struct Matrix *m2);


#endif