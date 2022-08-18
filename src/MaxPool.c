#include <stdlib.h>
#include <stdio.h>
#include "MaxPool.h"
#include "Matrix.h"
#include <float.h>
#include "ConvLayer.h"

struct MaxPool *newMaxPool(struct ConvLayer *layer){
    struct MaxPool *pool = (struct MaxPool*) malloc(sizeof(struct MaxPool));
    pool->inputSize = layer->inputSize;
    pool->outputSize = layer->outputSize;
    pool->numberOfMapsPerImage  = layer->numberOfMapsPerImage;
    pool->numberOfFilters = layer->numberOfFilters;

    pool->output = (struct Matrix***) malloc(sizeof(struct Matrix*) * pool->inputSize);
    for(int i = 0; i < layer->inputSize; i++){
        pool->output[i] = (struct Matrix**) malloc(sizeof(struct Matrix*) * layer->outputSize);
        for(int j = 0; j < layer->outputSize; j++){
            //initialize them so errors aren't thrown when they are freed :)
            pool->output[i][j] = newMatrix(1, 1);
        }
    }

    pool->flattenedOutput = newMatrix(1, 1);

    return pool;
}




void freeUnflattenedGradient(struct MaxPool *layer, struct Matrix ***g){
    for(int i = 0; i < layer->inputSize; i++){
        for(int j = 0; j < layer->outputSize; j++){
            //initialize them so errors aren't thrown when they are freed :)
            freeMatrix(g[i][j]);
        }
        free(g[i]);

    }
    free(g);
}

//unflattens the gradient COL-WISE
struct Matrix ***unflattenGradient(struct MaxPool *layer, struct Matrix *gradient){
    int h = layer->output[0][0]->height;
    int w = layer->output[0][0]->width;
    int f = layer->numberOfFilters * layer->numberOfMapsPerImage;
    //the images are stored col-wise on the gradient, so there is 1 widht per image
    int batchSize = gradient->width;

    struct Matrix ***g = (struct Matrix***) malloc(sizeof(struct Matrix*) * batchSize);

    for(int i = 0; i < layer->inputSize; i++){
        g[i] = (struct Matrix**) malloc(sizeof(struct Matrix*) * layer->outputSize);
        for(int j = 0; j < layer->outputSize; j++){
            //initialize them so errors aren't thrown when they are freed :)
            g[i][j] = newMatrix(h, w);
        }
    }

    for(int image = 0; image < batchSize; image++){
        for(int map = 0; map < layer->outputSize; map++){
            for(int i = 0; i < g[image][map]->height; i++){
                for(int j = 0; j < g[image][map]->width; j++){
                    g[image][map]->mat[i][j] = gradient->mat[(map * g[image][map]->height * g[image][map]->width) + i * g[image][map]->height + j][image];
                    
                }
            }
            //printMatrix(g[image][map]);
        }
    }

    return g;


}

void pool(struct MaxPool *layer, int poolSize, struct Matrix ***input){
    layer->input = input;
    //printMatrix(layer->input[0][0]);
    layer->poolSize = poolSize;
    for(int image = 0; image < layer->inputSize; image++){
        for(int map = 0; map < layer->outputSize; map++){
            //printMatrix(layer->input[image][map]);
            struct Matrix *tmp = maxPool(layer->input[image][map], poolSize);
            freeMatrix(layer->output[image][map]);
            layer->output[image][map] = tmp;
        }
    }
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

struct Matrix *getMaxPoolOutput(struct MaxPool *layer){
    return layer->flattenedOutput;
}


void flattenOutputMaxPool(struct MaxPool *layer){
    struct Matrix *finalOutput = newMatrix(1, 1);
    for(int image = 0; image < layer->inputSize; image++){
        struct Matrix *flattenedMatrix = newMatrix(1, 1);
        struct Matrix *flatMap = newMatrix(1, 1);
        for(int map = 0; map < layer->outputSize; map++){
            freeMatrix(flatMap);
            flatMap = flattenMatrix(layer->output[image][map]);

            struct Matrix *tmp = concatenateMatricesRowWise(flattenedMatrix, flatMap, 0);
            freeMatrix(flattenedMatrix);
            flattenedMatrix = tmp;
            //flattenedMatrix = concatenateMatricesRowWise(flattenedMatrix, flatMap, 0);

        }
        struct Matrix *tmp = concatenateMatricesColWise(finalOutput, flattenedMatrix);
        freeMatrix(finalOutput);
        finalOutput = tmp;
        freeMatrix(flatMap);
        freeMatrix(flattenedMatrix);
        //layer->output[image][0] = flattenedMatrix;
    }
    freeMatrix(layer->flattenedOutput);
    layer->flattenedOutput = finalOutput;    
}

struct Matrix ***backpropMaxPool(struct MaxPool *layer, struct Matrix *gradeint){
    struct Matrix ***g = unflattenGradient(layer, gradeint);
    struct Matrix ***bg = malloc(sizeof(struct Matrix*) * layer->inputSize);
    
    for(int i = 0; i < layer->inputSize; i++){
        bg[i] = (struct Matrix**) malloc(sizeof(struct Matrix*) * layer->outputSize);
        for(int j = 0; j < layer->outputSize; j++){
            //initialize them so errors aren't thrown when they are freed :)
            bg[i][j] = newMatrix(layer->input[0][0]->height, layer->input[0][0]->width);
            initMatrixWithZeros(bg[i][j]);


        }
    }
    int cur = 0;
    for(int image = 0; image < layer->inputSize; image++){
        for(int map = 0; map < layer->outputSize; map++){
            for(int i = 0; i < layer->output[image][map]->height; i++){
                for(int j = 0; j < layer->output[image][map]->width; j++){
                    float max = -FLT_MAX;
                    int mj = -1;
                    int mi = -1;
                    for(int x = 0; x < layer->poolSize; x++){
                        for(int y = 0; y < layer->poolSize; y++){
                            if (layer->input[image][map]->mat[(i * layer->poolSize)+x][(j * layer->poolSize)+y] > max){
                                max = layer->input[image][map]->mat[(i * layer->poolSize)+x][(j * layer->poolSize)+y];
                                mi = (i * layer->poolSize) + x;
                                mj = (j * layer->poolSize) + y;
                            }
                        }
                    }
                    printf("\n\n pre assignemnt \n\n");
                    printf("\n mj = %d\n", mj);
                    printf("\n mi = %d\n", mi);
                    //bg[image][map]->mat[mi][mj] = g[image][map]->mat[mi][mj];
                    bg[image][map]->mat[mi][mj] = gradeint->mat[cur][0];
                    cur++;
                }
            }
        }
    }
    return bg;




}
