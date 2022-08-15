#include "Layer.h"
#include "Matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include "ActivationFunctions.h"

struct Layer* newLayer(int numberOfInputs, int numberOfNuerons, int isOutputLayer){
    struct Layer *layer = malloc(sizeof(struct Layer));

    //set the input pointer to the parameter inputs
    //layer->inputs = inputs;
    layer->numberOfNeurons = numberOfNuerons;
    //initalize weights randomly since this layer is NEW
    //REMEMBER: weights are stored row-major so that transposition isn't necessary
    layer->weights = newMatrix(numberOfInputs, numberOfNuerons);

    initMatrixValuesRandomlyBetweenZeroAndOne(layer->weights);

    struct Matrix *tmp = divideMatrixByValue(layer->weights, 1000);
    freeMatrix(layer->weights);
    layer->weights = tmp;



    layer->biases = newMatrix(1, numberOfNuerons);
    initMatrixWithZeros(layer->biases);

    layer->isOutputLayer = isOutputLayer;
    layer->hasBeenForwarded = 0;

    return layer;

}


void forward(struct Layer *layer, struct Matrix *inputs){
    //store inputs for back propogation later
    if(layer->hasBeenForwarded){
        //printMatrix(layer->inputs); 
        free(layer->outputs);
        
    }
    layer->inputs = inputs;

    
    layer->outputs = muliplyMatrices(inputs, layer->weights);

    //printf("\n\n output after weights * inputs\n\n");
    //printf("\n inputs width: %d", inputs->width);
    //printf("\n inputs height: %d", inputs->height);
    //printf("\n weights width: %d", layer->weights->width);
    //printf("\n Weghts height: %d", layer->weights->height);
    //printMatrix(layer->outputs);
    addVectorToEachRow(layer->outputs, layer->biases);
    //layer->totals = copyMatrix(layer->outputs);
    callActivationFunction(layer);
    //printf("\n matrix after activation function\n");
    layer->hasBeenForwarded = 1;
}

void activateEachNeuronReLU(struct Layer *layer){
    for(int i = 0; i < layer->outputs->height; i++){
        for(int j = 0; j < layer->outputs->width; j++){
            layer->outputs->mat[i][j] = ReLU(layer->outputs->mat[i][j]);
        }
    }
}

