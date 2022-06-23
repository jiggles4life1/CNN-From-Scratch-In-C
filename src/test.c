#include <stdio.h>
#include "Matrice.h"

int main()
{
    struct Matrix myMatrix;
    myMatrix.height = 5;
    myMatrix.width = 5;

    struct Matrix m2;
    m2.height = 5;
    m2.width = 5;
    int counter = 1;
    for(int i = 0; i < myMatrix.height; i++){
        for(int j = 0; j < myMatrix.width; j++){
            myMatrix.mat[i][j] = counter;
            m2.mat[i][j] = counter;
            counter += 1;
        }
    }
    printMatrix(&myMatrix);
    printMatrix(&m2);

    struct Matrix mult = muliplyMatrices(&myMatrix, &m2);
    printMatrix(&mult);

    printf("\n WHOA THERE ITS C Code! \n");



    printf("\n\n\n\n\n");
    struct Matrix m1;
    m1.width = 3;
    m1.height = 2;
    m1.mat[0][0] = 2;
    m1.mat[0][1] = 8;
    m1.mat[0][2] = 3;
    m1.mat[1][0] = 5;
    m1.mat[1][1] = 4;
    m1.mat[1][2] = 1;

    struct Matrix n1;
    n1.width = 2;
    n1.height = 3;
    n1.mat[0][0] = 4;
    n1.mat[0][1] = 1;
    n1.mat[1][0] = 6;
    n1.mat[1][1] = 3;
    n1.mat[2][0] = 2;
    n1.mat[2][1] = 4;

    printMatrix(&m1);
    printMatrix(&n1);
    
    struct Matrix result = muliplyMatrices(&n1, &m1);
    printMatrix(&result);

    printf("\n\n\n");
    return 0;
}