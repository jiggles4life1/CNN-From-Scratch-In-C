#ifndef Matrice
#define Matrice

struct Matrix{
    float mat[32][32];
    unsigned short height;
    unsigned short width;
    //unsigned short label;

};

//constructor
struct Matrix *newMatrix(int height, int width);

//prints the matrix
void printMatrix(struct Matrix *matrix);

//sets the values in the matrix to 0
void initMatrixWithZeros(struct Matrix *matrix);

//sets all the values of the matrix to 1
void initMatrixWithOnes(struct Matrix *m);

//sets the shape of the matrix
void setShape(struct Matrix *m, int height, int width);

//matrix multiplication function
struct Matrix *muliplyMatrices(struct Matrix *m1, struct Matrix *m2);

//transpose function
void transposeMatrix(struct Matrix *m);

//initalizes the values of the matrix with range [-1 : 1]
void initMatrixValuesRandomlyBetweenOneAndOne(struct Matrix *m);

//adds the values of a vector to each row of the matrix 
void addVectorToEachRow(struct Matrix *m, struct Matrix*v);

//the total of all the values in the matrix
float sum(struct Matrix *m);

struct Matrix *elementWiseMultiplication(struct Matrix *x, struct Matrix *y);

struct Matrix *flattenMatrix(struct Matrix *m);


#endif