#include <math.h>
#include <stdio.h>
#include "Matrix.h"

double ReLU(double x){
    if (x <= 0){
        return 0;
    }
    else{
        return x;
    }
}


double exponentiation(double x){
    return (double) exp((double) x);
}

double naturalLog(double x){
    double y = log(x);
    return y;
}


double loss(struct Matrix *layerOutput, int imageNumber, short label){
    return -(naturalLog(layerOutput->mat[imageNumber][label]));

}

//NORMALIZES THE WHOLE MATRIX
//if you want it to go row by row, call that fucntion in Matrix.c


