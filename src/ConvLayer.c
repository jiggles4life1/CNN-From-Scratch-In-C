#include "ConvLayer.h"
#include <stdlib.h>
#include "Matrix.h"
#include <stdio.h>
#include <float.h>


struct ConvLayer *newConvLayer(int numberOfFilters, int filterSize, int stride, 
    struct Matrix ***images, int inputSize, int numberOfMapsPerImage, int poolSize){
    //get a new conv layer
    struct ConvLayer *layer = (struct ConvLayer*) malloc(sizeof(struct ConvLayer));
    layer->filterSize = filterSize;
    layer->stride = stride;
    layer->numberOfFilters = numberOfFilters;
    layer->numberOfMapsPerImage = numberOfMapsPerImage;
    //initalize space for the matrix pointers
    layer->filters = (struct Matrix**) malloc(sizeof(struct Matrix*) * numberOfFilters);

    layer->inputSize = inputSize;
    layer->input = images;
    //This is the output size per image. The batch size (input size) is constant
    layer->outputSize = (layer->numberOfMapsPerImage * layer->numberOfFilters);
    layer->output = (struct Matrix***) malloc(sizeof(struct Matrix*) * inputSize);

    //initialize a dumby matrix to free when flatten is called
    layer->flattenedOutput = newMatrix(1, 1);

    layer->poolSize = poolSize;

    




    //initialize all of the filters (matrices)
    for(int i = 0; i < numberOfFilters; i++){
        layer->filters[i] = newMatrix(filterSize, filterSize);
        initMatrixValuesRandomlyBetweenOneAndOne(layer->filters[i]); 
        struct Matrix *tmp = divideMatrixByValue(layer->filters[i], 9.0);
        freeMatrix(layer->filters[i]);
        layer->filters[i] = tmp;   
    }
    //it is input size becuase it is PER IMAGE
    //'input size' is the nubmer of maps the layer was given
    for(int i = 0; i < layer->inputSize; i++){
        layer->output[i] = (struct Matrix**) malloc(sizeof(struct Matrix*) * layer->outputSize);
        for(int j = 0; j < layer->outputSize; j++){
            //initialize them so errors aren't thrown when they are freed :)
            layer->output[i][j] = newMatrix(1, 1);
        }
    }


    return layer;


}

//I am not entirely sure why, but unlee the forward has been called on the layer
//freeing the layer will crash the program
//I assume this has to do with free uninitialized matrices but will look into later
void freeConvLayer(struct ConvLayer *layer){
    //free the filter matrices
    for(int i = 0; i < layer->numberOfFilters; i++){
        freeMatrix(layer->filters[i]);
    }
    free(layer->filters);

    //free the output matrices
    for(int i= 0; i < layer->inputSize; i++){
        //go through each output and free the matrix
        for(int j = 0; j < layer->outputSize; j++){
            freeMatrix(layer->output[i][j]);
        }
        free(layer->output[i]);
    }
    freeMatrix(layer->flattenedOutput);
    free(layer);

    //TODO free input?
}


void printConvLayer(struct ConvLayer *layer){
    printf("\nfilter size = %d\n", layer->filterSize);
    printf("\nnumberOfFilters = %d\n", layer->numberOfFilters);
    printf("\nstride = %d\n", layer->stride);
    printf("\nnumberOfMapsPerImage = %d\n", layer->numberOfMapsPerImage);
    printf("\noutput size = %d", layer->outputSize); 
    printf("\n\nFILTERS\n\n");
    printFilters(layer);

    printf("\n\nINPUTS\n\n");
    for(int i = 0; i < layer->inputSize; i++){
        for(int j = 0; j < layer->numberOfMapsPerImage; j++){
            printMatrix(layer->input[i][j]);
        }
    }
}


void printFilters(struct ConvLayer *layer){
    printf("\n\n");
    printf("Filter Size = %d", layer->filterSize);
    printf("\n\n");
    printf("Number Of Filters = %d", layer->numberOfFilters);
    printf("\n\n");
    printf("Stride = %d", layer->stride);
    printf("\n\n");
    for(int i = 0; i < layer->numberOfFilters; i++){
        printMatrix(layer->filters[i]);
        printf("\n\n");
    }
}


