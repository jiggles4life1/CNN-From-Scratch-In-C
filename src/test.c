#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Layer.h"
//#include "Vector.h"



int main()
{
    struct Matrix *inputs = newMatrix(3, 4);
    initMatrixValuesRandomlyBetweenOneAndOne(inputs);
    //printMatrix(inputs);

    //number of output of test data = 4 rn
    struct Layer *layer = newLayer(4, 5);
    //printMatrix(layer->weights);
    initMatrixWithOnes(layer->biases);
    forward(layer, inputs);
    //printMatrix(layer->outputs);
}