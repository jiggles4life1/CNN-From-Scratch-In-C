#include <math.h>
#include "Matrix.h"

float ReLU(float x){
    if (x <= 0){
        return 0;
    }
    else{
        return x;
    }
}


float exponentiation(float x){
    return (float) exp((double) x);
}

//NORMALIZES THE WHOLE MATRIX
//if you want it to go row by row, call that fucntion in Matrix.c