/*
    Equation for calculating the output size of the convolution matrix
    ((W-K+2P)/S)+1
    W = size of matrix (width and height must be equal)
    J = size of filter (kernel) (width and height must be equal)
    P = padding
    S = stride
*/
struct Matrix *convolution(struct Matrix *image, struct Matrix *filter, struct ConvLayer *layer){
    //we are using 0 padding for now so ignore it (for now)
    //also, the way we have set up the matrix struct, if there is padding
    //it will be included in the hiehght, so some redesign will be necessary.
    int size = ((image->height - layer->filterSize) / layer->stride) + 1;
    struct Matrix *m = newMatrix(size, size);

    for(int x = 0; x < m->height; x++){
        for(int y = 0; y < m->width; y++){

            //iterate through the kernel doing elemental multiplication
            float total = 0.0;
            for(int i = 0; i < filter->height; i++){
                for(int j = 0; j < filter->width; j++){
                    total += (image->mat[x+i][y+j] * filter->mat[i][j]);
                }
            }

            m->mat[x][y] = total;


        }
    }
    //printf("\n\n returnging from convolution \n\n");
    //printMatrix(m);
    return m;
}




void printConvLayerOutput(struct ConvLayer *layer){
    printf("\nCONV LAYER OUTPUT\n");
    printf("\nOUTPUT SIZE: %d", layer->outputSize);
    for(int image = 0; image < layer->inputSize; image++){
        for(int out = 0; out < layer->outputSize; out++){
            printf("\nWIDTH = %d", layer->output[image][out]->width);
            printf("\nHEIGHT = %d", layer->output[image][out]->height);
            printMatrix(layer->output[image][out]);
        }
    }
}

void forwardConvLayer(struct ConvLayer *layer, struct Matrix ***input){
    //Overview:
    //1: loop through each image:
    //2: at each image, loop through each activation map (1 means just plain image)
    //3  at each map, loop through each filter
    //4: populate the output array with each convoluted possibiliy
    //5: max pool if requested
    
    //int currentOutput = 0;

    //it is not the conv layers job to free the input of the time before if necessary
    //make sure that is done if the input is no longer needed. 
    layer->input = input;
    layer->outputSize = (layer->numberOfMapsPerImage * layer->numberOfFilters);

    for(int image = 0; image < layer->inputSize; image++){
        int currentOutput = 0;
        for(int map = 0; map < layer->numberOfMapsPerImage; map++){
            for(int filter = 0; filter < layer->numberOfFilters; filter++){

                struct Matrix *tmp = convolution(layer->input[image][map],
                    layer->filters[filter], layer);
                freeMatrix(layer->output[image][currentOutput]);
                layer->output[image][currentOutput] = tmp; 
                currentOutput++;

            }
        }
    }
    layer->prePoolHeight = layer->output[0][0]->height;
    layer->prePoolWidth = layer->output[0][0]->width;
}





struct Matrix *getConvLayerOutput(struct ConvLayer *layer){
    return layer->flattenedOutput;
}


struct Matrix backPropMaxPool(struct ConvLayer *layer, struct Matrix *gradient){
    int h = layer->output[0][0]->height;
    int w = layer->output[0][0]->width;
    int f = layer->numberOfFilters * layer->numberOfMapsPerImage;
    int batchSize = layer->inputSize;

    for(int image = 0; image < batchSize; image++){
        for(int map = 0; map < layer->outputSize; map++){

            for(int i = 0; i < h; i++){
                for(int j = 0; j < w; j++){
                    float max = -FLT_MAX;
                    int mi = -1;
                    int mj = -1;
                    for(int x = 0; x < layer->poolSize; x++){
                        for(int y = 0; y < layer->poolSize; y++){
                            if (layer->output[image][map]->mat[(i * layer->poolSize)+x][(j * layer->poolSize)+y] > max){
                                max =layer->output[image][map] ->mat[(i * layer->poolSize)+x][(j * layer->poolSize)+y];
                                mi = (i * layer->poolSize) + x;
                                mj = (j * layer->poolSize) + y;
                            }
                        }
                    }
                    //g[image][map]->mat[mi][mj] = 
                }
            }
        }
    }
}




