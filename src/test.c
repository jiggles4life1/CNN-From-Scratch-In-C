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
    double learningRate = 0.05;

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


    struct ConvLayer *layer = newConvLayer(8, 3, 1, input, batchSize, 1);

    //printf("\n\n printing conv layer\n\n");
    //printConvLayer(layer);

    forwardConvLayer(layer, input);
    poolOutput(layer, 2);
    //printConvLayerOutput(layer);
   
    flattenOutput(layer);

    //printMatrix(layer->output[0][0]);
    //printf("\n flattened width = %d", layer->output[0][0]->width);
    
    //since we normalize at start we dont need to here? 
    //secondLayer->output[0][0] = normalizeMatrix(secondLayer->output[0][0]);

    struct Layer *outputLayer = newLayer(getConvLayerOutput(layer)->width, 10, 1);
    forward(outputLayer, getConvLayerOutput(layer));


    //during the seconds pass we have to free the labels ptr before
    //using it again 
    short *labels = getRawLabels(images, batchSize);
    //same goes for labelsMat
    struct Matrix *labelsMat = newMatrix(1, batchSize);
    for(int i = 0; i < batchSize; i++){
        labelsMat->mat[0][i] = (double) labels[i];
    }
    
    //same goes for here during seconds pass
    struct Matrix *l = calculateLoss(outputLayer, labelsMat);
    


    
    //backProp(outputLayer, labelsMat, learningRate, l);

    printf("\n layer 2 weights \n");
    //printMatrix(outputLayer->weights);
    printf("\n layer 2 biases \n");
    //printMatrix(outputLayer->biases);
    printf("\n layer 2 output \n");
    printMatrix(outputLayer->outputs);



    printf("\n\n\n loss = ");
    printMatrix(l);


    freeMatrix(backProp(outputLayer, labelsMat, learningRate, l));
     //printf("\nback prop is crashing\n");

   /////////////////////////////////////////////////////
   
    
    //struct Matrix *input = flattenMatrix(normalizeImageTo255(convertImageToMatrix(&images[0])));
    /*
    struct Matrix *input = convertImageToMatrix(&images[0]);
    input = normalizeMatrix(input);
    input = flattenMatrix(input);
    struct Layer *fLayer = newLayer(input->width, 8, 0);
    forward(fLayer, input);
    struct Layer *outputLayer = newLayer(fLayer->numberOfNeurons, 10, 1);
    forward(outputLayer, fLayer->outputs);

    short *labels = getRawLabels(images, batchSize);
    struct Matrix *labelsMat = newMatrix(1, batchSize);
    for(int i = 0; i < batchSize; i++){
        labelsMat->mat[0][i] = (double) labels[i];
    }
    struct Matrix *l = calculateLoss(outputLayer, labelsMat);
    printf("\n\n\n loss = ");
    printMatrix(outputLayer->outputs);
    printMatrix(l);


    printf("\n layer 1 weights \n");
    printMatrix(fLayer->weights);
    printf("\n layer 1 biases \n");
    printMatrix(fLayer->biases);
    printf("\n layer 1 output \n");
    printMatrix(fLayer->outputs);

    printf("\n layer 2 weights \n");
    printMatrix(outputLayer->weights);
    printf("\n layer 2 biases \n");
    printMatrix(outputLayer->biases);
    printf("\n layer 2 output \n");
    printMatrix(outputLayer->outputs);
    

    //backProp(outputLayer, labelsMat, learningRate, l);

    int i = 0; 
    double lossOne = 0;
    double lossTwo = 0;
    double lossThree = 0;

    

    
    while (i < 500){
        images = getNImages(batchSize);
        for(int i = 0; i < batchSize; i++){
            //printImage(&images[i]);
        }

        struct Matrix *input = convertImageToMatrix(&images[0]);
        input = normalizeImageTo255(input);
        input = flattenMatrix(input);
        forward(fLayer, input);
        forward(outputLayer, fLayer->outputs);
        labels = getRawLabels(images, batchSize);
        struct Matrix *labelsMat = newMatrix(1, batchSize);
        for(int i = 0; i < batchSize; i++){
            labelsMat->mat[0][i] = (double) labels[i];
        }
        l = calculateLoss(outputLayer, labelsMat);
        //printf("\n\n\n loss = ");
        //printMatrix(outputLayer->outputs);
        //printMatrix(l);

        backProp(outputLayer, labelsMat, learningRate, l);

        //printf("\n\n iteration %d", i);
        lossOne += l->mat[0][0];
        i++;

        if(i % 100 == 0){
            printf("\n = loss avg = %f", lossOne / 100);
            lossOne = 0;
        }
        
    }

    */
    
    /*
    int i = 0;
    while(i < 2000){
        //printf("\n starting loop\n");
        free(images);
        //printf("\n images freed \n");
        images=getNImages(batchSize);
        printImage(&images[0]);
        freeConvLayerInputBatch(input, batchSize);
        //printf("\n conv layer batch input freed \n");
        input = convertImageBatchToConLayerFormat(images, batchSize);
        
        //struct Matrix *im = flattenMatrix(input[0][0]);
        
        forwardConvLayer(layer, input);

        poolOutput(layer, 2);

        forwardConvLayer(secondLayer, layer->output);

        poolOutput(secondLayer, 4);
        
        flattenOutput(secondLayer);

        //secondLayer->output[0][0] = normalizeMatrixByRow(secondLayer->output[0][0]);
        //printMatrix(getConvLayerOutput(secondLayer));
        forward(fLayer, getConvLayerOutput(secondLayer));

        forward(outputLayer, fLayer->outputs);

        //free the raw labels array
        free(labels);
        labels = getRawLabels(images, batchSize);
        for(int i = 0; i < batchSize; i++){
            labelsMat->mat[0][i] = (double) labels[i];
        }
        //free the loss matrix
        freeMatrix(l);

        l = calculateLoss(outputLayer, labelsMat);
        printMatrix(outputLayer->outputs);
        printf("\n loss = \n");
        printMatrix(l);
        backProp(outputLayer, labelsMat, learningRate, l);

        printf("\n\n i = %d\n\n", i);
        i++;
        

    }

    printMatrix(outputLayer->weights);
    printMatrix(outputLayer->biases);

    */
    int accuracy = 0;
    double avgLoss = 0.0;

    int i = 1;
    while (i < 500){
        free(images);
        images=getNImages(batchSize);
        //printImage(&images[0]);
        freeConvLayerInputBatch(input, batchSize);
        //printf("\n conv layer batch input freed \n");
        input = convertImageBatchToConLayerFormat(images, batchSize);

        forwardConvLayer(layer, input);
        poolOutput(layer, 2);
        flattenOutput(layer);
        forward(outputLayer, getConvLayerOutput(layer));

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


        backProp(outputLayer, labelsMat, learningRate, l);

        //printf("\n\n i = %d\n\n", i);

        if (i % 100 == 0){
            printf("\n\n ------ Past 100 Steps ------ \n\n");
            printf("\nAccuracy = %d%c\n", accuracy, '%');
            avgLoss = avgLoss / 100;
            printf("\nAverage Loss = %f\n", avgLoss);
            accuracy = 0;
            avgLoss = 0;
        }
        i++;


    }
    


}