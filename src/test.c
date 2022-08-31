#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Image.h"
#include "ImageLoader.h"
#include "ConvLayer.h"
#include "Layer.h"
#include <Math.h>
#include "ActivationFunctions.h"
#include "MaxPool.h"

//#include "Layer.h"
//#include "Vector.h"





int main()
{
    double learningRate = 0.001;

    int batchSize = 1;
    
    
    struct Image *images;
    images = getNImages(batchSize);
    for(int i = 0; i < batchSize; i++){
        printImage(&images[i]);
    }

    /*struct Matrix ***input = convertImageBatchToConLayerFormat(images, batchSize);

    //remember, the initial input has 1 map per image since it is just the image itself
    struct ConvLayer *layer = newConvLayer(4, 3, 1, input, batchSize, 1);
    printf("\n post conv init\n");
    forwardConvLayer(layer, input);
    */
    
    
    
    //////////////////////////////////////////////////////////////////////////
                        //THIS CODE IS THE CODE THAT WORKED BEFORE TRYING TO DEBUG IT NOT LEARNING//
    struct Matrix ***input = convertImageBatchToConLayerFormat(images, batchSize);


    struct ConvLayer *layer = newConvLayer(8, 3, 1, input, batchSize, 1, 2);

    forwardConvLayer(layer, input);
    printf("\n\n conv layer forwarded\n\n");
    //poolOutput(layer, layer->poolSize);
    struct MaxPool *poolLayer = newMaxPool(layer);
    printf("\n\n new pool layer created\n\n");
    //printConvLayerOutput(layer);
    pool(poolLayer, 2, layer->output);
    printf("\n\n pool layer forwarded\n\n");
    //flattenOutput(layer);
    flattenOutputMaxPool(poolLayer);
    printf("\n\n output of pool layer flattened\n\n");
    //printMatrix(poolLayer->output[0][0]);
    //printMatrix(layer->flattenedOutput);
    //printMatrix(poolLayer->flattenedOutput);
    //printf("\n pool width = %d\n", poolLayer->flattenedOutput->width);
    struct Layer *outputLayer = newLayer(getMaxPoolOutput(poolLayer)->width, 10, 1);
    printf("\n new output layer initialized\n");
    forward(outputLayer, getMaxPoolOutput(poolLayer));
    printf("\n\n output layer forwarded\n\n");
    //printMatrix(outputLayer->outputs);
    


    short *labels = getRawLabels(images, batchSize);
    struct Matrix *labelsMat = newMatrix(1, batchSize);
    for(int i = 0; i < batchSize; i++){
        labelsMat->mat[0][i] = (double) labels[i];
    }
    
    struct Matrix *l = calculateLoss(outputLayer, labelsMat);



    //printf("\n\n\n loss = ");
    //printMatrix(l);  
    //printMatrix(outputLayer->outputs);

    struct Matrix *gradient =(backProp(outputLayer, labelsMat, learningRate, l));
    
    
    struct Matrix ***bg = backpropMaxPool(poolLayer, gradient);
    
    struct Matrix ***finalBg= backpropConvLayer(layer, bg, learningRate);
    /*
    
    printf("\n\n oh wow succesffuly ran\n\n");

    //printMatrix(bg[0][0]);

    //printMatrix(poolLayer->input[0][0]);
    */
    freeMatrix(gradient);
    freeUnflattenedGradient(poolLayer, bg);

    


   //------------------------------------------------------
    
    int accuracy = 0;
    double avgLoss = 0.0;

    int i = 1;
    
    while (i < 60000){
        free(images);
        images=getNImages(batchSize);
        //printImage(&images[0]);
        freeConvLayerInputBatch(input, batchSize);
        //printf("\n conv layer batch input freed \n");
        input = convertImageBatchToConLayerFormat(images, batchSize);
        forwardConvLayer(layer, input);
        pool(poolLayer, 2, layer->output);
        flattenOutputMaxPool(poolLayer);
        
        forward(outputLayer, getMaxPoolOutput(poolLayer));
        
        freeMatrix(l);

        free(labels);
        labels = getRawLabels(images, batchSize);
        for(int i = 0; i < batchSize; i++){
            labelsMat->mat[0][i] = (double) labels[i];
        }
        l = calculateLoss(outputLayer, labelsMat);
        //printMatrix(outputLayer->outputs);
        //printf("\n loss = \n");
        //printMatrix(l);
        int prediction = getModelPrediction(outputLayer);
        //printf("\nPrediction = %d, actual = %d", prediction, (int) labelsMat->mat[0][0]);
        if(prediction == (int) labelsMat->mat[0][0]){
            accuracy++;
        }
        avgLoss += l->mat[0][0];

        struct Matrix *g  = backProp(outputLayer, labelsMat, learningRate, l);
        struct Matrix ***mpg = backpropMaxPool(poolLayer, g);
        struct Matrix ***clg = backpropConvLayer(layer, mpg, learningRate);

        freeMatrix(g);
        freeUnflattenedGradient(poolLayer, mpg);

        //printf("\n\n i = %d\n\n", i);

        if (i % 100 == 0){
            printf("\ni = %d", i);
            printf("\n\n ------ Past 100 Steps ------ \n\n");
            printf("\nAccuracy = %d%c\n", accuracy, '%');
            avgLoss = avgLoss / 100;
            printf("\nAverage Loss = %f\n", avgLoss);
            accuracy = 0;
            avgLoss = 0;
        }

        
        i++;
        //printf("\n %d", i);
        
    }
    printf("\n\n we outside the fucken loop \n\n");
    
    
    
    
    
    freeConvLayer(layer);
    freeConvLayerInputBatch(input, batchSize);
    freeLayer(outputLayer);
    freeMatrix(l);
    freeMatrix(labelsMat);

    freeMaxPoolLayer(poolLayer);
    


}