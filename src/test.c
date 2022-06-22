#include <stdio.h>
#include "Matrice.h"

int main()
{
    struct Matrix myMatrix;
    myMatrix.height = 5;
    myMatrix.width = 5;
    initMatrixWithZeros(&myMatrix);
    printMatrix(&myMatrix);
    printf("\n WHOA THERE ITS C Code! \n");
    return 0;
}