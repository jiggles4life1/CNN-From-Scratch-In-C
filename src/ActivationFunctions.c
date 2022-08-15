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


double ReLUPrime(double x){
    //despite Relu'(0) not strictly being defined
    //for the purposes of a neural network we can assign
    //Relu'(0) to 1 and it will not cause any major issues
    if (x < 0){
        return 0;
    }
    else{
        return 1;
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


double sigmoid(double x){
    //we maybe dont need this after all
    printf("\n\nSigmoid Function = NOT IMPLEMENTED\n\n");
    return x;
}
//NORMALIZES THE WHOLE MATRIX
//if you want it to go row by row, call that fucntion in Matrix.c


