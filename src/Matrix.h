#ifndef Matrice
#define Matrice

struct Matrix{
    float mat[32][32];
    unsigned short height;
    unsigned short width;
    //unsigned short label;

};

struct Matrix *newMatrix(int height, int width);

void printMatrix(struct Matrix *matrix);

void initMatrixWithZeros(struct Matrix *matrix);

void initMatrixWithOnes(struct Matrix *m);
void setShape(struct Matrix *m, int height, int width);


struct Matrix *muliplyMatrices(struct Matrix *m1, struct Matrix *m2);

void transposeMatrix(struct Matrix *m);

void initMatrixValuesRandomlyBetweenOneAndOne(struct Matrix *m);

void addVectorToEachRow(struct Matrix *m, struct Matrix*v);



#endif