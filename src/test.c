#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Image.h"
#include "ImageLoader.h"
#include "ConvLayer.h"

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

    struct Image *images;
    images = getNImages(1);
    printImage(&images[0]);

    struct Matrix *m = convertImageToMatrix(&images[0]);
    printMatrix(m);

    struct ConvLayer *convLayer = newConvLayer(4, 3, 1);
    printFilters(convLayer);


    struct Matrix *n = convolution(m, convLayer->filters[0], convLayer);
    printMatrix(n);



    n = maxPool(n, 2);
    printMatrix(n);

    printf("\n\n\n\n\n\n N SHOULD BE FLAT \n\n\n\n");

    n = flattenMatrix(n);
    printMatrix(n);

}