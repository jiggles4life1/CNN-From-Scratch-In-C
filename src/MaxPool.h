#include "Matrix.h"
#include "ConvLayer.h"
struct MaxPool{
    struct Matrix ***input;
    struct Matrix ***output;
    int inputSize;
    int numberOfMapsPerImage;
    int outputSize;
    int numberOfFilters;
    int poolSize;
    struct Matrix *flattenedOutput;
};



struct MaxPool *newMaxPool(struct ConvLayer *layer);

struct Matrix *maxPool(struct Matrix *m, int poolSize);

void pool(struct MaxPool *layer, int poolSize, struct Matrix ***input);


void freeUnflattenedGradient(struct MaxPool *layer, struct Matrix ***g);

struct Matrix ***unflattenGradient(struct MaxPool *layer, struct Matrix *gradient);

struct Matrix *getMaxPoolOutput(struct MaxPool *layer);

void flattenOutputMaxPool(struct MaxPool *layer);

struct Matrix ***backpropMaxPool(struct MaxPool *layer, struct Matrix *gradeint);

void freeMaxPoolLayer(struct MaxPool *layer);

void freeBackpropOutput(struct MaxPool *layer, struct Matrix *gradients);

//struct Matrix backPropMaxPool(struct ConvLayer *layer, struct Matrix *gradient);

