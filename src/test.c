#include <stdio.h>
//#include "Matrice.h"
#include "Vector.h"
int main()
{
    struct Vector vecOne;
    struct Vector vecTwo;


    initVector(4, &vecOne);
    initVector(4, &vecTwo);


    vecOne.vec[0] = 1.0;
    vecOne.vec[1]= 2.0;
    vecOne.vec[2]= 3.0;
    vecOne.vec[3]= 2.5;

    vecTwo.vec[0] = 0.2;
    vecTwo.vec[1] = 0.8;
    vecTwo.vec[2] = -0.5;
    vecTwo.vec[3] = 1.0;

    double d = dot(&vecTwo, &vecOne);
    printf("\n\n %f \n\n", d);


    printVector(&vecOne);


    freeVector(&vecOne);
    freeVector(&vecTwo);
    return 0;
}