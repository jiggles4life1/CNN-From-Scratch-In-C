#include "ConvLayer.h"
#include <stdlib.h>
#include "Matrix.h"
#include <stdio.h>
#include <float.h>


struct ConvLayer *newConvLayer(int numberOfFilters, int filterSize, int stride, 
    struct Matrix ***images, int inputSize, int numberOfMapsPerImage){
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



    //initialize all of the filters (matrices)
    for(int i = 0; i < numberOfFilters; i++){
        layer->filters[i] = newMatrix(filterSize, filterSize);
        initMatrixValuesRandomlyBetweenOneAndOne(layer->filters[i]);    
    }
    for(int i = 0; i < layer->inputSize; i++){
        layer->output[i] = (struct Matrix**) malloc(sizeof(struct Matrix*) * layer->outputSize);
    }


    return layer;


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

struct Matrix *maxPool(struct Matrix *m, int poolSize){
    if(m->height % poolSize != 0){
        printf("\n\n\nERROR: incompatible pooling and matrix Height\n\n");
        printf("\n pool size = %d", poolSize);
        printf("\n Matrix height = %d", m->height);
        return NULL;
    }

    if(m->width % poolSize != 0){
        printf("\n\n\nERROR: incompatible pooling and matrix Width\n\n");
        printf("\n pool size = %d", poolSize);
        printf("\n Matrix width = %d", m->width);
        return NULL;
    }

    struct Matrix *newMat = newMatrix(m->height/poolSize, m->width/poolSize);

    for(int i = 0; i < newMat->height; i++){
        for(int j = 0; j < newMat->width; j++){
            float max = -FLT_MAX;
            for(int x = 0; x < poolSize; x++){
                for(int y = 0; y < poolSize; y++){
                    if (m->mat[(i * poolSize)+x][(j * poolSize)+y] > max){
                        max = m->mat[(i * poolSize)+x][(j * poolSize)+y];
                    }
                }
            }
            newMat->mat[i][j] = max;
        }
    }
    return newMat;
}


void forwardConvLayer(struct ConvLayer *layer){
    //Overview:
    //1: loop through each image:
    //2: at each image, loop through each activation map (1 means just plain image)
    //3  at each map, loop through each filter
    //4: populate the output array with each convoluted possibiliy
    //5: max pool if requested
    
    //int currentOutput = 0;
    for(int image = 0; image < layer->inputSize; image++){
        int currentOutput = 0;
        for(int map = 0; map < layer->numberOfMapsPerImage; map++){
            //TODO: foward the thing
            for(int filter = 0; filter < layer->numberOfFilters; filter++){
                //printf("\n\n inside loop\n\n");
                //printMatrix(layer->input[image][map]);
                layer->output[image][currentOutput] = convolution(layer->input[image][map],
                    layer->filters[filter], layer);
                //printMatrix(layer->output[image][currentOutput]);
                currentOutput++;
                //printf("\n post iteration\n");

            }
        }
    }
}

void flattenOutput(struct ConvLayer *layer){

    //image is the current image we are iterating over
    //loop through each image in the batch
    struct Matrix *finalOutput = newMatrix(1, 1);
    for(int image = 0; image < layer->inputSize; image++){
        //int width = layer->outputSize * layer->output[image][0]->height * layer->output[image][0]->width;
        struct Matrix *flattenedMatrix = newMatrix(1, 1);
        //int c = 0;
        for(int map = 0; map < layer->outputSize; map++){
            //printMatrix(layer->output[image][map]);
            struct Matrix *flatMap = flattenMatrix(layer->output[image][map]);

            //printf("width of flattened mat: %d", flattenedMatrix->width);

            flattenedMatrix = concatenateMatricesRowWise(flattenedMatrix, flatMap, 0);
            //c += (layer->output[image][map]->height * layer->output[image][map]->width);
        }
        finalOutput = concatenateMatricesColWise(finalOutput, flattenedMatrix);
        //layer->output[image][0] = flattenedMatrix;
    }
    layer->output[0][0] = finalOutput;
    layer->outputSize = 1;
}


void poolOutput(struct ConvLayer *layer, int poolSize){
    for(int image = 0; image < layer->inputSize; image++){
        for(int map = 0; map < layer->outputSize; map++){
            layer->output[image][map] = maxPool(layer->output[image][map], poolSize);
        }
    }
}

struct Matrix *getConvLayerOutput(struct ConvLayer *layer){
    return layer->output[0][0];
}