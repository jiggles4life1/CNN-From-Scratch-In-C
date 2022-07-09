#include "ConvLayer.h"
#include <stdlib.h>
#include "Matrix.h"
#include <stdio.h>
#include <float.h>


struct ConvLayer *newConvLayer(int numberOfFilters, int filterSize, int stride){
    //get a new conv layer
    struct ConvLayer *layer = (struct ConvLayer*) malloc(sizeof(struct ConvLayer));
    layer->filterSize = filterSize;
    layer->stride = stride;
    layer->numberOfFilters = numberOfFilters;

    //initalize space for the matrix pointers
    layer->filters = (struct Matrix**) malloc(sizeof(struct Matrix*) * numberOfFilters);



    //initialize all of the filters (matrices)
    for(int i = 0; i < numberOfFilters; i++){
        layer->filters[i] = newMatrix(filterSize, filterSize);
        initMatrixValuesRandomlyBetweenOneAndOne(layer->filters[i]);    
    }
    return layer;


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

    return m;
}

struct Matrix *maxPool(struct Matrix *m, int poolSize){
    if(m->height % poolSize != 0){
        printf("\n\n\nERROR: incompatible pooling and matrix Height\n\n");
        return NULL;
    }

    if(m->width % poolSize != 0){
        printf("\n\n\nERROR: incompatible pooling and matrix Width\n\n");
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