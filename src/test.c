#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Image.h"
#include "ImageLoader.h"
#include "ConvLayer.h"
#include "Layer.h"
#include <Math.h>
#include "ActivationFunctions.h"

//#include "Layer.h"
//#include "Vector.h"



int main()
{


    int batchSize = 100;
    struct Image *images;
    images = getNImages(batchSize);
    for(int i = 0; i < batchSize; i++){
        printImage(&images[i]);
    }
    //struct Matrix *o = getOneHotEncodingOfLabels(images, batchSize);
    //struct Matrix *soft = newMatrix(1, 3);
    //soft->mat[0][0] = 0.5;
    //soft->mat[0][1] = 0.1;
    //soft->mat[0][2] = 0.2;
    
    //short label = 0;

    //printf("\n\n\n loss = %f\n\n", loss(soft, 0, label));



    
    //int batchSize = 5;
    //struct Image *images;
    //images = getNImages(batchSize);
    //for(int i = 0; i < batchSize; i++){
      //  printImage(&(images[i]));
    //}

    struct Matrix ***input = convertImageBatchToConLayerFormat(images, batchSize);
    



    //struct ConvLayer *layer = newConvLayer(4, 3, 1, input, 1, 1);
    struct ConvLayer *layer = newConvLayer(4, 3, 1, input, batchSize, 1);

    //printConvLayer(layer);
    forwardConvLayer(layer);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    poolOutput(layer, 2);
    
    struct ConvLayer *secondLayer = newConvLayer(4, 2, 1, layer->output, layer->inputSize, layer->outputSize);
    forwardConvLayer(secondLayer);
    poolOutput(secondLayer, 4);
    flattenOutput(secondLayer);
    printf("\n\n printing output of convolution\n\n");
    //printMatrix(layer->output[0][0]);
    printf("\n width = %d", secondLayer->output[0][0]->width);
    printMatrix(secondLayer->output[0][0]);
    
    secondLayer->output[0][0] = normalizeMatrixByRow(secondLayer->output[0][0]);



    struct Layer *flayer = newLayer(getConvLayerOutput(secondLayer)->width, 8, 0);
    forward(flayer, getConvLayerOutput(secondLayer));


    struct Layer *outputLayer = newLayer(flayer->numberOfNeurons, 10, 1);
    forward(outputLayer, flayer->outputs);

    printMatrix(outputLayer->outputs);


    printf("\n\n loss calculated\n");
    short *labels = getRawLabels(images, batchSize);
    struct Matrix *labelsMat = newMatrix(1, batchSize);
    for(int i = 0; i < batchSize; i++){
        printf("\n%d", labels[i]);
        labelsMat->mat[0][i] = (double) labels[i];
    }
    struct Matrix *l = calculateLoss(outputLayer, labelsMat);
    
    printMatrix(l);

    
    
   /////////////////////////////////////////////////////

    



}