void outputLayerSoftmaxActivation(struct Layer *layer){
    struct Matrix *tmp = subtractByMaxRowWise(layer->outputs);
    freeMatrix(layer->outputs);
    layer->outputs = tmp;
    if(layer->hasBeenForwarded){
        freeMatrix(layer->totals);
    }
    layer->totals = copyMatrix(layer->outputs);

    tmp = exponentiateMatrix(layer->outputs);
    free(layer->outputs);
    layer->outputs = tmp;
    tmp = normalizeMatrixByRow(layer->outputs);
    free(layer->outputs);
    layer->outputs = tmp;
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


struct Matrix *calculateLoss(struct Layer *layer, struct Matrix *labels){
    //first we need to clip the output
    //we clip them by 1e-7
    double min = 0.0000001;

    layer->outputs = clipMatrixValues(layer->outputs, min, 1-min);

    int batchSize = labels->width;

    struct Matrix *m = newMatrix(1, batchSize);

    for(int i = 0; i < batchSize; i++){

        double l = loss(layer->outputs, i, (short) labels->mat[0][i]);
        m->mat[0][i] = l;


    }

    return m;
}



struct Matrix *getSoftmaxGradient(struct Layer *layer, struct Matrix *labels,
                                  struct Matrix *loss, double learningRate){
    //width of 10 becuase there are 10 classes for our dataset
    //layer->outputs->height will just be the batch size
    //struct Matrix *g = newMatrix(layer->outputs->height, layer->outputs->width);
    //initMatrixWithZeros(g);

    //d_out_d_t
    /*struct Matrix *dt = newMatrix(layer->outputs->height, layer->outputs->width);
    struct Matrix *dldt = newMatrix(dt->height, dt->width);


    struct Matrix *dw = copyMatrix(layer->inputs);
    struct Matrix *db = copyMatrix(layer->biases);
    struct Matrix *di = copyMatrix(layer->weights);

    struct Matrix *dldw = newMatrix(layer->weights->height, layer->weights->width);
    struct Matrix *dldb = newMatrix(dldt->height, dldt->width);
    struct Matrix *dldi = newMatrix(layer->inputs->height, layer->outputs->width);


    struct Matrix *totals = copyMatrix(layer->totals);
    totals = exponentiateMatrix (totals);
    */
    
    int batchSize = labels->width;

    struct Matrix *gradient = newMatrix(batchSize, layer->outputs->width);
    initMatrixWithZeros(gradient);
    
    //
    for(int i = 0; i < batchSize; i++){
        //write the calc for derivative of loss for each thingy TODO = <--------
        //REMEMBER: the derivative of ln(x) = 1/x
        gradient->mat[i][(int) labels->mat[0][i]] = -1 / layer->outputs->mat[i][(int) labels->mat[0][i]]; 

    }

    
    struct Matrix *totalsExponential = exponentiateMatrix(layer->totals);
    double s = sum(totalsExponential);
    struct Matrix *dOutdt = newMatrix(totalsExponential->height, totalsExponential->width);
    int label = (int) labels->mat[0][0];


    //CURRENTLY HARDCODED FOR BATCH SIZE OF 1
    for (int j = 0; j < dOutdt->width; j++){
        dOutdt->mat[0][j] = (-totalsExponential->mat[0][label] * totalsExponential->mat[0][j]) / (s * s);
    }
    //no we calculate dOutdt for the correct class
    dOutdt->mat[0][label] = totalsExponential->mat[0][label] * ((s - totalsExponential->mat[0][label])) / (s * s);

    struct Matrix *dtdw = layer->inputs;
    double dtdb = 1;
    struct Matrix *dtdi = layer->weights;

    struct Matrix *dldt = multiplyByValue(dOutdt, gradient->mat[0][label]);


    struct Matrix *dldw = muliplyMatrices(transposeMatrix(dtdw), dldt);

    struct Matrix *dldb = multiplyByValue(dldt, dtdb);

    struct Matrix *dldi = muliplyMatrices(dtdi, transposeMatrix(dldt));



    struct Matrix *tmp;
    //printMatrix(dldw);
    tmp = multiplyByValue(dldw, learningRate);
    freeMatrix(dldw);
    dldw = tmp;

    tmp = elementWiseSubtraction(layer->weights, dldw);
    freeMatrix(layer->weights);
    layer->weights = tmp;
    
    tmp = multiplyByValue(dldb, learningRate);
    freeMatrix(dldb);
    dldb = tmp;
    
    tmp = elementWiseSubtraction(layer->biases, dldb);
    freeMatrix(layer->biases);
    layer->biases = tmp;


    //freeMatrix(dtdi);
    freeMatrix(dldt);
    //freeMatrix(dldw);
    freeMatrix(dldb);
    freeMatrix(gradient);
    freeMatrix(totalsExponential);
    freeMatrix(dOutdt);
    return dldi;



    //printf("\n\n gradient:: \n\n");
    //printMatrix(gradient);
    //for(int i = 0; i <)
    
    /*for(int i = 0; i < labels->width; i++){

        
        int label = (int) labels->mat[0][i];

        //get the sum of the layers input for this image
        double s = 0;
        for(int k = 0; k < totals->width; k++){
            s += totals->mat[i][k];
        }


        for(int k = 0; k < totals->width; k++){
            if(k != label){
                dt->mat[i][k] = (-totals->mat[i][label] * totals->mat[i][k]) / (s * s);
            }
            else{
                dt->mat[i][k] = ((totals->mat[i][k]) * (s - totals->mat[i][k])) / (s * s);
            }
        }


        //gradient = -1 / out_{i}
        //i guess???
        //also remember that every other value except for the correct class' spot
        //is going to be 0, thus why we can just calculate the gradient for g[i][label]
        g->mat[i][label] = -1 / (layer->outputs->mat[i][label]);

        //this is the gradients of loss against totals
        //for(int i = 0; i < dt->height; i++){
            for(int j = 0; j < dt->width; j++){
                dldt->mat[i][j] = dt->mat[i][j] * g->mat[i][label];
            }
        //}


        //now we calculate weights gradient, biases gradient

        //I believe dt is the input gradient.


    }
    */

    /*dw = transposeMatrix(dw);

    dldw = muliplyMatrices(dw, dldt);


    dldb = copyMatrix(dldt);

    //di = transposeMatrix(di);
    dldt = transposeMatrix(dldt);



    dldi = muliplyMatrices(di, dldt);





    dldw = multiplyByValue(dldw, learningRate);
    dldb = multiplyByValue(dldb, learningRate);



    layer->weights = elementWiseSubtraction(layer->weights, dldw);
    layer->biases = elementWiseSubtraction(layer->biases, dldb);

    */

    //printf("\n new weights \n");
    //printMatrix(layer->weights);
    //printf("\n new biases \n");
    //printMatrix(layer->biases);





    //return gradient;

}


struct Matrix *backProp(struct Layer *layer, struct Matrix *labels, double learningRate, struct Matrix *loss){
    //if the layer is the output layer then we have to get the initial input to the backprop phase.
    if(layer->isOutputLayer){
        struct Matrix *g = getSoftmaxGradient(layer, labels, loss, learningRate);
        //printMatrix(g);
        return g;
    }
    else{
        return NULL;
    }

}

int getModelPrediction(struct Layer *layer){
    if(!layer->isOutputLayer){
        printf("ERROR: LAYER IS NOT OUTPUT LAYER! in getModelPrediction, Layer.c");
        return -1;
    }

    double max = -FLT_MAX;
    int maxAt = 0;

    //we are looking for the index of the largest number
    for(int i = 0; i < layer->outputs->width; i++){
        if(layer->outputs->mat[0][i] > max){
            max = layer->outputs->mat[0][i];
            maxAt = i;
        }
    }

    return maxAt;
}