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
    int batchSize = 100;
    struct Image *images;
    images = getNImages(batchSize);
    for(int i = 0; i < batchSize; i++){
        printImage(&(images[i]));
    }

    struct Matrix ***input = convertImageBatchToConLayerFormat(images, batchSize);
    



    //struct ConvLayer *layer = newConvLayer(4, 3, 1, input, 1, 1);
    struct ConvLayer *layer = newConvLayer(4, 3, 1, input, batchSize, 1);

    //printConvLayer(layer);
    forwardConvLayer(layer);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    poolOutput(layer, 2);
    flattenOutput(layer);
    for(int image = 0; image < batchSize; image++){
        printMatrix(layer->output[image][0]);
    }
    /*
    struct ConvLayer *secondLayer = newConvLayer(4, 2, 1, layer->output, layer->inputSize, layer->outputSize);
    forwardConvLayer(secondLayer);
    poolOutput(secondLayer, 2);
    flattenOutput(secondLayer);
    printf("\n\n printing output of convolution\n\n");
    //printMatrix(layer->output[0][0]);
    printf("\n width = %d", secondLayer->output[0][0]->width);
    printMatrix(secondLayer->output[0][0]);
    
    */
    
    //struct ConvLayer *layer = newConvLayer(4, 3, 1, )
    
   /////////////////////////////////////////////////////
    



    /*struct Matrix *m = newMatrix(3, 3);
    m->mat[0][0] = 4.8;
    m->mat[0][1] = 1.21;
    m->mat[0][2] = 2.385;

    m->mat[1][0] = 8.9;
    m->mat[1][1] = 1.81;
    m->mat[1][2] = 0.2;

    m->mat[2][0] = 1.41;
    m->mat[2][1] = 1.051;
    m->mat[2][2] = 0.026;
    m = subtractByMaxRowWise(m);
    m = exponentiateMatrix(m);
    printMatrix(m);
    m = normalizeMatrixByRow(m);
    printMatrix(m);
    printf("\n\n sum = %f\n", sum(m));
    */



}