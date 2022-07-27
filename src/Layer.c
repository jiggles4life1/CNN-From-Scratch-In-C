#include "Layer.h"
#include "Matrix.h"
#include <stdlib.h>
#include "ActivationFunctions.h"

struct Layer* newLayer(int numberOfInputs, int numberOfNuerons, int isOutputLayer){
    struct Layer *layer = malloc(sizeof(struct Layer));

    //set the input pointer to the parameter inputs
    //layer->inputs = inputs;
    layer->numberOfNeurons = numberOfNuerons;
    //initalize weights randomly since this layer is NEW
    //REMEMBER: weights are stored row-major so that transposition isn't necessary
    layer->weights = newMatrix(numberOfInputs, numberOfNuerons);
    initMatrixValuesRandomlyBetweenOneAndOne(layer->weights);

    layer->biases = newMatrix(1, numberOfNuerons);
    initMatrixWithZeros(layer->biases);

    layer->isOutputLayer = isOutputLayer;

    return layer;

}


void forward(struct Layer *layer, struct Matrix *inputs){
    printf("\n\n\n\n starting forward \n\n\n\n");
    layer->outputs = muliplyMatrices(inputs, layer->weights);
    printMatrix(layer->outputs);
    addVectorToEachRow(layer->outputs, layer->biases);
    printMatrix(layer->outputs);
    callActivationFunction(layer);
    printMatrix(layer->outputs);
}

void activateEachNeuronReLU(struct Layer *layer){
    for(int i = 0; i < layer->outputs->height; i++){
        for(int j = 0; j < layer->outputs->width; j++){
            layer->outputs->mat[i][j] = ReLU(layer->outputs->mat[i][j]);
        }
    }
}

void outputLayerSoftmaxActivation(struct Layer *layer){
    printf("\n\n\n\nSTARTING ACTIVATION SOFTMAX\n\n\n\n");

    printMatrix(layer->outputs);

    layer->outputs = subtractByMaxRowWise(layer->outputs);
    printMatrix(layer->outputs);
    layer->outputs = exponentiateMatrix(layer->outputs);
    printMatrix(layer->outputs);
    layer->outputs = normalizeMatrixByRow(layer->outputs);
    printMatrix(layer->outputs);
}



void callActivationFunction(struct Layer *layer){
    //If it is the output layer
    if(layer->isOutputLayer){
        outputLayerSoftmaxActivation(layer);
    }
    //if it's not the output layer use ReLU()
    else{
        activateEachNeuronReLU(layer);
    }

}