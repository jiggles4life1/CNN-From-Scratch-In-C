#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Image.h"
#include "ImageLoader.h"

//#include "Layer.h"
//#include "Vector.h"



int main()
{
    /*
    struct Matrix *inputs = newMatrix(3, 4);
    initMatrixValuesRandomlyBetweenOneAndOne(inputs);
    //printMatrix(inputs);

    //number of output of test data = 4 rn
    struct Layer *layer = newLayer(4, 5);
    //printMatrix(layer->weights);
    initMatrixWithOnes(layer->biases);
    forward(layer, inputs);
    //printMatrix(layer->outputs);
    */

    int n = 10;
    struct Image *images;
    images = getNImages(1);

    struct Matrix *m = convertImageToMatrix(&images[0]);
    printMatrix(m);




}