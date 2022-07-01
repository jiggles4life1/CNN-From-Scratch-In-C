#include "Layer.h"
#include "Matrix.h"
#include <stdlib.h>

struct Layer* newLayer(int numberOfInputs, int numberOfNuerons){
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

    return layer;

}


void forward(struct Layer *layer, struct Matrix *inputs){
    layer->outputs = muliplyMatrices(inputs, layer->weights);
    printMatrix(layer->outputs);
    addVectorToEachRow(layer->outputs, layer->biases);
    printMatrix(layer->outputs);
}